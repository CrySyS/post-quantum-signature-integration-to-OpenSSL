#ifndef _BIT_H
#define _BIT_H

#include "gemss_macro.h"
#include "gemss_arch.h"
#include "gemss_simd.h"


/* Tools for the bits manipulation */


/* (2^k) - 1, k<64, and -1 for k=0  */
#define GEMSS_mask64(k) ((k)?(GEMSS_ONE64<<(k))-GEMSS_ONE64:GEMSS_MONE64)

/* (2^k) - 1, k<32, and -1 for k=0 */
#define GEMSS_mask32(k) ((k)?(GEMSS_ONE32<<(k))-GEMSS_ONE32:GEMSS_MONE32)

#define GEMSS_maskUINT(k) ((k)?(GEMSS_UINT_1<<(k))-GEMSS_UINT_1:GEMSS_UINT_M1)


/** The i-th bit of the UINT val. */
#define GEMSS_ITHBIT(val,i) ((val>>i)&GEMSS_UINT_1)


/** Compute the MSB position of one UINT. */
/*  Input: U an UINT
    Output: res the MSB position of U. If U is zero, res=0
*/
#define GEMSS_MSB_SP(res,U,j) \
    res=0;\
    /* Search the MSB position of one word */\
    for(j=GEMSS_NB_BITS_UINT>>1;j!=0;j>>=1) \
    {\
        if((U)>>(res^j))\
        {\
            /* To remember the choice of the high part */\
            res^=j;\
        }\
    }

/** Compute the MSB position of a multi-precision UINT. */
/*  Input: U an multiple precision UINT, stored on nb_word words
    Output: res the MSB position of U. If U is zero, res=0
*/
#define GEMSS_MSB_MP(res,U,i,j,nb_word) \
    i=nb_word-1;\
    /* Search the first word different from zero */\
    while(i&&(!U[i])) \
    {\
        --i;\
    }\
    /* Search the MSB of one word */\
    GEMSS_MSB_SP(res,U[i],j);\
    res^=i<<GEMSS_LOG2_SIZE_UINT;



/* Macros about computations on the bits of a word */


/* Goal: computed in constant-time:
    - GEMSS_COUNTBITS64  n=Hamming_weight(n)=sum of the 64 bits of n
    -    GEMSS_ORBITS64: n=(n==0)?0:1
    -   GEMSS_NORBITS64: n=(n==0)?1:0
    -   GEMSS_XORBITS64: n=Hamming_weight(n) modulo 2=sum of the 64 bits of n, mod 2
*/


/* The fastest method, using popcnt */
/* Here, the performance tests assume that the constants are already in 
   registers. It is not necessarily true. */
#ifdef GEMSS_ENABLED_POPCNT
    #ifdef GEMSS_MODE_64_BITS
        #define GEMSS_COUNTBITS64_POP(n) \
            n=GEMSS_POPCNT_U64(n);
    #elif defined(GEMSS_MODE_32_BITS) 
        #define GEMSS_COUNTBITS64_POP(n) \
            n=GEMSS_POPCNT_U32(n)+GEMSS_POPCNT_U32(n>>32);
    #endif

    #define GEMSS_COUNTBITS32_POP(n) \
        n=GEMSS_POPCNT_U32(n);

    #define GEMSS_ORBITS64_POP(n) \
        GEMSS_COUNTBITS64_POP(n); \
        /* The result is in {0,1,...,64} */\
        n+=63;\
        /* Now, the result is in {63,64,...,127} */\
        n>>=6;\
        /* Now, the result is in {0,1,...,1} */


    #define GEMSS_NORBITS64_POP(n) \
        --n;\
        GEMSS_COUNTBITS64_POP(n); \
        /* If n=0, then Hamming_weight(n-1)==64, else Hamming_weight(n-1)<64 */\
        /* Now, the result is in {64,0,...,63} */\
        n>>=6;\
        /* Now, the result is in {1,0,...,0} */


    #define GEMSS_NORBITS64_POP2(n) \
        GEMSS_COUNTBITS64_POP(n); \
        /* The result is in {0,1,...,64} */\
        --n;\
        /* Now, the result is in {2^{64}-1,0,...,63} */\
        n>>=63;\
        /* Now, the result is in {1,0,...,0} */


    #define GEMSS_XORBITS64_POP(n) \
        GEMSS_COUNTBITS64_POP(n); \
        n&=GEMSS_ONE64;
#endif


/* The second fastest method, based on tricks 
   with right shift of i == integer division by 2^i */


/* 5 logical operations */
#define GEMSS_ORBITS64_SHORT(n) \
    n|=n << 32U;\
    n>>=32U;\
    n+=((uint64_t)0xFFFFFFFF);\
    n>>=32U;


/* 5 logical operations */
#define GEMSS_NORBITS64_SHORT(n) \
    n|=n << 32U;\
    n>>=32U;\
    --n;\
    n>>=63U;


/* The third fastest method, based on the variable-precision SWAR algorithm */
/* https://stackoverflow.com/questions/2709430/
   count-number-of-bits-in-a-64-bit-long-big-integer */


/* 12 logical operations */
#define GEMSS_COUNTBITS64_SWAR(n) \
    n-=(n >> 1U) & ((uint64_t)0x5555555555555555);\
    n=(n & ((uint64_t)0x3333333333333333)) \
      + ((n >> 2U) & ((uint64_t)0x3333333333333333));\
    n=(((n + (n >> 4U)) & ((uint64_t)0xF0F0F0F0F0F0F0F)) \
       * ((uint64_t)0x101010101010101)) >> 56U;


/* 13 logical operations */
#define GEMSS_ORBITS64_SWAR(n) \
    n-=(n >> 1U) & ((uint64_t)0x5555555555555555);\
    n=(n & ((uint64_t)0x3333333333333333)) \
      + ((n >> 2U) & ((uint64_t)0x3333333333333333));\
    /* We change ((n/(2^56))+63)/64 in (n+63*(2^56))/(2^62) */\
    n=((((n + (n >> 4U)) & ((uint64_t)0xF0F0F0F0F0F0F0F)) \
      * ((uint64_t)0x101010101010101)) + ((uint64_t)0x3F00000000000000)) >> 62U;


/* 13 logical operations */
#define GEMSS_NORBITS64_SWAR(n) \
    --n;\
    n-=(n >> 1U) & ((uint64_t)0x5555555555555555);\
    n=(n & ((uint64_t)0x3333333333333333)) \
      + ((n >> 2U) & ((uint64_t)0x3333333333333333));\
    n=((((n + (n >> 4U)) & ((uint64_t)0xF0F0F0F0F0F0F0F)) \
        * ((uint64_t)0x101010101010101))) >> 62U;


/* 13 logical operations */
#define GEMSS_NORBITS64_SWAR2(n) \
    n-=(n >> 1U) & ((uint64_t)0x5555555555555555);\
    n=(n & ((uint64_t)0x3333333333333333)) \
      + ((n >> 2U) & ((uint64_t)0x3333333333333333));\
    /* We remark that ({0,1,...,63}+255)<<56 ={255<<56,0<<56,...,62<<56}*2^56*/\
    /* So, the 63-th bit is 1 iff Hamming_weight(n)=0 */\
    n=((((n + (n >> 4U)) & ((uint64_t)0xF0F0F0F0F0F0F0F)) \
      * ((uint64_t)0x101010101010101)) + ((uint64_t)0xFF00000000000000)) >> 63U;


/* Slow, 13 logical operations */
#define GEMSS_XORBITS64_SWAR2(n) \
    GEMSS_COUNTBITS64_SWAR(n); \
    n&=GEMSS_ONE64;


/* A special algorithm with 7 logical operations */
#define GEMSS_XORBITS64_SWAR(n) \
    /*  +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*  */\
    n^=(n << 1);\
    /*  +***+***+***+***+***+***+***+***+***+***+***+***+***+***+***+***  */\
    n^=(n << 2);\
    /*  +000+000+000+000+000+000+000+000+000+000+000+000+000+000+000+000  */\
    /* Then, we sum the 16 bits and store them in the bits 63 to 67. */\
    /* So the 63-th bit in the bit of parity. */\
    n=((n & ((uint64_t)0x8888888888888888)) *((uint64_t)0x1111111111111111))\
      >> 63;


/* A special algorithm with 7 logical operations */
#define GEMSS_XORBITS32_SWAR(n) \
    /*  +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*  */\
    n^=(n << 1);\
    /*  +***+***+***+***+***+***+***+***  */\
    n^=(n << 2);\
    /*  +000+000+000+000+000+000+000+000  */\
    /* Then, we sum the 8 bits and store them in the bits 31 to 34. */\
    /* So the 31-th bit in the bit of parity. */\
    n=((n & ((uint32_t)0x88888888)) *((uint32_t)0x11111111)) >> 31;


/* A special algorithm with 7 logical operations */
#define GEMSS_XORBITS16_SWAR(n) \
    /*  +*+*+*+*+*+*+*+*  */\
    n^=(n << 1);\
    /*  +***+***+***+***  */\
    n^=(n << 2);\
    /*  +000+000+000+000  */\
    /* Then, we sum the 4 bits and store them in the bits 15 to 17. */\
    /* So the 15-th bit in the bit of parity. */\
    n=((n & ((uint16_t)0x8888)) *((uint16_t)0x1111)) >> 15;


/* A special algorithm with 5 logical operations */
#define GEMSS_XORBITS8_SWAR(n) \
    /*  +*+*+*+*  */\
    n^=(n << 1);\
    /*  +0+0+0+0  */\
    /* Then, we sum the 4 bits and store them in the bits 7 to 9. */\
    /* So the 15-th bit in the bit of parity. */\
    n=((n & ((uint8_t)0xAA)) *((uint8_t)0x55)) >> 7;


/* The slowest method, based on the "dichotomic xor/or" */


/* A generic method using the dichotomic principle */
#define GEMSS_ORBITS(n,SIZE) \
    GEMSS_FOR_LOOP_COMPLETE(SIZE,GEMSS_RESERVED_VARIABLE>0,GEMSS_RESERVED_VARIABLE>>1U,\
                      n|=n>>GEMSS_RESERVED_VARIABLE)\
    n&=GEMSS_UINT_1;


#define GEMSS_NORBITS(n,SIZE) \
    GEMSS_FOR_LOOP_COMPLETE(SIZE,GEMSS_RESERVED_VARIABLE>0,GEMSS_RESERVED_VARIABLE>>1U,\
                      n|=n>>GEMSS_RESERVED_VARIABLE)\
    n=~n;\
    n&=GEMSS_UINT_1;


#define GEMSS_XORBITS(n,SIZE) \
    GEMSS_FOR_LOOP_COMPLETE(SIZE,GEMSS_RESERVED_VARIABLE>0,GEMSS_RESERVED_VARIABLE>>1U,\
                      n^=n>>GEMSS_RESERVED_VARIABLE)\
    n&=GEMSS_UINT_1;


/* 13 logical operations */
#define GEMSS_ORBITS64_DICHO(n) \
    n|=n >> 32U;\
    n|=n >> 16U;\
    n|=n >> 8U;\
    n|=n >> 4U;\
    n|=n >> 2U;\
    n|=n >> 1U;\
    n&=GEMSS_ONE64;


/* 14 logical operations */
#define GEMSS_NORBITS64_DICHO(n) \
    n|=n >> 32U;\
    n|=n >> 16U;\
    n|=n >> 8U;\
    n|=n >> 4U;\
    n|=n >> 2U;\
    n|=n >> 1U;\
    n=~n;\
    n&=GEMSS_ONE64;


/* 13 logical operations */
#define GEMSS_XORBITS64_DICHO(n) \
    n^=n >> 32U;\
    n^=n >> 16U;\
    n^=n >> 8U;\
    n^=n >> 4U;\
    n^=n >> 2U;\
    n^=n >> 1U;\
    n&=GEMSS_ONE64;


/* Choose the best method */
#ifdef GEMSS_ENABLED_POPCNT
    /* This code is also the reference version. */
    #define GEMSS_COUNTBITS64 GEMSS_COUNTBITS64_POP
    #define    GEMSS_ORBITS64    GEMSS_ORBITS64_POP
    #define   GEMSS_NORBITS64   GEMSS_NORBITS64_POP
    #define   GEMSS_XORBITS64   GEMSS_XORBITS64_POP

    #define GEMSS_COUNTBITS32 GEMSS_COUNTBITS32_POP
#elif defined(GEMSS_MQSOFT_REF)
    #define GEMSS_COUNTBITS64 GEMSS_COUNTBITS64_SWAR
    #define    GEMSS_ORBITS64    GEMSS_ORBITS64_DICHO
    #define   GEMSS_NORBITS64   GEMSS_NORBITS64_DICHO
    #define   GEMSS_XORBITS64   GEMSS_XORBITS64_DICHO
#else
    #define GEMSS_COUNTBITS64 GEMSS_COUNTBITS64_SWAR
    #define    GEMSS_ORBITS64    GEMSS_ORBITS64_SHORT
    #define   GEMSS_NORBITS64   GEMSS_NORBITS64_SHORT
    #define   GEMSS_XORBITS64   GEMSS_XORBITS64_SWAR
#endif


#if (GEMSS_NB_BITS_UINT==64U)
    #define GEMSS_COUNTBITS_UINT GEMSS_CONCAT(COUNTBITS,GEMSS_NB_BITS_UINT)
    #define    GEMSS_ORBITS_UINT GEMSS_CONCAT(   GEMSS_ORBITS,GEMSS_NB_BITS_UINT)
    #define   GEMSS_NORBITS_UINT GEMSS_CONCAT(  GEMSS_NORBITS,GEMSS_NB_BITS_UINT)
    #define   GEMSS_XORBITS_UINT GEMSS_CONCAT(  GEMSS_XORBITS,GEMSS_NB_BITS_UINT)
#elif defined(GEMSS_MQSOFT_REF)
    #define GEMSS_COUNTBITS_UINT  GEMSS_COUNTBITS64_SWAR
    #define  GEMSS_ORBITS_UINT(n)  GEMSS_ORBITS(n,GEMSS_NB_BITS_UINT)
    #define GEMSS_NORBITS_UINT(n) GEMSS_NORBITS(n,GEMSS_NB_BITS_UINT)
    #define GEMSS_XORBITS_UINT(n) GEMSS_XORBITS(n,GEMSS_NB_BITS_UINT)
#else
    #define GEMSS_COUNTBITS_UINT  GEMSS_COUNTBITS64_SWAR
    #define  GEMSS_ORBITS_UINT(n)  GEMSS_ORBITS(n,GEMSS_NB_BITS_UINT)
    #define GEMSS_NORBITS_UINT(n) GEMSS_NORBITS(n,GEMSS_NB_BITS_UINT)
    #define GEMSS_XORBITS_UINT(n) GEMSS_XORBITS(n,GEMSS_NB_BITS_UINT)
#endif




#endif
