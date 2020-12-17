#include "gemss_evalMQSnocst8_gf2.h"
#include "gemss_add_gf2x.h"
#include "gemss_init.h"
#include "gemss_simd.h"
#include "gemss_tools_gf2m.h"


/***************************************************************/
/***************************************************************/
/**** Classical variable-time evaluation using accumulator. ****/
/***************************************************************/
/***************************************************************/


/*** These variables define the number of variables and equations ***/
#define GEMSS_NB_VAR (GEMSS_HFEnv)
#define GEMSS_NB_EQ (GEMSS_HFEm)



/*** Useful macro ***/

/* GEMSS_NB_VAR = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_NB_VARq (GEMSS_NB_VAR/GEMSS_NB_BITS_UINT)
#define GEMSS_NB_VARr (GEMSS_NB_VAR%GEMSS_NB_BITS_UINT)


/* GEMSS_NB_EQ = 8*quo + rem */
#define GEMSS_NB_EQq (GEMSS_NB_EQ>>3)
#define GEMSS_NB_EQr (GEMSS_NB_EQ&7)
/* The number of bytes that an element of GF(2^GEMSS_NB_EQ) needs */
#if (GEMSS_NB_EQr)
    #define GEMSS_NB_BYTES_EQ (GEMSS_NB_EQq+1)
#else
    #define GEMSS_NB_BYTES_EQ GEMSS_NB_EQq
#endif

#define GEMSS_MASK_EQ GEMSS_mask64(GEMSS_NB_EQ&63)
#if (GEMSS_NB_EQ&63)
    #define GEMSS_MASK_64(c) (c)&=GEMSS_MASK_EQ;
    #define GEMSS_MASK2_64(c,a) (c)=(a)&GEMSS_MASK_EQ;
#else
    /* The AND is useless here */
    #define GEMSS_MASK_64(c)
    #define GEMSS_MASK2_64(c,a)
#endif


/* To choose macro for GEMSS_NB_WORD_EQ*64 bits */
#if (GEMSS_NB_BYTES_EQ<=8)
    #define GEMSS_NB_WORD_EQ 1
#elif (GEMSS_NB_BYTES_EQ<=16)
    #define GEMSS_NB_WORD_EQ 2
#elif (GEMSS_NB_BYTES_EQ<=24)
    #define GEMSS_NB_WORD_EQ 3
#elif (GEMSS_NB_BYTES_EQ<=32)
    #define GEMSS_NB_WORD_EQ 4
#elif (GEMSS_NB_BYTES_EQ<=40)
    #define GEMSS_NB_WORD_EQ 5
#elif (GEMSS_NB_BYTES_EQ<=48)
    #define GEMSS_NB_WORD_EQ 6
#elif (GEMSS_NB_BYTES_EQ<=56)
    #define GEMSS_NB_WORD_EQ 7
#elif (GEMSS_NB_BYTES_EQ<=64)
    #define GEMSS_NB_WORD_EQ 8
#elif (GEMSS_NB_BYTES_EQ<=72)
    #define GEMSS_NB_WORD_EQ 9
#elif (GEMSS_NB_BYTES_EQ<=80)
    #define GEMSS_NB_WORD_EQ 10
#elif (GEMSS_NB_BYTES_EQ<=88)
    #define GEMSS_NB_WORD_EQ 11
#elif (GEMSS_NB_BYTES_EQ<=96)
    #define GEMSS_NB_WORD_EQ 12
#endif

#define GEMSS_CONCAT_NB_WORD_EQ_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_WORD_EQ)



/*** Tuning ***/
#define GEMSS_LEN_UNROLLED_64 4







/* 64-bit version */

#if (GEMSS_NB_WORD_EQ<7)
    #define GEMSS_XOR_ELEM GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_EQ_SUP(GEMSS_ADD),_2_GF2X)
#else
    #define GEMSS_XOR_ELEM(a,b) GEMSS_ADD_2_GF2X(a,b,GEMSS_NB_WORD_EQ);
#endif

#if (GEMSS_NB_WORD_EQ<10)
    #define GEMSS_COPY_64bits_variables GEMSS_CONCAT_NB_WORD_EQ_SUP(GEMSS_COPY)
#else
    #define GEMSS_COPY_64bits_variables(c,a) GEMSS_COPY(c,a,GEMSS_NB_WORD_EQ)
#endif



#define GEMSS_LOOPJR_NOCST_64(START,NB_IT) \
    for(jr=START;jr<NB_IT;++jr)\
    {\
        if(xj&GEMSS_UINT_1)\
        {\
            GEMSS_XOR_ELEM(c,(const UINT*)pk);\
        }\
        pk+=GEMSS_NB_BYTES_EQ;\
        xj>>=1;\
    }



#if (GEMSS_LEN_UNROLLED_64==1)
    #define GEMSS_LOOPJR_UNROLLED_64 GEMSS_LOOPJR_NOCST_64
#else

#define GEMSS_LOOPJR_UNROLLED_64(START,NB_IT) \
    for(jr=START;jr<(NB_IT-GEMSS_LEN_UNROLLED_64+1);jr+=GEMSS_LEN_UNROLLED_64)\
    {\
        for(h=0;h<GEMSS_LEN_UNROLLED_64;++h)\
        {\
            if(xj&GEMSS_UINT_1)\
            {\
                GEMSS_XOR_ELEM(c,(const UINT*)pk);\
            }\
            pk+=GEMSS_NB_BYTES_EQ;\
            xj>>=1;\
        }\
    }\
    for(;jr<NB_IT;++jr)\
    {\
        if(xj&GEMSS_UINT_1)\
        {\
            GEMSS_XOR_ELEM(c,(const UINT*)pk);\
        }\
        pk+=GEMSS_NB_BYTES_EQ;\
        xj>>=1;\
    }

#endif



/* Requirement: 
            to increase the size of pk by (8-(GEMSS_NB_BYTES_EQ&7))&7 bytes */
void GEMSS_PREFIX_NAME(GEMSS_evalMQSnocst8_unrolled_gf2)(vecm_gf2 c, cst_vecnv_gf2 m,
                                            cst_mqsnv8_gf2m pk)
{
    UINT xi,xj;
    unsigned int iq,ir,i=GEMSS_NB_VAR,jq,jr;
    #if (GEMSS_LEN_UNROLLED_64!=1)
        unsigned int h;
    #endif

    /* Constant cst_pk */
    GEMSS_COPY_64bits_variables(c,(const UINT*)pk);
    pk+=GEMSS_NB_BYTES_EQ;

    /* for each row of the quadratic matrix of pk, excepted the last block */
    for(iq=0;iq<GEMSS_NB_VARq;++iq)
    {
        xi=m[iq];
        for(ir=0;ir<GEMSS_NB_BITS_UINT;++ir,--i)
        {
            if(xi&GEMSS_UINT_1) {

                /* for each column of the quadratic matrix of pk */

                /* xj=xi=1 */
                GEMSS_XOR_ELEM(c,(const UINT*)pk);
                pk+=GEMSS_NB_BYTES_EQ;

                xj=xi>>1;
                GEMSS_LOOPJR_UNROLLED_64(ir+1,GEMSS_NB_BITS_UINT);
                for(jq=iq+1;jq<GEMSS_NB_VARq;++jq)
                {
                    xj=m[jq];
                    GEMSS_LOOPJR_UNROLLED_64(0,GEMSS_NB_BITS_UINT);
                }
                #if (GEMSS_NB_VARr)
                    xj=m[GEMSS_NB_VARq];
                    #if(GEMSS_NB_VARr<(GEMSS_LEN_UNROLLED_64<<1))
                        GEMSS_LOOPJR_NOCST_64(0,GEMSS_NB_VARr);
                    #else
                        GEMSS_LOOPJR_UNROLLED_64(0,GEMSS_NB_VARr);
                    #endif
                #endif
            } else
            {
                pk+=i*GEMSS_NB_BYTES_EQ;
            }
            xi>>=1;
        }
    }

    /* the last block */
    #if (GEMSS_NB_VARr)
        xi=m[GEMSS_NB_VARq];
        for(ir=0;ir<GEMSS_NB_VARr;++ir,--i)
        {
            if(xi&GEMSS_UINT_1) {

                /* for each column of the quadratic matrix of pk */

                /* xj=xi=1 */
                GEMSS_XOR_ELEM(c,(const UINT*)pk);
                pk+=GEMSS_NB_BYTES_EQ;

                xj=xi>>1;
                #if(GEMSS_NB_VARr<(GEMSS_LEN_UNROLLED_64<<1))
                    GEMSS_LOOPJR_NOCST_64(ir+1,GEMSS_NB_VARr);
                #else
                    GEMSS_LOOPJR_UNROLLED_64(ir+1,GEMSS_NB_VARr);
                #endif
            } else
            {
                pk+=i*GEMSS_NB_BYTES_EQ;
            }
            xi>>=1;
        }
    #endif

    GEMSS_MASK_64(c[GEMSS_NB_WORD_EQ-1]);
}



