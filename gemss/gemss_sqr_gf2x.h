#ifndef _SQR_GF2X_H
#define _SQR_GF2X_H

#include <stdint.h>
#include "gemss_prefix_name.h"
#include "gemss_arch.h"

/* Squaring in GF(2)[x] */
/* (a+b*x^64)^2 = a^2 + (b^2)*x^128 */
/* The squaring is equivalent to put a zero bit between each bit */


/* Difference between SQR32 and SQR64LOW:
    - SQR32: we assume the 32-bit higher part of A is 0.
    - SQR64LOW: we do not the previous assumption.
*/


/***********************************************************************/
/***********************************************************************/
/********************** version without vectorization ******************/
/***********************************************************************/
/***********************************************************************/


/* Assume we want to insert a null bit between each bit of 0x00000000FFFFFFFF.
   We do as following:
    0x00000000FFFFFFFF (it is already an insertion of a zero 32-bit packed)
    0x0000FFFF0000FFFF (insertion by pack of 16 bits)
    0x00FF00FF00FF00FF (insertion by pack of 8 bits)
    0x0F0F0F0F0F0F0F0F (insertion by pack of 4 bits)
    0x3333333333333333 (insertion by pack of 2 bits)
    0x5555555555555555 (insertion by pack of 1 bit)
*/


uint64_t GEMSS_PREFIX_NAME(GEMSS_sqr32_no_simd_gf2x)(uint64_t A);
uint64_t GEMSS_PREFIX_NAME(GEMSS_sqr64low_no_simd_gf2x)(uint64_t A);
#define GEMSS_sqr32_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr32_no_simd_gf2x)
#define GEMSS_sqr64low_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr64low_no_simd_gf2x)


/* log_2(32)*3 = 5*3 = 15 instructions */
#define GEMSS_SQR32_NO_SIMD_GF2X(C,A) \
    (C)=((A)^(((uint64_t)(A))<<16))&((uint64_t)0x0000FFFF0000FFFF);\
    (C)=((C)^((C)<<8))&((uint64_t)0x00FF00FF00FF00FF);\
    (C)=((C)^((C)<<4))&((uint64_t)0x0F0F0F0F0F0F0F0F);\
    (C)=((C)^((C)<<2))&((uint64_t)0x3333333333333333);\
    (C)=((C)^((C)<<1))&((uint64_t)0x5555555555555555);

/* 1+log_2(32)*3 = 1+5*3 = 16 instructions */
#define GEMSS_SQR64LOW_NO_SIMD_GF2X(C,A) \
    (C)=(((A)&((uint64_t)0xFFFFFFFF))^((A)<<16))\
        &((uint64_t)0x0000FFFF0000FFFF);\
    (C)=((C)^((C)<<8))&((uint64_t)0x00FF00FF00FF00FF);\
    (C)=((C)^((C)<<4))&((uint64_t)0x0F0F0F0F0F0F0F0F);\
    (C)=((C)^((C)<<2))&((uint64_t)0x3333333333333333);\
    (C)=((C)^((C)<<1))&((uint64_t)0x5555555555555555);

#define GEMSS_SQR64_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR32_NO_SIMD_GF2X((C)[1],(A)>>32);\
    GEMSS_SQR64LOW_NO_SIMD_GF2X((C)[0],A);

#define GEMSS_SQR96_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR32_NO_SIMD_GF2X((C)[2],(A)[1]);\
    GEMSS_SQR64_NO_SIMD_GF2X(C,(A)[0]);

#define GEMSS_SQR128_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR64_NO_SIMD_GF2X(C+2,(A)[1]);\
    GEMSS_SQR64_NO_SIMD_GF2X(C,(A)[0]);

#define GEMSS_SQR160_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR32_NO_SIMD_GF2X((C)[4],(A)[2]);\
    GEMSS_SQR128_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR192_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR64_NO_SIMD_GF2X(C+4,(A)[2]);\
    GEMSS_SQR128_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR224_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR96_NO_SIMD_GF2X(C+4,A+2);\
    GEMSS_SQR128_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR256_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR128_NO_SIMD_GF2X(C+4,A+2);\
    GEMSS_SQR128_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR288_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR32_NO_SIMD_GF2X((C)[8],(A)[4]);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR320_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR64_NO_SIMD_GF2X(C+8,(A)[4]);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR352_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR96_NO_SIMD_GF2X(C+8,A+4);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR384_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR128_NO_SIMD_GF2X(C+8,A+4);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR416_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR160_NO_SIMD_GF2X(C+8,A+4);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR448_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR192_NO_SIMD_GF2X(C+8,A+4);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR480_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR224_NO_SIMD_GF2X(C+8,A+4);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR512_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR256_NO_SIMD_GF2X(C+8,A+4);\
    GEMSS_SQR256_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR544_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR32_NO_SIMD_GF2X((C)[16],(A)[8]);\
    GEMSS_SQR512_NO_SIMD_GF2X(C,A);

#define GEMSS_SQR576_NO_SIMD_GF2X(C,A) \
    GEMSS_SQR64_NO_SIMD_GF2X(C+16,(A)[8]);\
    GEMSS_SQR512_NO_SIMD_GF2X(C,A);


/***********************************************************************/
/***********************************************************************/
/*************************** sse2 version ******************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_SSE2
    uint64_t GEMSS_PREFIX_NAME(GEMSS_psqr64low_gf2x)(uint64_t A);
    void GEMSS_PREFIX_NAME(GEMSS_psqr64_gf2x)(uint64_t C[2], const uint64_t A[1]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr96_gf2x)(uint64_t C[3], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr128_gf2x)(uint64_t C[4], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr160_gf2x)(uint64_t C[5], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr192_gf2x)(uint64_t C[6], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr224_gf2x)(uint64_t C[7], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr256_gf2x)(uint64_t C[8], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr288_gf2x)(uint64_t C[9], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr320_gf2x)(uint64_t C[10], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr352_gf2x)(uint64_t C[11], const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr384_gf2x)(uint64_t C[12], const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr416_gf2x)(uint64_t C[13], const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr448_gf2x)(uint64_t C[14], const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr480_gf2x)(uint64_t C[15], const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr512_gf2x)(uint64_t C[16], const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr544_gf2x)(uint64_t C[17], const uint64_t A[9]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr576_gf2x)(uint64_t C[18], const uint64_t A[9]);

    #define GEMSS_psqr64low_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr64low_gf2x)
    #define GEMSS_psqr32_gf2x GEMSS_psqr64low_gf2x
    #define GEMSS_psqr64_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr64_gf2x)
    #define GEMSS_psqr96_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr96_gf2x)
    #define GEMSS_psqr128_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr128_gf2x)
    #define GEMSS_psqr160_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr160_gf2x)
    #define GEMSS_psqr192_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr192_gf2x)
    #define GEMSS_psqr224_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr224_gf2x)
    #define GEMSS_psqr256_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr256_gf2x)
    #define GEMSS_psqr288_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr288_gf2x)
    #define GEMSS_psqr320_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr320_gf2x)
    #define GEMSS_psqr352_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr352_gf2x)
    #define GEMSS_psqr384_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr384_gf2x)
    #define GEMSS_psqr416_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr416_gf2x)
    #define GEMSS_psqr448_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr448_gf2x)
    #define GEMSS_psqr480_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr480_gf2x)
    #define GEMSS_psqr512_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr512_gf2x)
    #define GEMSS_psqr544_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr544_gf2x)
    #define GEMSS_psqr576_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr576_gf2x)
#endif


/* 11 instructions */
#define GEMSS_PSQR64_LO_GF2X(C1,A1,RA,R1) \
    R1=GEMSS_PUNPACKLO_8(A1,RA);\
    C1=GEMSS_PAND_(R1,GEMSS_PSET1_8(0xF));\
    R1=GEMSS_PAND_(GEMSS_PXOR_(C1,GEMSS_PSLLI_16(C1,2)),GEMSS_PSET1_8(0x33));\
    C1=GEMSS_PAND_(GEMSS_PXOR_(R1,GEMSS_PSLLI_16(R1,1)),GEMSS_PSET1_8(0x55));

/* 11 instructions */
#define GEMSS_PSQR64_HI_GF2X(C1,A1,RA,R1) \
    R1=GEMSS_PUNPACKHI_8(A1,RA);\
    C1=GEMSS_PAND_(R1,GEMSS_PSET1_8(0xF));\
    R1=GEMSS_PAND_(GEMSS_PXOR_(C1,GEMSS_PSLLI_16(C1,2)),GEMSS_PSET1_8(0x33));\
    C1=GEMSS_PAND_(GEMSS_PXOR_(R1,GEMSS_PSLLI_16(R1,1)),GEMSS_PSET1_8(0x55));

/* 12 instructions */
#define GEMSS_PSQR64_GF2X(C1,A1,RA,R1) \
    RA=GEMSS_PSRLI_16(A1,4);\
    R1=GEMSS_PUNPACKLO_8(A1,RA);\
    C1=GEMSS_PAND_(R1,GEMSS_PSET1_8(0xF));\
    R1=GEMSS_PAND_(GEMSS_PXOR_(C1,GEMSS_PSLLI_16(C1,2)),GEMSS_PSET1_8(0x33));\
    C1=GEMSS_PAND_(GEMSS_PXOR_(R1,GEMSS_PSLLI_16(R1,1)),GEMSS_PSET1_8(0x55));

#define GEMSS_PSQR128_GF2X(C1,C2,A1,RA,R1) \
    RA=GEMSS_PSRLI_16(A1,4);\
    GEMSS_PSQR64_LO_GF2X(C1,A1,RA,R1);\
    GEMSS_PSQR64_HI_GF2X(C2,A1,RA,R1);

#define GEMSS_PSQR192_GF2X(C1,C2,C3,A1,A2,RA,R1) \
    GEMSS_PSQR128_GF2X(C1,C2,A1,RA,R1);\
    GEMSS_PSQR64_GF2X(C3,A2,RA,R1);

#define GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1) \
    GEMSS_PSQR128_GF2X(C1,C2,A1,RA,R1);\
    GEMSS_PSQR128_GF2X(C3,C4,A2,RA,R1);

#define GEMSS_PSQR320_GF2X(C1,C2,C3,C4,C5,A1,A2,A3,RA,R1) \
    GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1);\
    GEMSS_PSQR64_GF2X(C5,A3,RA,R1);

#define GEMSS_PSQR384_GF2X(C1,C2,C3,C4,C5,C6,A1,A2,A3,RA,R1) \
    GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1);\
    GEMSS_PSQR128_GF2X(C5,C6,A3,RA,R1);

#define GEMSS_PSQR448_GF2X(C1,C2,C3,C4,C5,C6,C7,A1,A2,A3,A4,RA,R1) \
    GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1);\
    GEMSS_PSQR192_GF2X(C5,C6,C7,A3,A4,RA,R1);

#define GEMSS_PSQR512_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A1,A2,A3,A4,RA,R1) \
    GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1);\
    GEMSS_PSQR256_GF2X(C5,C6,C7,C8,A3,A4,RA,R1);

#define GEMSS_PSQR576_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A1,A2,A3,A4,A5,RA,R1) \
    GEMSS_PSQR512_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A1,A2,A3,A4,RA,R1);\
    GEMSS_PSQR64_GF2X(C9,A5,RA,R1);


/***********************************************************************/
/***********************************************************************/
/*************************** shuffle version ***************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_SSSE3
    uint64_t GEMSS_PREFIX_NAME(GEMSS_psqr64low_shuffle_gf2x)(uint64_t A);
    void GEMSS_PREFIX_NAME(GEMSS_psqr64_shuffle_gf2x)(uint64_t C[2], const uint64_t A[1]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr96_shuffle_gf2x)(uint64_t C[3], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr128_shuffle_gf2x)(uint64_t C[4], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr160_shuffle_gf2x)(uint64_t C[5], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr192_shuffle_gf2x)(uint64_t C[6], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr224_shuffle_gf2x)(uint64_t C[7], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr256_shuffle_gf2x)(uint64_t C[8], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr288_shuffle_gf2x)(uint64_t C[9], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr320_shuffle_gf2x)(uint64_t C[10], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr352_shuffle_gf2x)(uint64_t C[11], const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr384_shuffle_gf2x)(uint64_t C[12], const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr416_shuffle_gf2x)(uint64_t C[13], const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr448_shuffle_gf2x)(uint64_t C[14], const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr480_shuffle_gf2x)(uint64_t C[15], const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr512_shuffle_gf2x)(uint64_t C[16], const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr544_shuffle_gf2x)(uint64_t C[17], const uint64_t A[9]);
    void GEMSS_PREFIX_NAME(GEMSS_psqr576_shuffle_gf2x)(uint64_t C[18], const uint64_t A[9]);


    #define GEMSS_psqr64low_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr64low_shuffle_gf2x)
    #define GEMSS_psqr32_shuffle_gf2x GEMSS_psqr64low_shuffle_gf2x
    #define GEMSS_psqr64_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr64_shuffle_gf2x)
    #define GEMSS_psqr96_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr96_shuffle_gf2x)
    #define GEMSS_psqr128_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr128_shuffle_gf2x)
    #define GEMSS_psqr160_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr160_shuffle_gf2x)
    #define GEMSS_psqr192_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr192_shuffle_gf2x)
    #define GEMSS_psqr224_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr224_shuffle_gf2x)
    #define GEMSS_psqr256_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr256_shuffle_gf2x)
    #define GEMSS_psqr288_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr288_shuffle_gf2x)
    #define GEMSS_psqr320_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr320_shuffle_gf2x)
    #define GEMSS_psqr352_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr352_shuffle_gf2x)
    #define GEMSS_psqr384_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr384_shuffle_gf2x)
    #define GEMSS_psqr416_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr416_shuffle_gf2x)
    #define GEMSS_psqr448_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr448_shuffle_gf2x)
    #define GEMSS_psqr480_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr480_shuffle_gf2x)
    #define GEMSS_psqr512_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr512_shuffle_gf2x)
    #define GEMSS_psqr544_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr544_shuffle_gf2x)
    #define GEMSS_psqr576_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_psqr576_shuffle_gf2x)
#endif


#define GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T) \
    M=GEMSS_PSET1_8(0x0F);\
    T=GEMSS_PSET_64((uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100);

/* 6 instructions */
#define GEMSS_PSQR64_SHUFFLE_V1_GF2X(E0,A128,M,T) \
    {__m128i C0,C1,D0,D1;\
    C0=GEMSS_PAND_(A128,M);\
    C1=GEMSS_PAND_(GEMSS_PSRLI_16(A128,4),M);\
\
    D0=GEMSS_PSHUFFLE_8(T,C0);\
    D1=GEMSS_PSHUFFLE_8(T,C1);\
\
    E0=GEMSS_PUNPACKLO_8(D0,D1);}

/* 4 instructions, faster than GEMSS_PSQR64_SHUFFLE_V1_GF2X */
#define GEMSS_PSQR64_SHUFFLE_GF2X(E0,A128,M,T) \
    {__m128i C0,D0;\
    E0=GEMSS_PSRLI_16(A128,4);\
    C0=GEMSS_PUNPACKLO_8(A128,E0);\
    D0=GEMSS_PAND_(C0,M);\
    E0=GEMSS_PSHUFFLE_8(T,D0);}

/* 7 instructions */
#define GEMSS_PSQR128_SHUFFLE_V1_GF2X(E0,E1,A128,M,T) \
    {__m128i C0,C1,D0,D1;\
    E0=GEMSS_PSRLI_16(A128,4);\
\
    C0=GEMSS_PUNPACKLO_8(A128,E0);\
    C1=GEMSS_PUNPACKHI_8(A128,E0);\
\
    D0=GEMSS_PAND_(C0,M);\
    D1=GEMSS_PAND_(C1,M);\
\
    E0=GEMSS_PSHUFFLE_8(T,D0);\
    E1=GEMSS_PSHUFFLE_8(T,D1);}

/* 7 instructions, faster than GEMSS_PSQR128_SHUFFLE_V1_GF2X */
#define GEMSS_PSQR128_SHUFFLE_GF2X(E0,E1,A128,M,T) \
    {__m128i C0,C1,D0,D1;\
    C0=GEMSS_PAND_(A128,M);\
    C1=GEMSS_PAND_(GEMSS_PSRLI_16(A128,4),M);\
\
    D0=GEMSS_PSHUFFLE_8(T,C0);\
    D1=GEMSS_PSHUFFLE_8(T,C1);\
\
    E0=GEMSS_PUNPACKLO_8(D0,D1);\
    E1=GEMSS_PUNPACKHI_8(D0,D1);}

/* General macros */
#define GEMSS_PSQR192_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T) \
    GEMSS_PSQR128_SHUFFLE_GF2X(E1,E2,A1,M,T);\
    GEMSS_PSQR64_SHUFFLE_GF2X(E3,A2,M,T);

#define GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T) \
    GEMSS_PSQR128_SHUFFLE_GF2X(E1,E2,A1,M,T);\
    GEMSS_PSQR128_SHUFFLE_GF2X(E3,E4,A2,M,T);

#define GEMSS_PSQR320_SHUFFLE_GF2X(E1,E2,E3,E4,E5,A1,A2,A3,M,T) \
    GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);\
    GEMSS_PSQR64_SHUFFLE_GF2X(E5,A3,M,T);

#define GEMSS_PSQR384_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,A1,A2,A3,M,T) \
    GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);\
    GEMSS_PSQR128_SHUFFLE_GF2X(E5,E6,A3,M,T);

#define GEMSS_PSQR448_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,A1,A2,A3,A4,M,T) \
    GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);\
    GEMSS_PSQR192_SHUFFLE_GF2X(E5,E6,E7,A3,A4,M,T);

#define GEMSS_PSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,A1,A2,A3,A4,M,T) \
    GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);\
    GEMSS_PSQR256_SHUFFLE_GF2X(E5,E6,E7,E8,A3,A4,M,T);

#define GEMSS_PSQR576_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,E9,A1,A2,A3,A4,A5,M,T) \
    GEMSS_PSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,A1,A2,A3,A4,M,T);\
    GEMSS_PSQR64_SHUFFLE_GF2X(E9,A5,M,T);


#ifdef GEMSS_ENABLED_AVX2
    uint64_t GEMSS_PREFIX_NAME(GEMSS_vpsqr64low_shuffle_gf2x)(uint64_t A);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr64_shuffle_gf2x)(uint64_t C[2], const uint64_t A[1]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr96_shuffle_gf2x)(uint64_t C[3], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr128_shuffle_gf2x)(uint64_t C[4], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr160_shuffle_gf2x)(uint64_t C[5], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr192_shuffle_gf2x)(uint64_t C[6], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr224_shuffle_gf2x)(uint64_t C[7], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr256_shuffle_gf2x)(uint64_t C[8], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr288_shuffle_gf2x)(uint64_t C[9], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr320_shuffle_gf2x)(uint64_t C[10],const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr352_shuffle_gf2x)(uint64_t C[11],const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr384_shuffle_gf2x)(uint64_t C[12],const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr416_shuffle_gf2x)(uint64_t C[13],const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr448_shuffle_gf2x)(uint64_t C[14],const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr480_shuffle_gf2x)(uint64_t C[15],const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr512_shuffle_gf2x)(uint64_t C[16],const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr544_shuffle_gf2x)(uint64_t C[17],const uint64_t A[9]);
    void GEMSS_PREFIX_NAME(GEMSS_vpsqr576_shuffle_gf2x)(uint64_t C[18],const uint64_t A[9]);

    #define GEMSS_vpsqr64low_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr64low_shuffle_gf2x)
    #define GEMSS_vpsqr32_shuffle_gf2x GEMSS_vpsqr64low_shuffle_gf2x
    #define GEMSS_vpsqr64_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr64_shuffle_gf2x)
    #define GEMSS_vpsqr96_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr96_shuffle_gf2x)
    #define GEMSS_vpsqr128_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr128_shuffle_gf2x)
    #define GEMSS_vpsqr160_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr160_shuffle_gf2x)
    #define GEMSS_vpsqr192_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr192_shuffle_gf2x)
    #define GEMSS_vpsqr224_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr224_shuffle_gf2x)
    #define GEMSS_vpsqr256_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr256_shuffle_gf2x)
    #define GEMSS_vpsqr288_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr288_shuffle_gf2x)
    #define GEMSS_vpsqr320_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr320_shuffle_gf2x)
    #define GEMSS_vpsqr352_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr352_shuffle_gf2x)
    #define GEMSS_vpsqr384_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr384_shuffle_gf2x)
    #define GEMSS_vpsqr416_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr416_shuffle_gf2x)
    #define GEMSS_vpsqr448_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr448_shuffle_gf2x)
    #define GEMSS_vpsqr480_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr480_shuffle_gf2x)
    #define GEMSS_vpsqr512_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr512_shuffle_gf2x)
    #define GEMSS_vpsqr544_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr544_shuffle_gf2x)
    #define GEMSS_vpsqr576_shuffle_gf2x GEMSS_PREFIX_NAME(GEMSS_vpsqr576_shuffle_gf2x)
#endif


#define GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T) \
    M=GEMSS_VPSET1_8(0x0F);\
    T=GEMSS_VPSET_64((uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100,\
               (uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100);

/* 4 instructions */
#define GEMSS_VPSQR64_SHUFFLE_GF2X(E0,A256,M,T) \
    {__m256i B1,C0,D0;\
    B1=GEMSS_VPSRLI_16(A256,4);\
    C0=GEMSS_VPUNPACKLO_8(A256,B1);\
    D0=GEMSS_VPAND_(C0,M);\
    E0=GEMSS_VPSHUFFLE_8(T,D0);}

/* 5 instructions */
#define GEMSS_VPSQR128_SHUFFLE_GF2X(E0,A256,M,T) \
    {__m256i B0,B1,C0,D0;\
    B0=GEMSS_VPPERMUTE4x64(A256,0xD8);\
    B1=GEMSS_VPSRLI_16(B0,4);\
    C0=GEMSS_VPUNPACKLO_8(B0,B1);\
    D0=GEMSS_VPAND_(C0,M);\
    E0=GEMSS_VPSHUFFLE_8(T,D0);}

/* unpack after */
/* 9 instructions */
#define GEMSS_VPSQR256_SHUFFLE_V1_GF2X(E0,E1,A256,M,T) \
    {__m256i B0,B1,C0,C1,D0,D1;\
    B0=GEMSS_VPAND_(A256,M);\
    B1=GEMSS_VPAND_(GEMSS_VPSRLI_16(A256,4),M);\
\
    C0=GEMSS_VPSHUFFLE_8(T,B0);\
    C1=GEMSS_VPSHUFFLE_8(T,B1);\
\
    D0=GEMSS_VPUNPACKLO_8(C0,C1);\
    D1=GEMSS_VPUNPACKHI_8(C0,C1);\
\
    E0=GEMSS_VPPERMUTE2x128(D0,D1,0x20);\
    E1=GEMSS_VPPERMUTE2x128(D0,D1,0x31);}

/* unpack before */
/* 8 instructions, faster than GEMSS_VPSQR256_SHUFFLE_V1_GF2X */
#define GEMSS_VPSQR256_SHUFFLE_GF2X(E0,E1,A256,M,T) \
    {__m256i B0,B1,C0,C1,D0,D1;\
    B0=GEMSS_VPPERMUTE4x64(A256,0xD8);\
    B1=GEMSS_VPSRLI_16(B0,4);\
\
    C0=GEMSS_VPUNPACKLO_8(B0,B1);\
    C1=GEMSS_VPUNPACKHI_8(B0,B1);\
\
    D0=GEMSS_VPAND_(C0,M);\
    D1=GEMSS_VPAND_(C1,M);\
\
    E0=GEMSS_VPSHUFFLE_8(T,D0);\
    E1=GEMSS_VPSHUFFLE_8(T,D1);}

#define GEMSS_VPSQR192_SHUFFLE_GF2X GEMSS_VPSQR256_SHUFFLE_GF2X

#define GEMSS_VPSQR320_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T) \
            GEMSS_VPSQR256_SHUFFLE_GF2X(E1,E2,A1,M,T);\
            GEMSS_VPSQR64_SHUFFLE_GF2X(E3,A2,M,T);

#define GEMSS_VPSQR384_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T) \
            GEMSS_VPSQR256_SHUFFLE_GF2X(E1,E2,A1,M,T);\
            GEMSS_VPSQR128_SHUFFLE_GF2X(E3,A2,M,T);

#define GEMSS_VPSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T) \
            GEMSS_VPSQR256_SHUFFLE_GF2X(E1,E2,A1,M,T);\
            GEMSS_VPSQR256_SHUFFLE_GF2X(E3,E4,A2,M,T);

#define GEMSS_VPSQR448_SHUFFLE_GF2X GEMSS_VPSQR512_SHUFFLE_GF2X

#define GEMSS_VPSQR576_SHUFFLE_GF2X(E1,E2,E3,E4,E5,A1,A2,A3,M,T) \
            GEMSS_VPSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);\
            GEMSS_VPSQR64_SHUFFLE_GF2X(E5,A3,M,T);


/***********************************************************************/
/***********************************************************************/
/**************************** pclmul version ***************************/
/***********************************************************************/
/***********************************************************************/


/* Here, A is an integer */
#define GEMSS_sqr64low_inlined_pclmul_gf2x(C,A) \
    GEMSS_PCVT_64(C,GEMSS_PCLMUL(GEMSS_PSETL_64(A),GEMSS_PSETL_64(A),0))

/* The pclmul instruction does not exploit that the 32 last bits are null */
#define GEMSS_sqr32_inlined_pclmul_gf2x GEMSS_sqr64low_inlined_pclmul_gf2x

/* Here, A is an integer and C is a pointer */
#define GEMSS_sqr64_inlined2_pclmul_gf2x(C,A) \
    GEMSS_PSTORE128(C,GEMSS_PCLMUL(GEMSS_PSETL_64(A),GEMSS_PSETL_64(A),0))

/* Here, A,C are pointers */
#define GEMSS_sqr64_inlined_pclmul_gf2x(C,A) \
    GEMSS_PSTORE128(C,GEMSS_PCLMUL(GEMSS_PLOADL(A),GEMSS_PLOADL(A),0))


#ifdef GEMSS_ENABLED_PCLMUL
    uint64_t GEMSS_PREFIX_NAME(GEMSS_sqr64low_pclmul_gf2x)(uint64_t A);
    void GEMSS_PREFIX_NAME(GEMSS_sqr64_pclmul_gf2x)(uint64_t C[2], const uint64_t A[1]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr96_pclmul_gf2x)(uint64_t C[3], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr128_pclmul_gf2x)(uint64_t C[4], const uint64_t A[2]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr160_pclmul_gf2x)(uint64_t C[5], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr192_pclmul_gf2x)(uint64_t C[6], const uint64_t A[3]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr224_pclmul_gf2x)(uint64_t C[7], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr256_pclmul_gf2x)(uint64_t C[8], const uint64_t A[4]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr288_pclmul_gf2x)(uint64_t C[9], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr320_pclmul_gf2x)(uint64_t C[10], const uint64_t A[5]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr352_pclmul_gf2x)(uint64_t C[11], const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr384_pclmul_gf2x)(uint64_t C[12], const uint64_t A[6]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr416_pclmul_gf2x)(uint64_t C[13], const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr448_pclmul_gf2x)(uint64_t C[14], const uint64_t A[7]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr480_pclmul_gf2x)(uint64_t C[15], const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr512_pclmul_gf2x)(uint64_t C[16], const uint64_t A[8]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr544_pclmul_gf2x)(uint64_t C[17], const uint64_t A[9]);
    void GEMSS_PREFIX_NAME(GEMSS_sqr576_pclmul_gf2x)(uint64_t C[18], const uint64_t A[9]);

    #define GEMSS_sqr64low_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr64low_pclmul_gf2x)
    #define GEMSS_sqr32_pclmul_gf2x GEMSS_sqr64low_pclmul_gf2x
    #define GEMSS_sqr64_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr64_pclmul_gf2x)
    #define GEMSS_sqr96_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr96_pclmul_gf2x)
    #define GEMSS_sqr128_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr128_pclmul_gf2x)
    #define GEMSS_sqr160_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr160_pclmul_gf2x)
    #define GEMSS_sqr192_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr192_pclmul_gf2x)
    #define GEMSS_sqr224_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr224_pclmul_gf2x)
    #define GEMSS_sqr256_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr256_pclmul_gf2x)
    #define GEMSS_sqr288_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr288_pclmul_gf2x)
    #define GEMSS_sqr320_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr320_pclmul_gf2x)
    #define GEMSS_sqr352_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr352_pclmul_gf2x)
    #define GEMSS_sqr384_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr384_pclmul_gf2x)
    #define GEMSS_sqr416_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr416_pclmul_gf2x)
    #define GEMSS_sqr448_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr448_pclmul_gf2x)
    #define GEMSS_sqr480_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr480_pclmul_gf2x)
    #define GEMSS_sqr512_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr512_pclmul_gf2x)
    #define GEMSS_sqr544_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr544_pclmul_gf2x)
    #define GEMSS_sqr576_pclmul_gf2x GEMSS_PREFIX_NAME(GEMSS_sqr576_pclmul_gf2x)
#endif


/***********************************************************************/
/***********************************************************************/
/********************** store at the end version ***********************/
/***********************************************************************/
/***********************************************************************/


/* WS: without store */
/* 1 pclmul */
#define GEMSS_SQR64_WS_PCLMUL_GF2X(z,x,pos) \
    z=GEMSS_PCLMUL(x,x,pos);

/* 2 pclmul */
#define GEMSS_SQR128_WS_PCLMUL_GF2X(z1,z2,x) \
    GEMSS_SQR64_WS_PCLMUL_GF2X(z1,x,0);\
    GEMSS_SQR64_WS_PCLMUL_GF2X(z2,x,17);

/* 3 pclmul */
#define GEMSS_SQR192_WS_PCLMUL_GF2X(z1,z2,z3,x1,x2) \
    GEMSS_SQR128_WS_PCLMUL_GF2X(z1,z2,x1);\
    GEMSS_SQR64_WS_PCLMUL_GF2X(z3,x2,0);

/* 4 pclmul */
#define GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2) \
    GEMSS_SQR128_WS_PCLMUL_GF2X(z1,z2,x1);\
    GEMSS_SQR128_WS_PCLMUL_GF2X(z3,z4,x2);

/* 5 pclmul */
#define GEMSS_SQR320_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,x1,x2,x3) \
    GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2);\
    GEMSS_SQR64_WS_PCLMUL_GF2X(z5,x3,0);

/* 6 pclmul */
#define GEMSS_SQR384_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,x1,x2,x3) \
    GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2);\
    GEMSS_SQR128_WS_PCLMUL_GF2X(z5,z6,x3);

/* 7 pclmul */
#define GEMSS_SQR448_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,x1,x2,x3,x4) \
    GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2);\
    GEMSS_SQR192_WS_PCLMUL_GF2X(z5,z6,z7,x3,x4);

/* 8 pclmul */
#define GEMSS_SQR512_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,x1,x2,x3,x4) \
    GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2);\
    GEMSS_SQR256_WS_PCLMUL_GF2X(z5,z6,z7,z8,x3,x4);

/* 9 pclmul */
#define GEMSS_SQR576_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,z9,x1,x2,x3,x4,x5) \
    GEMSS_SQR512_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,x1,x2,x3,x4);\
    GEMSS_SQR64_WS_PCLMUL_GF2X(z9,x5,0);


/***********************************************************************/
/***********************************************************************/
/********************** square and store version ***********************/
/***********************************************************************/
/***********************************************************************/


/* 1 pclmul */
#define GEMSS_SQR64LOW_PCLMUL_GF2X(C,x,pos) GEMSS_PCVT_64(C,GEMSS_PCLMUL(x,x,pos))
#define GEMSS_SQR64LOW_TAB_PCLMUL_GF2X(C,x,pos) GEMSS_PSTOREL(C,GEMSS_PCLMUL(x,x,pos))

#define GEMSS_SQR32_PCLMUL_GF2X(C,x) GEMSS_SQR64LOW_PCLMUL_GF2X(C,x,0)

#define GEMSS_SQR64_PCLMUL_GF2X(C,x,z,pos) \
    GEMSS_SQR64_WS_PCLMUL_GF2X(z,x,pos);\
    GEMSS_PSTORE128(C,z);

/* 2 pclmul */
#define GEMSS_SQR96_PCLMUL_GF2X(C,x,z) \
    GEMSS_SQR64_PCLMUL_GF2X(C,x,z,0);\
    GEMSS_SQR64LOW_TAB_PCLMUL_GF2X(C+2,x,17);

#define GEMSS_SQR128_PCLMUL_GF2X(C,x,z) \
    GEMSS_SQR64_PCLMUL_GF2X(C,x,z,0);\
    GEMSS_SQR64_PCLMUL_GF2X(C+2,x,z,17);

/* 3 pclmul */
#define GEMSS_SQR160_PCLMUL_GF2X(C,x1,x2,z) \
    GEMSS_SQR128_PCLMUL_GF2X(C,x1,z);\
    GEMSS_SQR64LOW_TAB_PCLMUL_GF2X(C+4,x2,0);

#define GEMSS_SQR192_PCLMUL_GF2X(C,x1,x2,z) \
    GEMSS_SQR128_PCLMUL_GF2X(C,x1,z);\
    GEMSS_SQR64_PCLMUL_GF2X(C+4,x2,z,0);

/* 4 pclmul */
#define GEMSS_SQR224_PCLMUL_GF2X(C,x1,x2,z) \
    GEMSS_SQR128_PCLMUL_GF2X(C,x1,z);\
    GEMSS_SQR96_PCLMUL_GF2X(C+4,x2,z);

#define GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z) \
    GEMSS_SQR128_PCLMUL_GF2X(C,x1,z);\
    GEMSS_SQR128_PCLMUL_GF2X(C+4,x2,z);

/* 5 pclmul */
#define GEMSS_SQR288_PCLMUL_GF2X(C,x1,x2,x3,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR64LOW_TAB_PCLMUL_GF2X(C+8,x3,0);

#define GEMSS_SQR320_PCLMUL_GF2X(C,x1,x2,x3,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR64_PCLMUL_GF2X(C+8,x3,z,0);

/* 6 pclmul */
#define GEMSS_SQR352_PCLMUL_GF2X(C,x1,x2,x3,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR96_PCLMUL_GF2X(C+8,x3,z);

#define GEMSS_SQR384_PCLMUL_GF2X(C,x1,x2,x3,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR128_PCLMUL_GF2X(C+8,x3,z);

/* 7 pclmul */
#define GEMSS_SQR416_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR160_PCLMUL_GF2X(C+8,x3,x4,z);

#define GEMSS_SQR448_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR192_PCLMUL_GF2X(C+8,x3,x4,z);

/* 8 pclmul */
#define GEMSS_SQR480_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR224_PCLMUL_GF2X(C+8,x3,x4,z);

#define GEMSS_SQR512_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
    GEMSS_SQR256_PCLMUL_GF2X(C,x1,x2,z);\
    GEMSS_SQR256_PCLMUL_GF2X(C+8,x3,x4,z);

/* 9 pclmul */
#define GEMSS_SQR544_PCLMUL_GF2X(C,x1,x2,x3,x4,x5,z) \
    GEMSS_SQR512_PCLMUL_GF2X(C,x1,x2,x3,x4,z);\
    GEMSS_SQR64LOW_TAB_PCLMUL_GF2X(C+16,x5,0);

#define GEMSS_SQR576_PCLMUL_GF2X(C,x1,x2,x3,x4,x5,z) \
    GEMSS_SQR512_PCLMUL_GF2X(C,x1,x2,x3,x4,z);\
    GEMSS_SQR64_PCLMUL_GF2X(C+16,x5,z,0);






/* Choice of the best constant-time squaring.
   We obtain this trade-off (without data dependencies). */
#ifdef GEMSS_ENABLED_PCLMUL
    /* Pclmul */
    #define GEMSS_best_sqr32_gf2x GEMSS_sqr32_inlined_pclmul_gf2x
    #define GEMSS_best_sqr64low_gf2x GEMSS_sqr64low_inlined_pclmul_gf2x
    #define GEMSS_best_sqr64_gf2x GEMSS_sqr64_inlined_pclmul_gf2x
    /* #define GEMSS_best_sqr64low_gf2x GEMSS_sqr64low_pclmul_gf2x */
    /* #define GEMSS_best_sqr64_gf2x GEMSS_sqr64_pclmul_gf2x */
    #define GEMSS_best_sqr96_gf2x GEMSS_sqr96_pclmul_gf2x
    #define GEMSS_best_sqr128_gf2x GEMSS_sqr128_pclmul_gf2x
    #define GEMSS_best_sqr160_gf2x GEMSS_sqr160_pclmul_gf2x
    #define GEMSS_best_sqr192_gf2x GEMSS_sqr192_pclmul_gf2x
    #define GEMSS_best_sqr224_gf2x GEMSS_sqr224_pclmul_gf2x

    #if (GEMSS_PROC_HASWELL&&defined(GEMSS_ENABLED_AVX2))
        /* Faster on Haswell */
        #define GEMSS_best_sqr256_gf2x GEMSS_vpsqr256_shuffle_gf2x
        #define GEMSS_best_sqr288_gf2x GEMSS_vpsqr288_shuffle_gf2x
        #define GEMSS_best_sqr320_gf2x GEMSS_vpsqr320_shuffle_gf2x
        #define GEMSS_best_sqr352_gf2x GEMSS_vpsqr352_shuffle_gf2x
        #define GEMSS_best_sqr384_gf2x GEMSS_vpsqr384_shuffle_gf2x
        #define GEMSS_best_sqr416_gf2x GEMSS_vpsqr416_shuffle_gf2x
        #define GEMSS_best_sqr448_gf2x GEMSS_vpsqr448_shuffle_gf2x
        #define GEMSS_best_sqr480_gf2x GEMSS_vpsqr480_shuffle_gf2x
        #define GEMSS_best_sqr512_gf2x GEMSS_vpsqr512_shuffle_gf2x
        #define GEMSS_best_sqr544_gf2x GEMSS_vpsqr544_shuffle_gf2x
        #define GEMSS_best_sqr576_gf2x GEMSS_vpsqr576_shuffle_gf2x
    #else
        /* Faster on Skylake */
        #define GEMSS_best_sqr256_gf2x GEMSS_sqr256_pclmul_gf2x
        #define GEMSS_best_sqr288_gf2x GEMSS_sqr288_pclmul_gf2x
        #define GEMSS_best_sqr320_gf2x GEMSS_sqr320_pclmul_gf2x
        #define GEMSS_best_sqr352_gf2x GEMSS_sqr352_pclmul_gf2x
        #define GEMSS_best_sqr384_gf2x GEMSS_sqr384_pclmul_gf2x
        #define GEMSS_best_sqr416_gf2x GEMSS_sqr416_pclmul_gf2x
        #define GEMSS_best_sqr448_gf2x GEMSS_sqr448_pclmul_gf2x
        #define GEMSS_best_sqr480_gf2x GEMSS_sqr480_pclmul_gf2x
        #define GEMSS_best_sqr512_gf2x GEMSS_sqr512_pclmul_gf2x
        #define GEMSS_best_sqr544_gf2x GEMSS_sqr544_pclmul_gf2x
        #define GEMSS_best_sqr576_gf2x GEMSS_sqr576_pclmul_gf2x
    #endif
#elif defined(GEMSS_ENABLED_AVX2)
    /* Shuffle */
    #if defined(GEMSS_ENABLED_SSSE3)
        #define GEMSS_best_sqr32_gf2x GEMSS_psqr32_shuffle_gf2x
        #define GEMSS_best_sqr64low_gf2x GEMSS_psqr64low_shuffle_gf2x
        #define GEMSS_best_sqr64_gf2x GEMSS_psqr64_shuffle_gf2x
        #define GEMSS_best_sqr96_gf2x GEMSS_psqr96_shuffle_gf2x
        #define GEMSS_best_sqr128_gf2x GEMSS_psqr128_shuffle_gf2x
        #define GEMSS_best_sqr160_gf2x GEMSS_psqr160_shuffle_gf2x
    #else
        #define GEMSS_best_sqr32_gf2x GEMSS_vpsqr32_shuffle_gf2x
        #define GEMSS_best_sqr64low_gf2x GEMSS_vpsqr64low_shuffle_gf2x
        #define GEMSS_best_sqr64_gf2x GEMSS_vpsqr64_shuffle_gf2x
        #define GEMSS_best_sqr96_gf2x GEMSS_vpsqr96_shuffle_gf2x
        #define GEMSS_best_sqr128_gf2x GEMSS_vpsqr128_shuffle_gf2x
        #define GEMSS_best_sqr160_gf2x GEMSS_vpsqr160_shuffle_gf2x
    #endif

    #if (GEMSS_PROC_HASWELL&&defined(GEMSS_ENABLED_SSSE3))
        /* Faster on Haswell */
        #define GEMSS_best_sqr192_gf2x GEMSS_psqr192_shuffle_gf2x
        #define GEMSS_best_sqr224_gf2x GEMSS_psqr224_shuffle_gf2x
    #else
        /* Faster on Skylake */
        #define GEMSS_best_sqr192_gf2x GEMSS_vpsqr192_shuffle_gf2x
        #define GEMSS_best_sqr224_gf2x GEMSS_vpsqr224_shuffle_gf2x
    #endif

    #define GEMSS_best_sqr256_gf2x GEMSS_vpsqr256_shuffle_gf2x
    #define GEMSS_best_sqr288_gf2x GEMSS_vpsqr288_shuffle_gf2x
    #define GEMSS_best_sqr320_gf2x GEMSS_vpsqr320_shuffle_gf2x
    #define GEMSS_best_sqr352_gf2x GEMSS_vpsqr352_shuffle_gf2x
    #define GEMSS_best_sqr384_gf2x GEMSS_vpsqr384_shuffle_gf2x
    #define GEMSS_best_sqr416_gf2x GEMSS_vpsqr416_shuffle_gf2x
    #define GEMSS_best_sqr448_gf2x GEMSS_vpsqr448_shuffle_gf2x
    #define GEMSS_best_sqr480_gf2x GEMSS_vpsqr480_shuffle_gf2x
    #define GEMSS_best_sqr512_gf2x GEMSS_vpsqr512_shuffle_gf2x
    #define GEMSS_best_sqr544_gf2x GEMSS_vpsqr544_shuffle_gf2x
    #define GEMSS_best_sqr576_gf2x GEMSS_vpsqr576_shuffle_gf2x
#elif defined(GEMSS_ENABLED_SSSE3)
    /* Shuffle */
    #define GEMSS_best_sqr32_gf2x GEMSS_psqr32_shuffle_gf2x
    #define GEMSS_best_sqr64low_gf2x GEMSS_psqr64low_shuffle_gf2x
    #define GEMSS_best_sqr64_gf2x GEMSS_psqr64_shuffle_gf2x
    #define GEMSS_best_sqr96_gf2x GEMSS_psqr96_shuffle_gf2x
    #define GEMSS_best_sqr128_gf2x GEMSS_psqr128_shuffle_gf2x
    #define GEMSS_best_sqr160_gf2x GEMSS_psqr160_shuffle_gf2x
    #define GEMSS_best_sqr192_gf2x GEMSS_psqr192_shuffle_gf2x
    #define GEMSS_best_sqr224_gf2x GEMSS_psqr224_shuffle_gf2x
    #define GEMSS_best_sqr256_gf2x GEMSS_psqr256_shuffle_gf2x
    #define GEMSS_best_sqr288_gf2x GEMSS_psqr288_shuffle_gf2x
    #define GEMSS_best_sqr320_gf2x GEMSS_psqr320_shuffle_gf2x
    #define GEMSS_best_sqr352_gf2x GEMSS_psqr352_shuffle_gf2x
    #define GEMSS_best_sqr384_gf2x GEMSS_psqr384_shuffle_gf2x
    #define GEMSS_best_sqr416_gf2x GEMSS_psqr416_shuffle_gf2x
    #define GEMSS_best_sqr448_gf2x GEMSS_psqr448_shuffle_gf2x
    #define GEMSS_best_sqr480_gf2x GEMSS_psqr480_shuffle_gf2x
    #define GEMSS_best_sqr512_gf2x GEMSS_psqr512_shuffle_gf2x
    #define GEMSS_best_sqr544_gf2x GEMSS_psqr544_shuffle_gf2x
    #define GEMSS_best_sqr576_gf2x GEMSS_psqr576_shuffle_gf2x
#elif defined(GEMSS_ENABLED_SSE2)
    /* sse2 */
    #define GEMSS_best_sqr32_gf2x GEMSS_psqr32_gf2x
    #define GEMSS_best_sqr64low_gf2x GEMSS_psqr64low_gf2x
    #define GEMSS_best_sqr64_gf2x GEMSS_psqr64_gf2x
    #define GEMSS_best_sqr96_gf2x GEMSS_psqr96_gf2x
    #define GEMSS_best_sqr128_gf2x GEMSS_psqr128_gf2x
    #define GEMSS_best_sqr160_gf2x GEMSS_psqr160_gf2x
    #define GEMSS_best_sqr192_gf2x GEMSS_psqr192_gf2x
    #define GEMSS_best_sqr224_gf2x GEMSS_psqr224_gf2x
    #define GEMSS_best_sqr256_gf2x GEMSS_psqr256_gf2x
    #define GEMSS_best_sqr288_gf2x GEMSS_psqr288_gf2x
    #define GEMSS_best_sqr320_gf2x GEMSS_psqr320_gf2x
    #define GEMSS_best_sqr352_gf2x GEMSS_psqr352_gf2x
    #define GEMSS_best_sqr384_gf2x GEMSS_psqr384_gf2x
    #define GEMSS_best_sqr416_gf2x GEMSS_psqr416_gf2x
    #define GEMSS_best_sqr448_gf2x GEMSS_psqr448_gf2x
    #define GEMSS_best_sqr480_gf2x GEMSS_psqr480_gf2x
    #define GEMSS_best_sqr512_gf2x GEMSS_psqr512_gf2x
    #define GEMSS_best_sqr544_gf2x GEMSS_psqr544_gf2x
    #define GEMSS_best_sqr576_gf2x GEMSS_psqr576_gf2x
#else
    /* Without SIMD */
    #define GEMSS_best_sqr32_gf2x GEMSS_sqr32_no_simd_gf2x
    #define GEMSS_best_sqr64low_gf2x GEMSS_sqr64low_no_simd_gf2x
    #define GEMSS_best_sqr64_gf2x(C,A) GEMSS_SQR64_NO_SIMD_GF2X((C),(*(A)))
    #define GEMSS_best_sqr96_gf2x GEMSS_SQR96_NO_SIMD_GF2X
    #define GEMSS_best_sqr128_gf2x GEMSS_SQR128_NO_SIMD_GF2X
    #define GEMSS_best_sqr160_gf2x GEMSS_SQR160_NO_SIMD_GF2X
    #define GEMSS_best_sqr192_gf2x GEMSS_SQR192_NO_SIMD_GF2X
    #define GEMSS_best_sqr224_gf2x GEMSS_SQR224_NO_SIMD_GF2X
    #define GEMSS_best_sqr256_gf2x GEMSS_SQR256_NO_SIMD_GF2X
    #define GEMSS_best_sqr288_gf2x GEMSS_SQR288_NO_SIMD_GF2X
    #define GEMSS_best_sqr320_gf2x GEMSS_SQR320_NO_SIMD_GF2X
    #define GEMSS_best_sqr352_gf2x GEMSS_SQR352_NO_SIMD_GF2X
    #define GEMSS_best_sqr384_gf2x GEMSS_SQR384_NO_SIMD_GF2X
    #define GEMSS_best_sqr416_gf2x GEMSS_SQR416_NO_SIMD_GF2X
    #define GEMSS_best_sqr448_gf2x GEMSS_SQR448_NO_SIMD_GF2X
    #define GEMSS_best_sqr480_gf2x GEMSS_SQR480_NO_SIMD_GF2X
    #define GEMSS_best_sqr512_gf2x GEMSS_SQR512_NO_SIMD_GF2X
    #define GEMSS_best_sqr544_gf2x GEMSS_SQR544_NO_SIMD_GF2X
    #define GEMSS_best_sqr576_gf2x GEMSS_SQR576_NO_SIMD_GF2X
#endif


/* Choice of the best variable-time squaring */
#if 1
    /* The best variable-time squaring is the constant-time squaring */
    #define GEMSS_best_sqr_nocst_32_gf2x GEMSS_best_sqr32_gf2x
    #define GEMSS_best_sqr_nocst_64low_gf2x GEMSS_best_sqr64low_gf2x
    #define GEMSS_best_sqr_nocst_64_gf2x GEMSS_best_sqr64_gf2x
    #define GEMSS_best_sqr_nocst_96_gf2x GEMSS_best_sqr96_gf2x
    #define GEMSS_best_sqr_nocst_128_gf2x GEMSS_best_sqr128_gf2x
    #define GEMSS_best_sqr_nocst_160_gf2x GEMSS_best_sqr160_gf2x
    #define GEMSS_best_sqr_nocst_192_gf2x GEMSS_best_sqr192_gf2x
    #define GEMSS_best_sqr_nocst_224_gf2x GEMSS_best_sqr224_gf2x
    #define GEMSS_best_sqr_nocst_256_gf2x GEMSS_best_sqr256_gf2x
    #define GEMSS_best_sqr_nocst_288_gf2x GEMSS_best_sqr288_gf2x
    #define GEMSS_best_sqr_nocst_320_gf2x GEMSS_best_sqr320_gf2x
    #define GEMSS_best_sqr_nocst_352_gf2x GEMSS_best_sqr352_gf2x
    #define GEMSS_best_sqr_nocst_384_gf2x GEMSS_best_sqr384_gf2x
    #define GEMSS_best_sqr_nocst_416_gf2x GEMSS_best_sqr416_gf2x
    #define GEMSS_best_sqr_nocst_448_gf2x GEMSS_best_sqr448_gf2x
    #define GEMSS_best_sqr_nocst_480_gf2x GEMSS_best_sqr480_gf2x
    #define GEMSS_best_sqr_nocst_512_gf2x GEMSS_best_sqr512_gf2x
    #define GEMSS_best_sqr_nocst_544_gf2x GEMSS_best_sqr544_gf2x
    #define GEMSS_best_sqr_nocst_576_gf2x GEMSS_best_sqr576_gf2x
#endif



#endif

