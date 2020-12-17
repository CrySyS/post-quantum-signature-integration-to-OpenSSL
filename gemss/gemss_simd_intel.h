#ifndef _SIMD_INTEL_H
#define _SIMD_INTEL_H

/* Intel intrinsics */

#include "gemss_arch.h"


#ifdef GEMSS_ENABLED_SSE
    /* 128-bit integer */
    #define GEMSS_M128i __m128i

    /* Set to 0 */
    #define GEMSS_PSETZERO_PS() _mm_setzero_ps()

    #define GEMSS_PSHUFFLE_PS(A,B,i) \
                ((__m128i)_mm_shuffle_ps((__m128)(A),(__m128)(B),i))

    #define GEMSS_PMOVE_PS(A,B) ((__m128i)_mm_move_ss((__m128)A,(__m128)B))
#endif


/* These intrinsics are available on SSE and SSE2 */
#ifdef GEMSS_ENABLED_SSE2
    /* Set to 0 */
    #define GEMSS_PSETZERO() _mm_setzero_si128()

    /* Bitwise operator */
    #define GEMSS_PAND_(A,B) _mm_and_si128(A,B)
    #define GEMSS_PANDNOT(A,B) _mm_andnot_si128(A,B)
    #define GEMSS_PXOR_(A,B) _mm_xor_si128(A,B)

    /* Load */
    #define GEMSS_PLOADL(A) _mm_loadl_epi64((__m128i*)(A))
    #define GEMSS_PLOAD(A) _mm_load_si128((__m128i*)(A))
    #define GEMSS_PLOADU(A) _mm_loadu_si128((__m128i*)(A))

    /* Store */
    #define GEMSS_PSTOREL(res,A) _mm_storel_epi64((__m128i*)(res),A)
    #define GEMSS_PSTORE(res,A) _mm_store_si128((__m128i*)(res),A);
    #define GEMSS_PSTOREU(res,A) _mm_storeu_si128((__m128i*)(res),A);

    /* Here, a 128-bit register is splitted in four 32-bit registers: 3|2|1|0.
       The next operation changes the order of these registers. */
    #define GEMSS_PSHUFFLE_32(A,i) _mm_shuffle_epi32(A,i)

    /* Unpack */
    #define GEMSS_PUNPACKLO_32(A,B) _mm_unpacklo_epi32(A,B)
    #define GEMSS_PUNPACKLO_64(A,B) _mm_unpacklo_epi64(A,B)
    #define GEMSS_PUNPACKHI_32(A,B) _mm_unpackhi_epi32(A,B)
    #define GEMSS_PUNPACKHI_64(A,B) _mm_unpackhi_epi64(A,B)
#elif defined(GEMSS_ENABLED_SSE)
    /* Set to 0 */
    #define GEMSS_PSETZERO() ((__m128i)GEMSS_PSETZERO_PS())

    /* Bitwise operator */
    #define GEMSS_PAND_(A,B) ((__m128i)_mm_and_ps((__m128)(A),(__m128)(B)))
    #define GEMSS_PANDNOT(A,B) ((__m128i)_mm_andnot_ps((__m128)(A),(__m128)(B)))
    #define GEMSS_PXOR_(A,B) ((__m128i)_mm_xor_ps((__m128)(A),(__m128)(B)))

    /* Load */
    #define GEMSS_PLOADL(A) ((__m128i)_mm_loadl_pi(GEMSS_PSETZERO_PS(),(__m64*)(A)))
    #define GEMSS_PLOAD(A) ((__m128i)_mm_load_ps((float*)(A)))
    #define GEMSS_PLOADU(A) ((__m128i)_mm_loadu_ps((float*)(A)))

    /* Store */
    #define GEMSS_PSTOREL(res,A) _mm_storel_pi((__m64*)(res),(__m128)(A))
    #define GEMSS_PSTORE(res,A) _mm_store_ps((float*)(res),(__m128)(A));
    #define GEMSS_PSTOREU(res,A) _mm_storeu_ps((float*)(res),(__m128)(A));

    /* Here, a 128-bit register is splitted in four 32-bit registers: 3|2|1|0.
       The next operation changes the order of these registers. */
    #define GEMSS_PSHUFFLE_32(A,i) GEMSS_PSHUFFLE_PS(A,A,i)

    /* Unpack */
    #define GEMSS_PUNPACKLO_32(A,B) \
                ((__m128i)_mm_unpacklo_ps((__m128)(A),(__m128)(B)))
    #define GEMSS_PUNPACKHI_32(A,B) \
                ((__m128i)_mm_unpackhi_ps((__m128)(A),(__m128)(B)))

    #define GEMSS_PUNPACKLO_64(A,B) \
                ((__m128i)_mm_movelh_ps((__m128)(A),(__m128)(B)))
    #define GEMSS_PUNPACKHI_64(A,B) \
                ((__m128i)_mm_movehl_ps((__m128)(B),(__m128)(A)))
#endif


#ifdef GEMSS_ENABLED_SSE2
    /* Shuffle */
    #define GEMSS_PSHUFFLE_PD(A,B,i) \
                ((__m128i)_mm_shuffle_pd((__m128d)(A),(__m128d)(B),i))

    /* Add */
    #define GEMSS_PADD_64(A,B) _mm_add_epi64(A,B)

    /* Sub */
    #define GEMSS_PSUB_64(A,B) _mm_sub_epi64(A,B)

    /* Set */
    #define GEMSS_PSET_8(AF,AE,AD,AC,AB,AA,A9,A8,A7,A6,A5,A4,A3,A2,A1,A0) \
                _mm_set_epi8(AF,AE,AD,AC,AB,AA,A9,A8,A7,A6,A5,A4,A3,A2,A1,A0)
    #define GEMSS_PSET_16(A7,A6,A5,A4,A3,A2,A1,A0) \
                _mm_set_epi16(A7,A6,A5,A4,A3,A2,A1,A0)
    #define GEMSS_PSET_32(A3,A2,A1,A0) _mm_set_epi32(A3,A2,A1,A0)
    #define GEMSS_PSET_64(A1,A0) _mm_set_epi64x(A1,A0)

    /* Set 1 */
    #define GEMSS_PSET1_8(A0) _mm_set1_epi8(A0)
    #define GEMSS_PSET1_16(A0) _mm_set1_epi16(A0)
    #define GEMSS_PSET1_32(A0) _mm_set1_epi32(A0)
    #define GEMSS_PSET1_64(A0) _mm_set1_epi64x(A0)

    /* Shift */
    #define GEMSS_PSLLI_16(A,i) _mm_slli_epi16(A,i)
    #define GEMSS_PSLLI_32(A,i) _mm_slli_epi32(A,i)
    #define GEMSS_PSLLI_64(A,i) _mm_slli_epi64(A,i)
    #define GEMSS_PSLLI_128(A,i) _mm_slli_si128(A,i)

    #define GEMSS_PSRLI_16(A,i) _mm_srli_epi16(A,i)
    #define GEMSS_PSRLI_32(A,i) _mm_srli_epi32(A,i)
    #define GEMSS_PSRLI_64(A,i) _mm_srli_epi64(A,i)
    #define GEMSS_PSRLI_128(A,i) _mm_srli_si128(A,i)

    /* Unpack */
    #define GEMSS_PUNPACKLO_8(A,B) _mm_unpacklo_epi8(A,B)
    #define GEMSS_PUNPACKLO_16(A,B) _mm_unpacklo_epi16(A,B)
    /* unpacklo_32 is already available in SSE */
    /* unpacklo_64 is already available in SSE */

    #define GEMSS_PUNPACKHI_8(A,B) _mm_unpackhi_epi8(A,B)
    #define GEMSS_PUNPACKHI_16(A,B) _mm_unpackhi_epi16(A,B)
    /* unpackhi_32 is already available in SSE */
    /* unpackhi_64 is already available in SSE */

    /* For x in {0,1}, compute -x as (x==1)?(-1):0. */

    /* Use: "one=GEMSS_PSET1_8(1);" to initialize the variable one */
    #define GEMSS_PMASK8_ONE(x,one) _mm_cmpeq_epi8(x,one)
    /* Use: "one=GEMSS_PSET1_16(1);" to initialize the variable one */
    #define GEMSS_PMASK16_ONE(x,one) _mm_cmpeq_epi16(x,one)
    /* Use: "one=GEMSS_PSET1_32(1);" to initialize the variable one */
    #define GEMSS_PMASK32_ONE(x,one) _mm_cmpeq_epi32(x,one)
#endif


/*** We implement here other functions, available on SSE and SSE2 ***/
#ifdef GEMSS_ENABLED_SSE2
    /* Left shift without 0 padding */
    #define GEMSS_PLMOVE64(x) GEMSS_PSLLI_128(x,8)

    /* Right shift without 0 padding */
    #define GEMSS_PRMOVE64(x) GEMSS_PSRLI_128(x,8)

    /* Left shift with 0 padding */
    #define GEMSS_PLSHIFT64(x) GEMSS_PSLLI_128(x,8)

    /* Right shift with 0 padding */
    #define GEMSS_PRSHIFT64(x) GEMSS_PSRLI_128(x,8)

    /* Here, a 128-bit register is splitted in four 32-bit registers: 3|2|1|0.
       The next operations change the order of these registers. */

    /* Duplicate one of the two 64-bit registers. */
    #define GEMSS_PSHUFFLE_32_1010(A) GEMSS_PSHUFFLE_32(A,0x44)
    #define GEMSS_PSHUFFLE_32_3232(A) GEMSS_PSHUFFLE_32(A,0xEE)

    #define GEMSS_PSETL_64(A0) GEMSS_PSET_64(0,A0)
    #define GEMSS_PSETH_64(A0) GEMSS_PSET_64(A0,0)
#elif defined(GEMSS_ENABLED_SSE)
    /* Left shift without 0 padding */
    #define GEMSS_PLMOVE64(x) GEMSS_PUNPACKLO_64(GEMSS_PSETZERO(),x)

    /* Right shift without 0 padding */
    #define GEMSS_PRMOVE64(x) GEMSS_PUNPACKHI_64(x,GEMSS_PSETZERO())

    /* Left shift with 0 padding */
    #define GEMSS_PLSHIFT64(x) GEMSS_PUNPACKLO_64(GEMSS_PSETZERO(),x)

    /* Right shift with 0 padding */
    #define GEMSS_PRSHIFT64(x) GEMSS_PUNPACKHI_64(x,GEMSS_PSETZERO())

    /* Here, a 128-bit register is splitted in four 32-bit registers: 3|2|1|0.
       The next operations change the order of these registers. */

    /* Duplicate one of the two 64-bit registers. */
    #define GEMSS_PSHUFFLE_32_1010(A) GEMSS_PUNPACKLO_32(A,A)
    #define GEMSS_PSHUFFLE_32_3232(A) GEMSS_PUNPACKHI_32(A,A)

    #define GEMSS_PSETL_64(A0) GEMSS_PLOADL(&(A0))
    #define GEMSS_PSETH_64(A0) GEMSS_PLSHIFT64(GEMSS_PSETL_64(A0))
#endif


#if (defined(GEMSS_ENABLED_SSE)||defined(GEMSS_ENABLED_SSE2))
    /*** We implement here other functions ***/

    /* Load */
    #define GEMSS_PINIT64(x,A) x=GEMSS_PLOADL(A);
    #define GEMSS_PINIT128(x,A) x=GEMSS_PLOADU(A);

    #define GEMSS_PINIT192(x1,x2,A) \
        GEMSS_PINIT128(x1,A);\
        GEMSS_PINIT64(x2,A+2);

    #define GEMSS_PINIT256(x1,x2,A) \
        GEMSS_PINIT128(x1,A);\
        GEMSS_PINIT128(x2,A+2);

    #define GEMSS_PINIT320(x1,x2,x3,A) \
        GEMSS_PINIT256(x1,x2,A);\
        GEMSS_PINIT64(x3,A+4);

    #define GEMSS_PINIT384(x1,x2,x3,A) \
        GEMSS_PINIT256(x1,x2,A);\
        GEMSS_PINIT128(x3,A+4);

    #define GEMSS_PINIT448(x1,x2,x3,x4,A) \
        GEMSS_PINIT256(x1,x2,A);\
        GEMSS_PINIT192(x3,x4,A+4);

    #define GEMSS_PINIT512(x1,x2,x3,x4,A) \
        GEMSS_PINIT256(x1,x2,A);\
        GEMSS_PINIT256(x3,x4,A+4);

    #define GEMSS_PINIT576(x1,x2,x3,x4,x5,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT64(x5,A+8);

    #define GEMSS_PINIT640(x1,x2,x3,x4,x5,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT128(x5,A+8);

    #define GEMSS_PINIT704(x1,x2,x3,x4,x5,x6,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT192(x5,x6,A+8);

    #define GEMSS_PINIT768(x1,x2,x3,x4,x5,x6,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT256(x5,x6,A+8);

    #define GEMSS_PINIT832(x1,x2,x3,x4,x5,x6,x7,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT320(x5,x6,x7,A+8);

    #define GEMSS_PINIT896(x1,x2,x3,x4,x5,x6,x7,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT384(x5,x6,x7,A+8);

    #define GEMSS_PINIT960(x1,x2,x3,x4,x5,x6,x7,x8,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT448(x5,x6,x7,x8,A+8);

    #define GEMSS_PINIT1024(x1,x2,x3,x4,x5,x6,x7,x8,A) \
        GEMSS_PINIT512(x1,x2,x3,x4,A);\
        GEMSS_PINIT512(x5,x6,x7,x8,A+8);

    #define GEMSS_PINIT1088(x1,x2,x3,x4,x5,x6,x7,x8,x9,A) \
        GEMSS_PINIT1024(x1,x2,x3,x4,x5,x6,x7,x8,A);\
        GEMSS_PINIT64(x9,A+16);

    #define GEMSS_PINIT1152(x1,x2,x3,x4,x5,x6,x7,x8,x9,A) \
        GEMSS_PINIT1024(x1,x2,x3,x4,x5,x6,x7,x8,A);\
        GEMSS_PINIT128(x9,A+16);


    /* Store */
    #define GEMSS_PSTORE128(A,x1) GEMSS_PSTOREU(A,x1)

    #define GEMSS_PSTORE192(A,x1,x2) \
        GEMSS_PSTORE128(A,x1);\
        GEMSS_PSTOREL(A+2,x2);

    #define GEMSS_PSTORE256(A,x1,x2) \
        GEMSS_PSTORE128(A,x1);\
        GEMSS_PSTORE128(A+2,x2);

    #define GEMSS_PSTORE320(A,x1,x2,x3) \
        GEMSS_PSTORE256(A,x1,x2);\
        GEMSS_PSTOREL(A+4,x3);

    #define GEMSS_PSTORE384(A,x1,x2,x3) \
        GEMSS_PSTORE256(A,x1,x2);\
        GEMSS_PSTORE128(A+4,x3);

    #define GEMSS_PSTORE448(A,x1,x2,x3,x4) \
        GEMSS_PSTORE256(A,x1,x2);\
        GEMSS_PSTORE192(A+4,x3,x4);

    #define GEMSS_PSTORE512(A,x1,x2,x3,x4) \
        GEMSS_PSTORE256(A,x1,x2);\
        GEMSS_PSTORE256(A+4,x3,x4);

    #define GEMSS_PSTORE576(A,x1,x2,x3,x4,x5) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTOREL(A+8,x5);

    #define GEMSS_PSTORE640(A,x1,x2,x3,x4,x5) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE128(A+8,x5);

    #define GEMSS_PSTORE704(A,x1,x2,x3,x4,x5,x6) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE192(A+8,x5,x6);

    #define GEMSS_PSTORE768(A,x1,x2,x3,x4,x5,x6) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE256(A+8,x5,x6);

    #define GEMSS_PSTORE832(A,x1,x2,x3,x4,x5,x6,x7) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE320(A+8,x5,x6,x7);

    #define GEMSS_PSTORE896(A,x1,x2,x3,x4,x5,x6,x7) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE384(A+8,x5,x6,x7);

    #define GEMSS_PSTORE960(A,x1,x2,x3,x4,x5,x6,x7,x8) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE448(A+8,x5,x6,x7,x8);

    #define GEMSS_PSTORE1024(A,x1,x2,x3,x4,x5,x6,x7,x8) \
        GEMSS_PSTORE512(A,x1,x2,x3,x4);\
        GEMSS_PSTORE512(A+8,x5,x6,x7,x8);

    #define GEMSS_PSTORE1088(A,x1,x2,x3,x4,x5,x6,x7,x8,x9) \
        GEMSS_PSTORE1024(A,x1,x2,x3,x4,x5,x6,x7,x8);\
        GEMSS_PSTOREL(A+16,x9);

    #define GEMSS_PSTORE1152(A,x1,x2,x3,x4,x5,x6,x7,x8,x9) \
        GEMSS_PSTORE1024(A,x1,x2,x3,x4,x5,x6,x7,x8);\
        GEMSS_PSTORE128(A+16,x9);


    /* Bitwise operator */
    #define GEMSS_PAND1_2(C,A) C=GEMSS_PAND_(A,C);

    #define GEMSS_PXOR1_(C,A,B) C=GEMSS_PXOR_(A,B);
    #define GEMSS_PXOR2_(C1,C2,A1,A2,B1,B2) \
        GEMSS_PXOR1_(C1,A1,B1)\
        GEMSS_PXOR1_(C2,A2,B2)
    #define GEMSS_PXOR3_(C1,C2,C3,A1,A2,A3,B1,B2,B3) \
        GEMSS_PXOR1_(C1,A1,B1)\
        GEMSS_PXOR1_(C2,A2,B2)\
        GEMSS_PXOR1_(C3,A3,B3)
    #define GEMSS_PXOR4_(C1,C2,C3,C4,A1,A2,A3,A4,B1,B2,B3,B4) \
        GEMSS_PXOR1_(C1,A1,B1)\
        GEMSS_PXOR1_(C2,A2,B2)\
        GEMSS_PXOR1_(C3,A3,B3)\
        GEMSS_PXOR1_(C4,A4,B4)

    #define GEMSS_PXOR1_2(C,A) C=GEMSS_PXOR_(A,C);
    #define GEMSS_PXOR2_2(C1,C2,A1,A2) \
        GEMSS_PXOR1_2(C1,A1)\
        GEMSS_PXOR1_2(C2,A2)
    #define GEMSS_PXOR3_2(C1,C2,C3,A1,A2,A3) \
        GEMSS_PXOR1_2(C1,A1)\
        GEMSS_PXOR1_2(C2,A2)\
        GEMSS_PXOR1_2(C3,A3)
    #define GEMSS_PXOR4_2(C1,C2,C3,C4,A1,A2,A3,A4) \
        GEMSS_PXOR1_2(C1,A1)\
        GEMSS_PXOR1_2(C2,A2)\
        GEMSS_PXOR1_2(C3,A3)\
        GEMSS_PXOR1_2(C4,A4)
    #define GEMSS_PXOR5_2(C1,C2,C3,C4,C5,A1,A2,A3,A4,A5) \
        GEMSS_PXOR1_2(C1,A1)\
        GEMSS_PXOR1_2(C2,A2)\
        GEMSS_PXOR1_2(C3,A3)\
        GEMSS_PXOR1_2(C4,A4)\
        GEMSS_PXOR1_2(C5,A5)
#endif


#ifdef GEMSS_ENABLED_SSSE3
    /* Shuffle */
    #define GEMSS_PSHUFFLE_8(A,B) _mm_shuffle_epi8(A,B)
#endif


#ifdef GEMSS_ENABLED_SSSE3
    #define GEMSS_PALIGNR(A2,A1,NB_BYTES) _mm_alignr_epi8(A2,A1,NB_BYTES)

    /*** We implement here other functions ***/

    #define GEMSS_PALIGNR_4(A2,A1) GEMSS_PALIGNR(A2,A1,4)
    #define GEMSS_PALIGNR_12(A2,A1) GEMSS_PALIGNR(A2,A1,12)
    #define GEMSS_PMIDDLE(A1,A2) GEMSS_PALIGNR(A2,A1,8)
#elif defined(GEMSS_ENABLED_SSE2)
    #define GEMSS_PALIGNR(A2,A1,NB_BYTES) \
        GEMSS_PXOR_(GEMSS_PSRLI_128(A1,NB_BYTES),GEMSS_PSLLI_128(A2,16-NB_BYTES))

    /*** We implement here other functions ***/

    #define GEMSS_PALIGNR_4(A2,A1) GEMSS_PSHUFFLE_32(GEMSS_PMOVE_PS(A1,A2),0x39)
    #define GEMSS_PALIGNR_12(A2,A1) GEMSS_PALIGNR(A2,A1,12)
    #define GEMSS_PMIDDLE(A1,A2) GEMSS_PSHUFFLE_PD(A1,A2,1)
    /* Slower */
/*    #define GEMSS_PMIDDLE(A1,A2) GEMSS_PUNPACKLO_64(GEMSS_PRMOVE64(A1),A2)*/
#elif defined(GEMSS_ENABLED_SSE)
    /*** We implement here other functions ***/

    #define GEMSS_PALIGNR_4(A2,A1) GEMSS_PSHUFFLE_32(GEMSS_PMOVE_PS(A1,A2),0x39)
    #define GEMSS_PALIGNR_12(A2,A1) \
                GEMSS_PMOVE_PS(GEMSS_PSHUFFLE_32(A2,0x93),GEMSS_PSHUFFLE_32(A1,0x93))
    #define GEMSS_PMIDDLE(A1,A2) GEMSS_PSHUFFLE_PS(A1,A2,0x4E)
    /* Slower */
/*    #define GEMSS_PMIDDLE(A1,A2) GEMSS_PUNPACKLO_64(GEMSS_PRMOVE64(A1),A2)*/
#endif


#ifdef GEMSS_ENABLED_SSE4_1
    /* Use: "one=GEMSS_PSET1_64(1);" to initialize the variable one */
    #define GEMSS_PMASK64_ONE(x,one) _mm_cmpeq_epi64(x,one)
#elif defined(GEMSS_ENABLED_SSE2)
    /* For x in {0,1}, compute -x as (0-x).
       The variable one is not used */
    #define GEMSS_PMASK64_ONE(x,one) GEMSS_PSUB_64(GEMSS_PSETZERO(),x)
#endif


#ifdef GEMSS_MODE_64_BITS
    #ifdef GEMSS_ENABLED_SSE2
        #define GEMSS_PCVT_64(C,A) (C)=_mm_cvtsi128_si64(A);
    #elif defined(GEMSS_ENABLED_SSE)
        #define GEMSS_PCVT_64(C,A) GEMSS_PSTOREL(&(C),A);
    #endif

    #ifdef GEMSS_ENABLED_SSE4_1
        #define GEMSS_EXTRACT64(A) _mm_extract_epi64(A,1)
    #elif defined(GEMSS_ENABLED_SSE2)
        #define GEMSS_EXTRACT64(A) _mm_cvtsi128_si64(GEMSS_PRMOVE64(A))
    #endif

#elif defined(GEMSS_ENABLED_SSE4_1)
    #define GEMSS_PCVT_64(C,A) GEMSS_PSTOREL(&(C),A);

    #define GEMSS_EXTRACT64(A) (((uint64_t)(unsigned)_mm_extract_epi32(A,2))\
                          ^(((uint64_t)_mm_extract_epi32(A,3))<<32))
#elif defined(GEMSS_ENABLED_SSE2)
    #define GEMSS_PCVT_64(C,A) GEMSS_PSTOREL(&(C),A);

    #define GEMSS_EXTRACT64(A) \
        (((uint64_t)(unsigned)_mm_cvtsi128_si32(GEMSS_PRMOVE64(A)))\
         ^(((uint64_t)_mm_cvtsi128_si32(GEMSS_PSRLI_128(A,12)))<<32))
#elif defined(GEMSS_ENABLED_SSE)
    #define GEMSS_PCVT_64(C,A) GEMSS_PSTOREL(&(C),A);
#endif


/* These intrinsics are available on AVX and AVX2 */
#ifdef GEMSS_ENABLED_AVX2
    /* Bitwise operators */
    #define GEMSS_VPAND_(A,B) _mm256_and_si256(A,B)
    #define GEMSS_VPXOR_(A,B) _mm256_xor_si256(A,B)

    /* Load + mask */
    #define GEMSS_PMASKLOAD(data,mask) \
        _mm_maskload_epi64((long long int*)(data),mask)
    #define GEMSS_VPMASKLOAD(data,mask) \
        _mm256_maskload_epi64((long long int*)(data),mask)

    /* Unpack */
    #define GEMSS_VPUNPACKLO_32(A,B) _mm256_unpacklo_epi32(A,B)
    #define GEMSS_VPUNPACKLO_64(A,B) _mm256_unpacklo_epi64(A,B)

    #define GEMSS_VPUNPACKHI_32(A,B) _mm256_unpackhi_epi32(A,B)
    #define GEMSS_VPUNPACKHI_64(A,B) _mm256_unpackhi_epi64(A,B)

    #define GEMSS_VPBLEND_32(A,B,i) _mm256_blend_epi32(A,B,i)

    /* Extract A128 in the higher 128-bit of DST256 */
    #define GEMSS_VPINSERT_128(DST256,A128) _mm256_inserti128_si256(DST256,A128,1)

    /* Extract the higher 128-bit register */
    #define GEMSS_VPEXTRACT128(A) _mm256_extracti128_si256(A,1)
#elif defined(GEMSS_ENABLED_AVX)
    /* Bitwise operators */
    #define GEMSS_VPAND_(A,B) ((__m256i)_mm256_and_pd((__m256d)(A),(__m256d)(B)))
    #define GEMSS_VPXOR_(A,B) ((__m256i)_mm256_xor_pd((__m256d)(A),(__m256d)(B)))

    /* Load + mask */
    #define GEMSS_PMASKLOAD(data,mask) \
        ((__m128i)_mm_maskload_pd((double*)(data),mask))
    #define GEMSS_VPMASKLOAD(data,mask) \
        ((__m256i)_mm256_maskload_pd((double*)(data),mask))

    /* Unpack */
    #define GEMSS_VPUNPACKLO_32(A,B) \
        ((__m256i)_mm256_unpacklo_ps((__m256)(A),(__m256)(B)))
    #define GEMSS_VPUNPACKLO_64(A,B) \
        ((__m256i)_mm256_unpacklo_pd((__m256d)(A),(__m256d)(B)))

    #define GEMSS_VPUNPACKHI_32(A,B) \
        ((__m256i)_mm256_unpackhi_ps((__m256)(A),(__m256)(B)))
    #define GEMSS_VPUNPACKHI_64(A,B) \
        ((__m256i)_mm256_unpackhi_pd((__m256d)(A),(__m256d)(B)))

    #define GEMSS_VPBLEND_32(A,B,i) ((__m256i)_mm256_blend_ps((__m256)(A),\
                                                        (__m256)(B),i))

    /* Extract A128 in the higher 128-bit of DST256 */
    #define GEMSS_VPINSERT_128(DST256,A128) _mm256_insertf128_si256(DST256,A128,1)

    /* Extract the higher 128-bit register */
    #define GEMSS_VPEXTRACT128(A) ((__m128i)_mm256_extractf128_pd((__m256d)(A),1))
#endif


/* These intrinsics are available on AVX */
#ifdef GEMSS_ENABLED_AVX
    /* 256-bit integer */
    #define GEMSS_M256i __m256i

    /* Set to 0 */
    #define GEMSS_VPSETZERO() _mm256_setzero_si256()

    /* Set */
    #define GEMSS_VPSET_32(A7,A6,A5,A4,A3,A2,A1,A0) \
                _mm256_set_epi32(A7,A6,A5,A4,A3,A2,A1,A0)
    #define GEMSS_VPSET_64(A3,A2,A1,A0) _mm256_set_epi64x(A3,A2,A1,A0)

    /* Set 1 */
    #define GEMSS_VPSET1_8(A0) _mm256_set1_epi8(A0)
    #define GEMSS_VPSET1_16(A0) _mm256_set1_epi16(A0)
    #define GEMSS_VPSET1_32(A0) _mm256_set1_epi32(A0)
    #define GEMSS_VPSET1_64(A0) _mm256_set1_epi64x(A0)

    /* Conversion */
    #define GEMSS_VPCVT_128(A) _mm256_castsi256_si128(A)
    #define GEMSS_PCVT_256(A) _mm256_castsi128_si256(A)

    /* Extraction */
    #ifdef GEMSS_MODE_64_BITS
        #define GEMSS_VPEXTRACT64(A,i) _mm256_extract_epi64(A,i)
    #else
        #define GEMSS_VPEXTRACT64(A,i) \
            (((uint64_t)(unsigned)_mm256_extract_epi32(A,((i)<<1)))\
             ^(((uint64_t)_mm256_extract_epi32(A,((i)<<1)+1))<<32))
    #endif

    /* Load */
    #define GEMSS_VPLOAD(A) _mm256_load_si256((__m256i*)(A))
    #define GEMSS_VPLOADU(A) _mm256_loadu_si256((__m256i*)(A))

    /* Store */
    #define GEMSS_VPSTORE(res,A) _mm256_store_si256((__m256i*)(res),A);
    #define GEMSS_VPSTOREU(res,A) _mm256_storeu_si256((__m256i*)(res),A);


    /*** We implement here other functions ***/


    #define GEMSS_VPSETL_64(A0) GEMSS_VPSET_64(0,0,0,A0)
    #define GEMSS_VPSETL2_64(A1,A0) GEMSS_VPSET_64(0,0,A1,A0)
    #define GEMSS_VPSETL3_64(A2,A1,A0) GEMSS_VPSET_64(0,A2,A1,A0)

    #define GEMSS_VPSET_FFF0 GEMSS_VPSET_64(GEMSS_MONE64,GEMSS_MONE64,GEMSS_MONE64,0)


    /* Load */
    #define GEMSS_VPINITU256(x,A) x=GEMSS_VPLOADU(A);

    #define GEMSS_VPINIT64(x,A) \
        x=GEMSS_PCVT_256(GEMSS_PLOADL(A));

    #define GEMSS_VPINIT128(x,A) \
        x=GEMSS_PCVT_256(GEMSS_PLOADU(A));

    #define GEMSS_VPINIT192(x,A) \
        x=GEMSS_VPINSERT_128(GEMSS_PCVT_256(GEMSS_PLOADU(A)),GEMSS_PLOADL(A+2));

    #define GEMSS_VPINIT256(x,A) x=GEMSS_VPLOADU(A);

    #define GEMSS_VPINIT320(x1,x2,A) \
        GEMSS_VPINIT256(x1,A);\
        GEMSS_VPINIT64(x2,A+4);

    #define GEMSS_VPINIT384(x1,x2,A) \
        GEMSS_VPINIT256(x1,A);\
        GEMSS_VPINIT128(x2,A+4);

    #define GEMSS_VPINIT448(x1,x2,A) \
        GEMSS_VPINIT256(x1,A);\
        GEMSS_VPINIT192(x2,A+4);

    #define GEMSS_VPINIT512(x1,x2,A) \
        GEMSS_VPINIT256(x1,A);\
        GEMSS_VPINIT256(x2,A+4);

    #define GEMSS_VPINIT576(x1,x2,x3,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT64(x3,A+8);

    #define GEMSS_VPINIT640(x1,x2,x3,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT128(x3,A+8);

    #define GEMSS_VPINIT704(x1,x2,x3,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT192(x3,A+8);

    #define GEMSS_VPINIT768(x1,x2,x3,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT256(x3,A+8);

    #define GEMSS_VPINIT832(x1,x2,x3,x4,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT320(x3,x4,A+8);

    #define GEMSS_VPINIT896(x1,x2,x3,x4,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT384(x3,x4,A+8);

    #define GEMSS_VPINIT960(x1,x2,x3,x4,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT448(x3,x4,A+8);

    #define GEMSS_VPINIT1024(x1,x2,x3,x4,A) \
        GEMSS_VPINIT512(x1,x2,A);\
        GEMSS_VPINIT512(x3,x4,A+8);

    #define GEMSS_VPINIT1088(x1,x2,x3,x4,x5,A) \
        GEMSS_VPINIT1024(x1,x2,x3,x4,A);\
        GEMSS_VPINIT64(x5,A+16);

    #define GEMSS_VPINIT1152(x1,x2,x3,x4,x5,A) \
        GEMSS_VPINIT1024(x1,x2,x3,x4,A);\
        GEMSS_VPINIT128(x5,A+16);


    /* Store */
    #define GEMSS_VPSTORE64(A,x) \
        GEMSS_PSTOREL(A,GEMSS_VPCVT_128(x));

    #define GEMSS_VPSTORE128(A,x) \
        GEMSS_PSTOREU(A,GEMSS_VPCVT_128(x));

    #define GEMSS_VPSTORE192(A,x) \
        GEMSS_PSTOREU(A,GEMSS_VPCVT_128(x));\
        GEMSS_PSTOREL(A+2,GEMSS_VPEXTRACT128(x));

    #define GEMSS_VPSTORE256 GEMSS_VPSTOREU

    #define GEMSS_VPSTORE320(A,x1,x2) \
        GEMSS_VPSTORE256(A,x1);\
        GEMSS_VPSTORE64(A+4,x2);

    #define GEMSS_VPSTORE384(A,x1,x2) \
        GEMSS_VPSTORE256(A,x1);\
        GEMSS_VPSTORE128(A+4,x2);

    #define GEMSS_VPSTORE448(A,x1,x2) \
        GEMSS_VPSTORE256(A,x1);\
        GEMSS_VPSTORE192(A+4,x2);

    #define GEMSS_VPSTORE512(A,x1,x2) \
        GEMSS_VPSTORE256(A,x1);\
        GEMSS_VPSTORE256(A+4,x2);

    #define GEMSS_VPSTORE576(A,x1,x2,x3) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE64(A+8,x3);

    #define GEMSS_VPSTORE640(A,x1,x2,x3) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE128(A+8,x3);

    #define GEMSS_VPSTORE704(A,x1,x2,x3) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE192(A+8,x3);

    #define GEMSS_VPSTORE768(A,x1,x2,x3) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE256(A+8,x3);

    #define GEMSS_VPSTORE832(A,x1,x2,x3,x4) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE320(A+8,x3,x4);

    #define GEMSS_VPSTORE896(A,x1,x2,x3,x4) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE384(A+8,x3,x4);

    #define GEMSS_VPSTORE960(A,x1,x2,x3,x4) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE448(A+8,x3,x4);

    #define GEMSS_VPSTORE1024(A,x1,x2,x3,x4) \
        GEMSS_VPSTORE512(A,x1,x2);\
        GEMSS_VPSTORE512(A+8,x3,x4);

    #define GEMSS_VPSTORE1088(A,x1,x2,x3,x4,x5) \
        GEMSS_VPSTORE1024(A,x1,x2,x3,x4);\
        GEMSS_VPSTORE64(A+16,x5);

    #define GEMSS_VPSTORE1152(A,x1,x2,x3,x4,x5) \
        GEMSS_VPSTORE1024(A,x1,x2,x3,x4);\
        GEMSS_VPSTORE128(A+16,x5);
#endif


/* These intrinsics are available on AVX2 only */
#ifdef GEMSS_ENABLED_AVX2
    /* Add */
    #define GEMSS_VPADD_64(A,B) _mm256_add_epi64(A,B)

    /* Sub */
    #define GEMSS_VPSUB_64(A,B) _mm256_sub_epi64(A,B)

    /* Shift */
    #define GEMSS_VPSLLI_16(A,i) _mm256_slli_epi16(A,i)
    #define GEMSS_VPSLLI_32(A,i) _mm256_slli_epi32(A,i)
    #define GEMSS_VPSLLI_64(A,i) _mm256_slli_epi64(A,i)
    #define GEMSS_VPSLLI_128(A,i) _mm256_slli_si256(A,i)

    #define GEMSS_VPSRLI_16(A,i) _mm256_srli_epi16(A,i)
    #define GEMSS_VPSRLI_32(A,i) _mm256_srli_epi32(A,i)
    #define GEMSS_VPSRLI_64(A,i) _mm256_srli_epi64(A,i)
    #define GEMSS_VPSRLI_128(A,i) _mm256_srli_si256(A,i)

    /* Use: "one=GEMSS_VPSET1_8(1);" to initialize the variable one */
    #define GEMSS_VPMASK8_ONE(x,one) _mm256_cmpeq_epi8(x,one)
    /* Use: "one=GEMSS_VPSET1_16(1);" to initialize the variable one */
    #define GEMSS_VPMASK16_ONE(x,one) _mm256_cmpeq_epi16(x,one)
    /* Use: "one=GEMSS_VPSET1_32(1);" to initialize the variable one */
    #define GEMSS_VPMASK32_ONE(x,one) _mm256_cmpeq_epi32(x,one)
    /* Use: "one=GEMSS_VPSET1_64(1);" to initialize the variable one */
    #define GEMSS_VPMASK64_ONE(x,one) _mm256_cmpeq_epi64(x,one)

    /* Shuffle */
    #define GEMSS_VPSHUFFLE_8(A,B) _mm256_shuffle_epi8(A,B)

    /* Unpack */
    #define GEMSS_VPUNPACKLO_8(A,B) _mm256_unpacklo_epi8(A,B)
    #define GEMSS_VPUNPACKLO_16(A,B) _mm256_unpacklo_epi16(A,B)

    #define GEMSS_VPUNPACKHI_8(A,B) _mm256_unpackhi_epi8(A,B)
    #define GEMSS_VPUNPACKHI_16(A,B) _mm256_unpackhi_epi16(A,B)

    /* Permute */
    #define GEMSS_VPPERMUTE4x64(A,i) _mm256_permute4x64_epi64(A,i)
    #define GEMSS_VPPERMUTE2x128(A,B,i) _mm256_permute2x128_si256(A,B,i)


    /*** We implement here other functions ***/


    /* Here, a 256-bit register is splitted in four 64-bit registers: 3|2|1|0.
       The next operations change the order of these registers. */

    /* Rotate Through Carry Left, Rotate Through Carry Right (circular shift) */
    #define GEMSS_VPPERMUTE4x64_0321(A) GEMSS_VPPERMUTE4x64(A,0x39)
    #define GEMSS_VPPERMUTE4x64_1032(A) GEMSS_VPPERMUTE4x64(A,0x4E)
    #define GEMSS_VPPERMUTE4x64_2103(A) GEMSS_VPPERMUTE4x64(A,0x93)

    /* Duplicate one of the four 64-bit registers. */
    #define GEMSS_VPPERMUTE4x64_0000(A) GEMSS_VPPERMUTE4x64(A,0)
    #define GEMSS_VPPERMUTE4x64_1111(A) GEMSS_VPPERMUTE4x64(A,0x55)
    #define GEMSS_VPPERMUTE4x64_2222(A) GEMSS_VPPERMUTE4x64(A,0xAA)
    #define GEMSS_VPPERMUTE4x64_3333(A) GEMSS_VPPERMUTE4x64(A,0xFF)
#endif


#if (defined(GEMSS_ENABLED_AVX)||defined(GEMSS_ENABLED_AVX2))
    /*** We implement here other functions ***/
    #define GEMSS_VPSET_128(A1,A0) GEMSS_VPINSERT_128(GEMSS_PCVT_256(A0),A1)

    #define GEMSS_VPAND1_2(C,A) C=GEMSS_VPAND_(A,C);

    #define GEMSS_VPXOR1_(C,A,B) C=GEMSS_VPXOR_(A,B);
    #define GEMSS_VPXOR2_(C1,C2,A1,A2,B1,B2) \
        GEMSS_VPXOR1_(C1,A1,B1)\
        GEMSS_VPXOR1_(C2,A2,B2)
    #define GEMSS_VPXOR3_(C1,C2,C3,A1,A2,A3,B1,B2,B3) \
        GEMSS_VPXOR1_(C1,A1,B1)\
        GEMSS_VPXOR1_(C2,A2,B2)\
        GEMSS_VPXOR1_(C3,A3,B3)
    #define GEMSS_VPXOR4_(C1,C2,C3,C4,A1,A2,A3,A4,B1,B2,B3,B4) \
        GEMSS_VPXOR1_(C1,A1,B1)\
        GEMSS_VPXOR1_(C2,A2,B2)\
        GEMSS_VPXOR1_(C3,A3,B3)\
        GEMSS_VPXOR1_(C4,A4,B4)

    #define GEMSS_VPXOR1_2(C,A) C=GEMSS_VPXOR_(A,C);
    #define GEMSS_VPXOR2_2(C1,C2,A1,A2) \
        GEMSS_VPXOR1_2(C1,A1)\
        GEMSS_VPXOR1_2(C2,A2)
    #define GEMSS_VPXOR3_2(C1,C2,C3,A1,A2,A3) \
        GEMSS_VPXOR1_2(C1,A1)\
        GEMSS_VPXOR1_2(C2,A2)\
        GEMSS_VPXOR1_2(C3,A3)
    #define GEMSS_VPXOR4_2(C1,C2,C3,C4,A1,A2,A3,A4) \
        GEMSS_VPXOR1_2(C1,A1)\
        GEMSS_VPXOR1_2(C2,A2)\
        GEMSS_VPXOR1_2(C3,A3)\
        GEMSS_VPXOR1_2(C4,A4)
#endif


#ifdef GEMSS_ENABLED_PCLMUL
    /* Carry less multiplication */
    #define GEMSS_PCLMUL(A,B,i) _mm_clmulepi64_si128(A,B,i)
#endif


/* Hamming weight, sum of the bits */
#ifdef GEMSS_ENABLED_POPCNT
    #ifdef GEMSS_MODE_64_BITS
        #define GEMSS_POPCNT_U64 _mm_popcnt_u64
    #elif defined(GEMSS_MODE_32_BITS) 
        #define GEMSS_POPCNT_U32 _mm_popcnt_u32
    #endif
#endif



#endif

