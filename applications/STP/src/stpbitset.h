/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2019 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not visit scip.zib.de.         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   stpbitset.h
 * @brief  header only, simple implementation of a bitset
 * @author Daniel Rehfeldt
 *
 * Implements a simple bitset.
 * NOTE: for efficiency reasons the bitset type is based on an STP_Vector and thus
 * uses a non-SCIP-standard allocation method. In this way we avoid indirections, because
 * we directly access the raw array.
 * todo if too slow use extra fixed-size vector that uses standard memory allocs, or even
 * cache-aligned mallocs
 *
 */


/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/


#ifndef APPLICATIONS_STP_SRC_STPBITSET_H_
#define APPLICATIONS_STP_SRC_STPBITSET_H_

#include "scip/scip.h"
#include "stpvector.h"

#ifdef __cplusplus
extern "C" {
#endif


#define STP_Bitset STP_Vectype(uint64_t)


/** todo: more efficiently, currently just a text-book implementation.
 *  probably want to have case distinction for compilers and use intrinsics
 *  at least for gcc and intel */
static
inline int bitsetinternalPopcount(
   uint64_t              number              /**< to get popcount for */
   )
{
   const uint64_t stpbit_m1 = 0x5555555555555555;
   const uint64_t stpbit_m2 = 0x3333333333333333;
   const uint64_t stpbit_m4 = 0x0f0f0f0f0f0f0f0f;
   const uint64_t stpbit_powseries = 0x0101010101010101;
   uint64_t n = number;

   n -= (n >> 1) & stpbit_m1;
   n = (n & stpbit_m2) + ((n >> 2) & stpbit_m2);
   n = (n + (n >> 4)) & stpbit_m4;

   return (int) ((n * stpbit_powseries) >> 56);
}


/*
 * Interface methods
 */

/** initializes clean (all-0) bitset and returns */
static
inline STP_Bitset stpbitset_new(
   SCIP*                 scip,               /**< SCIP data structure */
   int                   maxnbits            /**< size of bitset */
   )
{
   STP_Bitset bitset = NULL;
   const int size = (maxnbits + 63) / 64;

   assert(maxnbits > 0);
   assert(size > 0);

   StpVecReserve(scip, bitset, size);

   // todo do that more efficiently with new Stp_Vector reserve method
   for( int i = 0; i < size; i++ )
   {
      StpVecPushBack(scip, bitset, (uint64_t) 0);
   }

   return bitset;
}

/** frees */
static
inline void stpbitset_free(
   SCIP*                 scip,               /**< SCIP data structure */
   STP_Bitset*           bitset              /**< bitset pointer */
   )
{
   assert(scip && bitset);
   assert(*bitset);

   StpVecFree(scip, *bitset);

   assert(NULL == *bitset);
}


/** gets number of bits that can be stored  */
static
inline int stpbitset_getCapacity(
   STP_Bitset           bitset              /**< bitset */
   )
{
   assert(bitset);
   assert(StpVecGetcapacity(bitset) == StpVecGetSize(bitset));

   return (StpVecGetcapacity(bitset) * 64);
}


/** sets bit to TRUE (1) */
static
inline void stpbitset_setBitTrue(
   STP_Bitset           bitset,              /**< bitset */
   int                  index                /**< bit index */
   )
{
   assert(bitset);
   assert(0 <= index && index < stpbitset_getCapacity(bitset));

   bitset[index / 64] |= (uint64_t) 1 << (((uint64_t) index) & 63);
}


/** sets bit to FALSE (0) */
static
inline void stpbitset_setBitFalse(
   STP_Bitset           bitset,              /**< bitset */
   int                  index                /**< bit index */
   )
{
   assert(bitset);
   assert(0 <= index && index < stpbitset_getCapacity(bitset));

   bitset[index / 64] &= !((uint64_t) 1 << (((uint64_t) index) & 63));
}


/** do bitsets (of same size) intersect? */
static
inline SCIP_Bool stpbitset_haveIntersection(
   STP_Bitset           bitset1,             /**< bitset */
   STP_Bitset           bitset2              /**< bitset */
   )
{
   const int vecsize = StpVecGetSize(bitset1);

   assert(bitset1 && bitset2);
   assert(stpbitset_getCapacity(bitset1) == stpbitset_getCapacity(bitset2));
   assert(StpVecGetSize(bitset1) == StpVecGetSize(bitset2));
   assert(vecsize > 0);

   for( int i = 0; i < vecsize; i++ )
   {
      if( (bitset1[i] & bitset2[i]) != 0 )
         return TRUE;
   }

   return FALSE;
}


/** gets number of 1-bits */
static
inline int stpbitset_getPopcount(
   STP_Bitset           bitset               /**< bitset */
   )
{
   int popcount = 0;
   const int vecsize = StpVecGetSize(bitset);

   assert(vecsize > 0);

   for( int i = 0; i < vecsize; i++ )
   {
      popcount += bitsetinternalPopcount(bitset[i]);
   }

   return popcount;
}


#ifdef __cplusplus
}
#endif


#endif /* APPLICATIONS_STP_SRC_STPBITSET_H_ */
