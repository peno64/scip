/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   heur_tm.h
 * @ingroup PRIMALHEURISTICS
 * @brief  TM primal heuristic
 * @author Gerald Gamrath
 * @author Thorsten Koch
 * @author Michael Winkler
 *
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_HEUR_TM_H__
#define __SCIP_HEUR_TM_H__

#include "scip/scip.h"
#include "grph.h"
#define DEFAULT_HOPFACTOR 0.33
#ifdef __cplusplus
extern "C" {
#endif

   /** creates the TM primal heuristic and includes it in SCIP */
   extern
   SCIP_RETCODE SCIPincludeHeurTM(
      SCIP*                 scip                /**< SCIP data structure */
      );
#if 0
   extern
   SCIP_RETCODE SCIPtmHeur(
      SCIP*                 scip,                  /**< SCIP data structure */
      const GRAPH*          graph,                 /**< graph structure */
      PATH**                path,
      SCIP_Real*            cost,
      SCIP_Real*            costrev,
      int*                  result
      );
#endif
   extern
   SCIP_RETCODE do_layer(
      SCIP*                 scip,               /**< SCIP data structure */
      SCIP_HEURDATA* heurdata,
      const GRAPH*  graph,
      int*          starts,
      int*          bestnewstart,
      int*          best_result,
      int           runs,
      int           bestincstart,
      SCIP_Real*    cost,
      SCIP_Real*    costrev,
      SCIP_Real*    hopfactor,
      SCIP_Real     maxcost,
      SCIP_Bool*    success
      );

   extern
   SCIP_RETCODE do_prune(
      SCIP*                 scip,               /**< SCIP data structure */
      const GRAPH*          g,                  /**< graph structure */
      SCIP_Real*            cost,               /**< edge costs */
      int                   layer,
      int*                  result,             /**< ST edges */
      char*                 connected           /**< ST nodes */
      );

   extern
   SCIP_RETCODE do_pcprune(
      SCIP*                 scip,               /**< SCIP data structure */
      const GRAPH*          g,                  /**< graph structure */
      SCIP_Real*            cost,               /**< edge costs */
      int*                  result,             /**< ST edges */
      char*                 connected           /**< ST nodes */
      );

   extern
   SCIP_RETCODE do_degprune(
      SCIP*                 scip,               /**< SCIP data structure */
      const GRAPH*          g,                  /**< graph structure */
      int*                  result,             /**< ST edges */
      char*                 connected           /**< ST nodes */
      );
#ifdef __cplusplus
}
#endif

#endif
