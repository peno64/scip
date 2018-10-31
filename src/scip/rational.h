/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2018 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not visit scip.zib.de.         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   scip/rational.h
 * @ingroup INTERNALAPI
 * @brief  rational wrapper
 * @author Leon Eifler
  */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_RATIONAL_H__
#define __SCIP_RATIONAL_H__

#include <stdbool.h>
#include "scip/def.h"
#include "scip/intervalarith.h"
#ifdef WITH_GMP
#include <gmp.h>
#ifdef WITH_ZIMPL
#include "zimpl/numb.h"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum SCIP_RoundModeR
{
   SCIP_ROUND_DOWNWARDS,
   SCIP_ROUND_UPWARDS,
   SCIP_ROUND_NEAREST
};

typedef enum SCIP_RoundModeR SCIP_ROUNDMODER;

typedef struct SCIP_Rational SCIP_Rational;

/*
 * Creation methods
 */

/** Allocate and create a rational from nominator and denominator */
EXTERN
SCIP_Rational* RcreateInt(
   BMS_BLKMEM*           mem,
   int                   nom,                /**< the nominator */
   int                   denom               /**< the denominator */
   );

/** Allocate and create a rational from a string in the format, e.g. "12/35" */
EXTERN
SCIP_Rational* RcreateString(
   BMS_BLKMEM*           mem,                /**< block memory */
   const char*           desc                /**< the String describing the rational */
   );

/** create an array of rationals */
EXTERN
SCIP_Rational** RcreateArray(
   BMS_BLKMEM*           mem,                /**< block memory */
   int                   size                /**< the size of the array */
   );

/** create a copy of a rational */
EXTERN
SCIP_Rational* Rcopy(
   BMS_BLKMEM*           mem,                /**< block memory */
   SCIP_Rational*        src                 /**< rational to copy */
   );

#ifdef WITH_GMP
/** create a rational from an mpq_t */
EXTERN
SCIP_Rational* RcreateGMP(
   BMS_BLKMEM*           mem,                /**< block memory */
   const mpq_t           numb                /**< the mpq_rational */
   );
#endif

/** delete a rational and free the allocated memory */
EXTERN
void Rdelete(
   BMS_BLKMEM*           mem,                /**< block memory */
   SCIP_Rational**       r                   /**< adress of the rational */
   );

/** delete an array of rationals and free the allocated memory */
EXTERN
void RdeleteArray(
   BMS_BLKMEM*           mem,                /**< block memory */
   SCIP_Rational***      array,              /**< address of rational array */
   int                   size                /**< size of the array */
   );

/** delete an array of rationals and free the allocated memory */
EXTERN
void RdeleteArrayVals(
   BMS_BLKMEM*           mem,                /**< block memory */
   SCIP_Rational***      array,              /**< address of rational array */
   int                   size                /**< size of the array */
   );

/** set a rational to the value of another rational */
EXTERN
void Rset(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        src                 /**< the src */
   );

/** set a rational to a nom/denom value */
EXTERN
void RsetInt(
   SCIP_Rational*        res,                /**< the result */
   int                   nom,                /**< the nominator */
   int                   denom               /**< the denominator */
   );

/** set a rational to the value described by a string */
EXTERN
void RsetString(
   SCIP_Rational*        res,                /**< the result */
   const char*           desc                /**< the string describing the rational */
   );

/** set a rational to the value of another a real */
EXTERN
void RsetReal(
   SCIP_Rational*        r,
   SCIP_Real             real
   );

/*
 * Computing methods
 */

/** add two rationals and save the result in res*/
EXTERN
void Radd(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op1,                /**< first operand */
   SCIP_Rational*        op2                 /**< second operand */
   );

/** add a rational and a real and save the result in res*/
EXTERN
void RaddReal(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        rat,                /**< rational number */
   SCIP_Real             real                /**< real number */
   );

/** subtract two rationals and save the result in res*/
EXTERN
void Rdiff(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op1,                /**< first operand */
   SCIP_Rational*        op2                 /**< second operand */
   );

/** subtract a rational and a real and save the result in res*/
EXTERN
void RdiffReal(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        rat,                /**< rational number */
   SCIP_Real             real                /**< real number */
   );

/** returns the relative difference: (val1-val2)/max(|val1|,|val2|,1.0) of two rationals */
EXTERN
void RrelDiff(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        val1,               /**< first value to be compared */
   SCIP_Rational*        val2                /**< second value to be compared */
   );

/** multiply two rationals and save the result in res*/
EXTERN
void Rmult(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op1,                /**< first operand */
   SCIP_Rational*        op2                 /**< second operand */
   );

/** multiply a rational and a real and save the result in res*/
EXTERN
void RmultReal(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op1,                /**< first operand */
   SCIP_Real             op2                 /**< second operand */
   );

/** divide two rationals and save the result in res*/
EXTERN
void Rdiv(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op1,                /**< first operand */
   SCIP_Rational*        op2                 /**< second operand */
   );

/** divide a rational and a real and save the result in res*/
EXTERN
void RdivReal(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op1,                /**< first operand */
   SCIP_Real             op2                 /**< second operand */
   );

/** set res to -op */
EXTERN
void Rneg(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op                  /**< operand */
   );

/** set res to Abs(op) */
EXTERN
void Rabs(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op                  /**< operand */
   );

/** set res to 1/op */
EXTERN
void Rinv(
   SCIP_Rational*        res,                /**< the result */
   SCIP_Rational*        op                  /**< operand */
   );

/** compute the minimum of two rationals */
EXTERN
void Rmin(
   SCIP_Rational*        ret,                /**< the result */
   SCIP_Rational*        r1,                 /**< the first rational */
   SCIP_Rational*        r2                  /**< the second rational */
   );

/*
 * Comparisoon methods
 */

/** check if two rationals are equal */
EXTERN
SCIP_Bool RisEqual(
   SCIP_Rational*        r1,                 /**< the first rational */
   SCIP_Rational*        r2                  /**< the second rational */
   );

/** check if a rational and a real are equal */
EXTERN
SCIP_Bool RisEqualReal(
   SCIP_Rational*        r1,                 /**< the rational */
   SCIP_Real             r2                  /**< the real */
   );

/** check if the first rational is greater than the second*/
EXTERN
SCIP_Bool RisGT(
   SCIP_Rational*        r1,                 /**< the first rational */
   SCIP_Rational*        r2                  /**< the second rational */
   );

/** check if the first rational is smaller than the second*/
EXTERN
SCIP_Bool RisLT(
   SCIP_Rational*        r1,                 /**< the first rational */
   SCIP_Rational*        r2                  /**< the second rational */
   );

/** check if the first rational is smaller or equal than the second*/
EXTERN
SCIP_Bool RisLE(
   SCIP_Rational*        r1,                 /**< the first rational */
   SCIP_Rational*        r2                  /**< the second rational */
   );

/** check if the first rational is greater or equal than the second*/
EXTERN
SCIP_Bool RisGE(
   SCIP_Rational*        r1,                 /**< the first rational */
   SCIP_Rational*        r2                  /**< the second rational */
   );

/** check if the rational is zero */
EXTERN
SCIP_Bool RisZero(
   SCIP_Rational*        r                   /**< the rational to check */
   );

/** check if the rational is positive */
EXTERN
SCIP_Bool RisPositive(
   SCIP_Rational*        r                   /**< the rational to check */
   );

/** check if the rational is negative */
EXTERN
SCIP_Bool RisNegative(
   SCIP_Rational*        r                   /**< the rational to check */
   );

/** check if the rational is positive infinity */
EXTERN
SCIP_Bool RisInfinity(
   SCIP_Rational*        r                   /**< the rational to check */
   );

/** check if the rational is negative infinity */
EXTERN
SCIP_Bool RisNegInfinity(
   SCIP_Rational*        r                   /**< the rational to check */
   );

/** check if the rational is of infinite value */
EXTERN
SCIP_Bool RisAbsInfinity(
   SCIP_Rational*        r                   /**< the rational to check */
   );

/*
 * Printing/Conversion methods
 */

/** print a Rational to std out */
void RtoString(
   SCIP_Rational*        r,                  /**< the rational to print */
   char*                 str
   );

/** print a rational to command line (for debugging) */
void Rprint(
   SCIP_Rational*        r                   /**< the rational to print */
   );

/** return approximation of Rational as SCIP_Real */
EXTERN
SCIP_Real RgetRealRelax(
   SCIP_Rational*        r,                  /**< the rational to convert */
   SCIP_ROUNDMODE        roundmode           /**< rounding direction (not really working yet) */
   );

/** return approximation of Rational as SCIP_Real */
EXTERN
SCIP_Real RgetRealApprox(
   SCIP_Rational*        r                   /**< the rational to convert */
   );

EXTERN
void testNumericsRational();

#ifdef __cplusplus
}
#endif

#endif
