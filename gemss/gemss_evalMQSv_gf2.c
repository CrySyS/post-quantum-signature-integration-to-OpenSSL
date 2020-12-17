#include "gemss_evalMQSv_gf2.h"
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2n.h"
#include "gemss_tools_gf2v.h"
#include "gemss_sizes_HFE.h"

/* This file is a modified copy of evalMQS_gf2.c, used for the constant-time 
   evaluation of the constant of the GEMSS_HFEv polynomial. 
   The main modification is the parameters GEMSS_NB_VAR and GEMSS_NB_EQ */

/* Input:
    m a vector of v elements of GF(2)
    pk a MQ system with n equations in GF(2)[x1,...,xv]

  Output:
    c a vector of n elements of GF(2), c is the evaluation of pk in m
*/
/* void GEMSS_evalMQSv_gf2(vecn_gf2 c, cst_vecv_gf2 m, cst_mqsv_gf2n pk) */


#define GEMSS_HYBRID_FUNCTIONS 0


/*** These variables define the number of variables and equations ***/
#define GEMSS_NB_VAR (GEMSS_HFEv)
#define GEMSS_NB_EQ (GEMSS_HFEn)


#if GEMSS_NB_VAR


/*** Useful macro ***/

/* GEMSS_NB_VAR = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_NB_VARq (GEMSS_NB_VAR/GEMSS_NB_BITS_UINT)
#define GEMSS_NB_VARr (GEMSS_NB_VAR%GEMSS_NB_BITS_UINT)


/* GEMSS_NB_EQ = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_NB_EQq (GEMSS_NB_EQ/GEMSS_NB_BITS_UINT)
#define GEMSS_NB_EQr (GEMSS_NB_EQ%GEMSS_NB_BITS_UINT)
/* The number of word that an element of GF(2^GEMSS_NB_EQ) needs */
#if (GEMSS_NB_EQr)
    #define GEMSS_NB_WORD_EQ_TMP (GEMSS_NB_EQq+1)
#else
    #define GEMSS_NB_WORD_EQ_TMP GEMSS_NB_EQq
#endif


/* To choose macro for GEMSS_NB_WORD_EQ*64 bits */
#if (GEMSS_NB_WORD_EQ_TMP == 1)
    #define GEMSS_NB_WORD_EQ 1
#elif (GEMSS_NB_WORD_EQ_TMP == 2)
    #define GEMSS_NB_WORD_EQ 2
#elif (GEMSS_NB_WORD_EQ_TMP == 3)
    #define GEMSS_NB_WORD_EQ 3
#elif (GEMSS_NB_WORD_EQ_TMP == 4)
    #define GEMSS_NB_WORD_EQ 4
#elif (GEMSS_NB_WORD_EQ_TMP == 5)
    #define GEMSS_NB_WORD_EQ 5
#elif (GEMSS_NB_WORD_EQ_TMP == 6)
    #define GEMSS_NB_WORD_EQ 6
#elif (GEMSS_NB_WORD_EQ_TMP == 7)
    #define GEMSS_NB_WORD_EQ 7
#elif (GEMSS_NB_WORD_EQ_TMP == 8)
    #define GEMSS_NB_WORD_EQ 8
#elif (GEMSS_NB_WORD_EQ_TMP == 9)
    #define GEMSS_NB_WORD_EQ 9
#elif (GEMSS_NB_WORD_EQ_TMP == 10)
    #define GEMSS_NB_WORD_EQ 10
#elif (GEMSS_NB_WORD_EQ_TMP == 11)
    #define GEMSS_NB_WORD_EQ 11
#elif (GEMSS_NB_WORD_EQ_TMP == 12)
    #define GEMSS_NB_WORD_EQ 12
#endif

#define GEMSS_CONCAT_NB_WORD_EQ_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_WORD_EQ)








/* 64-bit version */

#if (GEMSS_NB_WORD_EQ<7)
    #define GEMSS_XOR_ELEM GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_EQ_SUP(GEMSS_ADD),_2_GF2X)
    #define GEMSS_xorLoadMask1_gf2EQ GEMSS_CONCAT_NB_WORD_EQ_SUP(GEMSS_XORLOADMASK1_)
#else
    #define GEMSS_XOR_ELEM(a,b) GEMSS_ADD_2_GF2X(a,b,GEMSS_NB_WORD_EQ);
    #define GEMSS_xorLoadMask1_gf2EQ(res,a,b) GEMSS_XORLOADMASK1(res,a,b,GEMSS_NB_WORD_EQ)
#endif

#if (GEMSS_NB_WORD_EQ<10)
    #define GEMSS_COPY_64bits_variables GEMSS_CONCAT_NB_WORD_EQ_SUP(GEMSS_COPY)
#else
    #define GEMSS_COPY_64bits_variables(c,a) GEMSS_COPY(c,a,GEMSS_NB_WORD_EQ)
#endif




/**************************************************************************/
/**************************************************************************/
/*** Classical constant-time evaluation using a mask to multiply by xi. ***/
/**************************************************************************/
/**************************************************************************/


#if GEMSS_NB_VARr
    #define GEMSS_REM_X \
        xi=m[i];\
        for(j=0;j<GEMSS_NB_VARr;++j,++k)\
        {\
            x[k]=-((xi>>j)&GEMSS_UINT_1);\
        }
#else
    #define GEMSS_REM_X
#endif




/* Input:
    m a vector of n+v elements of GF(2)
    pk a MQ system with m equations in GF(2)[x1,...,x_(n+v)]

  Output:
    c a vector of m elements of GF(2), c is the evaluation of pk in m
*/
void GEMSS_PREFIX_NAME(GEMSS_evalMQSv_classical_gf2)(vecm_gf2 c, cst_vecnv_gf2 m,
                                         cst_mqsnv_gf2m pk)
{
    UINT xi;
    UINT x[GEMSS_NB_VAR];
    static_vecm_gf2 tmp[GEMSS_NB_WORD_EQ];
    unsigned int i,j,k;

    /* Compute one time all -((xi>>1)&GEMSS_UINT_1) */
    k=0;
    for(i=0;i<GEMSS_NB_VARq;++i)
    {
        xi=m[i];
        for(j=0;j<GEMSS_NB_BITS_UINT;++j,++k)
        {
            x[k]=-((xi>>j)&GEMSS_UINT_1);
        }
    }
    GEMSS_REM_X;

    /* Constant cst_pk */
    GEMSS_COPY_64bits_variables(c,pk);
    #if GEMSS_HYBRID_FUNCTIONS
        c[GEMSS_NB_EQq]=pk[GEMSS_NB_EQq];
    #endif
    pk+=GEMSS_NB_WORD_EQ;

    /* for each row of the quadratic matrix of pk, excepted the last block */
    for(i=0;i<GEMSS_NB_VAR;++i)
    {
        /* for each column of the quadratic matrix of pk */

        /* xj=xi */
        GEMSS_COPY_64bits_variables(tmp,pk)
        pk+=GEMSS_NB_WORD_EQ;

        for(j=i+1;j<GEMSS_NB_VAR;++j)
        {
            GEMSS_xorLoadMask1_gf2EQ(tmp,pk,x[j]);
            pk+=GEMSS_NB_WORD_EQ;
        }
        /* Multiply by xi */
        GEMSS_xorLoadMask1_gf2EQ(c,tmp,x[i]);
    }
}


#if (GEMSS_NB_VAR>2)
void GEMSS_PREFIX_NAME(GEMSS_evalMQSv_unrolled_gf2)(vecm_gf2 c, cst_vecnv_gf2 m,
                                        cst_mqsnv_gf2m pk)
{
    UINT xi;
    UINT x[GEMSS_NB_VAR];
    static_vecm_gf2 tmp[GEMSS_NB_WORD_EQ];
    unsigned int i,j,k;

    /* Compute one time all -((xi>>1)&GEMSS_UINT_1) */
    k=0;
    for(i=0;i<GEMSS_NB_VARq;++i)
    {
        xi=m[i];
        for(j=0;j<GEMSS_NB_BITS_UINT;++j,++k)
        {
            x[k]=-((xi>>j)&GEMSS_UINT_1);
        }
    }
    GEMSS_REM_X;

    /* Constant cst_pk */
    GEMSS_COPY_64bits_variables(c,pk);
    #if GEMSS_HYBRID_FUNCTIONS
        c[GEMSS_NB_EQq]=pk[GEMSS_NB_EQq];
    #endif
    pk+=GEMSS_NB_WORD_EQ;

    /* for each row of the quadratic matrix of pk, excepted the last block */
    for(i=0;i<GEMSS_NB_VAR;++i)
    {
        /* for each column of the quadratic matrix of pk */

        /* xj=xi */
        GEMSS_COPY_64bits_variables(tmp,pk)
        pk+=GEMSS_NB_WORD_EQ;

        for(j=i+1;j<(GEMSS_NB_VAR-3);j+=4)
        {
            GEMSS_xorLoadMask1_gf2EQ(tmp,pk,x[j]);
            pk+=GEMSS_NB_WORD_EQ;
            GEMSS_xorLoadMask1_gf2EQ(tmp,pk,x[j+1]);
            pk+=GEMSS_NB_WORD_EQ;
            GEMSS_xorLoadMask1_gf2EQ(tmp,pk,x[j+2]);
            pk+=GEMSS_NB_WORD_EQ;
            GEMSS_xorLoadMask1_gf2EQ(tmp,pk,x[j+3]);
            pk+=GEMSS_NB_WORD_EQ;
        }
        for(;j<GEMSS_NB_VAR;++j)
        {
            GEMSS_xorLoadMask1_gf2EQ(tmp,pk,x[j]);
            pk+=GEMSS_NB_WORD_EQ;
        }
        /* Multiply by xi */
        GEMSS_xorLoadMask1_gf2EQ(c,tmp,x[i]);
    }
}
#endif







#endif

