#ifndef _MUL_GF2X_H
#define _MUL_GF2X_H

#include <stdint.h>
#include "gemss_prefix_name.h"
#include "gemss_arch.h"

/* Multiplication in GF(2)[x] */


/***********************************************************************/
/***********************************************************************/
/********************** version without vectorization ******************/
/***********************************************************************/
/***********************************************************************/


uint64_t GEMSS_PREFIX_NAME(GEMSS_mul32_no_simd_gf2x)(uint64_t A, uint64_t B);
uint64_t GEMSS_PREFIX_NAME(GEMSS_mul64low_no_simd_gf2x)(uint64_t A, uint64_t B);
void GEMSS_PREFIX_NAME(GEMSS_mul64_no_simd_gf2x)(uint64_t C[2], const uint64_t A[1],
                                                    const uint64_t B[1]);
void GEMSS_PREFIX_NAME(GEMSS_mul96_no_simd_gf2x)(uint64_t C[3], const uint64_t A[2],
                                                     const uint64_t B[2]);
void GEMSS_PREFIX_NAME(GEMSS_mul128_no_simd_gf2x)(uint64_t C[4], const uint64_t A[2],
                                                     const uint64_t B[2]);
void GEMSS_PREFIX_NAME(GEMSS_mul160_no_simd_gf2x)(uint64_t C[5], const uint64_t A[3],
                                                     const uint64_t B[3]);
void GEMSS_PREFIX_NAME(GEMSS_mul192_no_simd_gf2x)(uint64_t C[6], const uint64_t A[3],
                                                     const uint64_t B[3]);
void GEMSS_PREFIX_NAME(GEMSS_mul224_no_simd_gf2x)(uint64_t C[7], const uint64_t A[4],
                                                     const uint64_t B[4]);
void GEMSS_PREFIX_NAME(GEMSS_mul256_no_simd_gf2x)(uint64_t C[8], const uint64_t A[4],
                                                     const uint64_t B[4]);
void GEMSS_PREFIX_NAME(GEMSS_mul288_no_simd_gf2x)(uint64_t C[9], const uint64_t A[5],
                                                     const uint64_t B[5]);
void GEMSS_PREFIX_NAME(GEMSS_mul320_no_simd_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                      const uint64_t B[5]);
void GEMSS_PREFIX_NAME(GEMSS_mul352_no_simd_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                      const uint64_t B[6]);
void GEMSS_PREFIX_NAME(GEMSS_mul384_no_simd_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                      const uint64_t B[6]);
void GEMSS_PREFIX_NAME(GEMSS_mul416_no_simd_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                      const uint64_t B[7]);
void GEMSS_PREFIX_NAME(GEMSS_mul448_no_simd_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                      const uint64_t B[7]);
void GEMSS_PREFIX_NAME(GEMSS_mul480_no_simd_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                      const uint64_t B[8]);
void GEMSS_PREFIX_NAME(GEMSS_mul512_no_simd_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                      const uint64_t B[8]);
void GEMSS_PREFIX_NAME(GEMSS_mul544_no_simd_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                      const uint64_t B[9]);
void GEMSS_PREFIX_NAME(GEMSS_mul576_no_simd_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                      const uint64_t B[9]);

#define GEMSS_mul32_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul32_no_simd_gf2x)
#define GEMSS_mul64low_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul64low_no_simd_gf2x)
#define GEMSS_mul64_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul64_no_simd_gf2x)
#define GEMSS_mul96_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul96_no_simd_gf2x)
#define GEMSS_mul128_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul128_no_simd_gf2x)
#define GEMSS_mul160_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul160_no_simd_gf2x)
#define GEMSS_mul192_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul192_no_simd_gf2x)
#define GEMSS_mul224_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul224_no_simd_gf2x)
#define GEMSS_mul256_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul256_no_simd_gf2x)
#define GEMSS_mul288_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul288_no_simd_gf2x)
#define GEMSS_mul320_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul320_no_simd_gf2x)
#define GEMSS_mul352_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul352_no_simd_gf2x)
#define GEMSS_mul384_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul384_no_simd_gf2x)
#define GEMSS_mul416_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul416_no_simd_gf2x)
#define GEMSS_mul448_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul448_no_simd_gf2x)
#define GEMSS_mul480_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul480_no_simd_gf2x)
#define GEMSS_mul512_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul512_no_simd_gf2x)
#define GEMSS_mul544_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul544_no_simd_gf2x)
#define GEMSS_mul576_no_simd_gf2x GEMSS_PREFIX_NAME(GEMSS_mul576_no_simd_gf2x)


/* Classical, 189 = 31×6+3 instructions */
#define GEMSS_MUL32_NO_UNROLLED_NO_SIMD_GF2X(C,A,B,i) \
    (C)=(-((B)&GEMSS_ONE64))&(A);\
    for(i=1;i<32;++i)\
    {\
        (C)^=((-(((B)>>i)&GEMSS_ONE64))&(A))<<i;\
    }


/* Classical, 189 = 31×6+3 instructions */
#define GEMSS_MUL32_NO_SIMD_GF2X(C,A,B) \
    (C)=(-((B)&GEMSS_ONE64))&(A);\
    (C)^=((-(((B)>>1)&GEMSS_ONE64))&(A))<<1;\
    (C)^=((-(((B)>>2)&GEMSS_ONE64))&(A))<<2;\
    (C)^=((-(((B)>>3)&GEMSS_ONE64))&(A))<<3;\
    (C)^=((-(((B)>>4)&GEMSS_ONE64))&(A))<<4;\
    (C)^=((-(((B)>>5)&GEMSS_ONE64))&(A))<<5;\
    (C)^=((-(((B)>>6)&GEMSS_ONE64))&(A))<<6;\
    (C)^=((-(((B)>>7)&GEMSS_ONE64))&(A))<<7;\
    (C)^=((-(((B)>>8)&GEMSS_ONE64))&(A))<<8;\
    (C)^=((-(((B)>>9)&GEMSS_ONE64))&(A))<<9;\
    (C)^=((-(((B)>>10)&GEMSS_ONE64))&(A))<<10;\
    (C)^=((-(((B)>>11)&GEMSS_ONE64))&(A))<<11;\
    (C)^=((-(((B)>>12)&GEMSS_ONE64))&(A))<<12;\
    (C)^=((-(((B)>>13)&GEMSS_ONE64))&(A))<<13;\
    (C)^=((-(((B)>>14)&GEMSS_ONE64))&(A))<<14;\
    (C)^=((-(((B)>>15)&GEMSS_ONE64))&(A))<<15;\
    (C)^=((-(((B)>>16)&GEMSS_ONE64))&(A))<<16;\
    (C)^=((-(((B)>>17)&GEMSS_ONE64))&(A))<<17;\
    (C)^=((-(((B)>>18)&GEMSS_ONE64))&(A))<<18;\
    (C)^=((-(((B)>>19)&GEMSS_ONE64))&(A))<<19;\
    (C)^=((-(((B)>>20)&GEMSS_ONE64))&(A))<<20;\
    (C)^=((-(((B)>>21)&GEMSS_ONE64))&(A))<<21;\
    (C)^=((-(((B)>>22)&GEMSS_ONE64))&(A))<<22;\
    (C)^=((-(((B)>>23)&GEMSS_ONE64))&(A))<<23;\
    (C)^=((-(((B)>>24)&GEMSS_ONE64))&(A))<<24;\
    (C)^=((-(((B)>>25)&GEMSS_ONE64))&(A))<<25;\
    (C)^=((-(((B)>>26)&GEMSS_ONE64))&(A))<<26;\
    (C)^=((-(((B)>>27)&GEMSS_ONE64))&(A))<<27;\
    (C)^=((-(((B)>>28)&GEMSS_ONE64))&(A))<<28;\
    (C)^=((-(((B)>>29)&GEMSS_ONE64))&(A))<<29;\
    (C)^=((-(((B)>>30)&GEMSS_ONE64))&(A))<<30;\
    (C)^=((-(((B)>>31)&GEMSS_ONE64))&(A))<<31; 


/* Classical, 380 = 62*6+8 instructions */
#define GEMSS_MUL64LOW_NO_UNROLLED_NO_SIMD_GF2X(C,A,B,i) \
    (C)=(-((B)&GEMSS_ONE64))&(A);\
    /* Optimization: the '&1' is removed */\
    (C)^=((-((B)>>63))&(A))<<63;\
    for(i=1;i<63;++i)\
    {\
        (C)^=((-(((B)>>i)&GEMSS_ONE64))&(A))<<i;\
    }


/* Classical, 380 = 62×6+8 instructions */
#define GEMSS_MUL64LOW_NO_SIMD_GF2X(C,A,B) \
    (C)=(-((B)&GEMSS_ONE64))&(A);\
    (C)^=((-(((B)>>1)&GEMSS_ONE64))&(A))<<1;\
    (C)^=((-(((B)>>2)&GEMSS_ONE64))&(A))<<2;\
    (C)^=((-(((B)>>3)&GEMSS_ONE64))&(A))<<3;\
    (C)^=((-(((B)>>4)&GEMSS_ONE64))&(A))<<4;\
    (C)^=((-(((B)>>5)&GEMSS_ONE64))&(A))<<5;\
    (C)^=((-(((B)>>6)&GEMSS_ONE64))&(A))<<6;\
    (C)^=((-(((B)>>7)&GEMSS_ONE64))&(A))<<7;\
    (C)^=((-(((B)>>8)&GEMSS_ONE64))&(A))<<8;\
    (C)^=((-(((B)>>9)&GEMSS_ONE64))&(A))<<9;\
    (C)^=((-(((B)>>10)&GEMSS_ONE64))&(A))<<10;\
    (C)^=((-(((B)>>11)&GEMSS_ONE64))&(A))<<11;\
    (C)^=((-(((B)>>12)&GEMSS_ONE64))&(A))<<12;\
    (C)^=((-(((B)>>13)&GEMSS_ONE64))&(A))<<13;\
    (C)^=((-(((B)>>14)&GEMSS_ONE64))&(A))<<14;\
    (C)^=((-(((B)>>15)&GEMSS_ONE64))&(A))<<15;\
    (C)^=((-(((B)>>16)&GEMSS_ONE64))&(A))<<16;\
    (C)^=((-(((B)>>17)&GEMSS_ONE64))&(A))<<17;\
    (C)^=((-(((B)>>18)&GEMSS_ONE64))&(A))<<18;\
    (C)^=((-(((B)>>19)&GEMSS_ONE64))&(A))<<19;\
    (C)^=((-(((B)>>20)&GEMSS_ONE64))&(A))<<20;\
    (C)^=((-(((B)>>21)&GEMSS_ONE64))&(A))<<21;\
    (C)^=((-(((B)>>22)&GEMSS_ONE64))&(A))<<22;\
    (C)^=((-(((B)>>23)&GEMSS_ONE64))&(A))<<23;\
    (C)^=((-(((B)>>24)&GEMSS_ONE64))&(A))<<24;\
    (C)^=((-(((B)>>25)&GEMSS_ONE64))&(A))<<25;\
    (C)^=((-(((B)>>26)&GEMSS_ONE64))&(A))<<26;\
    (C)^=((-(((B)>>27)&GEMSS_ONE64))&(A))<<27;\
    (C)^=((-(((B)>>28)&GEMSS_ONE64))&(A))<<28;\
    (C)^=((-(((B)>>29)&GEMSS_ONE64))&(A))<<29;\
    (C)^=((-(((B)>>30)&GEMSS_ONE64))&(A))<<30;\
    (C)^=((-(((B)>>31)&GEMSS_ONE64))&(A))<<31;\
\
    (C)^=((-(((B)>>32)&GEMSS_ONE64))&(A))<<32;\
    (C)^=((-(((B)>>33)&GEMSS_ONE64))&(A))<<33;\
    (C)^=((-(((B)>>34)&GEMSS_ONE64))&(A))<<34;\
    (C)^=((-(((B)>>35)&GEMSS_ONE64))&(A))<<35;\
    (C)^=((-(((B)>>36)&GEMSS_ONE64))&(A))<<36;\
    (C)^=((-(((B)>>37)&GEMSS_ONE64))&(A))<<37;\
    (C)^=((-(((B)>>38)&GEMSS_ONE64))&(A))<<38;\
    (C)^=((-(((B)>>39)&GEMSS_ONE64))&(A))<<39;\
    (C)^=((-(((B)>>40)&GEMSS_ONE64))&(A))<<40;\
    (C)^=((-(((B)>>41)&GEMSS_ONE64))&(A))<<41;\
    (C)^=((-(((B)>>42)&GEMSS_ONE64))&(A))<<42;\
    (C)^=((-(((B)>>43)&GEMSS_ONE64))&(A))<<43;\
    (C)^=((-(((B)>>44)&GEMSS_ONE64))&(A))<<44;\
    (C)^=((-(((B)>>45)&GEMSS_ONE64))&(A))<<45;\
    (C)^=((-(((B)>>46)&GEMSS_ONE64))&(A))<<46;\
    (C)^=((-(((B)>>47)&GEMSS_ONE64))&(A))<<47;\
    (C)^=((-(((B)>>48)&GEMSS_ONE64))&(A))<<48;\
    (C)^=((-(((B)>>49)&GEMSS_ONE64))&(A))<<49;\
    (C)^=((-(((B)>>50)&GEMSS_ONE64))&(A))<<50;\
    (C)^=((-(((B)>>51)&GEMSS_ONE64))&(A))<<51;\
    (C)^=((-(((B)>>52)&GEMSS_ONE64))&(A))<<52;\
    (C)^=((-(((B)>>53)&GEMSS_ONE64))&(A))<<53;\
    (C)^=((-(((B)>>54)&GEMSS_ONE64))&(A))<<54;\
    (C)^=((-(((B)>>55)&GEMSS_ONE64))&(A))<<55;\
    (C)^=((-(((B)>>56)&GEMSS_ONE64))&(A))<<56;\
    (C)^=((-(((B)>>57)&GEMSS_ONE64))&(A))<<57;\
    (C)^=((-(((B)>>58)&GEMSS_ONE64))&(A))<<58;\
    (C)^=((-(((B)>>59)&GEMSS_ONE64))&(A))<<59;\
    (C)^=((-(((B)>>60)&GEMSS_ONE64))&(A))<<60;\
    (C)^=((-(((B)>>61)&GEMSS_ONE64))&(A))<<61;\
    (C)^=((-(((B)>>62)&GEMSS_ONE64))&(A))<<62;\
    /* Optimization: the '&1' is removed */\
    (C)^=((-((B)>>63))&(A))<<63;


/* Classical, 505 = 62×8+9 instructions */
#define GEMSS_MUL64_NO_UNROLLED_NO_SIMD_GF2X(C,A,B,i,tmp) \
    (C)[0]=(-((B)&GEMSS_ONE64))&(A);\
    /* Optimization: the '&1' is removed */\
    tmp=((-((B)>>63))&(A));\
    (C)[0]^=tmp<<63;\
    (C)[1]=tmp>>1;\
    for(i=1;i<63;++i)\
    {\
        tmp=((-(((B)>>i)&GEMSS_ONE64))&(A));\
        (C)[0]^=tmp<<i;\
        (C)[1]^=tmp>>(64-i);\
    }


/* Classical, 505 = 62×8+9 instructions */
#define GEMSS_MUL64_NO_SIMD_GF2X(C,A,B,tmp) \
    (C)[0]=(-((B)&GEMSS_ONE64))&(A);\
    /* Optimization: the '&1' is removed */\
    tmp=((-((B)>>63))&(A));\
    (C)[0]^=tmp<<63;\
    (C)[1]=tmp>>1;\
\
    tmp=((-(((B)>>1)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<1;\
    (C)[1]^=tmp>>63;\
    tmp=((-(((B)>>2)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<2;\
    (C)[1]^=tmp>>62;\
    tmp=((-(((B)>>3)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<3;\
    (C)[1]^=tmp>>61;\
    tmp=((-(((B)>>4)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<4;\
    (C)[1]^=tmp>>60;\
    tmp=((-(((B)>>5)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<5;\
    (C)[1]^=tmp>>59;\
    tmp=((-(((B)>>6)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<6;\
    (C)[1]^=tmp>>58;\
    tmp=((-(((B)>>7)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<7;\
    (C)[1]^=tmp>>57;\
    tmp=((-(((B)>>8)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<8;\
    (C)[1]^=tmp>>56;\
    tmp=((-(((B)>>9)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<9;\
    (C)[1]^=tmp>>55;\
    tmp=((-(((B)>>10)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<10;\
    (C)[1]^=tmp>>54;\
    tmp=((-(((B)>>11)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<11;\
    (C)[1]^=tmp>>53;\
    tmp=((-(((B)>>12)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<12;\
    (C)[1]^=tmp>>52;\
    tmp=((-(((B)>>13)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<13;\
    (C)[1]^=tmp>>51;\
    tmp=((-(((B)>>14)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<14;\
    (C)[1]^=tmp>>50;\
    tmp=((-(((B)>>15)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<15;\
    (C)[1]^=tmp>>49;\
    tmp=((-(((B)>>16)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<16;\
    (C)[1]^=tmp>>48;\
    tmp=((-(((B)>>17)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<17;\
    (C)[1]^=tmp>>47;\
    tmp=((-(((B)>>18)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<18;\
    (C)[1]^=tmp>>46;\
    tmp=((-(((B)>>19)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<19;\
    (C)[1]^=tmp>>45;\
    tmp=((-(((B)>>20)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<20;\
    (C)[1]^=tmp>>44;\
    tmp=((-(((B)>>21)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<21;\
    (C)[1]^=tmp>>43;\
    tmp=((-(((B)>>22)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<22;\
    (C)[1]^=tmp>>42;\
    tmp=((-(((B)>>23)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<23;\
    (C)[1]^=tmp>>41;\
    tmp=((-(((B)>>24)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<24;\
    (C)[1]^=tmp>>40;\
    tmp=((-(((B)>>25)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<25;\
    (C)[1]^=tmp>>39;\
    tmp=((-(((B)>>26)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<26;\
    (C)[1]^=tmp>>38;\
    tmp=((-(((B)>>27)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<27;\
    (C)[1]^=tmp>>37;\
    tmp=((-(((B)>>28)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<28;\
    (C)[1]^=tmp>>36;\
    tmp=((-(((B)>>29)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<29;\
    (C)[1]^=tmp>>35;\
    tmp=((-(((B)>>30)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<30;\
    (C)[1]^=tmp>>34;\
    tmp=((-(((B)>>31)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<31;\
    (C)[1]^=tmp>>33;\
\
    tmp=((-(((B)>>32)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<32;\
    (C)[1]^=tmp>>32;\
    tmp=((-(((B)>>33)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<33;\
    (C)[1]^=tmp>>31;\
    tmp=((-(((B)>>34)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<34;\
    (C)[1]^=tmp>>30;\
    tmp=((-(((B)>>35)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<35;\
    (C)[1]^=tmp>>29;\
    tmp=((-(((B)>>36)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<36;\
    (C)[1]^=tmp>>28;\
    tmp=((-(((B)>>37)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<37;\
    (C)[1]^=tmp>>27;\
    tmp=((-(((B)>>38)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<38;\
    (C)[1]^=tmp>>26;\
    tmp=((-(((B)>>39)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<39;\
    (C)[1]^=tmp>>25;\
    tmp=((-(((B)>>40)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<40;\
    (C)[1]^=tmp>>24;\
    tmp=((-(((B)>>41)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<41;\
    (C)[1]^=tmp>>23;\
    tmp=((-(((B)>>42)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<42;\
    (C)[1]^=tmp>>22;\
    tmp=((-(((B)>>43)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<43;\
    (C)[1]^=tmp>>21;\
    tmp=((-(((B)>>44)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<44;\
    (C)[1]^=tmp>>20;\
    tmp=((-(((B)>>45)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<45;\
    (C)[1]^=tmp>>19;\
    tmp=((-(((B)>>46)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<46;\
    (C)[1]^=tmp>>18;\
    tmp=((-(((B)>>47)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<47;\
    (C)[1]^=tmp>>17;\
    tmp=((-(((B)>>48)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<48;\
    (C)[1]^=tmp>>16;\
    tmp=((-(((B)>>49)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<49;\
    (C)[1]^=tmp>>15;\
    tmp=((-(((B)>>50)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<50;\
    (C)[1]^=tmp>>14;\
    tmp=((-(((B)>>51)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<51;\
    (C)[1]^=tmp>>13;\
    tmp=((-(((B)>>52)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<52;\
    (C)[1]^=tmp>>12;\
    tmp=((-(((B)>>53)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<53;\
    (C)[1]^=tmp>>11;\
    tmp=((-(((B)>>54)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<54;\
    (C)[1]^=tmp>>10;\
    tmp=((-(((B)>>55)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<55;\
    (C)[1]^=tmp>>9;\
    tmp=((-(((B)>>56)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<56;\
    (C)[1]^=tmp>>8;\
    tmp=((-(((B)>>57)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<57;\
    (C)[1]^=tmp>>7;\
    tmp=((-(((B)>>58)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<58;\
    (C)[1]^=tmp>>6;\
    tmp=((-(((B)>>59)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<59;\
    (C)[1]^=tmp>>5;\
    tmp=((-(((B)>>60)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<60;\
    (C)[1]^=tmp>>4;\
    tmp=((-(((B)>>61)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<61;\
    (C)[1]^=tmp>>3;\
    tmp=((-(((B)>>62)&GEMSS_ONE64))&(A));\
    (C)[0]^=tmp<<62;\
    (C)[1]^=tmp>>2;


/* Karatsuba, 1205 = 505*2+189+6 instructions */
#define GEMSS_MUL96_NO_SIMD_GF2X(C,A,B,tmp,AA,BB) \
    { uint64_t RESERVED_BUF2[2];\
    GEMSS_MUL64_NO_SIMD_GF2X(C,(A)[0],(B)[0],tmp);\
    GEMSS_MUL32_NO_SIMD_GF2X((C)[2],(A)[1],(B)[1]);\
\
    (C)[2]^=(C)[1];\
    (C)[1]=(C)[0]^(C)[2];\
    /*  C[0] = C0
        C[1] = C0^C1^C2
        C[2] = C1^C2 */\
    AA=(A)[0]^(A)[1];\
    BB=(B)[0]^(B)[1];\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[1]^=RESERVED_BUF2[0];\
    (C)[2]^=RESERVED_BUF2[1];}


/* Karatsuba, 1522 = 505*3+7 instructions */
#define GEMSS_MUL128_NO_SIMD_GF2X(C,A,B,tmp,AA,BB) \
    { uint64_t RESERVED_BUF2[2];\
    GEMSS_MUL64_NO_SIMD_GF2X(C,(A)[0],(B)[0],tmp);\
    GEMSS_MUL64_NO_SIMD_GF2X((C)+2,(A)[1],(B)[1],tmp);\
\
    (C)[2]^=(C)[1];\
    (C)[1]=(C)[0]^(C)[2];\
    (C)[2]^=(C)[3];\
    /*  C[0] = C0
        C[1] = C0^C1^C2
        C[2] = C1^C2^C3
        C[3] = C3 */\
    AA=(A)[0]^(A)[1];\
    BB=(B)[0]^(B)[1];\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[1]^=RESERVED_BUF2[0];\
    (C)[2]^=RESERVED_BUF2[1];}


/* Karatsuba with 6 multiplications, 2733 = 505*5+189+19 instructions */
#define GEMSS_MUL160_NO_SIMD_GF2X(C,A,B,tmp,AA,BB) \
    { uint64_t RESERVED_BUF2[2];\
    /* A0*B0 */\
    GEMSS_MUL64_NO_SIMD_GF2X(C,(A)[0],(B)[0],tmp);\
    /* A2*B2 */\
    GEMSS_MUL32_NO_SIMD_GF2X((C)[4],(A)[2],(B)[2]);\
    /* A1*B1 */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,(A)[1],(B)[1],tmp)\
    (C)[1]^=RESERVED_BUF2[0];\
    (C)[4]^=RESERVED_BUF2[1];\
    (C)[2]=(C)[4];\
    (C)[3]=(C)[1];\
    /*  C[0] = C0
        C[1] = C1^C2
        C[2] = C4^C3
        C[3] = C1^C2
        C[4] = C4^C3 */\
    (C)[1]^=(C)[0];\
    (C)[2]^=(C)[1];\
    (C)[3]^=(C)[4];\
    /*  C[0] = C0
        C[1] = C0^(C1^C2)
        C[2] = (C0^C1^C2)^(C3^C4)
        C[3] = (C1^C2)^(C3^C4)
        C[4] = C3^C4 */\
    AA=(A)[0]^(A)[1];\
    BB=(B)[0]^(B)[1];\
    /* (A0+A1)*(B0+B1) */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[1]^=RESERVED_BUF2[0];\
    (C)[2]^=RESERVED_BUF2[1];\
    AA=(A)[1]^(A)[2];\
    BB=(B)[1]^(B)[2];\
    /* (A1+A2)*(B1+B2) */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[3]^=RESERVED_BUF2[0];\
    (C)[4]^=RESERVED_BUF2[1];\
    AA=(A)[0]^(A)[2];\
    BB=(B)[0]^(B)[2];\
    /* (A0+A2)*(B0+B2) */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[2]^=RESERVED_BUF2[0];\
    (C)[3]^=RESERVED_BUF2[1];}


/* Karatsuba with 6 multiplications, 3050 = 505*6+20 instructions */
#define GEMSS_MUL192_NO_SIMD_GF2X(C,A,B,tmp,AA,BB) \
    { uint64_t RESERVED_BUF2[2];\
    /* A0*B0 */\
    GEMSS_MUL64_NO_SIMD_GF2X(C,(A)[0],(B)[0],tmp);\
    /* A2*B2 */\
    GEMSS_MUL64_NO_SIMD_GF2X((C)+4,(A)[2],(B)[2],tmp);\
    /* A1*B1 */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,(A)[1],(B)[1],tmp)\
    (C)[1]^=RESERVED_BUF2[0];\
    (C)[4]^=RESERVED_BUF2[1];\
    (C)[2]=(C)[4];\
    (C)[3]=(C)[1];\
    /*  C[0] = C0
        C[1] = C1^C2
        C[2] = C4^C3
        C[3] = C1^C2
        C[4] = C4^C3
        C[5] = C5 */\
    (C)[1]^=(C)[0];\
    (C)[4]^=(C)[5];\
    (C)[2]^=(C)[1];\
    (C)[3]^=(C)[4];\
    /*  C[0] = C0
        C[1] = C0^(C1^C2)
        C[2] = (C0^C1^C2)^(C3^C4)
        C[3] = (C1^C2)^(C3^C4^C5)
        C[4] = (C3^C4)^C5
        C[5] = C5 */\
    AA=(A)[0]^(A)[1];\
    BB=(B)[0]^(B)[1];\
    /* (A0+A1)*(B0+B1) */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[1]^=RESERVED_BUF2[0];\
    (C)[2]^=RESERVED_BUF2[1];\
    AA=(A)[1]^(A)[2];\
    BB=(B)[1]^(B)[2];\
    /* (A1+A2)*(B1+B2) */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[3]^=RESERVED_BUF2[0];\
    (C)[4]^=RESERVED_BUF2[1];\
    AA=(A)[0]^(A)[2];\
    BB=(B)[0]^(B)[2];\
    /* (A0+A2)*(B0+B2) */\
    GEMSS_MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
    (C)[2]^=RESERVED_BUF2[0];\
    (C)[3]^=RESERVED_BUF2[1];}


/* Karatsuba, 4264 = 1522*2+1205+15 instructions */
#define GEMSS_MUL224_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2) \
    { uint64_t RESERVED_BUF4[4];\
    GEMSS_MUL128_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL96_NO_SIMD_GF2X((C)+4,(A)+2,(B)+2,tmp,tmp1,tmp2);\
    (C)[2]^=(C)[4];\
    (C)[3]^=(C)[5];\
    (C)[4]=(C)[2];\
    (C)[5]=(C)[3];\
    (C)[2]^=(C)[0];\
    (C)[3]^=(C)[1];\
    (C)[4]^=(C)[6];\
    (AA)[0]=(A)[0]^(A)[2];\
    (AA)[1]=(A)[1]^(A)[3];\
    (BB)[0]=(B)[0]^(B)[2];\
    (BB)[1]=(B)[1]^(B)[3];\
    GEMSS_MUL128_NO_SIMD_GF2X(RESERVED_BUF4,AA,BB,tmp,tmp1,tmp2);\
    (C)[2]^=RESERVED_BUF4[0];\
    (C)[3]^=RESERVED_BUF4[1];\
    (C)[4]^=RESERVED_BUF4[2];\
    (C)[5]^=RESERVED_BUF4[3];}


/* Karatsuba, 4582 = 1522*3+16 instructions */
#define GEMSS_MUL256_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2) \
    { uint64_t RESERVED_BUF4[4];\
    GEMSS_MUL128_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL128_NO_SIMD_GF2X((C)+4,(A)+2,(B)+2,tmp,tmp1,tmp2);\
    (C)[2]^=(C)[4];\
    (C)[3]^=(C)[5];\
    (C)[4]=(C)[2];\
    (C)[5]=(C)[3];\
    (C)[2]^=(C)[0];\
    (C)[3]^=(C)[1];\
    (C)[4]^=(C)[6];\
    (C)[5]^=(C)[7];\
    (AA)[0]=(A)[0]^(A)[2];\
    (AA)[1]=(A)[1]^(A)[3];\
    (BB)[0]=(B)[0]^(B)[2];\
    (BB)[1]=(B)[1]^(B)[3];\
    GEMSS_MUL128_NO_SIMD_GF2X(RESERVED_BUF4,AA,BB,tmp,tmp1,tmp2);\
    (C)[2]^=RESERVED_BUF4[0];\
    (C)[3]^=RESERVED_BUF4[1];\
    (C)[4]^=RESERVED_BUF4[2];\
    (C)[5]^=RESERVED_BUF4[3];}


/* Karatsuba, 7006 = 2733*2+1522+18 instructions */
#define GEMSS_MUL288_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2) \
    { uint64_t RESERVED_BUF6[5];\
    GEMSS_MUL128_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL160_NO_SIMD_GF2X((C)+4,(A)+2,(B)+2,tmp,tmp1,tmp2);\
    (C)[4]^=(C)[2];\
    (C)[5]^=(C)[3];\
    (C)[2]=(C)[4]^(C)[0];\
    (C)[3]=(C)[5]^(C)[1];\
    (C)[4]^=(C)[6];\
    (C)[5]^=(C)[7];\
    (C)[6]^=(C)[8];\
    (AA)[0]=(A)[0]^(A)[2];\
    (AA)[1]=(A)[1]^(A)[3];\
    (AA)[2]=(A)[4];\
    (BB)[0]=(B)[0]^(B)[2];\
    (BB)[1]=(B)[1]^(B)[3];\
    (BB)[2]=(B)[4];\
    GEMSS_MUL160_NO_SIMD_GF2X(RESERVED_BUF6,AA,BB,tmp,tmp1,tmp2);\
    (C)[2]^=RESERVED_BUF6[0];\
    (C)[3]^=RESERVED_BUF6[1];\
    (C)[4]^=RESERVED_BUF6[2];\
    (C)[5]^=RESERVED_BUF6[3];\
    (C)[6]^=RESERVED_BUF6[4];}


/* Karatsuba, 7642 = 3050*2+1522+20 instructions */
#define GEMSS_MUL320_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_MUL128_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL192_NO_SIMD_GF2X((C)+4,(A)+2,(B)+2,tmp,tmp1,tmp2);\
    (C)[4]^=(C)[2];\
    (C)[5]^=(C)[3];\
    (C)[2]=(C)[4]^(C)[0];\
    (C)[3]=(C)[5]^(C)[1];\
    (C)[4]^=(C)[6];\
    (C)[5]^=(C)[7];\
    (C)[6]^=(C)[8];\
    (C)[7]^=(C)[9];\
    (AA)[0]=(A)[0]^(A)[2];\
    (AA)[1]=(A)[1]^(A)[3];\
    (AA)[2]=(A)[4];\
    (BB)[0]=(B)[0]^(B)[2];\
    (BB)[1]=(B)[1]^(B)[3];\
    (BB)[2]=(B)[4];\
    GEMSS_MUL192_NO_SIMD_GF2X(RESERVED_BUF6,AA,BB,tmp,tmp1,tmp2);\
    (C)[2]^=RESERVED_BUF6[0];\
    (C)[3]^=RESERVED_BUF6[1];\
    (C)[4]^=RESERVED_BUF6[2];\
    (C)[5]^=RESERVED_BUF6[3];\
    (C)[6]^=RESERVED_BUF6[4];\
    (C)[7]^=RESERVED_BUF6[5];}


/* Karatsuba, 8853 = 3050*2+2733+20 instructions */
#define GEMSS_MUL352_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_MUL192_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL160_NO_SIMD_GF2X((C)+6,(A)+3,(B)+3,tmp,tmp1,tmp2);\
    (C)[6]^=(C)[3];\
    (C)[7]^=(C)[4];\
    (C)[8]^=(C)[5];\
    (C)[3]=(C)[6]^(C)[0];\
    (C)[4]=(C)[7]^(C)[1];\
    (C)[5]=(C)[8]^(C)[2];\
    (C)[6]^=(C)[9];\
    (C)[7]^=(C)[10];\
    (AA)[0]=(A)[0]^(A)[3];\
    (AA)[1]=(A)[1]^(A)[4];\
    (AA)[2]=(A)[2]^(A)[5];\
    (BB)[0]=(B)[0]^(B)[3];\
    (BB)[1]=(B)[1]^(B)[4];\
    (BB)[2]=(B)[2]^(B)[5];\
    GEMSS_MUL192_NO_SIMD_GF2X(RESERVED_BUF6,AA,BB,tmp,tmp1,tmp2);\
    (C)[3]^=RESERVED_BUF6[0];\
    (C)[4]^=RESERVED_BUF6[1];\
    (C)[5]^=RESERVED_BUF6[2];\
    (C)[6]^=RESERVED_BUF6[3];\
    (C)[7]^=RESERVED_BUF6[4];\
    (C)[8]^=RESERVED_BUF6[5];}


/* Karatsuba, 9171 = 3050*3+21 instructions */
#define GEMSS_MUL384_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_MUL192_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL192_NO_SIMD_GF2X((C)+6,(A)+3,(B)+3,tmp,tmp1,tmp2);\
    (C)[6]^=(C)[3];\
    (C)[7]^=(C)[4];\
    (C)[8]^=(C)[5];\
    (C)[3]=(C)[6]^(C)[0];\
    (C)[4]=(C)[7]^(C)[1];\
    (C)[5]=(C)[8]^(C)[2];\
    (C)[6]^=(C)[9];\
    (C)[7]^=(C)[10];\
    (C)[8]^=(C)[11];\
    (AA)[0]=(A)[0]^(A)[3];\
    (AA)[1]=(A)[1]^(A)[4];\
    (AA)[2]=(A)[2]^(A)[5];\
    (BB)[0]=(B)[0]^(B)[3];\
    (BB)[1]=(B)[1]^(B)[4];\
    (BB)[2]=(B)[2]^(B)[5];\
    GEMSS_MUL192_NO_SIMD_GF2X(RESERVED_BUF6,AA,BB,tmp,tmp1,tmp2);\
    (C)[3]^=RESERVED_BUF6[0];\
    (C)[4]^=RESERVED_BUF6[1];\
    (C)[5]^=RESERVED_BUF6[2];\
    (C)[6]^=RESERVED_BUF6[3];\
    (C)[7]^=RESERVED_BUF6[4];\
    (C)[8]^=RESERVED_BUF6[5];}


/* Karatsuba, 11603 = 4264*2+3050+25 instructions */
#define GEMSS_MUL416_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2) \
    { uint64_t RESERVED_BUF8[7];\
    GEMSS_MUL192_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL224_NO_SIMD_GF2X((C)+6,(A)+3,(B)+3,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[6]^=(C)[3];\
    (C)[7]^=(C)[4];\
    (C)[8]^=(C)[5];\
    (C)[3]=(C)[6]^(C)[0];\
    (C)[4]=(C)[7]^(C)[1];\
    (C)[5]=(C)[8]^(C)[2];\
    (C)[6]^=(C)[9];\
    (C)[7]^=(C)[10];\
    (C)[8]^=(C)[11];\
    (C)[9]^=(C)[12];\
    (AA)[0]=(A)[0]^(A)[3];\
    (AA)[1]=(A)[1]^(A)[4];\
    (AA)[2]=(A)[2]^(A)[5];\
    (AA)[3]=(A)[6];\
    (BB)[0]=(B)[0]^(B)[3];\
    (BB)[1]=(B)[1]^(B)[4];\
    (BB)[2]=(B)[2]^(B)[5];\
    (BB)[3]=(B)[6];\
    GEMSS_MUL224_NO_SIMD_GF2X(RESERVED_BUF8,AA,BB,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[3]^=RESERVED_BUF8[0];\
    (C)[4]^=RESERVED_BUF8[1];\
    (C)[5]^=RESERVED_BUF8[2];\
    (C)[6]^=RESERVED_BUF8[3];\
    (C)[7]^=RESERVED_BUF8[4];\
    (C)[8]^=RESERVED_BUF8[5];\
    (C)[9]^=RESERVED_BUF8[6];}


/* Karatsuba, 12241 = 4582*2+3050+27 instructions */
#define GEMSS_MUL448_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_MUL192_NO_SIMD_GF2X(C,A,B,tmp,tmp1,tmp2);\
    GEMSS_MUL256_NO_SIMD_GF2X((C)+6,(A)+3,(B)+3,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[6]^=(C)[3];\
    (C)[7]^=(C)[4];\
    (C)[8]^=(C)[5];\
    (C)[3]=(C)[6]^(C)[0];\
    (C)[4]=(C)[7]^(C)[1];\
    (C)[5]=(C)[8]^(C)[2];\
    (C)[6]^=(C)[9];\
    (C)[7]^=(C)[10];\
    (C)[8]^=(C)[11];\
    (C)[9]^=(C)[12];\
    (C)[10]^=(C)[13];\
    (AA)[0]=(A)[0]^(A)[3];\
    (AA)[1]=(A)[1]^(A)[4];\
    (AA)[2]=(A)[2]^(A)[5];\
    (AA)[3]=(A)[6];\
    (BB)[0]=(B)[0]^(B)[3];\
    (BB)[1]=(B)[1]^(B)[4];\
    (BB)[2]=(B)[2]^(B)[5];\
    (BB)[3]=(B)[6];\
    GEMSS_MUL256_NO_SIMD_GF2X(RESERVED_BUF8,AA,BB,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[3]^=RESERVED_BUF8[0];\
    (C)[4]^=RESERVED_BUF8[1];\
    (C)[5]^=RESERVED_BUF8[2];\
    (C)[6]^=RESERVED_BUF8[3];\
    (C)[7]^=RESERVED_BUF8[4];\
    (C)[8]^=RESERVED_BUF8[5];\
    (C)[9]^=RESERVED_BUF8[6];\
    (C)[10]^=RESERVED_BUF8[7];}


/* Karatsuba, 13459 = 4582*2+4264+31 instructions */
#define GEMSS_MUL480_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_MUL256_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);\
    GEMSS_MUL224_NO_SIMD_GF2X((C)+8,(A)+4,(B)+4,tmp,AA,BB,tmp1,tmp2);\
    (C)[4]^=(C)[8];\
    (C)[5]^=(C)[9];\
    (C)[6]^=(C)[10];\
    (C)[7]^=(C)[11];\
    (C)[8]=(C)[4];\
    (C)[9]=(C)[5];\
    (C)[10]=(C)[6];\
    (C)[11]=(C)[7];\
    (C)[4]^=(C)[0];\
    (C)[5]^=(C)[1];\
    (C)[6]^=(C)[2];\
    (C)[7]^=(C)[3];\
    (C)[8]^=(C)[12];\
    (C)[9]^=(C)[13];\
    (C)[10]^=(C)[14];\
    (AA)[0]=(A)[0]^(A)[4];\
    (AA)[1]=(A)[1]^(A)[5];\
    (AA)[2]=(A)[2]^(A)[6];\
    (AA)[3]=(A)[3]^(A)[7];\
    (BB)[0]=(B)[0]^(B)[4];\
    (BB)[1]=(B)[1]^(B)[5];\
    (BB)[2]=(B)[2]^(B)[6];\
    (BB)[3]=(B)[3]^(B)[7];\
    GEMSS_MUL256_NO_SIMD_GF2X(RESERVED_BUF8,AA,BB,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[4]^=RESERVED_BUF8[0];\
    (C)[5]^=RESERVED_BUF8[1];\
    (C)[6]^=RESERVED_BUF8[2];\
    (C)[7]^=RESERVED_BUF8[3];\
    (C)[8]^=RESERVED_BUF8[4];\
    (C)[9]^=RESERVED_BUF8[5];\
    (C)[10]^=RESERVED_BUF8[6];\
    (C)[11]^=RESERVED_BUF8[7];}


/* Karatsuba, 13778 = 4582*3+32 instructions */
#define GEMSS_MUL512_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_MUL256_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);\
    GEMSS_MUL256_NO_SIMD_GF2X((C)+8,(A)+4,(B)+4,tmp,AA,BB,tmp1,tmp2);\
    (C)[4]^=(C)[8];\
    (C)[5]^=(C)[9];\
    (C)[6]^=(C)[10];\
    (C)[7]^=(C)[11];\
    (C)[8]=(C)[4];\
    (C)[9]=(C)[5];\
    (C)[10]=(C)[6];\
    (C)[11]=(C)[7];\
    (C)[4]^=(C)[0];\
    (C)[5]^=(C)[1];\
    (C)[6]^=(C)[2];\
    (C)[7]^=(C)[3];\
    (C)[8]^=(C)[12];\
    (C)[9]^=(C)[13];\
    (C)[10]^=(C)[14];\
    (C)[11]^=(C)[15];\
    (AA)[0]=(A)[0]^(A)[4];\
    (AA)[1]=(A)[1]^(A)[5];\
    (AA)[2]=(A)[2]^(A)[6];\
    (AA)[3]=(A)[3]^(A)[7];\
    (BB)[0]=(B)[0]^(B)[4];\
    (BB)[1]=(B)[1]^(B)[5];\
    (BB)[2]=(B)[2]^(B)[6];\
    (BB)[3]=(B)[3]^(B)[7];\
    GEMSS_MUL256_NO_SIMD_GF2X(RESERVED_BUF8,AA,BB,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[4]^=RESERVED_BUF8[0];\
    (C)[5]^=RESERVED_BUF8[1];\
    (C)[6]^=RESERVED_BUF8[2];\
    (C)[7]^=RESERVED_BUF8[3];\
    (C)[8]^=RESERVED_BUF8[4];\
    (C)[9]^=RESERVED_BUF8[5];\
    (C)[10]^=RESERVED_BUF8[6];\
    (C)[11]^=RESERVED_BUF8[7];}


/* Karatsuba, 18626 = 7006*2+4582+32 instructions */
#define GEMSS_MUL544_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2) \
    { uint64_t RESERVED_BUF10[9];\
    GEMSS_MUL256_NO_SIMD_GF2X(C,A,B,tmp,tmp3,tmp4,tmp1,tmp2);\
    GEMSS_MUL288_NO_SIMD_GF2X((C)+8,(A)+4,(B)+4,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[8]^=(C)[4];\
    (C)[9]^=(C)[5];\
    (C)[10]^=(C)[6];\
    (C)[11]^=(C)[7];\
    (C)[4]=(C)[8]^(C)[0];\
    (C)[5]=(C)[9]^(C)[1];\
    (C)[6]=(C)[10]^(C)[2];\
    (C)[7]=(C)[11]^(C)[3];\
    (C)[8]^=(C)[12];\
    (C)[9]^=(C)[13];\
    (C)[10]^=(C)[14];\
    (C)[11]^=(C)[15];\
    (C)[12]^=(C)[16];\
    (AA)[0]=(A)[0]^(A)[4];\
    (AA)[1]=(A)[1]^(A)[5];\
    (AA)[2]=(A)[2]^(A)[6];\
    (AA)[3]=(A)[3]^(A)[7];\
    (AA)[4]=(A)[8];\
    (BB)[0]=(B)[0]^(B)[4];\
    (BB)[1]=(B)[1]^(B)[5];\
    (BB)[2]=(B)[2]^(B)[6];\
    (BB)[3]=(B)[3]^(B)[7];\
    (BB)[4]=(B)[8];\
    GEMSS_MUL288_NO_SIMD_GF2X(RESERVED_BUF10,AA,BB,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[4]^=RESERVED_BUF10[0];\
    (C)[5]^=RESERVED_BUF10[1];\
    (C)[6]^=RESERVED_BUF10[2];\
    (C)[7]^=RESERVED_BUF10[3];\
    (C)[8]^=RESERVED_BUF10[4];\
    (C)[9]^=RESERVED_BUF10[5];\
    (C)[10]^=RESERVED_BUF10[6];\
    (C)[11]^=RESERVED_BUF10[7];\
    (C)[12]^=RESERVED_BUF10[8];}


/* Karatsuba, 19900 = 7642*2+4582+34 instructions */
#define GEMSS_MUL576_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2) \
    { uint64_t RESERVED_BUF10[10];\
    GEMSS_MUL256_NO_SIMD_GF2X(C,A,B,tmp,tmp3,tmp4,tmp1,tmp2);\
    GEMSS_MUL320_NO_SIMD_GF2X((C)+8,(A)+4,(B)+4,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[8]^=(C)[4];\
    (C)[9]^=(C)[5];\
    (C)[10]^=(C)[6];\
    (C)[11]^=(C)[7];\
    (C)[4]=(C)[8]^(C)[0];\
    (C)[5]=(C)[9]^(C)[1];\
    (C)[6]=(C)[10]^(C)[2];\
    (C)[7]=(C)[11]^(C)[3];\
    (C)[8]^=(C)[12];\
    (C)[9]^=(C)[13];\
    (C)[10]^=(C)[14];\
    (C)[11]^=(C)[15];\
    (C)[12]^=(C)[16];\
    (C)[13]^=(C)[17];\
    (AA)[0]=(A)[0]^(A)[4];\
    (AA)[1]=(A)[1]^(A)[5];\
    (AA)[2]=(A)[2]^(A)[6];\
    (AA)[3]=(A)[3]^(A)[7];\
    (AA)[4]=(A)[8];\
    (BB)[0]=(B)[0]^(B)[4];\
    (BB)[1]=(B)[1]^(B)[5];\
    (BB)[2]=(B)[2]^(B)[6];\
    (BB)[3]=(B)[3]^(B)[7];\
    (BB)[4]=(B)[8];\
    GEMSS_MUL320_NO_SIMD_GF2X(RESERVED_BUF10,AA,BB,tmp,tmp3,tmp4,tmp1,tmp2);\
    (C)[4]^=RESERVED_BUF10[0];\
    (C)[5]^=RESERVED_BUF10[1];\
    (C)[6]^=RESERVED_BUF10[2];\
    (C)[7]^=RESERVED_BUF10[3];\
    (C)[8]^=RESERVED_BUF10[4];\
    (C)[9]^=RESERVED_BUF10[5];\
    (C)[10]^=RESERVED_BUF10[6];\
    (C)[11]^=RESERVED_BUF10[7];\
    (C)[12]^=RESERVED_BUF10[8];\
    (C)[13]^=RESERVED_BUF10[9];}


/***********************************************************************/
/***********************************************************************/
/*************************** sse2 version ******************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_SSE2
    uint64_t GEMSS_PREFIX_NAME(GEMSS_pmul32_gf2x)(uint64_t A, uint64_t B);
    void GEMSS_PREFIX_NAME(GEMSS_pmul64_gf2x)(uint64_t C[2], const uint64_t A[1],
                                                 const uint64_t B[1]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul96_gf2x)(uint64_t C[3], const uint64_t A[2],
                                                 const uint64_t B[2]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul128_gf2x)(uint64_t C[4], const uint64_t A[2],
                                                  const uint64_t B[2]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul160_gf2x)(uint64_t C[5], const uint64_t A[3],
                                                  const uint64_t B[3]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul192_gf2x)(uint64_t C[6], const uint64_t A[3],
                                                  const uint64_t B[3]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul224_gf2x)(uint64_t C[7], const uint64_t A[4],
                                                  const uint64_t B[4]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul256_gf2x)(uint64_t C[8], const uint64_t A[4],
                                                  const uint64_t B[4]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul288_gf2x)(uint64_t C[9], const uint64_t A[5],
                                                  const uint64_t B[5]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul320_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                   const uint64_t B[5]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul352_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                   const uint64_t B[6]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul384_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                   const uint64_t B[6]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul416_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                   const uint64_t B[7]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul448_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                   const uint64_t B[7]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul480_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                   const uint64_t B[8]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul512_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                   const uint64_t B[8]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul544_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                   const uint64_t B[9]);
    void GEMSS_PREFIX_NAME(GEMSS_pmul576_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                   const uint64_t B[9]);
    #define GEMSS_pmul32_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul32_gf2x)
    #define GEMSS_pmul64_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul64_gf2x)
    #define GEMSS_pmul96_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul96_gf2x)
    #define GEMSS_pmul128_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul128_gf2x)
    #define GEMSS_pmul160_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul160_gf2x)
    #define GEMSS_pmul192_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul192_gf2x)
    #define GEMSS_pmul224_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul224_gf2x)
    #define GEMSS_pmul256_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul256_gf2x)
    #define GEMSS_pmul288_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul288_gf2x)
    #define GEMSS_pmul320_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul320_gf2x)
    #define GEMSS_pmul352_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul352_gf2x)
    #define GEMSS_pmul384_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul384_gf2x)
    #define GEMSS_pmul416_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul416_gf2x)
    #define GEMSS_pmul448_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul448_gf2x)
    #define GEMSS_pmul480_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul480_gf2x)
    #define GEMSS_pmul512_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul512_gf2x)
    #define GEMSS_pmul544_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul544_gf2x)
    #define GEMSS_pmul576_gf2x GEMSS_PREFIX_NAME(GEMSS_pmul576_gf2x)
#endif


/* ~ 2*8 = 16 instructions */
/* Classical, 31 = 9+10+12 instructions */
#define GEMSS_PMUL16_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one16) \
    RA=GEMSS_PSET1_16(A0);\
    RB=GEMSS_PSET_16((B0)>>14,(B0)>>10,(B0)>>6,(B0)>>2,(B0)>>12,(B0)>>8,(B0)>>4,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK16_ONE(GEMSS_PAND_(RB,one16),one16));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK16_ONE(GEMSS_PAND_(GEMSS_PSRLI_16(RB,1),one16),one16));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_16(M,1));\
    CH=GEMSS_PSRLI_16(M,15);\
\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_16(CL,CH),GEMSS_PSLLI_32(GEMSS_PUNPACKHI_16(CL,CH),2));\
    GEMSS_PXOR1_2(C1,GEMSS_PSRLI_128(C1,7));\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_32(GEMSS_PSRLI_128(C1,4),4));\
    GEMSS_PAND1_2(C1,GEMSS_PSET_32(0,0,0,GEMSS_MONE32));


/* ~ 4*6 = 24 instructions */
/* Classical, 33 = 5+21+7 instructions */
#define GEMSS_PMUL16_WS_CLAS0_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32) \
    RA=GEMSS_PSET1_32(A0);\
    RB=GEMSS_PSET_32((B0)>>12,(B0)>>4,(B0)>>8,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(RB,one32),one32));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,1),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,1));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,2),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,2));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,3),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,3));\
\
    CH=GEMSS_PXOR_(CL,GEMSS_PSRLI_128(GEMSS_PSLLI_32(CL,4),8));\
    C1=GEMSS_PXOR_(CH,GEMSS_PSRLI_128(CH,3));\
    GEMSS_PAND1_2(C1,GEMSS_PSET_32(0,0,0,GEMSS_MONE32));


/* ~ 8*8 = 64 instructions */
/* Classical, 72 = 5+59+8 instructions */
#define GEMSS_PMUL32_NO_UNROLLED_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32,i) \
    RA=GEMSS_PSET1_32(A0);\
    RB=GEMSS_PSET_32((B0)>>24,(B0)>>8,(B0)>>16,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(RB,one32),one32));\
    CH=GEMSS_PSETZERO();\
    for(i=1;i<8;++i)\
    {\
        M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,i),one32),one32));\
        GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,i));\
        GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,32-i));\
    }\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_32(CL,CH),GEMSS_PSLLI_128(GEMSS_PUNPACKHI_32(CL,CH),1));\
    GEMSS_PXOR1_2(C1,GEMSS_PSRLI_128(C1,6));\
    GEMSS_PAND1_2(C1,GEMSS_PSET_64(0,GEMSS_MONE64));


/* ~ 8*8 = 64 instructions */
/* Classical, 71 = 5+58+8 instructions */
/* The fastest method */
#define GEMSS_PMUL32_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32) \
    RA=GEMSS_PSET1_32(A0);\
    RB=GEMSS_PSET_32((B0)>>24,(B0)>>8,(B0)>>16,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(RB,one32),one32));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,1),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,1));\
    CH=GEMSS_PSRLI_32(M,31);\
\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,2),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,2));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,30));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,3),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,3));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,29));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,4),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,4));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,28));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,5),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,5));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,27));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,6),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,6));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,26));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,7),one32),one32));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,7));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,25));\
\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_32(CL,CH),GEMSS_PSLLI_128(GEMSS_PUNPACKHI_32(CL,CH),1));\
    GEMSS_PXOR1_2(C1,GEMSS_PSRLI_128(C1,6));\
    GEMSS_PAND1_2(C1,GEMSS_PSET_64(0,GEMSS_MONE64));


/* Karatsuba, 103 = 3*31+10 instructions */
/* Really slow */
#define GEMSS_PMUL32_WS_KAR_CLAS16_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,one16) \
    GEMSS_PMUL16_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one16);\
    GEMSS_PMUL16_WS_CLAS_GF2X(M,(A0)>>16,(B0)>>16,RA,RB,CL,CH,M,one16);\
    CM=GEMSS_PXOR_(C1,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,4));\
    GEMSS_PMUL16_WS_CLAS_GF2X(M,(A0)^((A0)>>16),(B0)^((B0)>>16),RA,RB,CL,CH,M,one16);\
\
    M=GEMSS_PXOR_(CM,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,2));


/* Karatsuba, 109 = 3*33+10 instructions */
/* The fastest Karatsuba method */
#define GEMSS_PMUL32_WS_KAR_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,one32) \
    GEMSS_PMUL16_WS_CLAS0_GF2X(C1,(A0)&GEMSS_MONE16,B0,RA,RB,CL,CH,M,one32);\
    GEMSS_PMUL16_WS_CLAS0_GF2X(M,((A0)>>16)&GEMSS_MONE16,(B0)>>16,RA,RB,CL,CH,M,one32);\
    CM=GEMSS_PXOR_(C1,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,4));\
    GEMSS_PMUL16_WS_CLAS0_GF2X(M,((A0)^((A0)>>16))&GEMSS_MONE16,(B0)^((B0)>>16),\
                         RA,RB,CL,CH,M,one32);\
\
    M=GEMSS_PXOR_(CM,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,2));


/* ~ 32*8 = 256 instructions */
/* Classical, 258 = 3+251+4 instructions */
#define GEMSS_PMUL64_NO_UNROLLED_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one64,i) \
    RA=GEMSS_PSET1_64(A0);\
    RB=GEMSS_PSET_64((B0)>>32,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(RB,one64),one64));\
    CH=GEMSS_PSETZERO();\
    for(i=1;i<32;++i)\
    {\
        M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,i),one64),one64));\
        GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,i));\
        GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,64-i));\
    }\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_64(CL,CH),GEMSS_PSLLI_128(GEMSS_PUNPACKHI_64(CL,CH),4));


/* ~ 32*8 = 256 instructions */
/* Classical, 257 = 3+250+4 instructions */
#define GEMSS_PMUL64_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one64) \
    RA=GEMSS_PSET1_64(A0);\
    RB=GEMSS_PSET_64((B0)>>32,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(RB,one64),one64));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,1),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,1));\
    CH=GEMSS_PSRLI_64(M,63);\
\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,2),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,2));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,62));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,3),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,3));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,61));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,4),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,4));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,60));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,5),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,5));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,59));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,6),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,6));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,58));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,7),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,7));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,57));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,8),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,8));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,56));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,9),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,9));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,55));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,10),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,10));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,54));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,11),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,11));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,53));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,12),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,12));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,52));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,13),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,13));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,51));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,14),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,14));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,50));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,15),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,15));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,49));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,16),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,16));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,48));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,17),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,17));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,47));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,18),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,18));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,46));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,19),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,19));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,45));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,20),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,20));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,44));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,21),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,21));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,43));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,22),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,22));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,42));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,23),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,23));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,41));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,24),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,24));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,40));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,25),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,25));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,39));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,26),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,26));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,38));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,27),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,27));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,37));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,28),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,28));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,36));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,29),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,29));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,35));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,30),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,30));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,34));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,31),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,31));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,33));\
\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_64(CL,CH),GEMSS_PSLLI_128(GEMSS_PUNPACKHI_64(CL,CH),4));


/* ~ 16*13 = 208 instructions */
/* Classical, 220 = 7+199+14 instructions */
#define GEMSS_PMUL64_NO_UNROLLED_WS_CLAS2_GF2X(C1,A0,B0,RA,RAM,RB,CL,CH,CLM,CHM,M,\
                                         one32,i) \
    RA=GEMSS_PSET_32((A0)>>32,(A0)>>32,A0,A0);\
    RAM=GEMSS_PSET_32(A0,A0,(A0)>>32,(A0)>>32);\
    RB=GEMSS_PSET_32((B0)>>48,(B0)>>32,(B0)>>16,B0);\
\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(RB,one32),one32);\
    CL=GEMSS_PAND_(RA,C1);\
    CH=GEMSS_PSETZERO();\
    CLM=GEMSS_PAND_(RAM,C1);\
    CHM=GEMSS_PSETZERO();\
    for(i=1;i<16;++i)\
    {\
        C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,i),one32),one32);\
        M=GEMSS_PAND_(RA,C1);\
        GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,i));\
        GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,32-i));\
        M=GEMSS_PAND_(RAM,C1);\
        GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,i));\
        GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,32-i));\
    }\
\
    RAM=GEMSS_PXOR_(GEMSS_PUNPACKLO_32(CLM,CHM),GEMSS_PUNPACKHI_32(CLM,CHM));\
    CLM=GEMSS_PUNPACKLO_32(CL,CH);\
    CHM=GEMSS_PUNPACKHI_32(CL,CH);\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_64(CLM,CHM),GEMSS_PSLLI_128(GEMSS_PUNPACKHI_64(CLM,CHM),2));\
    GEMSS_PXOR1_2(C1,\
            GEMSS_PSLLI_128(GEMSS_PAND_(GEMSS_PXOR_(RAM,GEMSS_PSRLI_128(RAM,6)),GEMSS_PSET_64(0,GEMSS_MONE64)),4));


/* ~ 16*13 = 208 instructions */
/* Classical, 219 = 7+198+14 instructions */
/* The fastest method */
#define GEMSS_PMUL64_WS_CLAS2_GF2X(C1,A0,B0,RA,RAM,RB,CL,CH,CLM,CHM,M,one32) \
    RA=GEMSS_PSET_32((A0)>>32,(A0)>>32,A0,A0);\
    RAM=GEMSS_PSET_32(A0,A0,(A0)>>32,(A0)>>32);\
    RB=GEMSS_PSET_32((B0)>>48,(B0)>>32,(B0)>>16,B0);\
\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(RB,one32),one32);\
    CL=GEMSS_PAND_(RA,C1);\
    CLM=GEMSS_PAND_(RAM,C1);\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,1),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,1));\
    CH=GEMSS_PSRLI_32(M,31);\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,1));\
    CHM=GEMSS_PSRLI_32(M,31);\
\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,2),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,2));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,30));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,2));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,30));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,3),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,3));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,29));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,3));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,29));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,4),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,4));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,28));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,4));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,28));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,5),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,5));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,27));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,5));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,27));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,6),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,6));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,26));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,6));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,26));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,7),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,7));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,25));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,7));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,25));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,8),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,8));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,24));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,8));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,24));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,9),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,9));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,23));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,9));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,23));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,10),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,10));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,22));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,10));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,22));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,11),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,11));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,21));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,11));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,21));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,12),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,12));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,20));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,12));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,20));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,13),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,13));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,19));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,13));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,19));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,14),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,14));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,18));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,14));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,18));\
    C1=GEMSS_PMASK32_ONE(GEMSS_PAND_(GEMSS_PSRLI_32(RB,15),one32),one32);\
    M=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_32(M,15));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_32(M,17));\
    M=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_32(M,15));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_32(M,17));\
\
    RAM=GEMSS_PXOR_(GEMSS_PUNPACKLO_32(CLM,CHM),GEMSS_PUNPACKHI_32(CLM,CHM));\
    CLM=GEMSS_PUNPACKLO_32(CL,CH);\
    CHM=GEMSS_PUNPACKHI_32(CL,CH);\
    C1=GEMSS_PXOR_(GEMSS_PUNPACKLO_64(CLM,CHM),GEMSS_PSLLI_128(GEMSS_PUNPACKHI_64(CLM,CHM),2));\
    GEMSS_PXOR1_2(C1,\
            GEMSS_PSLLI_128(GEMSS_PAND_(GEMSS_PXOR_(RAM,GEMSS_PSRLI_128(RAM,6)),GEMSS_PSET_64(0,GEMSS_MONE64)),4));


/* Karatsuba, 337 = 109*3+10 instructions */
#define GEMSS_PMUL64_WS_KAR_KAR32_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,CM1,CM2,one32) \
    GEMSS_PMUL32_WS_KAR_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM1,one32);\
    GEMSS_PMUL32_WS_KAR_GF2X(M,(A0)>>32,(B0)>>32,RA,RB,CL,CH,CM1,CM2,one32);\
    CM=GEMSS_PXOR_(C1,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,8));\
    GEMSS_PMUL32_WS_KAR_GF2X(M,(A0)^((A0)>>32),(B0)^((B0)>>32),\
                       RA,RB,CL,CH,CM1,CM2,one32);\
\
    M=GEMSS_PXOR_(CM,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,4));


/* Karatsuba, 223 = 71*3+10 instructions */
/* The fastest Karatsuba method */
#define GEMSS_PMUL64_WS_KAR_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,one32) \
    GEMSS_PMUL32_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32);\
    GEMSS_PMUL32_WS_CLAS_GF2X(M,(A0)>>32,(B0)>>32,RA,RB,CL,CH,M,one32);\
    CM=GEMSS_PXOR_(C1,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,8));\
    GEMSS_PMUL32_WS_CLAS_GF2X(M,(A0)^((A0)>>32),(B0)^((B0)>>32),RA,RB,CL,CH,M,one32);\
\
    M=GEMSS_PXOR_(CM,M);\
    GEMSS_PXOR1_2(C1,GEMSS_PSLLI_128(M,4));


/* Double mul64 in parallel */
/* ~ 64*8 = 512 instructions */
/* Classical, 511 = 2+507+2 instructions */
#define GEMSS_PMUL64x2_NO_UNROLLED_WS_CLAS_GF2X(C1,C2,A0,A1,B0,B1,RA,RB,CL,CH,M,\
                                          one64,i) \
    RA=GEMSS_PSET_64(A1,A0);\
    RB=GEMSS_PSET_64(B1,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(RB,one64),one64));\
    CH=GEMSS_PSETZERO();\
    for(i=1;i<64;++i)\
    {\
        M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,i),one64),one64));\
        GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,i));\
        GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,64-i));\
    }\
    C1=GEMSS_PUNPACKLO_64(CL,CH);\
    C2=GEMSS_PUNPACKHI_64(CL,CH);


/* ~ 64*8 = 512 instructions */
/* Classical, 509 = 2+505+2 instructions */
#define GEMSS_PMUL64x2_WS_CLAS_GF2X(C1,C2,A0,A1,B0,B1,RA,RB,M,one64) \
    RA=GEMSS_PSET_64(A1,A0);\
    RB=GEMSS_PSET_64(B1,B0);\
\
    CL=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(RB,one64),one64));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,1),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,1));\
    CH=GEMSS_PSRLI_64(M,63);\
\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,2),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,2));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,62));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,3),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,3));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,61));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,4),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,4));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,60));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,5),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,5));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,59));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,6),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,6));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,58));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,7),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,7));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,57));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,8),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,8));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,56));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,9),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,9));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,55));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,10),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,10));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,54));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,11),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,11));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,53));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,12),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,12));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,52));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,13),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,13));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,51));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,14),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,14));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,50));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,15),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,15));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,49));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,16),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,16));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,48));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,17),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,17));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,47));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,18),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,18));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,46));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,19),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,19));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,45));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,20),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,20));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,44));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,21),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,21));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,43));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,22),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,22));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,42));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,23),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,23));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,41));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,24),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,24));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,40));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,25),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,25));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,39));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,26),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,26));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,38));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,27),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,27));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,37));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,28),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,28));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,36));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,29),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,29));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,35));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,30),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,30));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,34));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,31),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,31));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,33));\
\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,32),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,32));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,32));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,33),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,33));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,31));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,34),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,34));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,30));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,35),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,35));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,29));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,36),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,36));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,28));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,37),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,37));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,27));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,38),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,38));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,26));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,39),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,39));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,25));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,40),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,40));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,24));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,41),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,41));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,23));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,42),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,42));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,22));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,43),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,43));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,21));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,44),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,44));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,20));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,45),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,45));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,19));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,46),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,46));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,18));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,47),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,47));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,17));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,48),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,48));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,16));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,49),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,49));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,15));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,50),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,50));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,14));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,51),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,51));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,13));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,52),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,52));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,12));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,53),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,53));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,11));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,54),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,54));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,10));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,55),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,55));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,9));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,56),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,56));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,8));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,57),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,57));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,7));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,58),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,58));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,6));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,59),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,59));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,5));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,60),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,60));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,4));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,61),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,61));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,3));\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,62),one64),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,62));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,2));\
    /* Optimization: the '&1' is removed */\
    M=GEMSS_PAND_(RA,GEMSS_PMASK64_ONE(GEMSS_PSRLI_64(RB,63),one64));\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(M,63));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(M,1));\
\
    C1=GEMSS_PUNPACKLO_64(CL,CH);\
    C2=GEMSS_PUNPACKHI_64(CL,CH);\


/* Karatsuba, 525 = 223*2+71*1+8 instructions */
#define GEMSS_PMUL96_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,M2,CM,one32) \
    GEMSS_PMUL64_WS_KAR_GF2X(C1,(A)[0],(B)[0],RA,RB,CL,CH,M,CM,one32);\
    GEMSS_PMUL32_WS_CLAS_GF2X(C2,(A)[1],(B)[1],RA,RB,CL,CH,M,one32);\
    GEMSS_PMUL64_WS_KAR_GF2X(CM,(A)[0]^(A)[1],(B)[0]^(B)[1],RA,RB,CL,CH,M,M2,one32);\
\
    GEMSS_PXOR1_2(CM,C1);\
    GEMSS_PXOR1_2(CM,C2);\
    GEMSS_PXOR1_2(C1,GEMSS_PLSHIFT64(CM));\
    GEMSS_PXOR1_2(C2,GEMSS_PRSHIFT64(CM));


/* ~ 64*13 = 832 instructions */
/* Classical, 835 = 3+823+9 instructions */
/* The fastest classical method */
#define GEMSS_PMUL128_NO_UNROLLED_WS_CLAS_GF2X(C1,C2,A,B,RA,RAM,RB,CL,CH,CLM,CHM,\
                                         one64,i) \
    RA=GEMSS_PSET_64((A)[1],(A)[0]);\
    RAM=GEMSS_PSET_64((A)[0],(A)[1]);\
    RB=GEMSS_PSET_64((B)[1],(B)[0]);\
\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(RB,one64),one64);\
    CL=GEMSS_PAND_(RA,C1);\
    CH=GEMSS_PSETZERO();\
    CLM=GEMSS_PAND_(RAM,C1);\
    CHM=GEMSS_PSETZERO();\
    for(i=1;i<64;++i)\
    {\
        C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,i),one64),one64);\
        C2=GEMSS_PAND_(RA,C1);\
        GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,i));\
        GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,64-i));\
        C2=GEMSS_PAND_(RAM,C1);\
        GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,i));\
        GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,64-i));\
    }\
    C1=GEMSS_PUNPACKLO_64(CL,CH);\
    C2=GEMSS_PUNPACKHI_64(CL,CH);\
\
    RAM=GEMSS_PXOR_(GEMSS_PUNPACKLO_64(CLM,CHM),GEMSS_PUNPACKHI_64(CLM,CHM));\
    GEMSS_PXOR1_2(C1,GEMSS_PLSHIFT64(RAM));\
    GEMSS_PXOR1_2(C2,GEMSS_PRSHIFT64(RAM));


/* ~ 64*13 = 832 instructions */
/* Classical, 832 = 3+820+9 instructions */
#define GEMSS_PMUL128_WS_CLAS_GF2X(C1,C2,A,B,RA,RAM,RB,CL,CH,CLM,CHM,one64) \
    RA=GEMSS_PSET_64((A)[1],(A)[0]);\
    RAM=GEMSS_PSET_64((A)[0],(A)[1]);\
    RB=GEMSS_PSET_64((B)[1],(B)[0]);\
\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(RB,one64),one64);\
    CL=GEMSS_PAND_(RA,C1);\
    CLM=GEMSS_PAND_(RAM,C1);\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,1),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,1));\
    CH=GEMSS_PSRLI_64(C2,63);\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,1));\
    CHM=GEMSS_PSRLI_64(C2,63);\
\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,2),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,2));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,62));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,2));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,62));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,3),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,3));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,61));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,3));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,61));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,4),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,4));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,60));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,4));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,60));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,5),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,5));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,59));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,5));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,59));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,6),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,6));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,58));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,6));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,58));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,7),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,7));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,57));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,7));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,57));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,8),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,8));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,56));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,8));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,56));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,9),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,9));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,55));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,9));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,55));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,10),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,10));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,54));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,10));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,54));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,11),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,11));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,53));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,11));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,53));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,12),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,12));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,52));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,12));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,52));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,13),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,13));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,51));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,13));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,51));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,14),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,14));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,50));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,14));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,50));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,15),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,15));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,49));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,15));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,49));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,16),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,16));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,48));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,16));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,48));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,17),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,17));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,47));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,17));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,47));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,18),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,18));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,46));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,18));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,46));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,19),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,19));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,45));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,19));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,45));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,20),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,20));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,44));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,20));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,44));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,21),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,21));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,43));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,21));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,43));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,22),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,22));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,42));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,22));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,42));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,23),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,23));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,41));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,23));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,41));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,24),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,24));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,40));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,24));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,40));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,25),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,25));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,39));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,25));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,39));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,26),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,26));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,38));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,26));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,38));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,27),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,27));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,37));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,27));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,37));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,28),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,28));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,36));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,28));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,36));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,29),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,29));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,35));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,29));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,35));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,30),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,30));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,34));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,30));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,34));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,31),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,31));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,33));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,31));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,33));\
\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,32),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,32));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,32));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,32));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,32));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,33),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,33));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,31));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,33));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,31));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,34),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,34));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,30));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,34));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,30));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,35),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,35));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,29));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,35));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,29));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,36),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,36));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,28));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,36));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,28));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,37),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,37));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,27));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,37));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,27));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,38),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,38));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,26));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,38));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,26));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,39),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,39));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,25));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,39));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,25));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,40),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,40));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,24));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,40));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,24));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,41),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,41));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,23));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,41));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,23));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,42),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,42));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,22));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,42));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,22));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,43),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,43));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,21));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,43));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,21));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,44),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,44));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,20));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,44));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,20));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,45),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,45));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,19));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,45));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,19));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,46),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,46));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,18));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,46));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,18));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,47),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,47));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,17));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,47));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,17));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,48),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,48));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,16));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,48));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,16));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,49),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,49));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,15));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,49));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,15));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,50),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,50));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,14));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,50));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,14));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,51),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,51));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,13));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,51));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,13));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,52),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,52));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,12));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,52));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,12));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,53),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,53));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,11));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,53));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,11));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,54),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,54));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,10));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,54));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,10));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,55),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,55));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,9));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,55));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,9));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,56),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,56));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,8));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,56));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,8));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,57),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,57));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,7));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,57));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,7));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,58),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,58));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,6));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,58));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,6));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,59),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,59));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,5));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,59));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,5));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,60),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,60));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,4));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,60));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,4));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,61),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,61));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,3));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,61));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,3));\
    C1=GEMSS_PMASK64_ONE(GEMSS_PAND_(GEMSS_PSRLI_64(RB,62),one64),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,62));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,2));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,62));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,2));\
    /* Optimization: the '&1' is removed */\
    C1=GEMSS_PMASK64_ONE(GEMSS_PSRLI_64(RB,63),one64);\
    C2=GEMSS_PAND_(RA,C1);\
    GEMSS_PXOR1_2(CL,GEMSS_PSLLI_64(C2,63));\
    GEMSS_PXOR1_2(CH,GEMSS_PSRLI_64(C2,1));\
    C2=GEMSS_PAND_(RAM,C1);\
    GEMSS_PXOR1_2(CLM,GEMSS_PSLLI_64(C2,63));\
    GEMSS_PXOR1_2(CHM,GEMSS_PSRLI_64(C2,1));\
\
    C1=GEMSS_PUNPACKLO_64(CL,CH);\
    C2=GEMSS_PUNPACKHI_64(CL,CH);\
\
    RAM=GEMSS_PXOR_(GEMSS_PUNPACKLO_64(CLM,CHM),GEMSS_PUNPACKHI_64(CLM,CHM));\
    GEMSS_PXOR1_2(C1,GEMSS_PLSHIFT64(RAM));\
    GEMSS_PXOR1_2(C2,GEMSS_PRSHIFT64(RAM));


/* Karatsuba, 779 = 257*3+8 instructions */
#define GEMSS_PMUL128_WS_KAR_CLAS_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,CM,one64) \
    GEMSS_PMUL64_WS_CLAS_GF2X(C1,(A)[0],(B)[0],RA,RB,CL,CH,M,one64);\
    GEMSS_PMUL64_WS_CLAS_GF2X(C2,(A)[1],(B)[1],RA,RB,CL,CH,M,one64);\
    GEMSS_PMUL64_WS_CLAS_GF2X(CM,(A)[0]^(A)[1],(B)[0]^(B)[1],RA,RB,CL,CH,M,one64);\
\
    GEMSS_PXOR1_2(CM,C1);\
    GEMSS_PXOR1_2(CM,C2);\
    GEMSS_PXOR1_2(C1,GEMSS_PLSHIFT64(CM));\
    GEMSS_PXOR1_2(C2,GEMSS_PRSHIFT64(CM));


/* Karatsuba, 665 = 219*3+8 instructions */
#define GEMSS_PMUL128_WS_KAR_CLAS2_GF2X(C1,C2,A,B,RA,RAM,RB,CL,CH,M,CM,CLM,CHM,one32)\
    GEMSS_PMUL64_WS_CLAS2_GF2X(C1,(A)[0],(B)[0],RA,RAM,RB,CL,CH,CLM,CHM,M,one32);\
    GEMSS_PMUL64_WS_CLAS2_GF2X(C2,(A)[1],(B)[1],RA,RAM,RB,CL,CH,CLM,CHM,M,one32);\
    GEMSS_PMUL64_WS_CLAS2_GF2X(CM,(A)[0]^(A)[1],(B)[0]^(B)[1],\
                         RA,RAM,RB,CL,CH,CLM,CHM,M,one32);\
\
    GEMSS_PXOR1_2(CM,C1);\
    GEMSS_PXOR1_2(CM,C2);\
    GEMSS_PXOR1_2(C1,GEMSS_PLSHIFT64(CM));\
    GEMSS_PXOR1_2(C2,GEMSS_PRSHIFT64(CM));


/* Karatsuba, 677 = 223*3+8 instructions */
/* The fastest method */
#define GEMSS_PMUL128_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,M2,CM,one32) \
    GEMSS_PMUL64_WS_KAR_GF2X(C1,(A)[0],(B)[0],RA,RB,CL,CH,M,CM,one32);\
    GEMSS_PMUL64_WS_KAR_GF2X(C2,(A)[1],(B)[1],RA,RB,CL,CH,M,CM,one32);\
    GEMSS_PMUL64_WS_KAR_GF2X(CM,(A)[0]^(A)[1],(B)[0]^(B)[1],RA,RB,CL,CH,M,M2,one32);\
\
    GEMSS_PXOR1_2(CM,C1);\
    GEMSS_PXOR1_2(CM,C2);\
    GEMSS_PXOR1_2(C1,GEMSS_PLSHIFT64(CM));\
    GEMSS_PXOR1_2(C2,GEMSS_PRSHIFT64(CM));


/* Karatsuba with 6 multiplications, 1204 = 223*5+71*1+18 instructions */
#define GEMSS_PMUL160_WS_KAR6_GF2X(z1,z2,z3,A,B,RA,RB,CL,CH,M,M2,CM,res1,res2,one32) \
    /* A0*B0 */\
    GEMSS_PMUL64_WS_KAR_GF2X(z1,(A)[0],(B)[0],RA,RB,CL,CH,M,CM,one32);\
    /* A1*B1 */\
    GEMSS_PMUL64_WS_KAR_GF2X(z2,(A)[1],(B)[1],RA,RB,CL,CH,M,CM,one32);\
    /* A2*B2 */\
    GEMSS_PMUL32_WS_CLAS_GF2X(z3,(A)[2],(B)[2],RA,RB,CL,CH,M,one32);\
\
    res1=GEMSS_PXOR_(z1,z2);\
    res2=GEMSS_PXOR_(z3,z2);\
    z2=GEMSS_PXOR_(res1,z3);\
    /*  C[0] = C0
        C[1] = C1^(C0^C2)
        C[2] = C2^(C1^C3)^C0^C4
        C[3] = C3^(C4^C2)^C1^C5
        C[4] = C4^(C5^C3)
        C[5] = C5 */\
    /* (A1 A1) */\
    GEMSS_PMUL64_WS_KAR_GF2X(M2,((A)[0]^(A)[1]),((B)[0]^(B)[1]),RA,RB,\
                       CL,CH,M,CM,one32);\
    GEMSS_PXOR1_2(res1,M2);\
    /* (A1+A2)*(B1+B2) */\
    GEMSS_PMUL64_WS_KAR_GF2X(M2,((A)[1]^(A)[2]),((B)[1]^(B)[2]),RA,RB,\
                       CL,CH,M,CM,one32);\
    GEMSS_PXOR1_2(res2,M2);\
    /* (A0+A2)*(B0+B2) */\
    GEMSS_PMUL64_WS_KAR_GF2X(M2,((A)[0]^(A)[2]),((B)[0]^(B)[2]),RA,RB,\
                       CL,CH,M,CM,one32);\
    GEMSS_PXOR1_2(z2,M2);\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(res1));\
    GEMSS_PXOR1_2(z3,GEMSS_PRSHIFT64(res2));\
    GEMSS_PXOR1_2(z2,GEMSS_PMIDDLE(res1,res2));


/* Karatsuba with 6 multiplications, 1356 = 223*6+18 instructions */
#define GEMSS_PMUL192_WS_KAR6_GF2X(z1,z2,z3,A,B,RA,RB,CL,CH,M,M2,CM,res1,res2,one32) \
    /* A0*B0 */\
    GEMSS_PMUL64_WS_KAR_GF2X(z1,(A)[0],(B)[0],RA,RB,CL,CH,M,CM,one32);\
    /* A1*B1 */\
    GEMSS_PMUL64_WS_KAR_GF2X(z2,(A)[1],(B)[1],RA,RB,CL,CH,M,CM,one32);\
    /* A2*B2 */\
    GEMSS_PMUL64_WS_KAR_GF2X(z3,(A)[2],(B)[2],RA,RB,CL,CH,M,CM,one32);\
\
    res1=GEMSS_PXOR_(z1,z2);\
    res2=GEMSS_PXOR_(z3,z2);\
    z2=GEMSS_PXOR_(res1,z3);\
    /*  C[0] = C0
        C[1] = C1^(C0^C2)
        C[2] = C2^(C1^C3)^C0^C4
        C[3] = C3^(C4^C2)^C1^C5
        C[4] = C4^(C5^C3)
        C[5] = C5 */\
    /* (A1 A1) */\
    GEMSS_PMUL64_WS_KAR_GF2X(M2,((A)[0]^(A)[1]),((B)[0]^(B)[1]),RA,RB,\
                       CL,CH,M,CM,one32);\
    GEMSS_PXOR1_2(res1,M2);\
    /* (A1+A2)*(B1+B2) */\
    GEMSS_PMUL64_WS_KAR_GF2X(M2,((A)[1]^(A)[2]),((B)[1]^(B)[2]),RA,RB,\
                       CL,CH,M,CM,one32);\
    GEMSS_PXOR1_2(res2,M2);\
    /* (A0+A2)*(B0+B2) */\
    GEMSS_PMUL64_WS_KAR_GF2X(M2,((A)[0]^(A)[2]),((B)[0]^(B)[2]),RA,RB,\
                       CL,CH,M,CM,one32);\
    GEMSS_PXOR1_2(z2,M2);\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(res1));\
    GEMSS_PXOR1_2(z3,GEMSS_PRSHIFT64(res2));\
    GEMSS_PXOR1_2(z2,GEMSS_PMIDDLE(res1,res2));


/* Karatsuba, 1889 = 677*2+525+10 instructions */
#define GEMSS_PMUL224_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32) \
    { uint64_t RESERVED_BUF4[4];\
    GEMSS_PMUL128_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,MM,CM,one32);\
    GEMSS_PMUL96_WS_KAR_GF2X(C3,C4,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,one32);\
    RESERVED_BUF4[0]=(A)[0]^(A)[2];\
    RESERVED_BUF4[1]=(A)[1]^(A)[3];\
    RESERVED_BUF4[2]=(B)[0]^(B)[2];\
    RESERVED_BUF4[3]=(B)[1]^(B)[3];\
    GEMSS_PMUL128_WS_KAR_GF2X(M1,M2,RESERVED_BUF4,RESERVED_BUF4+2,\
                        RA,RB,CL,CH,M,MM,CM,one32);\
\
    GEMSS_PXOR1_2(M1,C1);\
    GEMSS_PXOR1_2(M2,C2);\
    GEMSS_PXOR1_2(M1,C3);\
    GEMSS_PXOR1_2(M2,C4);\
    GEMSS_PXOR1_2(C2,M1);\
    GEMSS_PXOR1_2(C3,M2);}


/* Karatsuba, 2040 = 677*3+9 instructions */
#define GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32) \
    { uint64_t RESERVED_BUF4[4];\
    GEMSS_PMUL128_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,MM,CM,one32);\
    GEMSS_PMUL128_WS_KAR_GF2X(C3,C4,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,one32);\
\
    GEMSS_PXOR1_2(C3,C2);\
    C2=GEMSS_PXOR_(C3,C1);\
    GEMSS_PXOR1_2(C3,C4);\
\
    RESERVED_BUF4[0]=(A)[0]^(A)[2];\
    RESERVED_BUF4[1]=(A)[1]^(A)[3];\
    RESERVED_BUF4[2]=(B)[0]^(B)[2];\
    RESERVED_BUF4[3]=(B)[1]^(B)[3];\
    GEMSS_PMUL128_WS_KAR_GF2X(M1,M2,RESERVED_BUF4,RESERVED_BUF4+2,\
                        RA,RB,CL,CH,M,MM,CM,one32);\
\
    GEMSS_PXOR1_2(C2,M1);\
    GEMSS_PXOR1_2(C3,M2);}


/* Karatsuba, 3098 = 1204*2+677+13 instructions */
#define GEMSS_PMUL288_WS_KAR_GF2X(C1,C2,C3,C4,C5,A,B,RA,RB,CL,CH,M,MM,CM,\
                            M1,M2,M3,res1,res2,one32) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_PMUL128_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,MM,CM,one32)\
    GEMSS_PMUL160_WS_KAR6_GF2X(C3,C4,C5,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,\
                         res1,res2,one32)\
    GEMSS_PXOR1_2(C3,C2);\
    C2=GEMSS_PXOR_(C3,C1);\
    GEMSS_PXOR1_2(C3,C4);\
    GEMSS_PXOR1_2(C4,C5);\
\
    RESERVED_BUF6[0]=(A)[0]^(A)[2];\
    RESERVED_BUF6[1]=(A)[1]^(A)[3];\
    RESERVED_BUF6[2]=(A)[4];\
    RESERVED_BUF6[3]=(B)[0]^(B)[2];\
    RESERVED_BUF6[4]=(B)[1]^(B)[3];\
    RESERVED_BUF6[5]=(B)[4];\
    GEMSS_PMUL160_WS_KAR6_GF2X(M1,M2,M3,RESERVED_BUF6,RESERVED_BUF6+3,RA,RB,CL,CH,\
                         M,MM,CM,res1,res2,one32);\
\
    GEMSS_PXOR1_2(C2,M1);\
    GEMSS_PXOR1_2(C3,M2);\
    GEMSS_PXOR1_2(C4,M3);}


/* Karatsuba, 3402 = 1356*2+677+13 instructions */
#define GEMSS_PMUL320_WS_KAR_GF2X(C1,C2,C3,C4,C5,A,B,RA,RB,CL,CH,M,MM,CM,\
                            M1,M2,M3,res1,res2,one32) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_PMUL128_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,MM,CM,one32)\
    GEMSS_PMUL192_WS_KAR6_GF2X(C3,C4,C5,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,\
                         res1,res2,one32)\
    GEMSS_PXOR1_2(C3,C2);\
    C2=GEMSS_PXOR_(C3,C1);\
    GEMSS_PXOR1_2(C3,C4);\
    GEMSS_PXOR1_2(C4,C5);\
\
    RESERVED_BUF6[0]=(A)[0]^(A)[2];\
    RESERVED_BUF6[1]=(A)[1]^(A)[3];\
    RESERVED_BUF6[2]=(A)[4];\
    RESERVED_BUF6[3]=(B)[0]^(B)[2];\
    RESERVED_BUF6[4]=(B)[1]^(B)[3];\
    RESERVED_BUF6[5]=(B)[4];\
    GEMSS_PMUL192_WS_KAR6_GF2X(M1,M2,M3,RESERVED_BUF6,RESERVED_BUF6+3,RA,RB,CL,CH,\
                         M,MM,CM,res1,res2,one32);\
\
    GEMSS_PXOR1_2(C2,M1);\
    GEMSS_PXOR1_2(C3,M2);\
    GEMSS_PXOR1_2(C4,M3);}


/* Karatsuba, 3936 = 1356*2+1204+20 instructions */
#define GEMSS_PMUL352_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,A,B,RA,RB,CL,CH,M,MM,CM,\
                            M1,M2,M3,res1,res2,one32) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_PMUL192_WS_KAR6_GF2X(C1,C2,C3,A,B,RA,RB,CL,CH,M,MM,CM,res1,res2,one32)\
    GEMSS_PMUL160_WS_KAR6_GF2X(C4,C5,C6,(A)+3,(B)+3,RA,RB,CL,CH,M,MM,CM,\
                         res1,res2,one32)\
\
    RESERVED_BUF6[0]=(A)[0]^(A)[3];\
    RESERVED_BUF6[1]=(A)[1]^(A)[4];\
    RESERVED_BUF6[2]=(A)[2]^(A)[5];\
    RESERVED_BUF6[3]=(B)[0]^(B)[3];\
    RESERVED_BUF6[4]=(B)[1]^(B)[4];\
    RESERVED_BUF6[5]=(B)[2]^(B)[5];\
    GEMSS_PMUL192_WS_KAR6_GF2X(M1,M2,M3,RESERVED_BUF6,RESERVED_BUF6+3,RA,RB,\
                         CL,CH,M,MM,CM,res1,res2,one32)\
\
    GEMSS_PXOR1_2(M1,C1);\
    GEMSS_PXOR1_2(M2,C2);\
    GEMSS_PXOR1_2(M3,C3);\
    GEMSS_PXOR1_2(M1,C4);\
    GEMSS_PXOR1_2(M2,C5);\
    GEMSS_PXOR1_2(M3,C6);\
    GEMSS_PXOR1_2(C2,GEMSS_PLSHIFT64(M1));\
    GEMSS_PXOR1_2(C3,GEMSS_PMIDDLE(M1,M2));\
    GEMSS_PXOR1_2(C4,GEMSS_PMIDDLE(M2,M3));\
    GEMSS_PXOR1_2(C5,GEMSS_PRSHIFT64(M3));}


/* Karatsuba, 4088 = 1356*3+20 instructions */
#define GEMSS_PMUL384_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,A,B,RA,RB,CL,CH,M,MM,CM,\
                            M1,M2,M3,res1,res2,one32) \
    { uint64_t RESERVED_BUF6[6];\
    GEMSS_PMUL192_WS_KAR6_GF2X(C1,C2,C3,A,B,RA,RB,CL,CH,M,MM,CM,res1,res2,one32)\
    GEMSS_PMUL192_WS_KAR6_GF2X(C4,C5,C6,(A)+3,(B)+3,RA,RB,CL,CH,M,MM,CM,\
                         res1,res2,one32)\
\
    RESERVED_BUF6[0]=(A)[0]^(A)[3];\
    RESERVED_BUF6[1]=(A)[1]^(A)[4];\
    RESERVED_BUF6[2]=(A)[2]^(A)[5];\
    RESERVED_BUF6[3]=(B)[0]^(B)[3];\
    RESERVED_BUF6[4]=(B)[1]^(B)[4];\
    RESERVED_BUF6[5]=(B)[2]^(B)[5];\
    GEMSS_PMUL192_WS_KAR6_GF2X(M1,M2,M3,RESERVED_BUF6,RESERVED_BUF6+3,RA,RB,\
                         CL,CH,M,MM,CM,res1,res2,one32)\
\
    GEMSS_PXOR1_2(M1,C1);\
    GEMSS_PXOR1_2(M2,C2);\
    GEMSS_PXOR1_2(M3,C3);\
    GEMSS_PXOR1_2(M1,C4);\
    GEMSS_PXOR1_2(M2,C5);\
    GEMSS_PXOR1_2(M3,C6);\
    GEMSS_PXOR1_2(C2,GEMSS_PLSHIFT64(M1));\
    GEMSS_PXOR1_2(C3,GEMSS_PMIDDLE(M1,M2));\
    GEMSS_PXOR1_2(C4,GEMSS_PMIDDLE(M2,M3));\
    GEMSS_PXOR1_2(C5,GEMSS_PRSHIFT64(M3));}


/* Karatsuba, 5301 = 2040*2+1204+17 instructions */
#define GEMSS_PMUL416_WS_KAR_V1_GF2X(C1,C2,C3,C4,C5,C6,C7,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,M1,M2,M3,M4,one32) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
    GEMSS_PMUL160_WS_KAR6_GF2X(C5,C6,C7,(A)+4,(B)+4,RA,RB,CL,CH,M,M2,CM,\
                         CM1,CM2,one32)\
    C5=GEMSS_PXOR_(C3,C5);\
    C6=GEMSS_PXOR_(C4,C6);\
    C3=GEMSS_PXOR_(C5,C1);\
    C4=GEMSS_PXOR_(C6,C2);\
    C5=GEMSS_PXOR_(C5,C7);\
\
    RESERVED_BUF8[0]=(A)[0]^(A)[4];\
    RESERVED_BUF8[1]=(A)[1]^(A)[5];\
    RESERVED_BUF8[2]=(A)[2]^(A)[6];\
    RESERVED_BUF8[3]=(A)[3];\
    RESERVED_BUF8[4]=(B)[0]^(B)[4];\
    RESERVED_BUF8[5]=(B)[1]^(B)[5];\
    RESERVED_BUF8[6]=(B)[2]^(B)[6];\
    RESERVED_BUF8[7]=(B)[3];\
    GEMSS_PMUL256_WS_KAR_GF2X(M1,M2,M3,M4,RESERVED_BUF8,RESERVED_BUF8+4,RA,RB,CL,CH,\
                        M,MM,CM,CM1,CM2,one32);\
\
    GEMSS_PXOR1_2(C3,M1);\
    GEMSS_PXOR1_2(C4,M2);\
    GEMSS_PXOR1_2(C5,M3);\
    GEMSS_PXOR1_2(C6,M4);}


/* Karatsuba, 5157 = 1889*2+1356+23 instructions */
#define GEMSS_PMUL416_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,M1,M2,M3,M4,one32) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_PMUL192_WS_KAR6_GF2X(C1,C2,C3,A,B,RA,RB,CL,CH,M,M2,CM,\
                         CM1,CM2,one32)\
    GEMSS_PMUL224_WS_KAR_GF2X(C4,C5,C6,C7,(A)+3,(B)+3,RA,RB,CL,CH,M,MM,CM,M1,M2,\
                        one32)\
\
    RESERVED_BUF8[0]=(A)[0]^(A)[3];\
    RESERVED_BUF8[1]=(A)[1]^(A)[4];\
    RESERVED_BUF8[2]=(A)[2]^(A)[5];\
    RESERVED_BUF8[3]=(A)[6];\
    RESERVED_BUF8[4]=(B)[0]^(B)[3];\
    RESERVED_BUF8[5]=(B)[1]^(B)[4];\
    RESERVED_BUF8[6]=(B)[2]^(B)[5];\
    RESERVED_BUF8[7]=(B)[6];\
    GEMSS_PMUL224_WS_KAR_GF2X(M1,M2,M3,M4,RESERVED_BUF8,RESERVED_BUF8+4,RA,RB,CL,CH,\
                        M,MM,CM,CM1,CM2,one32);\
\
    GEMSS_PXOR1_2(M1,C1);\
    GEMSS_PXOR1_2(M2,C2);\
    GEMSS_PXOR1_2(M3,C3);\
    GEMSS_PXOR1_2(M1,C4);\
    GEMSS_PXOR1_2(M2,C5);\
    GEMSS_PXOR1_2(M3,C6);\
    GEMSS_PXOR1_2(M4,C7);\
    GEMSS_PXOR1_2(C2,GEMSS_PLSHIFT64(M1));\
    GEMSS_PXOR1_2(C3,GEMSS_PMIDDLE(M1,M2));\
    GEMSS_PXOR1_2(C4,GEMSS_PMIDDLE(M2,M3));\
    GEMSS_PXOR1_2(C5,GEMSS_PMIDDLE(M3,M4));}


/* Karatsuba, 5453 = 2040*2+1356+17 instructions */
#define GEMSS_PMUL448_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,M1,M2,M3,M4,one32) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
    GEMSS_PMUL192_WS_KAR6_GF2X(C5,C6,C7,(A)+4,(B)+4,RA,RB,CL,CH,M,M2,CM,\
                         CM1,CM2,one32)\
    C5=GEMSS_PXOR_(C3,C5);\
    C6=GEMSS_PXOR_(C4,C6);\
    C3=GEMSS_PXOR_(C5,C1);\
    C4=GEMSS_PXOR_(C6,C2);\
    C5=GEMSS_PXOR_(C5,C7);\
\
    RESERVED_BUF8[0]=(A)[0]^(A)[4];\
    RESERVED_BUF8[1]=(A)[1]^(A)[5];\
    RESERVED_BUF8[2]=(A)[2]^(A)[6];\
    RESERVED_BUF8[3]=(A)[3];\
    RESERVED_BUF8[4]=(B)[0]^(B)[4];\
    RESERVED_BUF8[5]=(B)[1]^(B)[5];\
    RESERVED_BUF8[6]=(B)[2]^(B)[6];\
    RESERVED_BUF8[7]=(B)[3];\
    GEMSS_PMUL256_WS_KAR_GF2X(M1,M2,M3,M4,RESERVED_BUF8,RESERVED_BUF8+4,RA,RB,CL,CH,\
                        M,MM,CM,CM1,CM2,one32);\
\
    GEMSS_PXOR1_2(C3,M1);\
    GEMSS_PXOR1_2(C4,M2);\
    GEMSS_PXOR1_2(C5,M3);\
    GEMSS_PXOR1_2(C6,M4);}


/* Karatsuba, 5987 = 2040*2+1889+18 instructions */
#define GEMSS_PMUL480_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,M1,M2,M3,M4,one32) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32);\
    GEMSS_PMUL224_WS_KAR_GF2X(C5,C6,C7,C8,(A)+4,(B)+4,\
                        RA,RB,CL,CH,M,MM,CM,M3,M4,one32);\
    C5=GEMSS_PXOR_(C3,C5);\
    C6=GEMSS_PXOR_(C4,C6);\
    C3=GEMSS_PXOR_(C5,C1);\
    C4=GEMSS_PXOR_(C6,C2);\
    C5=GEMSS_PXOR_(C5,C7);\
    C6=GEMSS_PXOR_(C6,C8);\
\
    RESERVED_BUF8[0]=(A)[0]^(A)[4];\
    RESERVED_BUF8[1]=(A)[1]^(A)[5];\
    RESERVED_BUF8[2]=(A)[2]^(A)[6];\
    RESERVED_BUF8[3]=(A)[3]^(A)[7];\
    RESERVED_BUF8[4]=(B)[0]^(B)[4];\
    RESERVED_BUF8[5]=(B)[1]^(B)[5];\
    RESERVED_BUF8[6]=(B)[2]^(B)[6];\
    RESERVED_BUF8[7]=(B)[3]^(B)[7];\
    GEMSS_PMUL256_WS_KAR_GF2X(M1,M2,M3,M4,RESERVED_BUF8,RESERVED_BUF8+4,RA,RB,CL,CH,\
                        M,MM,CM,CM1,CM2,one32);\
\
    GEMSS_PXOR1_2(C3,M1);\
    GEMSS_PXOR1_2(C4,M2);\
    GEMSS_PXOR1_2(C5,M3);\
    GEMSS_PXOR1_2(C6,M4);}


/* Karatsuba, 6138 = 2040*3+18 instructions */
#define GEMSS_PMUL512_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,M1,M2,M3,M4,one32) \
    { uint64_t RESERVED_BUF8[8];\
    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32);\
    GEMSS_PMUL256_WS_KAR_GF2X(C5,C6,C7,C8,(A)+4,(B)+4,\
                        RA,RB,CL,CH,M,MM,CM,M3,M4,one32);\
    C5=GEMSS_PXOR_(C3,C5);\
    C6=GEMSS_PXOR_(C4,C6);\
    C3=GEMSS_PXOR_(C5,C1);\
    C4=GEMSS_PXOR_(C6,C2);\
    C5=GEMSS_PXOR_(C5,C7);\
    C6=GEMSS_PXOR_(C6,C8);\
\
    RESERVED_BUF8[0]=(A)[0]^(A)[4];\
    RESERVED_BUF8[1]=(A)[1]^(A)[5];\
    RESERVED_BUF8[2]=(A)[2]^(A)[6];\
    RESERVED_BUF8[3]=(A)[3]^(A)[7];\
    RESERVED_BUF8[4]=(B)[0]^(B)[4];\
    RESERVED_BUF8[5]=(B)[1]^(B)[5];\
    RESERVED_BUF8[6]=(B)[2]^(B)[6];\
    RESERVED_BUF8[7]=(B)[3]^(B)[7];\
    GEMSS_PMUL256_WS_KAR_GF2X(M1,M2,M3,M4,RESERVED_BUF8,RESERVED_BUF8+4,RA,RB,CL,CH,\
                        M,MM,CM,CM1,CM2,one32);\
\
    GEMSS_PXOR1_2(C3,M1);\
    GEMSS_PXOR1_2(C4,M2);\
    GEMSS_PXOR1_2(C5,M3);\
    GEMSS_PXOR1_2(C6,M4);}


/* Karatsuba, 8258 = 3098*2+2040+22 instructions */
#define GEMSS_PMUL544_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,CM3,M1,M2,M3,M4,M5,res1,res2,one32) \
    { uint64_t RESERVED_BUF10[10];\
    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
    GEMSS_PMUL288_WS_KAR_GF2X(C5,C6,C7,C8,C9,(A)+4,(B)+4,RA,RB,CL,CH,M,MM,CM,\
                        M1,M2,M3,res1,res2,one32)\
    C5=GEMSS_PXOR_(C3,C5);\
    C6=GEMSS_PXOR_(C4,C6);\
    C3=GEMSS_PXOR_(C5,C1);\
    C4=GEMSS_PXOR_(C6,C2);\
    C5=GEMSS_PXOR_(C5,C7);\
    C6=GEMSS_PXOR_(C6,C8);\
    C7=GEMSS_PXOR_(C7,C9);\
\
    RESERVED_BUF10[0]=(A)[0]^(A)[4];\
    RESERVED_BUF10[1]=(A)[1]^(A)[5];\
    RESERVED_BUF10[2]=(A)[2]^(A)[6];\
    RESERVED_BUF10[3]=(A)[3]^(A)[7];\
    RESERVED_BUF10[4]=(A)[8];\
    RESERVED_BUF10[5]=(B)[0]^(B)[4];\
    RESERVED_BUF10[6]=(B)[1]^(B)[5];\
    RESERVED_BUF10[7]=(B)[2]^(B)[6];\
    RESERVED_BUF10[8]=(B)[3]^(B)[7];\
    RESERVED_BUF10[9]=(B)[8];\
    GEMSS_PMUL288_WS_KAR_GF2X(M1,M2,M3,M4,M5,RESERVED_BUF10,RESERVED_BUF10+5,RA,RB,\
                        CL,CH,M,MM,CM,CM1,CM2,CM3,res1,res2,one32)\
\
    GEMSS_PXOR1_2(C3,M1);\
    GEMSS_PXOR1_2(C4,M2);\
    GEMSS_PXOR1_2(C5,M3);\
    GEMSS_PXOR1_2(C6,M4);\
    GEMSS_PXOR1_2(C7,M5);}


/* Karatsuba, 8866 = 3402*2+2040+22 instructions */
#define GEMSS_PMUL576_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A,B,RA,RB,CL,CH,M,MM,CM,\
                            CM1,CM2,CM3,M1,M2,M3,M4,M5,res1,res2,one32) \
    { uint64_t RESERVED_BUF10[10];\
    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
    GEMSS_PMUL320_WS_KAR_GF2X(C5,C6,C7,C8,C9,(A)+4,(B)+4,RA,RB,CL,CH,M,MM,CM,\
                        M1,M2,M3,res1,res2,one32)\
    C5=GEMSS_PXOR_(C3,C5);\
    C6=GEMSS_PXOR_(C4,C6);\
    C3=GEMSS_PXOR_(C5,C1);\
    C4=GEMSS_PXOR_(C6,C2);\
    C5=GEMSS_PXOR_(C5,C7);\
    C6=GEMSS_PXOR_(C6,C8);\
    C7=GEMSS_PXOR_(C7,C9);\
\
    RESERVED_BUF10[0]=(A)[0]^(A)[4];\
    RESERVED_BUF10[1]=(A)[1]^(A)[5];\
    RESERVED_BUF10[2]=(A)[2]^(A)[6];\
    RESERVED_BUF10[3]=(A)[3]^(A)[7];\
    RESERVED_BUF10[4]=(A)[8];\
    RESERVED_BUF10[5]=(B)[0]^(B)[4];\
    RESERVED_BUF10[6]=(B)[1]^(B)[5];\
    RESERVED_BUF10[7]=(B)[2]^(B)[6];\
    RESERVED_BUF10[8]=(B)[3]^(B)[7];\
    RESERVED_BUF10[9]=(B)[8];\
    GEMSS_PMUL320_WS_KAR_GF2X(M1,M2,M3,M4,M5,RESERVED_BUF10,RESERVED_BUF10+5,RA,RB,\
                        CL,CH,M,MM,CM,CM1,CM2,CM3,res1,res2,one32)\
\
    GEMSS_PXOR1_2(C3,M1);\
    GEMSS_PXOR1_2(C4,M2);\
    GEMSS_PXOR1_2(C5,M3);\
    GEMSS_PXOR1_2(C6,M4);\
    GEMSS_PXOR1_2(C7,M5);}


/***********************************************************************/
/***********************************************************************/
/**************************** pclmul version ***************************/
/***********************************************************************/
/***********************************************************************/


/* Here, A,B are integers */
#define GEMSS_pclmul64low_inlined_gf2x(C,A,B) \
    GEMSS_PCVT_64(C,GEMSS_PCLMUL(GEMSS_PSETL_64(A),GEMSS_PSETL_64(B),0))

/* The pclmul instruction does not exploit that the 32 last bits are null */
#define GEMSS_pclmul32_inlined_gf2x GEMSS_pclmul64low_inlined_gf2x

/* Here, A,B are integers and C is a pointer */
#define GEMSS_pclmul64_inlined2_gf2x(C,A,B) \
    GEMSS_PSTORE128(C,GEMSS_PCLMUL(GEMSS_PSETL_64(A),GEMSS_PSETL_64(B),0))

/* Here, A,B,C are pointers */
#define GEMSS_pclmul64_inlined_gf2x(C,A,B) \
    GEMSS_PSTORE128(C,GEMSS_PCLMUL(GEMSS_PLOADL(A),GEMSS_PLOADL(B),0))


#ifdef GEMSS_ENABLED_PCLMUL
    uint64_t GEMSS_PREFIX_NAME(GEMSS_pclmul64low_gf2x)(uint64_t A, uint64_t B);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul64_gf2x)(uint64_t C[2], const uint64_t A[1],
                                                   const uint64_t B[1]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul96_gf2x)(uint64_t C[3], const uint64_t A[2],
                                                   const uint64_t B[2]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul128_gf2x)(uint64_t C[4], const uint64_t A[2],
                                                    const uint64_t B[2]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul160_gf2x)(uint64_t C[5], const uint64_t A[3],
                                                    const uint64_t B[3]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul192_gf2x)(uint64_t C[6], const uint64_t A[3],
                                                    const uint64_t B[3]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul224_gf2x)(uint64_t C[7], const uint64_t A[4],
                                                    const uint64_t B[4]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul256_gf2x)(uint64_t C[8], const uint64_t A[4],
                                                    const uint64_t B[4]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul288_gf2x)(uint64_t C[9], const uint64_t A[5],
                                                    const uint64_t B[5]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul320_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                     const uint64_t B[5]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul352_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                     const uint64_t B[6]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul384_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                     const uint64_t B[6]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul416_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                     const uint64_t B[7]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul448_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                     const uint64_t B[7]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul480_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                     const uint64_t B[8]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul512_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                     const uint64_t B[8]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul544_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                     const uint64_t B[9]);
    void GEMSS_PREFIX_NAME(GEMSS_pclmul576_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                     const uint64_t B[9]);
    #define GEMSS_pclmul64low_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul64low_gf2x)
    #define GEMSS_pclmul64_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul64_gf2x)
    #define GEMSS_pclmul96_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul96_gf2x)
    #define GEMSS_pclmul128_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul128_gf2x)
    #define GEMSS_pclmul160_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul160_gf2x)
    #define GEMSS_pclmul192_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul192_gf2x)
    #define GEMSS_pclmul224_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul224_gf2x)
    #define GEMSS_pclmul256_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul256_gf2x)
    #define GEMSS_pclmul288_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul288_gf2x)
    #define GEMSS_pclmul320_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul320_gf2x)
    #define GEMSS_pclmul352_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul352_gf2x)
    #define GEMSS_pclmul384_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul384_gf2x)
    #define GEMSS_pclmul416_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul416_gf2x)
    #define GEMSS_pclmul448_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul448_gf2x)
    #define GEMSS_pclmul480_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul480_gf2x)
    #define GEMSS_pclmul512_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul512_gf2x)
    #define GEMSS_pclmul544_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul544_gf2x)
    #define GEMSS_pclmul576_gf2x GEMSS_PREFIX_NAME(GEMSS_pclmul576_gf2x)

    /* The pclmul instruction does not exploit that the 32 last bits are null */
    #define GEMSS_pclmul32_gf2x GEMSS_pclmul64low_gf2x
#endif


/***********************************************************************/
/***********************************************************************/
/********************** store at the end version ***********************/
/***********************************************************************/
/***********************************************************************/


/* Classical: 4 mul64, 5 other instructions */
#define GEMSS_PCLMUL128_WS_CLAS_GF2X(z1,z2,x,y,sum,res_low,res_high) \
    /* X^0 */\
    res_low=GEMSS_PCLMUL(x,y,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x, y, 1);\
    z2=GEMSS_PCLMUL(x, y, 0x10);\
    res_high=GEMSS_PXOR_(z1,z2);\
\
    /* mid2_low: x^64 ... x^127 */\
    sum=GEMSS_PLSHIFT64(res_high);\
    /* mid2_low + L */\
    z1=GEMSS_PXOR_(res_low,sum);\
\
    /* X^128 */\
    res_low=GEMSS_PCLMUL(x,y,0x11);\
\
    /* mid2_high: x^128 ... x^191 */\
    sum=GEMSS_PRSHIFT64(res_high);\
    /* mid2_high + H */\
    z2=GEMSS_PXOR_(res_low,sum);


/* Classical: 4 mul64, 7 other instructions */
#define GEMSS_PCLMUL128_ADD_CLAS_GF2X(z3,z4,z1,z2,x,y,sum,res_low,res_high) \
    /* X^0 */\
    res_low=GEMSS_PCLMUL(x,y,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x, y, 1);\
    z2=GEMSS_PCLMUL(x, y, 0x10);\
    res_high=GEMSS_PXOR_(z1,z2);\
\
    /* mid2_low: x^64 ... x^127 */\
    sum=GEMSS_PLSHIFT64(res_high);\
    /* mid2_low + L */\
    z3^=GEMSS_PXOR_(res_low,sum);\
\
    /* X^128 */\
    res_low=GEMSS_PCLMUL(x,y,0x11);\
\
    /* mid2_high: x^128 ... x^191 */\
    sum=GEMSS_PRSHIFT64(res_high);\
    /* mid2_high + H */\
    z4^=GEMSS_PXOR_(res_low,sum);


/* Karatsuba: 3 mul64, 10 other instructions */
#define GEMSS_PCLMUL128_WS_KAR_GF2X(z1,z2,x,y,sum,res_low,res_high) \
    /* X^0 */\
    z1=GEMSS_PCLMUL(x,y,0);\
    /* X^128 */\
    z2=GEMSS_PCLMUL(x,y,0x11);\
\
    res_low=GEMSS_PXOR_(x,GEMSS_PRSHIFT64(x));\
    res_high=GEMSS_PXOR_(y,GEMSS_PRSHIFT64(y));\
\
    sum=GEMSS_PCLMUL(res_low,res_high,0);\
    GEMSS_PXOR1_2(sum,z1);\
    GEMSS_PXOR1_2(sum,z2);\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(sum));\
    GEMSS_PXOR1_2(z2,GEMSS_PRSHIFT64(sum));


/* Karatsuba: 3 mul64, 12 other instructions */
#define GEMSS_PCLMUL128_ADD_KAR_GF2X(z3,z4,z1,z2,x,y,sum,res_low,res_high) \
    /* X^0 */\
    z1=GEMSS_PCLMUL(x,y,0);\
    /* X^128 */\
    z2=GEMSS_PCLMUL(x,y,0x11);\
\
    res_low=GEMSS_PXOR_(x,GEMSS_PRSHIFT64(x));\
    res_high=GEMSS_PXOR_(y,GEMSS_PRSHIFT64(y));\
\
    sum=GEMSS_PCLMUL(res_low,res_high,0);\
    GEMSS_PXOR1_2(sum,z1);\
    GEMSS_PXOR1_2(sum,z2);\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(sum));\
    GEMSS_PXOR1_2(z3,z1);\
    GEMSS_PXOR1_2(z2,GEMSS_PRSHIFT64(sum));\
    GEMSS_PXOR1_2(z4,z2);


/* Classical: 9 mul64, 1 GEMSS_PMIDDLE, 9 other instructions */
#define GEMSS_PCLMUL192_WS_CLAS_GF2X(z3,z1,z2,x1,x2,y1,y2,sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 1);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    res1=GEMSS_PCLMUL(x2,y2,0);\
    res2=GEMSS_PRSHIFT64(sum);\
    z2=GEMSS_PXOR_(res1,res2);


/* Karatsuba: 6 mul64, 1 GEMSS_PMIDDLE, 19 other instructions */
#define GEMSS_PCLMUL192_WS_KAR_GF2X(z1,z2,z3,x1,x2,y1,y2,sum,res1,res2) \
    {__m128i u31;\
    /* A0*B0 */\
    z1=GEMSS_PCLMUL(x1,y1,0);\
    /* A1*B1 */\
    z2=GEMSS_PCLMUL(x1,y1,0x11);\
    /* A2*B2 */\
    z3=GEMSS_PCLMUL(x2,y2,0);\
\
    res1=GEMSS_PXOR_(z1,z2);\
    res2=GEMSS_PXOR_(z3,z2);\
    z2=GEMSS_PXOR_(res1,z3);\
    /*  C[0] = C0
        C[1] = C1^(C0^C2)
        C[2] = C2^(C1^C3)^C0^C4
        C[3] = C3^(C4^C2)^C1^C5
        C[4] = C4^(C5^C3)
        C[5] = C5 */\
    /* (A2 A2) */\
    u31=GEMSS_PSHUFFLE_32_1010(x2);\
    /* (B2 B2) */\
    sum=GEMSS_PSHUFFLE_32_1010(y2);\
    /* (A2 A2) ^ (A0 A1) */\
    GEMSS_PXOR1_2(u31,x1);\
    /* (B2 B2) ^ (B0 B1) */\
    GEMSS_PXOR1_2(sum,y1);\
    /* (A0+A2)*(B0+B2) */\
    GEMSS_PXOR1_2(z2,GEMSS_PCLMUL(u31,sum,0));\
    /* (A1+A2)*(B1+B2) */\
    GEMSS_PXOR1_2(res2,GEMSS_PCLMUL(u31,sum,0x11));\
    /* (A0+A1)*(B0+B1) */\
    GEMSS_PXOR1_2(res1,GEMSS_PCLMUL(GEMSS_PXOR_(x1,GEMSS_PRSHIFT64(x1)),\
                        GEMSS_PXOR_(y1,GEMSS_PRSHIFT64(y1)),0));\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(res1));\
    GEMSS_PXOR1_2(z3,GEMSS_PRSHIFT64(res2));\
    GEMSS_PXOR1_2(z2,GEMSS_PMIDDLE(res1,res2));}


/* Karatsuba: 2 mul128, 1 mul64, 4 other instructions */
#define GEMSS_PCLMUL192_WS_KAR256_GF2X(z1,z2,z3,x1,x2,y1,y2,sum,res1,res2) \
    {__m128i x,y,u31,u32;\
    GEMSS_PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
    z3=GEMSS_PCLMUL(x2,y2,0);\
\
    x=GEMSS_PXOR_(x1,x2);\
    y=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(z3,z2);\
    z2=GEMSS_PXOR_(z3,z1);\
\
    GEMSS_PCLMUL128_ADD_GF2X(z2,z3,u31,u32,x,y,sum,res1,res2);}


/* Classical: 16 mul64, 2 GEMSS_PMIDDLE, 15 other instructions */
#define GEMSS_PCLMUL256_WS_CLAS_GF2X(z3,z4,z1,z2,x1,x2,y1,y2,sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z4=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(y1, x2, 0x11);\
    z2=GEMSS_PCLMUL(y2, x2, 0);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0x11);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    z2=GEMSS_PCLMUL(x2, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
\
    /* X^384 */\
    res1=GEMSS_PCLMUL(x2,y2,0x11);\
    sum=GEMSS_PRSHIFT64(res2);\
    z2=GEMSS_PXOR_(res1,sum);


/* Classical: 16 mul64, 2 GEMSS_PMIDDLE, 19 other instructions */
/* xor the res to z3,z4,z5,z6 */
#define GEMSS_PCLMUL256_ADD_CLAS_GF2X(z3,z4,z5,z6,z1,z2,x1,x2,y1,y2,sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3^=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z4^=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(y1, x2, 0x11);\
    z2=GEMSS_PCLMUL(y2, x2, 0);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0x11);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    z2=GEMSS_PCLMUL(x2, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z5^=GEMSS_PXOR_(res1,z2);\
\
    /* X^384 */\
    res1=GEMSS_PCLMUL(x2,y2,0x11);\
    sum=GEMSS_PRSHIFT64(res2);\
    z6^=GEMSS_PXOR_(res1,sum);


/* Karatsuba: 3 mul128, 5 other instructions */
#define GEMSS_PCLMUL256_WS_KAR_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2) \
    {__m128i x,y,u41,u42;\
    GEMSS_PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL128_WS_GF2X(z3,z4,x2,y2,sum,res1,res2);\
\
    x=GEMSS_PXOR_(x1,x2);\
    y=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(z3,z2);\
    z2=GEMSS_PXOR_(z3,z1);\
    GEMSS_PXOR1_2(z3,z4);\
\
    GEMSS_PCLMUL128_ADD_GF2X(z2,z3,u41,u42,x,y,sum,res1,res2);}


/* Karatsuba: 3 mul128, 9 other instructions */
#define GEMSS_PCLMUL256_ADD_KAR_GF2X(z1,z2,z3,z4,z5,z6,x1,x2,y1,y2,sum,res1,res2) \
    {__m128i x,y,u41,u42;\
    GEMSS_PCLMUL128_WS_GF2X(u41,u42,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL128_WS_GF2X(z5,z6,x2,y2,sum,res1,res2);\
\
    x=GEMSS_PXOR_(x1,x2);\
    y=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(z1,u41);\
    GEMSS_PXOR1_2(z4,z6);\
\
    GEMSS_PXOR1_2(z5,u42);\
    GEMSS_PXOR1_2(z2,GEMSS_PXOR_(z5,u41));\
    GEMSS_PXOR1_2(z3,GEMSS_PXOR_(z5,z6));\
\
    GEMSS_PCLMUL128_ADD_GF2X(z2,z3,u41,u42,x,y,sum,res1,res2);}


/* Karatsuba: 3 mul128, 5 other instructions */
#define GEMSS_PCLMUL256_WS_KAR2_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2) \
    {__m128i x,y,u41,u42;\
    GEMSS_PCLMUL128_WS_KAR_GF2X(z1,z2,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL128_WS_KAR_GF2X(z3,z4,x2,y2,sum,res1,res2);\
\
    x=GEMSS_PXOR_(x1,x2);\
    y=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(z3,z2);\
    z2=GEMSS_PXOR_(z3,z1);\
    GEMSS_PXOR1_2(z3,z4);\
\
    GEMSS_PCLMUL128_ADD_KAR_GF2X(z2,z3,u41,u42,x,y,sum,res1,res2);}


/* Karatsuba: 3 mul128, 9 other instructions */
#define GEMSS_PCLMUL256_ADD_KAR2_GF2X(z1,z2,z3,z4,z5,z6,x1,x2,y1,y2,sum,res1,res2) \
    {__m128i x,y,u41,u42;\
    GEMSS_PCLMUL128_WS_KAR_GF2X(u41,u42,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL128_WS_KAR_GF2X(z5,z6,x2,y2,sum,res1,res2);\
\
    x=GEMSS_PXOR_(x1,x2);\
    y=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(z1,u41);\
    GEMSS_PXOR1_2(z4,z6);\
\
    GEMSS_PXOR1_2(z5,u42);\
    GEMSS_PXOR1_2(z2,GEMSS_PXOR_(z5,u41));\
    GEMSS_PXOR1_2(z3,GEMSS_PXOR_(z5,z6));\
\
    GEMSS_PCLMUL128_ADD_KAR_GF2X(z2,z3,u41,u42,x,y,sum,res1,res2);}


/* Classical: 25 mul64, 3 GEMSS_PMIDDLE, 23 other instructions */
#define GEMSS_PCLMUL320_WS_CLAS_GF2X(z3,z4,z5,z1,z2,x1,x2,x3,y1,y2,y3,sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z4=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 1);\
    z2=GEMSS_PCLMUL(x2, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z5=GEMSS_PXOR_(res1,z2);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x2, y3, 0);\
    z2=GEMSS_PCLMUL(x2, y2, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x2, y3, 1);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
\
    /* X^512 */\
    res1=GEMSS_PCLMUL(x3,y3,0);\
    res2=GEMSS_PRSHIFT64(sum);\
    z2=GEMSS_PXOR_(res1,res2);


/* Classical: 25 mul64, 3 GEMSS_PMIDDLE, 28 other instructions */
/* xor the res to z3,z4,z5,z6,z7 */
#define GEMSS_PCLMUL320_ADD_CLAS_GF2X(z3,z4,z5,z6,z7,z1,z2,x1,x2,x3,y1,y2,y3,\
                                sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3^=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z4^=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 1);\
    z2=GEMSS_PCLMUL(x2, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z5^=GEMSS_PXOR_(res1,z2);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x2, y3, 0);\
    z2=GEMSS_PCLMUL(x2, y2, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x2, y3, 1);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z6^=GEMSS_PXOR_(res1,z2);\
\
    /* X^512 */\
    res1=GEMSS_PCLMUL(x3,y3,0);\
    res2=GEMSS_PRSHIFT64(sum);\
    z7^=GEMSS_PXOR_(res1,res2);


/* Karatsuba: 2 mul192, 1 mul128, 9 other instructions */
#define GEMSS_PCLMUL320_WS_KAR_GF2X(z1,z2,z3,z4,z5,x1,x2,x3,y1,y2,y3,sum,res1,res2)\
    {__m128i x1m,y1m,R1,R2,R3;\
    GEMSS_PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL192_WS_GF2X(z3,z4,z5,x2,x3,y2,y3,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x2);\
    y1m=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(z3,z2);\
    z2=GEMSS_PXOR_(z3,z1);\
    GEMSS_PXOR1_2(z3,z4);\
    GEMSS_PXOR1_2(z4,z5);\
\
    GEMSS_PCLMUL192_WS_GF2X(R1,R2,R3,x1m,x3,y1m,y3,sum,res1,res2);\
\
    GEMSS_PXOR1_2(z2,R1);\
    GEMSS_PXOR1_2(z3,R2);\
    GEMSS_PXOR1_2(z4,R3);}


/* Karatsuba: 2 mul192, 1 mul128, 14 other instructions */
/* xor the res to z1,z2,z3,z4,z5 */
#define GEMSS_PCLMUL320_ADD_KAR_GF2X(z1,z2,z3,z4,z5,z6,z7,x1,x2,x3,y1,y2,y3,\
                               sum,res1,res2) \
    {__m128i x1m,y1m,R1,R2,R3;\
    GEMSS_PCLMUL128_WS_GF2X(z6,z7,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL192_WS_GF2X(R1,R2,R3,x2,x3,y2,y3,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x2);\
    y1m=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(R1,z7);\
    z7=GEMSS_PXOR_(R1,z6);\
    GEMSS_PXOR1_2(R1,R2);\
    GEMSS_PXOR1_2(R2,R3);\
\
    GEMSS_PXOR1_2(z1,z6);\
    GEMSS_PXOR1_2(z2,z7);\
    GEMSS_PXOR1_2(z3,R1);\
    GEMSS_PXOR1_2(z4,R2);\
    GEMSS_PXOR1_2(z5,R3);\
\
    GEMSS_PCLMUL192_WS_GF2X(R1,R2,R3,x1m,x3,y1m,y3,sum,res1,res2);\
\
    GEMSS_PXOR1_2(z2,R1);\
    GEMSS_PXOR1_2(z3,R2);\
    GEMSS_PXOR1_2(z4,R3);}


/* Classical: 36 mul64, 4 GEMSS_PMIDDLE, 33 other instructions */
#define GEMSS_PCLMUL384_WS_CLAS_GF2X(z3,z4,z5,z6,z1,z2,x1,x2,x3,y1,y2,y3,\
                               sum,res1,res2)\
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z4=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 0x10);\
    z2=GEMSS_PCLMUL(x1, y3, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z5=GEMSS_PXOR_(res1,z2);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x1, y3, 0x11);\
    z2=GEMSS_PCLMUL(x2, y3, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0x11);\
    res1=GEMSS_PXOR_(z1,sum);\
    z2=GEMSS_PCLMUL(x3, y2, 0);\
    sum=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x3, y1, 0x11);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x2, y3, 0x10);\
    z2=GEMSS_PCLMUL(x2, y3, 1);\
    sum=GEMSS_PXOR_(z1,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    z1=GEMSS_PXOR_(sum,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 1);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z6=GEMSS_PXOR_(res1,z2);\
\
    /* X^512 */\
    z1=GEMSS_PCLMUL(x2, y3, 0x11);\
    z2=GEMSS_PCLMUL(x3, y3, 0);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0x11);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^576 */\
    z1=GEMSS_PCLMUL(x3, y3, 0x10);\
    z2=GEMSS_PCLMUL(x3, y3, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
\
    /* X^640 */\
    res1=GEMSS_PCLMUL(x3,y3,0x11);\
    sum=GEMSS_PRSHIFT64(res2);\
    z2=GEMSS_PXOR_(res1,sum);


/* Karatsuba: 3 mul192, 4 GEMSS_PMIDDLE, 18 other instructions */
#define GEMSS_PCLMUL384_WS_KAR_GF2X(z1,z2,z3,z4,z5,z6,x1,x2,x3,y1,y2,y3,\
                              sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,R1,R2,R3;\
    GEMSS_PCLMUL192_WS_GF2X(z1,z2,z3,x1,x2,y1,y2,sum,res1,res2);\
\
    x1m=GEMSS_PMIDDLE(x2,x3);\
    x2m=GEMSS_PRSHIFT64(x3);\
    y1m=GEMSS_PMIDDLE(y2,y3);\
    y2m=GEMSS_PRSHIFT64(y3);\
\
    GEMSS_PCLMUL192_WS_GF2X(z4,z5,z6,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PXOR1_2(x1m,x1);\
    GEMSS_PXOR1_2(x2m,x2);\
    GEMSS_PXOR1_2(y1m,y1);\
    GEMSS_PXOR1_2(y2m,y2);\
\
    GEMSS_PCLMUL192_WS_GF2X(R1,R2,R3,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PXOR1_2(R1,GEMSS_PXOR_(z1,z4));\
    GEMSS_PXOR1_2(R2,GEMSS_PXOR_(z2,z5));\
    GEMSS_PXOR1_2(R3,GEMSS_PXOR_(z3,z6));\
    GEMSS_PXOR1_2(z2,GEMSS_PLSHIFT64(R1));\
    GEMSS_PXOR1_2(z5,GEMSS_PRSHIFT64(R3));\
    GEMSS_PXOR1_2(z3,GEMSS_PMIDDLE(R1,R2));\
    GEMSS_PXOR1_2(z4,GEMSS_PMIDDLE(R2,R3));}


/* Classical: 49 mul64, 5 GEMSS_PMIDDLE, 45 other instructions */
#define GEMSS_PCLMUL448_WS_CLAS_GF2X(z3,z4,z5,z6,z7,z1,z2,x1,x2,x3,x4,y1,y2,y3,y4,\
                               sum,res1,res2)\
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z3=GEMSS_PXOR_(res1,sum);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z4=GEMSS_PXOR_(res1,z2);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 0x10);\
    z2=GEMSS_PCLMUL(x1, y3, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z5=GEMSS_PXOR_(res1,z2);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x1, y4, 0);\
    z2=GEMSS_PCLMUL(x1, y3, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y3, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
    z2=GEMSS_PCLMUL(x2, y2, 0x11);\
    sum=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
    z2=GEMSS_PCLMUL(x3, y1, 0x11);\
    sum=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x4, y1, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x1, y4, 1);\
    z2=GEMSS_PCLMUL(x2, y3, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z2=GEMSS_PCLMUL(x2, y3, 1);\
    z1=GEMSS_PXOR_(sum,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 1);\
    z1=GEMSS_PXOR_(sum,z2);\
    z2=GEMSS_PCLMUL(x4, y1, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z6=GEMSS_PXOR_(res1,z2);\
\
    /* X^512 */\
    z1=GEMSS_PCLMUL(x2, y4, 0);\
    z2=GEMSS_PCLMUL(x2, y3, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y3, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z2=GEMSS_PCLMUL(x3, y2, 0x11);\
    res2=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x4, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^576 */\
    z1=GEMSS_PCLMUL(x2, y4, 1);\
    z2=GEMSS_PCLMUL(x3, y3, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y3, 1);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x4, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z7=GEMSS_PXOR_(res1,z2);\
\
    /* X^640 */\
    z1=GEMSS_PCLMUL(x3, y4, 0);\
    z2=GEMSS_PCLMUL(x3, y3, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x4, y3, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^704 */\
    z1=GEMSS_PCLMUL(x3, y4, 1);\
    z2=GEMSS_PCLMUL(x4, y3, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
\
    /* X^768 */\
    res1=GEMSS_PCLMUL(x4,y4,0);\
    res2=GEMSS_PRSHIFT64(sum);\
    z2=GEMSS_PXOR_(res1,res2);


/* Karatsuba: 2 mul256, 1 mul192, 9 other instructions */
#define GEMSS_PCLMUL448_WS_KAR_GF2X(z1,z2,z3,z4,z5,z6,z7,x1,x2,x3,x4,y1,y2,y3,y4,\
                              sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,t1,t2;\
    GEMSS_PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL192_WS_GF2X(z5,z6,z7,x3,x4,y3,y4,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x3);\
    x2m=GEMSS_PXOR_(x2,x4);\
    y1m=GEMSS_PXOR_(y1,y3);\
    y2m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
\
    GEMSS_PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);}


/* Karatsuba: 3 mul256, 1 mul192, 10 other instructions */
#define GEMSS_PCLMUL512_WS_KAR_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,x1,x2,x3,x4,y1,y2,y3,y4,\
                              sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,t1,t2;\
    GEMSS_PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL256_WS_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x3);\
    x2m=GEMSS_PXOR_(x2,x4);\
    y1m=GEMSS_PXOR_(y1,y3);\
    y2m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
    z6=GEMSS_PXOR_(z6,z8);\
\
    GEMSS_PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);}


/* Karatsuba: 3 mul256, 1 mul192, 10 other instructions */
#define GEMSS_PCLMUL512_WS_KAR2_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,x1,x2,x3,x4,y1,y2,y3,y4,\
                               sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,t1,t2;\
    GEMSS_PCLMUL256_WS_KAR2_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL256_WS_KAR2_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x3);\
    x2m=GEMSS_PXOR_(x2,x4);\
    y1m=GEMSS_PXOR_(y1,y3);\
    y2m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
    z6=GEMSS_PXOR_(z6,z8);\
\
    GEMSS_PCLMUL256_ADD_KAR2_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);}


/* Karatsuba: 2 mul320, 1 mul256, 11 other instructions */
#define GEMSS_PCLMUL576_WS_KAR_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,z9,\
                              x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,sum,res1,res2)\
    {__m128i x11m,x22m,y11m,y22m,t1,t2;\
    GEMSS_PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL320_WS_GF2X(z5,z6,z7,z8,z9,x3,x4,x5,y3,y4,y5,sum,res1,res2);\
\
    x11m=GEMSS_PXOR_(x1,x3);\
    x22m=GEMSS_PXOR_(x2,x4);\
    y11m=GEMSS_PXOR_(y1,y3);\
    y22m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
    z6=GEMSS_PXOR_(z6,z8);\
    z7=GEMSS_PXOR_(z7,z9);\
\
    GEMSS_PCLMUL320_ADD_GF2X(z3,z4,z5,z6,z7,t1,t2,x11m,x22m,x5,y11m,y22m,y5,\
                       sum,res1,res2);}


#if GEMSS_PROC_HASWELL
    #define GEMSS_PCLMUL128_WS_GF2X GEMSS_PCLMUL128_WS_CLAS_GF2X
    #define GEMSS_PCLMUL192_WS_GF2X GEMSS_PCLMUL192_WS_KAR_GF2X
    #define GEMSS_PCLMUL256_WS_GF2X GEMSS_PCLMUL256_WS_KAR_GF2X
    #define GEMSS_PCLMUL320_WS_GF2X GEMSS_PCLMUL320_WS_KAR_GF2X
    #define GEMSS_PCLMUL384_WS_GF2X GEMSS_PCLMUL384_WS_KAR_GF2X
    #define GEMSS_PCLMUL448_WS_GF2X GEMSS_PCLMUL448_WS_KAR_GF2X
    #define GEMSS_PCLMUL512_WS_GF2X GEMSS_PCLMUL512_WS_KAR2_GF2X
    #define GEMSS_PCLMUL576_WS_GF2X GEMSS_PCLMUL576_WS_KAR_GF2X

    #define GEMSS_PCLMUL128_ADD_GF2X GEMSS_PCLMUL128_ADD_CLAS_GF2X
    #define GEMSS_PCLMUL256_ADD_GF2X GEMSS_PCLMUL256_ADD_KAR_GF2X
    #define GEMSS_PCLMUL320_ADD_GF2X GEMSS_PCLMUL320_ADD_KAR_GF2X
#else
    /* Skylake */
    #define GEMSS_PCLMUL128_WS_GF2X GEMSS_PCLMUL128_WS_CLAS_GF2X
    #define GEMSS_PCLMUL192_WS_GF2X GEMSS_PCLMUL192_WS_CLAS_GF2X
    #define GEMSS_PCLMUL256_WS_GF2X GEMSS_PCLMUL256_WS_KAR_GF2X
    #define GEMSS_PCLMUL320_WS_GF2X GEMSS_PCLMUL320_WS_CLAS_GF2X
    #define GEMSS_PCLMUL384_WS_GF2X GEMSS_PCLMUL384_WS_CLAS_GF2X
    #define GEMSS_PCLMUL448_WS_GF2X GEMSS_PCLMUL448_WS_KAR_GF2X
    #define GEMSS_PCLMUL512_WS_GF2X GEMSS_PCLMUL512_WS_KAR_GF2X
    #define GEMSS_PCLMUL576_WS_GF2X GEMSS_PCLMUL576_WS_KAR_GF2X

    #define GEMSS_PCLMUL128_ADD_GF2X GEMSS_PCLMUL128_ADD_CLAS_GF2X
    #define GEMSS_PCLMUL256_ADD_GF2X GEMSS_PCLMUL256_ADD_KAR_GF2X
    #define GEMSS_PCLMUL320_ADD_GF2X GEMSS_PCLMUL320_ADD_CLAS_GF2X
#endif


/***********************************************************************/
/***********************************************************************/
/********************** mul and store version **************************/
/***********************************************************************/
/***********************************************************************/


/* 1 mul64 */
#define GEMSS_PCLMUL64LOW_GF2X(C,x,y,pos) GEMSS_PCVT_64((C),GEMSS_PCLMUL(x,y,pos))

#define GEMSS_PCLMUL32_GF2X(C,x,y) GEMSS_PCLMUL64LOW_GF2X(C,x,y,0)

/* 1 mul64 */
#define GEMSS_PCLMUL64_GF2X(C,x,y,z,pos) \
    z=GEMSS_PCLMUL(x, y, pos);\
    GEMSS_PSTORE128(C,z);


/* Classical: 4 mul64, 5 other instructions */
#define GEMSS_PCLMUL128_CLAS_FINAL(FINAL_STORE,C,x,y,z1,z2,sum,res_low,res_high) \
    /* X^0 */\
    res_low=GEMSS_PCLMUL(x,y,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x, y, 1);\
    z2=GEMSS_PCLMUL(x, y, 0x10);\
    res_high=GEMSS_PXOR_(z1,z2);\
\
    /* mid2_low: x^64 ... x^127 */\
    sum=GEMSS_PLSHIFT64(res_high);\
    /* mid2_low + L */\
    z1=GEMSS_PXOR_(res_low,sum);\
    GEMSS_PSTORE128(C,z1);\
\
    /* X^128 */\
    res_low=GEMSS_PCLMUL(x,y,0x11);\
\
    /* mid2_high: x^128 ... x^191 */\
    sum=GEMSS_PRSHIFT64(res_high);\
    /* mid2_high + H */\
    z2=GEMSS_PXOR_(res_low,sum);\
    FINAL_STORE;


#define GEMSS_PCLMUL96_CLAS_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
        GEMSS_PCLMUL128_CLAS_FINAL(GEMSS_PSTOREL(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
#define GEMSS_PCLMUL128_CLAS_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
        GEMSS_PCLMUL128_CLAS_FINAL(GEMSS_PSTORE128(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)


/* Karatsuba: 3 mul64, 10 other instructions */
#define GEMSS_PCLMUL128_KAR_FINAL(FINAL_STORE,C,x,y,z1,z2,sum,res_low,res_high) \
    /* X^0 */\
    z1=GEMSS_PCLMUL(x,y,0);\
    /* X^128 */\
    z2=GEMSS_PCLMUL(x,y,0x11);\
\
    res_low=GEMSS_PXOR_(x,GEMSS_PRSHIFT64(x));\
    res_high=GEMSS_PXOR_(y,GEMSS_PRSHIFT64(y));\
\
    /* X^64 */\
    sum=GEMSS_PCLMUL(res_low,res_high,0);\
    GEMSS_PXOR1_2(sum,z1);\
    GEMSS_PXOR1_2(sum,z2);\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(sum));\
    GEMSS_PXOR1_2(z2,GEMSS_PRSHIFT64(sum));\
\
    GEMSS_PSTORE128(C,z1);\
    FINAL_STORE;


#define GEMSS_PCLMUL96_KAR_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
        GEMSS_PCLMUL128_KAR_FINAL(GEMSS_PSTOREL(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
#define GEMSS_PCLMUL128_KAR_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
        GEMSS_PCLMUL128_KAR_FINAL(GEMSS_PSTORE128(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)


/* Classical: 9 mul64, 1 GEMSS_PMIDDLE, 9 other instructions */
#define GEMSS_PCLMUL192_CLAS_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z1=GEMSS_PXOR_(res1,sum);\
    GEMSS_PSTORE128(C,z1);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 1);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+2,z1);\
\
    /* X^256 */\
    res1=GEMSS_PCLMUL(x2,y2,0);\
    z1=GEMSS_PRSHIFT64(sum);\
    z2=GEMSS_PXOR_(res1,z1);\
    FINAL_STORE;


#define GEMSS_PCLMUL160_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL192_CLAS_FINAL(GEMSS_PSTOREL(C+4,z2),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
#define GEMSS_PCLMUL192_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL192_CLAS_FINAL(GEMSS_PSTORE128(C+4,z2),C,x1,x2,y1,y2,\
                             z1,z2,sum,res1,res2)


/* Karatsuba: 6 mul64, 1 GEMSS_PMIDDLE, 19 other instructions */
#define GEMSS_PCLMUL192_KAR_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
    {__m128i u31,u333;\
    /* A0*B0 */\
    z1=GEMSS_PCLMUL(x1,y1,0);\
    /* A1*B1 */\
    z2=GEMSS_PCLMUL(x1,y1,0x11);\
    /* A2*B2 */\
    u333=GEMSS_PCLMUL(x2,y2,0);\
\
    res1=GEMSS_PXOR_(z1,z2);\
    res2=GEMSS_PXOR_(u333,z2);\
    z2=GEMSS_PXOR_(res1,u333);\
    /*  C[0] = C0
        C[1] = C1^(C0^C2)
        C[2] = C2^(C1^C3)^C0^C4
        C[3] = C3^(C4^C2)^C1^C5
        C[4] = C4^(C5^C3)
        C[5] = C5 */\
    /* (A2 A2) */\
    u31=GEMSS_PSHUFFLE_32_1010(x2);\
    /* (B2 B2) */\
    sum=GEMSS_PSHUFFLE_32_1010(y2);\
    /* (A2 A2) ^ (A0 A1) */\
    GEMSS_PXOR1_2(u31,x1);\
    /* (B2 B2) ^ (B0 B1) */\
    GEMSS_PXOR1_2(sum,y1);\
    /* (A0+A2)*(B0+B2) */\
    GEMSS_PXOR1_2(z2,GEMSS_PCLMUL(u31,sum,0));\
    /* (A1+A2)*(B1+B2) */\
    GEMSS_PXOR1_2(res2,GEMSS_PCLMUL(u31,sum,0x11));\
    /* (A0+A1)*(B0+B1) */\
    GEMSS_PXOR1_2(res1,GEMSS_PCLMUL(GEMSS_PXOR_(x1,GEMSS_PRSHIFT64(x1)),\
                        GEMSS_PXOR_(y1,GEMSS_PRSHIFT64(y1)),0));\
\
    GEMSS_PXOR1_2(z1,GEMSS_PLSHIFT64(res1));\
    GEMSS_PXOR1_2(u333,GEMSS_PRSHIFT64(res2));\
    GEMSS_PXOR1_2(z2,GEMSS_PMIDDLE(res1,res2));\
\
    GEMSS_PSTORE128(C,z1);\
    FINAL_STORE;\
    GEMSS_PSTORE128(C+2,z2);}


#define GEMSS_PCLMUL160_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL192_KAR_FINAL(GEMSS_PSTOREL(C+4,u333),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
#define GEMSS_PCLMUL192_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL192_KAR_FINAL(GEMSS_PSTORE128(C+4,u333),C,x1,x2,y1,y2,\
                            z1,z2,sum,res1,res2)


/* Classical: 16 mul64, 2 GEMSS_PMIDDLE, 15 other instructions */
#define GEMSS_PCLMUL256_CLAS_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z1=GEMSS_PXOR_(res1,sum);\
    GEMSS_PSTORE128(C,z1);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+2,z1);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(y1, x2, 0x11);\
    z2=GEMSS_PCLMUL(y2, x2, 0);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0x11);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    z2=GEMSS_PCLMUL(x2, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+4,z1);\
\
    /* X^384 */\
    res1=GEMSS_PCLMUL(x2,y2,0x11);\
    z1=GEMSS_PRSHIFT64(res2);\
    z2=GEMSS_PXOR_(res1,z1);\
    FINAL_STORE;


#define GEMSS_PCLMUL224_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL256_CLAS_FINAL(GEMSS_PSTOREL(C+6,z2),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
#define GEMSS_PCLMUL256_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL256_CLAS_FINAL(GEMSS_PSTORE128(C+6,z2),C,x1,x2,y1,y2,\
                             z1,z2,sum,res1,res2)


/* Karatsuba: 3 mul128, 5 other instructions */
#define GEMSS_PCLMUL256_KAR_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
    {__m128i x,y,u41,u42,u43,u44;\
    GEMSS_PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL128_WS_GF2X(u43,u44,x2,y2,sum,res1,res2);\
\
    x=GEMSS_PXOR_(x1,x2);\
    y=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(u43,z2);\
    z2=GEMSS_PXOR_(u43,z1);\
    GEMSS_PXOR1_2(u43,u44);\
\
    GEMSS_PCLMUL128_ADD_GF2X(z2,u43,u41,u42,x,y,sum,res1,res2);\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,u43);\
    FINAL_STORE;}


#define GEMSS_PCLMUL224_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL256_KAR_FINAL(GEMSS_PSTOREL(C+6,u44),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
#define GEMSS_PCLMUL256_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL256_KAR_FINAL(GEMSS_PSTORE128(C+6,u44),C,x1,x2,y1,y2,z1,z2,\
                            sum,res1,res2)


/* Classical: 25 mul64, 3 GEMSS_PMIDDLE, 23 other instructions */
#define GEMSS_PCLMUL320_CLAS_FINAL(FINAL_STORE,C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z1=GEMSS_PXOR_(res1,sum);\
    GEMSS_PSTORE128(C,z1);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+2,z1);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 1);\
    z2=GEMSS_PCLMUL(x2, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+4,z1);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x2, y3, 0);\
    z2=GEMSS_PCLMUL(x2, y2, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x2, y3, 1);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+6,z1);\
\
    /* X^512 */\
    res1=GEMSS_PCLMUL(x3,y3,0);\
    z1=GEMSS_PRSHIFT64(sum);\
    z2=GEMSS_PXOR_(res1,z1);\
    FINAL_STORE;


#define GEMSS_PCLMUL288_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL320_CLAS_FINAL(GEMSS_PSTOREL(C+8,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)
#define GEMSS_PCLMUL320_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL320_CLAS_FINAL(GEMSS_PSTORE128(C+8,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)


/* Karatsuba: 2 mul192, 1 mul128, 9 other instructions */
#define GEMSS_PCLMUL320_KAR_FINAL(FINAL_STORE,C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2) \
    {__m128i x1m,y1m,R1,R2,R3,u53,u54,u55;\
    GEMSS_PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
    GEMSS_PCLMUL192_WS_GF2X(u53,u54,u55,x2,x3,y2,y3,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x2);\
    y1m=GEMSS_PXOR_(y1,y2);\
\
    GEMSS_PXOR1_2(u53,z2);\
    z2=GEMSS_PXOR_(u53,z1);\
    GEMSS_PXOR1_2(u53,u54);\
    GEMSS_PXOR1_2(u54,u55);\
\
    GEMSS_PCLMUL192_WS_GF2X(R1,R2,R3,x1m,x3,y1m,y3,sum,res1,res2);\
\
    GEMSS_PXOR1_2(z2,R1);\
    GEMSS_PXOR1_2(u53,R2);\
    GEMSS_PXOR1_2(u54,R3);\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,u53);\
    GEMSS_PSTORE128(C+6,u54);\
    FINAL_STORE;}


#define GEMSS_PCLMUL288_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL320_KAR_FINAL(GEMSS_PSTOREL(C+8,u55),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                            sum,res1,res2)
#define GEMSS_PCLMUL320_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL320_KAR_FINAL(GEMSS_PSTORE128(C+8,u55),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                            sum,res1,res2)


/* Classical: 36 mul64, 4 GEMSS_PMIDDLE, 33 other instructions */
#define GEMSS_PCLMUL384_CLAS_FINAL(FINAL_STORE,C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z1=GEMSS_PXOR_(res1,sum);\
    GEMSS_PSTORE128(C,z1);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+2,z1);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 0x10);\
    z2=GEMSS_PCLMUL(x1, y3, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+4,z1);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x1, y3, 0x11);\
    z2=GEMSS_PCLMUL(x2, y3, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0x11);\
    res1=GEMSS_PXOR_(z1,sum);\
    z2=GEMSS_PCLMUL(x3, y2, 0);\
    sum=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x3, y1, 0x11);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x2, y3, 0x10);\
    z2=GEMSS_PCLMUL(x2, y3, 1);\
    sum=GEMSS_PXOR_(z1,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    z1=GEMSS_PXOR_(sum,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 1);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+6,z1);\
\
    /* X^512 */\
    z1=GEMSS_PCLMUL(x2, y3, 0x11);\
    z2=GEMSS_PCLMUL(x3, y3, 0);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0x11);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^576 */\
    z1=GEMSS_PCLMUL(x3, y3, 0x10);\
    z2=GEMSS_PCLMUL(x3, y3, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+8,z1);\
\
    /* X^640 */\
    res1=GEMSS_PCLMUL(x3,y3,0x11);\
    z1=GEMSS_PRSHIFT64(res2);\
    z2=GEMSS_PXOR_(res1,z1);\
    FINAL_STORE;


#define GEMSS_PCLMUL352_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL384_CLAS_FINAL(GEMSS_PSTOREL(C+10,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)
#define GEMSS_PCLMUL384_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL384_CLAS_FINAL(GEMSS_PSTORE128(C+10,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)


/* Karatsuba: 3 mul192, 4 GEMSS_PMIDDLE, 18 other instructions */
#define GEMSS_PCLMUL384_KAR_FINAL(FINAL_STORE,C,x1,x2,x3,y1,y2,y3,z1,z2,\
                            sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,R1,R2,R3,u63,u64,u65,u66;\
    GEMSS_PCLMUL192_WS_GF2X(z1,z2,u63,x1,x2,y1,y2,sum,res1,res2);\
\
    x1m=GEMSS_PMIDDLE(x2,x3);\
    x2m=GEMSS_PRSHIFT64(x3);\
    y1m=GEMSS_PMIDDLE(y2,y3);\
    y2m=GEMSS_PRSHIFT64(y3);\
\
    GEMSS_PCLMUL192_WS_GF2X(u64,u65,u66,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PXOR1_2(x1m,x1);\
    GEMSS_PXOR1_2(x2m,x2);\
    GEMSS_PXOR1_2(y1m,y1);\
    GEMSS_PXOR1_2(y2m,y2);\
\
    GEMSS_PCLMUL192_WS_GF2X(R1,R2,R3,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PXOR1_2(R1,GEMSS_PXOR_(z1,u64));\
    GEMSS_PXOR1_2(R2,GEMSS_PXOR_(z2,u65));\
    GEMSS_PXOR1_2(R3,GEMSS_PXOR_(u63,u66));\
    GEMSS_PXOR1_2(z2,GEMSS_PLSHIFT64(R1));\
    GEMSS_PXOR1_2(u65,GEMSS_PRSHIFT64(R3));\
    GEMSS_PXOR1_2(u63,GEMSS_PMIDDLE(R1,R2));\
    GEMSS_PXOR1_2(u64,GEMSS_PMIDDLE(R2,R3));\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,u63);\
    GEMSS_PSTORE128(C+6,u64);\
    GEMSS_PSTORE128(C+8,u65);\
    FINAL_STORE;}


#define GEMSS_PCLMUL352_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL384_KAR_FINAL(GEMSS_PSTOREL(C+10,u66),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                            sum,res1,res2)
#define GEMSS_PCLMUL384_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL384_KAR_FINAL(GEMSS_PSTORE128(C+10,u66),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                            sum,res1,res2)


/* Classical: 49 mul64, 5 GEMSS_PMIDDLE, 45 other instructions */
#define GEMSS_PCLMUL448_CLAS_FINAL(FINAL_STORE,C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,\
                             sum,res1,res2) \
    /* X^0 */\
    res1=GEMSS_PCLMUL(x1,y1,0);\
\
    /* X^64 */\
    z1=GEMSS_PCLMUL(x1, y1, 1);\
    z2=GEMSS_PCLMUL(x1, y1, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    sum=GEMSS_PLSHIFT64(res2);\
    z1=GEMSS_PXOR_(res1,sum);\
    GEMSS_PSTORE128(C,z1);\
\
    /* X^128 */\
    z1=GEMSS_PCLMUL(x1, y1, 0x11);\
    z2=GEMSS_PCLMUL(x2, y1, 0);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x1, y2, 0);\
    res1=GEMSS_PXOR_(sum,z1);\
\
    /* X^192 */\
    z1=GEMSS_PCLMUL(x1, y2, 1);\
    z2=GEMSS_PCLMUL(x1, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(y1, x2, 1);\
    z2=GEMSS_PXOR_(sum,z1);\
    z1=GEMSS_PCLMUL(y1, x2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+2,z1);\
\
    /* X^256 */\
    z1=GEMSS_PCLMUL(x1, y3, 0);\
    z2=GEMSS_PCLMUL(x1, y2, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y1, 0x11);\
    res2=GEMSS_PXOR_(z1,res1);\
    z2=GEMSS_PCLMUL(x3, y1, 0);\
    res1=GEMSS_PXOR_(res2,z2);\
\
    /* X^320 */\
    z1=GEMSS_PCLMUL(x1, y3, 0x10);\
    z2=GEMSS_PCLMUL(x1, y3, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y2, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x2, y2, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y1, 0x10);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x3, y1, 1);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+4,z1);\
\
    /* X^384 */\
    z1=GEMSS_PCLMUL(x1, y4, 0);\
    z2=GEMSS_PCLMUL(x1, y3, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x2, y3, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
    z2=GEMSS_PCLMUL(x2, y2, 0x11);\
    sum=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x3, y2, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
    z2=GEMSS_PCLMUL(x3, y1, 0x11);\
    sum=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x4, y1, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^448 */\
    z1=GEMSS_PCLMUL(x1, y4, 1);\
    z2=GEMSS_PCLMUL(x2, y3, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z2=GEMSS_PCLMUL(x2, y3, 1);\
    z1=GEMSS_PXOR_(sum,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
    z2=GEMSS_PCLMUL(x3, y2, 1);\
    z1=GEMSS_PXOR_(sum,z2);\
    z2=GEMSS_PCLMUL(x4, y1, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+6,z1);\
\
    /* X^512 */\
    z1=GEMSS_PCLMUL(x2, y4, 0);\
    z2=GEMSS_PCLMUL(x2, y3, 0x11);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y3, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
    z2=GEMSS_PCLMUL(x3, y2, 0x11);\
    res2=GEMSS_PXOR_(res1,z2);\
    z1=GEMSS_PCLMUL(x4, y2, 0);\
    res1=GEMSS_PXOR_(res2,z1);\
\
    /* X^576 */\
    z1=GEMSS_PCLMUL(x2, y4, 1);\
    z2=GEMSS_PCLMUL(x3, y3, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x3, y3, 1);\
    z2=GEMSS_PXOR_(res2,z1);\
    z1=GEMSS_PCLMUL(x4, y2, 0x10);\
    res2=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(sum,res2);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+8,z1);\
\
    /* X^640 */\
    z1=GEMSS_PCLMUL(x3, y4, 0);\
    z2=GEMSS_PCLMUL(x3, y3, 0x11);\
    sum=GEMSS_PXOR_(z1,z2);\
    z1=GEMSS_PCLMUL(x4, y3, 0);\
    res1=GEMSS_PXOR_(z1,sum);\
\
    /* X^704 */\
    z1=GEMSS_PCLMUL(x3, y4, 1);\
    z2=GEMSS_PCLMUL(x4, y3, 0x10);\
    sum=GEMSS_PXOR_(z1,z2);\
\
    z2=GEMSS_PMIDDLE(res2,sum);\
    z1=GEMSS_PXOR_(res1,z2);\
    GEMSS_PSTORE128(C+10,z1);\
\
    /* X^768 */\
    res1=GEMSS_PCLMUL(x4,y4,0);\
    res2=GEMSS_PRSHIFT64(sum);\
    z2=GEMSS_PXOR_(res1,res2);\
    FINAL_STORE;


#define GEMSS_PCLMUL416_CLAS_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL448_CLAS_FINAL(GEMSS_PSTOREL(C+12,z2),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)

#define GEMSS_PCLMUL448_CLAS_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL448_CLAS_FINAL(GEMSS_PSTORE128(C+12,z2),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)


/* Karatsuba: 2 mul256, 1 mul192, 9 other instructions */
#define GEMSS_PCLMUL448_KAR_FINAL(FINAL_STORE,C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,\
                            sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,t1,t2,z3,z4,z5,z6,z7;\
    GEMSS_PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL192_WS_GF2X(z5,z6,z7,x3,x4,y3,y4,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x3);\
    x2m=GEMSS_PXOR_(x2,x4);\
    y1m=GEMSS_PXOR_(y1,y3);\
    y2m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
\
    GEMSS_PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,z3);\
    GEMSS_PSTORE128(C+6,z4);\
    GEMSS_PSTORE128(C+8,z5);\
    GEMSS_PSTORE128(C+10,z6);\
    FINAL_STORE;}


#define GEMSS_PCLMUL416_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL448_KAR_FINAL(GEMSS_PSTOREL(C+12,z7),C,x1,x2,x3,x4,\
                            y1,y2,y3,y4,z1,z2,sum,res1,res2)

#define GEMSS_PCLMUL448_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL448_KAR_FINAL(GEMSS_PSTORE128(C+12,z7),C,x1,x2,x3,x4,\
                            y1,y2,y3,y4,z1,z2,sum,res1,res2)


/* Karatsuba: 3 mul256, 1 mul192, 10 other instructions */
#define GEMSS_PCLMUL512_KAR_FINAL(FINAL_STORE,C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,\
                            sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,t1,t2,z3,z4,z5,z6,z7,z8;\
    GEMSS_PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL256_WS_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x3);\
    x2m=GEMSS_PXOR_(x2,x4);\
    y1m=GEMSS_PXOR_(y1,y3);\
    y2m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
    z6=GEMSS_PXOR_(z6,z8);\
\
    GEMSS_PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,z3);\
    GEMSS_PSTORE128(C+6,z4);\
    GEMSS_PSTORE128(C+8,z5);\
    GEMSS_PSTORE128(C+10,z6);\
    GEMSS_PSTORE128(C+12,z7);\
    FINAL_STORE;}


#define GEMSS_PCLMUL480_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL512_KAR_FINAL(GEMSS_PSTOREL(C+14,z8),C,x1,x2,x3,x4,\
                            y1,y2,y3,y4,z1,z2,sum,res1,res2)

#define GEMSS_PCLMUL512_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL512_KAR_FINAL(GEMSS_PSTORE128(C+14,z8),C,x1,x2,x3,x4,\
                            y1,y2,y3,y4,z1,z2,sum,res1,res2)


/* Karatsuba: 3 mul256, 1 mul192, 10 other instructions */
#define GEMSS_PCLMUL512_KAR2_FINAL(FINAL_STORE,C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,\
                             sum,res1,res2)\
    {__m128i x1m,x2m,y1m,y2m,t1,t2,z3,z4,z5,z6,z7,z8;\
    GEMSS_PCLMUL256_WS_KAR2_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL256_WS_KAR2_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
\
    x1m=GEMSS_PXOR_(x1,x3);\
    x2m=GEMSS_PXOR_(x2,x4);\
    y1m=GEMSS_PXOR_(y1,y3);\
    y2m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
    z6=GEMSS_PXOR_(z6,z8);\
\
    GEMSS_PCLMUL256_ADD_KAR2_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,z3);\
    GEMSS_PSTORE128(C+6,z4);\
    GEMSS_PSTORE128(C+8,z5);\
    GEMSS_PSTORE128(C+10,z6);\
    GEMSS_PSTORE128(C+12,z7);\
    FINAL_STORE;}


#define GEMSS_PCLMUL480_KAR2_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL512_KAR2_FINAL(GEMSS_PSTOREL(C+14,z8),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)

#define GEMSS_PCLMUL512_KAR2_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
        GEMSS_PCLMUL512_KAR2_FINAL(GEMSS_PSTORE128(C+14,z8),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)


/* Karatsuba: 2 mul320, 1 mul256, 11 other instructions */
#define GEMSS_PCLMUL576_KAR_FINAL(FINAL_STORE,C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,\
                            sum,res1,res2)\
    {__m128i x11m,x22m,y11m,y22m,t1,t2,z3,z4,z5,z6,z7,z8,z9;\
    GEMSS_PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
    GEMSS_PCLMUL320_WS_GF2X(z5,z6,z7,z8,z9,x3,x4,x5,y3,y4,y5,sum,res1,res2);\
\
    x11m=GEMSS_PXOR_(x1,x3);\
    x22m=GEMSS_PXOR_(x2,x4);\
    y11m=GEMSS_PXOR_(y1,y3);\
    y22m=GEMSS_PXOR_(y2,y4);\
\
    z5=GEMSS_PXOR_(z3,z5);\
    z6=GEMSS_PXOR_(z4,z6);\
    z3=GEMSS_PXOR_(z5,z1);\
    z4=GEMSS_PXOR_(z6,z2);\
    z5=GEMSS_PXOR_(z5,z7);\
    z6=GEMSS_PXOR_(z6,z8);\
    z7=GEMSS_PXOR_(z7,z9);\
\
    GEMSS_PCLMUL320_ADD_GF2X(z3,z4,z5,z6,z7,t1,t2,x11m,x22m,x5,y11m,y22m,y5,\
                       sum,res1,res2);\
\
    GEMSS_PSTORE128(C,z1);\
    GEMSS_PSTORE128(C+2,z2);\
    GEMSS_PSTORE128(C+4,z3);\
    GEMSS_PSTORE128(C+6,z4);\
    GEMSS_PSTORE128(C+8,z5);\
    GEMSS_PSTORE128(C+10,z6);\
    GEMSS_PSTORE128(C+12,z7);\
    GEMSS_PSTORE128(C+14,z8);\
    FINAL_STORE;}


#define GEMSS_PCLMUL544_KAR_GF2X(C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)\
        GEMSS_PCLMUL576_KAR_FINAL(GEMSS_PSTOREL(C+16,z9),C,x1,x2,x3,x4,x5,\
                            y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)

#define GEMSS_PCLMUL576_KAR_GF2X(C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)\
        GEMSS_PCLMUL576_KAR_FINAL(GEMSS_PSTORE128(C+16,z9),C,x1,x2,x3,x4,x5,\
                            y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)


#if GEMSS_PROC_HASWELL
    #define GEMSS_PCLMUL96_GF2X  GEMSS_PCLMUL96_CLAS_GF2X
    #define GEMSS_PCLMUL128_GF2X GEMSS_PCLMUL128_CLAS_GF2X
    #define GEMSS_PCLMUL160_GF2X GEMSS_PCLMUL160_KAR_GF2X
    #define GEMSS_PCLMUL192_GF2X GEMSS_PCLMUL192_KAR_GF2X
    #define GEMSS_PCLMUL224_GF2X GEMSS_PCLMUL224_KAR_GF2X
    #define GEMSS_PCLMUL256_GF2X GEMSS_PCLMUL256_KAR_GF2X
    #define GEMSS_PCLMUL288_GF2X GEMSS_PCLMUL288_KAR_GF2X
    #define GEMSS_PCLMUL320_GF2X GEMSS_PCLMUL320_KAR_GF2X
    #define GEMSS_PCLMUL352_GF2X GEMSS_PCLMUL352_KAR_GF2X
    #define GEMSS_PCLMUL384_GF2X GEMSS_PCLMUL384_KAR_GF2X
    #define GEMSS_PCLMUL416_GF2X GEMSS_PCLMUL416_KAR_GF2X
    #define GEMSS_PCLMUL448_GF2X GEMSS_PCLMUL448_KAR_GF2X
    #define GEMSS_PCLMUL480_GF2X GEMSS_PCLMUL480_KAR2_GF2X
    #define GEMSS_PCLMUL512_GF2X GEMSS_PCLMUL512_KAR2_GF2X
    #define GEMSS_PCLMUL544_GF2X GEMSS_PCLMUL544_KAR_GF2X
    #define GEMSS_PCLMUL576_GF2X GEMSS_PCLMUL576_KAR_GF2X
#else
    /* Skylake */
    #define GEMSS_PCLMUL96_GF2X  GEMSS_PCLMUL96_CLAS_GF2X
    #define GEMSS_PCLMUL128_GF2X GEMSS_PCLMUL128_CLAS_GF2X
    #define GEMSS_PCLMUL160_GF2X GEMSS_PCLMUL160_CLAS_GF2X
    #define GEMSS_PCLMUL192_GF2X GEMSS_PCLMUL192_CLAS_GF2X
    #define GEMSS_PCLMUL224_GF2X GEMSS_PCLMUL224_KAR_GF2X
    #define GEMSS_PCLMUL256_GF2X GEMSS_PCLMUL256_KAR_GF2X
    #define GEMSS_PCLMUL288_GF2X GEMSS_PCLMUL288_CLAS_GF2X
    #define GEMSS_PCLMUL320_GF2X GEMSS_PCLMUL320_CLAS_GF2X
    #define GEMSS_PCLMUL352_GF2X GEMSS_PCLMUL352_CLAS_GF2X
    #define GEMSS_PCLMUL384_GF2X GEMSS_PCLMUL384_CLAS_GF2X
    #define GEMSS_PCLMUL416_GF2X GEMSS_PCLMUL416_KAR_GF2X
    #define GEMSS_PCLMUL448_GF2X GEMSS_PCLMUL448_KAR_GF2X
    #define GEMSS_PCLMUL480_GF2X GEMSS_PCLMUL480_KAR_GF2X
    #define GEMSS_PCLMUL512_GF2X GEMSS_PCLMUL512_KAR_GF2X
    #define GEMSS_PCLMUL544_GF2X GEMSS_PCLMUL544_KAR_GF2X
    #define GEMSS_PCLMUL576_GF2X GEMSS_PCLMUL576_KAR_GF2X
#endif






/* Choice of the best multiplication */
#if GEMSS_ENABLED_GF2X
    /* The gf2x library has the priority when enabled.
       In this case, the chosen muliplication is not necessarily the fastest. */
    #include <gf2x/gf2x_mul1.h>
    #include <gf2x/gf2x_mul2.h>
    #include <gf2x/gf2x_mul3.h>
    #include <gf2x/gf2x_mul4.h>
    #include <gf2x/gf2x_mul5.h>
    #include <gf2x/gf2x_mul6.h>
    #include <gf2x/gf2x_mul7.h>
    #include <gf2x/gf2x_mul8.h>
    #include <gf2x/gf2x_mul9.h>

    #ifdef GEMSS_MODE_64_BITS
        #define GEMSS_best_mul32_gf2x GEMSS_mul32_no_simd_gf2x
        #define GEMSS_best_mul64low_gf2x GEMSS_mul64low_no_simd_gf2x

        #ifdef __PCLMUL__
            #define GEMSS_best_mul64_gf2x(C,A,B) gf2x_mul1((C),*(A),*(B))
            #define GEMSS_best_mul128_gf2x(C,A,B) gf2x_mul2((C),(A),(B))
            #define GEMSS_best_mul192_gf2x(C,A,B) gf2x_mul3((C),(A),(B))
            #define GEMSS_best_mul256_gf2x(C,A,B) gf2x_mul4((C),(A),(B))
            #define GEMSS_best_mul320_gf2x(C,A,B) gf2x_mul5((C),(A),(B))
            #define GEMSS_best_mul384_gf2x(C,A,B) gf2x_mul6((C),(A),(B))
            #define GEMSS_best_mul448_gf2x(C,A,B) gf2x_mul7((C),(A),(B))
            #define GEMSS_best_mul512_gf2x(C,A,B) gf2x_mul8((C),(A),(B))
            #define GEMSS_best_mul576_gf2x(C,A,B) gf2x_mul9((C),(A),(B))
        #else
            /* Prototype of gf2x_mul from the gf2x library */
            extern void gf2x_mul(unsigned long *c,
    	        	const unsigned long *a, unsigned long an,
    	        	const unsigned long *b, unsigned long bn);

            /* To inline functions could be failed */
            #define GEMSS_best_mul64_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                (const unsigned long*)(A),1,\
                                                (const unsigned long*)(B),1)
            #define GEMSS_best_mul128_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),2,\
                                                 (const unsigned long*)(B),2)
            #define GEMSS_best_mul192_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),3,\
                                                 (const unsigned long*)(B),3)
            #define GEMSS_best_mul256_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),4,\
                                                 (const unsigned long*)(B),4)
            #define GEMSS_best_mul320_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),5,\
                                                 (const unsigned long*)(B),5)
            #define GEMSS_best_mul384_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),6,\
                                                 (const unsigned long*)(B),6)
            #define GEMSS_best_mul448_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),7,\
                                                 (const unsigned long*)(B),7)
            #define GEMSS_best_mul512_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),8,\
                                                 (const unsigned long*)(B),8)
            #define GEMSS_best_mul576_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),9,\
                                                 (const unsigned long*)(B),9)
        #endif

        /* XXX The number of word of C must be even XXX */
        #define GEMSS_best_mul96_gf2x  GEMSS_best_mul128_gf2x
        #define GEMSS_best_mul160_gf2x GEMSS_best_mul192_gf2x
        #define GEMSS_best_mul224_gf2x GEMSS_best_mul256_gf2x
        #define GEMSS_best_mul288_gf2x GEMSS_best_mul320_gf2x
        #define GEMSS_best_mul352_gf2x GEMSS_best_mul384_gf2x
        #define GEMSS_best_mul416_gf2x GEMSS_best_mul448_gf2x
        #define GEMSS_best_mul480_gf2x GEMSS_best_mul512_gf2x
        #define GEMSS_best_mul544_gf2x GEMSS_best_mul576_gf2x
    #elif defined(GEMSS_MODE_32_BITS)
        #define GEMSS_best_mul64low_gf2x GEMSS_mul64low_no_simd_gf2x

        /* Prototype of gf2x_mul from the gf2x library */
        extern void gf2x_mul(unsigned long *c,
	        	const unsigned long *a, unsigned long an,
	        	const unsigned long *b, unsigned long bn);

        /* The number of word of C can be odd */
        #ifdef __PCLMUL__
            #define GEMSS_best_mul32_gf2x(C,A,B) gf2x_mul1((unsigned long*)(C),\
                                                     (unsigned long)(*(A)),\
                                                     (unsigned long)(*(B)))
            #define GEMSS_best_mul64_gf2x(C,A,B) gf2x_mul2((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul96_gf2x(C,A,B) gf2x_mul3((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul128_gf2x(C,A,B) gf2x_mul4((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul160_gf2x(C,A,B) gf2x_mul5((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul192_gf2x(C,A,B) gf2x_mul6((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul224_gf2x(C,A,B) gf2x_mul7((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul256_gf2x(C,A,B) gf2x_mul8((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
            #define GEMSS_best_mul288_gf2x(C,A,B) gf2x_mul9((unsigned long*)(C),\
                                                     (const unsigned long*)(A),\
                                                     (const unsigned long*)(B))
        #else
            /* To inline functions could be failed */
            #define GEMSS_best_mul32_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                (const unsigned long*)(A),1,\
                                                (const unsigned long*)(B),1)
            #define GEMSS_best_mul64_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),2,\
                                                 (const unsigned long*)(B),2)
            #define GEMSS_best_mul96_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),3,\
                                                 (const unsigned long*)(B),3)
            #define GEMSS_best_mul128_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),4,\
                                                 (const unsigned long*)(B),4)
            #define GEMSS_best_mul160_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),5,\
                                                 (const unsigned long*)(B),5)
            #define GEMSS_best_mul192_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),6,\
                                                 (const unsigned long*)(B),6)
            #define GEMSS_best_mul224_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),7,\
                                                 (const unsigned long*)(B),7)
            #define GEMSS_best_mul256_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),8,\
                                                 (const unsigned long*)(B),8)
            #define GEMSS_best_mul288_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),9,\
                                                 (const unsigned long*)(B),9)
        #endif


        #define GEMSS_best_mul320_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),10,\
                                                 (const unsigned long*)(B),10)
        #define GEMSS_best_mul352_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),11,\
                                                 (const unsigned long*)(B),11)
        #define GEMSS_best_mul384_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),12,\
                                                 (const unsigned long*)(B),12)
        #define GEMSS_best_mul416_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),13,\
                                                 (const unsigned long*)(B),13)
        #define GEMSS_best_mul448_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),14,\
                                                 (const unsigned long*)(B),14)
        #define GEMSS_best_mul480_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),15,\
                                                 (const unsigned long*)(B),15)
        #define GEMSS_best_mul512_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),16,\
                                                 (const unsigned long*)(B),16)
        #define GEMSS_best_mul544_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),17,\
                                                 (const unsigned long*)(B),17)
        #define GEMSS_best_mul576_gf2x(C,A,B) gf2x_mul((unsigned long*)(C),\
                                                 (const unsigned long*)(A),18,\
                                                 (const unsigned long*)(B),18)
    #endif

#elif defined(GEMSS_ENABLED_PCLMUL)
    #define GEMSS_best_mul32_gf2x GEMSS_pclmul32_inlined_gf2x
    #define GEMSS_best_mul64low_gf2x GEMSS_pclmul64low_inlined_gf2x
    #define GEMSS_best_mul64_gf2x GEMSS_pclmul64_inlined_gf2x
    /* #define GEMSS_best_mul32_gf2x  GEMSS_pclmul32_gf2x */
    /* #define GEMSS_best_mul64low_gf2x GEMSS_pclmul64low_gf2x */
    /* #define GEMSS_best_mul64_gf2x  GEMSS_pclmul64_gf2x */
    #define GEMSS_best_mul128_gf2x GEMSS_pclmul128_gf2x
    #define GEMSS_best_mul192_gf2x GEMSS_pclmul192_gf2x
    #define GEMSS_best_mul256_gf2x GEMSS_pclmul256_gf2x
    #define GEMSS_best_mul320_gf2x GEMSS_pclmul320_gf2x
    #define GEMSS_best_mul384_gf2x GEMSS_pclmul384_gf2x
    #define GEMSS_best_mul448_gf2x GEMSS_pclmul448_gf2x
    #define GEMSS_best_mul512_gf2x GEMSS_pclmul512_gf2x
    #define GEMSS_best_mul576_gf2x GEMSS_pclmul576_gf2x

    /* The number of word of C can be odd */
    #define GEMSS_best_mul96_gf2x  GEMSS_pclmul96_gf2x
    #define GEMSS_best_mul160_gf2x GEMSS_pclmul160_gf2x
    #define GEMSS_best_mul224_gf2x GEMSS_pclmul224_gf2x
    #define GEMSS_best_mul288_gf2x GEMSS_pclmul288_gf2x
    #define GEMSS_best_mul352_gf2x GEMSS_pclmul352_gf2x
    #define GEMSS_best_mul416_gf2x GEMSS_pclmul416_gf2x
    #define GEMSS_best_mul480_gf2x GEMSS_pclmul480_gf2x
    #define GEMSS_best_mul544_gf2x GEMSS_pclmul544_gf2x
#elif defined(GEMSS_ENABLED_SSE2)
    /* sse2 */
    #define GEMSS_best_mul32_gf2x GEMSS_pmul32_gf2x
    #define GEMSS_best_mul64low_gf2x GEMSS_mul64low_no_simd_gf2x
    #define GEMSS_best_mul64_gf2x  GEMSS_pmul64_gf2x
    #define GEMSS_best_mul96_gf2x  GEMSS_pmul96_gf2x
    #define GEMSS_best_mul128_gf2x GEMSS_pmul128_gf2x
    #define GEMSS_best_mul160_gf2x GEMSS_pmul160_gf2x
    #define GEMSS_best_mul192_gf2x GEMSS_pmul192_gf2x
    #define GEMSS_best_mul224_gf2x GEMSS_pmul224_gf2x
    #define GEMSS_best_mul256_gf2x GEMSS_pmul256_gf2x
    #define GEMSS_best_mul288_gf2x GEMSS_pmul288_gf2x
    #define GEMSS_best_mul320_gf2x GEMSS_pmul320_gf2x
    #define GEMSS_best_mul352_gf2x GEMSS_pmul352_gf2x
    #define GEMSS_best_mul384_gf2x GEMSS_pmul384_gf2x
    #define GEMSS_best_mul416_gf2x GEMSS_pmul416_gf2x
    #define GEMSS_best_mul448_gf2x GEMSS_pmul448_gf2x
    #define GEMSS_best_mul480_gf2x GEMSS_pmul480_gf2x
    #define GEMSS_best_mul512_gf2x GEMSS_pmul512_gf2x
    #define GEMSS_best_mul544_gf2x GEMSS_pmul544_gf2x
    #define GEMSS_best_mul576_gf2x GEMSS_pmul576_gf2x
#else
    /* Without SIMD */
    #define GEMSS_best_mul32_gf2x GEMSS_mul32_no_simd_gf2x
    #define GEMSS_best_mul64low_gf2x GEMSS_mul64low_no_simd_gf2x
    #define GEMSS_best_mul64_gf2x  GEMSS_mul64_no_simd_gf2x
    #define GEMSS_best_mul96_gf2x  GEMSS_mul96_no_simd_gf2x
    #define GEMSS_best_mul128_gf2x GEMSS_mul128_no_simd_gf2x
    #define GEMSS_best_mul160_gf2x GEMSS_mul160_no_simd_gf2x
    #define GEMSS_best_mul192_gf2x GEMSS_mul192_no_simd_gf2x
    #define GEMSS_best_mul224_gf2x GEMSS_mul224_no_simd_gf2x
    #define GEMSS_best_mul256_gf2x GEMSS_mul256_no_simd_gf2x
    #define GEMSS_best_mul288_gf2x GEMSS_mul288_no_simd_gf2x
    #define GEMSS_best_mul320_gf2x GEMSS_mul320_no_simd_gf2x
    #define GEMSS_best_mul352_gf2x GEMSS_mul352_no_simd_gf2x
    #define GEMSS_best_mul384_gf2x GEMSS_mul384_no_simd_gf2x
    #define GEMSS_best_mul416_gf2x GEMSS_mul416_no_simd_gf2x
    #define GEMSS_best_mul448_gf2x GEMSS_mul448_no_simd_gf2x
    #define GEMSS_best_mul480_gf2x GEMSS_mul480_no_simd_gf2x
    #define GEMSS_best_mul512_gf2x GEMSS_mul512_no_simd_gf2x
    #define GEMSS_best_mul544_gf2x GEMSS_mul544_no_simd_gf2x
    #define GEMSS_best_mul576_gf2x GEMSS_mul576_no_simd_gf2x
#endif



#endif

