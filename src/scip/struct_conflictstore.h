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

/**@file   struct_sepastore.h
 * @brief  datastructures for storing conflicts
 * @author Jakob Witzig
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_STRUCT_CONFLICTSTORE_H__
#define __SCIP_STRUCT_CONFLICTSTORE_H__


#include "scip/def.h"
#include "scip/type_conflictstore.h"

#ifdef __cplusplus
extern "C" {
#endif

/** storage for conflicts */
struct SCIP_ConflictStore
{
   SCIP_CONS**           conflicts;          /**< array with conflicts */
   SCIP_Longint          lastnodenum;        /**< number of the last seen node */
   int                   conflictsize;       /**< size of conflict array (boundes by conflict->maxpoolsize) */
   int                   nconflicts;         /**< number of stored conflicts */
   int                   nconflictsfound;    /**< total number of conflicts found so far */
   int                   firstused;          /**< first used slot in the storage */
   int                   firstfree;          /**< first free slot in the storage */
};

#ifdef __cplusplus
}
#endif

#endif
