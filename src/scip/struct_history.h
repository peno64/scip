/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2003 Tobias Achterberg                              */
/*                                                                           */
/*                  2002-2003 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the SCIP Academic Licence.        */
/*                                                                           */
/*  You should have received a copy of the SCIP Academic License             */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma ident "@(#) $Id: struct_history.h,v 1.1 2004/01/07 13:14:15 bzfpfend Exp $"

/**@file   struct_history.h
 * @brief  datastructures for branching history
 * @author Tobias Achterberg
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __STRUCT_HISTORY_H__
#define __STRUCT_HISTORY_H__


#include "def.h"
#include "type_history.h"


/** branching history information for single variable and single direction */
struct History
{
   Real             count[2];           /**< number of (partial) summands in down/upwards history (may be fractional) */
   Real             sum[2];             /**< sum of (partial) history values for down/upwards branching */
};


#endif
