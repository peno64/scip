/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2013 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   reopt.c
 * @brief  methods for collecting reoptimization information
 * @author Jakob Witzig
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/
//#define SCIP_DEBUG
#include <assert.h>

#include "scip/def.h"
#include "scip/scip.h"
#include "scip/set.h"
#include "scip/sol.h"
#include "scip/misc.h"
#include "scip/reopt.h"
#include "scip/prob.h"


/*
 * memory growing methods for dynamically allocated arrays
 */

/** ensures, that sols[pos] array can store at least num entries */
static
SCIP_RETCODE ensureSolsSize(
   SCIP_REOPT*           reopt,             /**< primal data */
   SCIP_SET*             set,               /**< global SCIP settings */
   int                   num,               /**< minimum number of entries to store */
   int                   run                /**< run for which the memory should checked */
)
{
   assert(run >= 0);
   assert(run <= reopt->runsize);

   if( num > reopt->solssize[run] )
   {
      int newsize;

      newsize = num;
      SCIP_ALLOC( BMSreallocMemoryArray(&reopt->sols[run], newsize) );
      reopt->solssize[run] = newsize;
   }
   assert(num <= reopt->solssize[run]);

   return SCIP_OKAY;
}

/** ensures, that sols array can store at least num entries */
static
SCIP_RETCODE ensureRunSize(
   SCIP_REOPT*           reopt,             /**< primal data */
   SCIP_SET*             set,                /**< global SCIP settings */
   int                   num                 /**< minimum number of entries to store */
)
{
   if( num >= reopt->runsize )
   {
      int newsize;
      int s;

      newsize = 2*reopt->runsize;
      SCIP_ALLOC( BMSreallocMemoryArray(&reopt->sols, newsize) );
      SCIP_ALLOC( BMSreallocMemoryArray(&reopt->nsols, newsize) );
      SCIP_ALLOC( BMSreallocMemoryArray(&reopt->solssize, newsize) );
      SCIP_ALLOC( BMSreallocMemoryArray(&reopt->solsused, newsize) );
      SCIP_ALLOC( BMSreallocMemoryArray(&reopt->objs, newsize) );

      for(s = reopt->runsize; s < newsize; s++)
      {
         reopt->sols[s] = NULL;
         reopt->objs[s] = NULL;
         reopt->nsols[s] = 0;
         reopt->solssize[s] = 0;
         reopt->solsused[s] = FALSE;
      }

      reopt->runsize = newsize;
   }
   assert(num <= reopt->runsize);

   return SCIP_OKAY;
}

/*
 * local methods
 */

/* add solutions to origprimal space */
static
SCIP_RETCODE addSols(
   SCIP_REOPT*           reopt,
   SCIP_PRIMAL*          primal,
   BMS_BLKMEM*           probmem,
   SCIP_SET*             set,
   SCIP_MESSAGEHDLR*     messagehdlr,
   SCIP_STAT*            stat,
   SCIP_PROB*            origprob,
   SCIP_PROB*            transprob,
   SCIP_TREE*            tree,
   SCIP_LP*              lp,
   SCIP_EVENTQUEUE*      eventqueue,
   SCIP_EVENTFILTER*     eventfilter,
   int                   run,
   int*                  naddedsols
)
{
   int s;

   (*naddedsols) = 0;

   for(s = reopt->nsols[run]-1; s >= 0; s--)
   {
      SCIP_SOL* sol;
      SCIP_Real solobj;

      sol = reopt->sols[run][s]->sol;

      SCIPsolRecomputeObj(sol, set, stat, origprob);

      solobj = SCIPsolGetObj(sol, set, transprob);

      /* we do not want to add solutions with objective value +infinity */
      if( !SCIPisInfinity(set->scip, solobj) && !SCIPisInfinity(set->scip, -solobj) )
      {
         SCIP_SOL* bestsol = SCIPgetBestSol(set->scip);
         SCIP_Bool stored;

         /* add primal solution to solution storage by copying it */
         SCIP_CALL( SCIPprimalAddSol(primal, probmem, set, messagehdlr, stat, origprob, transprob,
               tree, lp, eventqueue, eventfilter, sol, &stored) );

         if( stored )
         {
            if( bestsol != SCIPgetBestSol(set->scip) )
               SCIPstoreSolutionGap(set->scip);
         }
      }
   }
   reopt->solsused[run] = TRUE;

   (*naddedsols) = reopt->nsols[run];

   return SCIP_OKAY;
}

/* returns similariry of two objective functions */
static
SCIP_Real reoptSimilarity(
   SCIP*                 scip,
   SCIP_REOPT*           reopt,
   int                   obj1_id,
   int                   obj2_id
)
{
   SCIP_Real sim;
   int id;
   int scale;

   /* calc similarity */
   scale = 0;
   sim = 0.0;
   for(id = 0; id < SCIPgetNVars(scip); id++)
   {
      if(reopt->objs[obj1_id][id] != 0 || reopt->objs[obj2_id][id] != 0)
      {
         SCIP_Real c1;
         SCIP_Real c2;

         c1 = reopt->objs[obj1_id][id];
         c2 = reopt->objs[obj2_id][id];

         sim += MAX(0, MIN(c1/c2, c2/c1) );

         scale++;
      }
   }

   return sim/scale;
}

static
SCIP_RETCODE createSolTree(
   SCIP_REOPT*           reopt
)
{
   assert(reopt != NULL);

   SCIP_ALLOC( BMSallocMemory(&reopt->soltree) );
   reopt->soltree->nsols = 0;

   SCIP_ALLOC( BMSallocMemory(&reopt->soltree->root) );
   reopt->soltree->root->father = NULL;
   reopt->soltree->root->rchild = NULL;
   reopt->soltree->root->lchild = NULL;

   return SCIP_OKAY;
}

static
SCIP_RETCODE soltreefreeNode(
   SCIP*                 scip,
   SCIP_REOPT*           reopt,
   SCIP_SOLNODE*         node
)
{
   assert(reopt != NULL);
   assert(node != NULL);

   /* free recursive right subtree */
   if( node->rchild != NULL )
   {
      SCIP_CALL( soltreefreeNode(scip, reopt, node->rchild) );
   }

   /* free recursive left subtree */
   if( node->lchild != NULL )
   {
      SCIP_CALL( soltreefreeNode(scip, reopt, node->lchild) );
   }

   if( node->sol != NULL )
   {
      SCIP_CALL( SCIPfreeSol(scip, &node->sol) );
   }

   /* free this nodes */
   BMSfreeMemoryNull(&node);

   return SCIP_OKAY;
}

static
SCIP_RETCODE freeSolTree(
   SCIP*                 scip,
   SCIP_REOPT*           reopt
)
{
   assert(reopt != NULL);
   assert(reopt->soltree != NULL);
   assert(reopt->soltree->root != NULL);

   SCIP_CALL( soltreefreeNode(scip, reopt, reopt->soltree->root) );

   BMSfreeMemory(&reopt->soltree);

   return SCIP_OKAY;
}

static
SCIP_RETCODE soltreeAddNode(
   SCIP_REOPT*           reopt,
   SCIP_SOLNODE*         father,
   SCIP_Bool             rchild,
   SCIP_Bool             lchild,
   SCIP_Real             val
)
{
   SCIP_SOLNODE* newnode;

   assert(reopt != NULL);
   assert(father != NULL);
   assert(rchild == !lchild);
   assert((rchild && father->rchild == NULL) || (lchild && father->lchild == NULL));

   SCIP_ALLOC( BMSallocMemory(&newnode) );
   newnode->sol = NULL;
   newnode->father = father;
   newnode->rchild = NULL;
   newnode->lchild = NULL;
   newnode->val = val;

   if( rchild )
      father->rchild = newnode;
   else
      father->lchild = newnode;

   return SCIP_OKAY;
}

static
SCIP_RETCODE soltreeAddSol(
   SCIP*                 scip,
   SCIP_REOPT*           reopt,
   SCIP_SET*             set,
   SCIP_STAT*            stat,
   SCIP_VAR**            vars,
   SCIP_SOL*             sol,
   SCIP_SOLNODE**        solnode,
   int                   nvars,
   SCIP_Bool*            added
)
{
   SCIP_SOLNODE* cursolnode;
   int* varidlist;
   int varid;
   int orderid;

   assert(reopt != NULL);
   assert(sol != NULL);

   cursolnode = reopt->soltree->root;
   (*added) = FALSE;

   for(orderid = 0; orderid < nvars; orderid++)
   {
      const char* varname;
      SCIP_Real objval;

      varid = orderid;
      varname = SCIPvarGetName(vars[varid]);

      assert(SCIPvarGetType(vars[varid]) == SCIP_VARTYPE_BINARY);

      objval = SCIPsolGetVal(sol, set, stat, vars[varid]);
      if( SCIPsetIsFeasEQ(set, objval, 0) )
      {
         if( cursolnode->rchild == NULL )
         {
            SCIP_CALL( soltreeAddNode(reopt, cursolnode, TRUE, FALSE, objval) );
            assert(cursolnode->rchild != NULL);
            (*added) = TRUE;
         }
         cursolnode = cursolnode->rchild;
      }
      else
      {
         assert(SCIPsetIsFeasEQ(set, objval, 1));
         if( cursolnode->lchild == NULL )
         {
            SCIP_CALL( soltreeAddNode(reopt, cursolnode, FALSE, TRUE, objval) );
            assert(cursolnode->lchild != NULL);
            (*added) = TRUE;
         }
         cursolnode = cursolnode->lchild;
      }
   }

   if( (*added) )
   {
      SCIP_SOL* copysol;
      SCIP_CALL( SCIPcreateSolCopy(scip, &copysol, sol) );

      cursolnode->sol = copysol;
      (*solnode) = cursolnode;
   }

#ifdef SCIP_DEBUG
   {
      printf(">> %s\n", (*added) ? "add sol" : "skip sol");
   }
#endif

   return SCIP_OKAY;
}

/*
 * public methods
 */

/** creates reopt data */
SCIP_RETCODE SCIPreoptCreate(
   SCIP_REOPT**          reopt                   /**< pointer to reopt data */
)
{
   int s;

   assert(reopt != NULL);

   SCIP_ALLOC( BMSallocMemory(reopt) );
   (*reopt)->sols = NULL;
   (*reopt)->nsols = NULL;
   (*reopt)->solssize = NULL;
   (*reopt)->solsused = NULL;
   (*reopt)->varnamehash = NULL;
   (*reopt)->runsize = 200;
   (*reopt)->run = -1;

   SCIP_ALLOC( BMSallocMemoryArray(&(*reopt)->sols, (*reopt)->runsize) );
   SCIP_ALLOC( BMSallocMemoryArray(&(*reopt)->nsols, (*reopt)->runsize) );
   SCIP_ALLOC( BMSallocMemoryArray(&(*reopt)->solssize, (*reopt)->runsize) );
   SCIP_ALLOC( BMSallocMemoryArray(&(*reopt)->solsused, (*reopt)->runsize) );
   SCIP_ALLOC( BMSallocMemoryArray(&(*reopt)->objs, (*reopt)->runsize) );

   for(s = 0; s < (*reopt)->runsize; s++)
   {
      (*reopt)->nsols[s] = 0;
      (*reopt)->solssize[s] = 0;
      (*reopt)->solsused[s] = FALSE;
      (*reopt)->sols[s] = NULL;
      (*reopt)->objs[s] = NULL;
   }

   /* create SCIP_SOLTREE */
   SCIP_CALL( createSolTree((*reopt)) );

   return SCIP_OKAY;
}

/** frees reopt data */
SCIP_RETCODE SCIPreoptFree(
   SCIP*                 scip,
   SCIP_REOPT**          reopt,              /**< pointer to primal data */
   BMS_BLKMEM*           blkmem              /**< block memory */
   )
{
   int s;
   int p;

   assert(reopt != NULL);
   assert(*reopt != NULL);

   /* free solution tree */
   SCIP_CALL( freeSolTree(scip, (*reopt)) );

   /* free solutions */
   for( p = (*reopt)->runsize-1; p >= 0; --p )
   {
      if( (*reopt)->sols[p] != NULL )
      {
         BMSfreeMemoryArrayNull(&(*reopt)->sols[p]);
      }

      if( (*reopt)->objs[p] != NULL )
      {
         BMSfreeMemoryArrayNull(&(*reopt)->objs[p]);
      }
   }

   BMSfreeMemoryArrayNull(&(*reopt)->sols);
   BMSfreeMemoryArrayNull(&(*reopt)->nsols);
   BMSfreeMemoryArrayNull(&(*reopt)->solssize);
   BMSfreeMemoryArrayNull(&(*reopt)->solsused);
   BMSfreeMemoryArrayNull(&(*reopt)->objs);
   BMSfreeMemory(reopt);

   return SCIP_OKAY;
}

/** add a solution to the last run */
SCIP_RETCODE SCIPreoptAddSol(
   SCIP*                 scip,
   SCIP_REOPT*           reopt,
   SCIP_SET*             set,
   SCIP_STAT*            stat,
   SCIP_SOL*             sol,
   SCIP_Bool*            added,
   int                   run
)
{
   SCIP_SOLNODE* solnode;
   int num;
   int insertpos;

   assert(reopt != NULL);
   assert(set != NULL);
   assert(sol != NULL);
   assert(run >= 0);

   assert(reopt->sols[run] != NULL);

   if( set->reopt_savesols == -1 )
      num = reopt->nsols[run]+1;
   else
      num = set->reopt_savesols;

   /* check memory */
   SCIP_CALL( ensureSolsSize(reopt, set, num, run) );

   /** ad solution to solution tree */
   SCIP_CALL( soltreeAddSol(scip, reopt, set, stat, SCIPgetVars(scip), sol, &solnode, SCIPgetNVars(scip), added) );

   if( (*added) )
   {
      assert(solnode != NULL);

      /** add solution */
      insertpos = reopt->nsols[run];
      reopt->sols[run][insertpos] = solnode;
      reopt->nsols[run]++;
      assert(set->reopt_savesols == -1 || reopt->nsols[run] <= set->reopt_savesols);
   }

   return SCIP_OKAY;
}

/* add a run */
SCIP_RETCODE SCIPreoptAddRun(
   SCIP_SET*             set,
   SCIP_REOPT*           reopt,
   int                   run,
   int                   size
)
{
   assert(reopt != NULL);

   /* check memory */
   SCIP_CALL( ensureRunSize(reopt, set, run) );

   /* set number of last run */
   reopt->run = run;

   /* allocate memory */
   reopt->solssize[run] = size;
   SCIP_ALLOC( BMSallocMemoryArray(&reopt->sols[run], size) );

   return SCIP_OKAY;
}

/* returns number of solution */
int SCIPreoptGetNSols(
   SCIP_REOPT*           reopt,
   int                   run
)
{
   assert(reopt != NULL);
   assert(run <= reopt->runsize);

   if( reopt->sols[run] == NULL )
      return 0;
   else
      return reopt->nsols[run];
}

/* add solutions to origprimal space */
SCIP_RETCODE SCIPreoptUpdateSols(
   SCIP*                 scip,
   SCIP_REOPT*           reopt,
   SCIP_PRIMAL*          primal,
   BMS_BLKMEM*           probmem,
   SCIP_SET*             set,
   SCIP_MESSAGEHDLR*     messagehdlr,
   SCIP_STAT*            stat,
   SCIP_PROB*            origprob,
   SCIP_PROB*            transprob,
   SCIP_TREE*            tree,
   SCIP_LP*              lp,
   SCIP_EVENTQUEUE*      eventqueue,
   SCIP_EVENTFILTER*     eventfilter,
   SCIP_Real             simparam
)
{
   int naddedsols;
   int run;

   assert(reopt != NULL);
   assert(primal != NULL);
   assert(probmem != NULL);
   assert(set != NULL);
   assert(messagehdlr != NULL);
   assert(stat != NULL);
   assert(origprob != NULL);
   assert(transprob != NULL);
   assert(tree != NULL);
   assert(lp != NULL);
   assert(eventqueue != NULL);
   assert(eventfilter != NULL);

   naddedsols = 0;

   for(run = reopt->run; run >= 0; run--)
   {
      SCIP_Real sim;
      sim = reoptSimilarity(scip, reopt, run, reopt->run+1);

      if( sim >= simparam )
      {
         SCIP_CALL( addSols(reopt, primal, probmem, set, messagehdlr,
               stat, origprob, transprob, tree, lp, eventqueue, eventfilter,
               run, &naddedsols) );

#ifdef SCIP_DEBUG
         {
            printf(">> add %d solutions from run %d (lambda = %.4f).\n", naddedsols, run, sim);
         }
#endif
      }
   }

   return SCIP_OKAY;
}

/* returns the number of saved solutions overall runs */
int SCIPreoptNSavedSols(
   SCIP_REOPT*           reopt
)
{
   int nsavedsols;
   int r;

   assert(reopt != NULL);

   nsavedsols = 0;
   for(r = reopt->run; r >= 0; r--)
   {
      nsavedsols += reopt->nsols[r];
   }
   return nsavedsols;
}

/* returns the number of reused sols over all runs */
int SCIPreoptNUsedSols(
   SCIP_REOPT*           reopt
)
{
   int nsolsused;
   int r;

   assert(reopt != NULL);

   nsolsused = 0;
   for(r = reopt->run; r >= 0; r--)
   {
      if( reopt->solsused[r] )
         nsolsused += reopt->nsols[r];
   }

   return nsolsused;
}

/* save objective function */
SCIP_RETCODE SCIPreoptSaveObj(
   SCIP*                 scip,
   SCIP_REOPT*           reopt,
   SCIP_SET*             set,
   int                   run
)
{
   SCIP_VAR** vars;
   int id;

   assert(reopt != NULL);

   /* check memory */
   SCIP_CALL( ensureRunSize(reopt, set, run) );

   vars = SCIPgetVars(scip);

   /* get memory */
   SCIP_CALL( SCIPallocClearMemoryArray(scip, &reopt->objs[run], SCIPgetNVars(scip)) );

   /* save coefficients */
   vars = SCIPgetVars(scip);
   for(id = 0; id < SCIPgetNVars(scip); id++)
   {
      reopt->objs[run][id] = SCIPvarGetObj(vars[id]);
   }

#ifdef SCIP_DEBUG
   {
      printf(">> saved obj in run %d:\n", run);
      printf("   obj: ");

      for(id = 0; id < SCIPgetNVars(scip); id++)
      {
         SCIP_Real objval;
         const char* name;

         objval = reopt->objs[run][id];
         name = SCIPvarGetName(vars[id]);

         if( objval != 0 )
            printf("%s%f%s ", objval < 0 ? "" : "+", objval, name);
      }
      printf("\n");
   }
#endif

   return SCIP_OKAY;
}

