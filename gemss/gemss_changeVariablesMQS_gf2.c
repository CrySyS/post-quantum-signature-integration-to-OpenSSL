#include "gemss_changeVariablesMQS_gf2.h"
#include <stdlib.h>
#include "gemss_tools_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_vecMatProduct_gf2.h"

/* To do a change of variables in a MQ System */


/**
 * @brief   Apply the change of variables x'=xS to a MQS stored with a monomial
 * representation.
 * @details MQS = (c,Q), with c the constant part in GF(2^n) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2^n). We have MQS = c + xQxt
 * with x =  (x0 x1 ... x_(n+v)). At the end of the function, we have
 * MQS = c + xQ'xt with Q' = SQSt. We multiply S by Q, then SQ by St.
 * @param[in,out]   MQS A MQS in GF(2^n)[x1,...,x_(n+v)] (n equations,
 * n+v variables).
 * @param[in]   S   A matrix (n+v)*(n+v) in GF(2). S should be invertible
 * (by definition of a change of variables).
 * @return   0 if the result is correct, GEMSS_ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  This function uses SIMD only when the vecMatProduct function uses
 * it.
 * @remark  Constant-time implementation.
 */
int GEMSS_PREFIX_NAME(GEMSS_changeVariablesMQS_simd_gf2)(mqsnv_gf2n MQS, cst_GLnv_gf2 S)
{
    UINT tmp[GEMSS_NB_WORD_GFqn];
    mqsnv_gf2n MQS2, MQS2_cp;
    cst_mqsnv_gf2n MQS_cpi,MQS_cpj;
    cst_GLnv_gf2 S_cpi,S_cpj;
    unsigned int i,j;

    /* Tmp matrix (n+v)*(n+v) of quadratic terms to compute S*Q */
    MQS2=(UINT*)malloc(GEMSS_HFEnv*GEMSS_HFEnv*GEMSS_NB_WORD_GFqn*sizeof(UINT));
    GEMSS_VERIFY_ALLOC_RET(MQS2);

    /* To avoid the constant of MQS */
    MQS+=GEMSS_NB_WORD_GFqn;

    /* Step 1: compute MQS2 = S*Q */
    /* Use multiplication by transpose (so by rows of Q) */
    /* It is possible because X*Q*tX = X*tQ*tX (with X = (x1 ... xn)) */
    /* Warning : Q is a upper triangular matrix in GF(q^n) */


    MQS2_cp=MQS2;
    S_cpj=S;

    /* for each row j of S */
    for(j=0;j<GEMSS_HFEnv;++j)
    {
        /* initialisation at the first row of Q */
        MQS_cpi=MQS;
        /* for each row of Q */
        for(i=0;i<GEMSS_HFEnv;++i)
        {
            /* Compute a dot product */
            GEMSS_vecMatProductnvn_start_gf2(MQS2_cp,S_cpj,MQS_cpi,i);
            MQS_cpi+=GEMSS_NB_WORD_GFqn*(GEMSS_HFEnv-i);
            /* update the next element to compute */
            MQS2_cp+=GEMSS_NB_WORD_GFqn;
        }
        S_cpj+=GEMSS_NB_WORD_GF2nv;
    }


    /* Step 2: compute MQS = MQS2*tS = (S*Q)*tS */
    /* Use multiplication by transpose (so by rows of S) */

    /* Permute MQS and MQS2 */
    MQS_cpj=MQS2;
    MQS2_cp=MQS;
    S_cpj=S;
 
    /* First: compute upper triangular result */

    /* for each row j of MQS2 */
    for(j=0;j<GEMSS_HFEnv;++j)
    {
        S_cpi=S_cpj;

        /* for each row >=j of S */
        for(i=j;i<GEMSS_HFEnv;++i)
        {
            /* Compute a dot product with complete rows */
            /* (Init to 0 the res) */
            GEMSS_vecMatProductnvn_gf2(MQS2_cp,S_cpi,MQS_cpj);
            /* update the next element to compute */
            MQS2_cp+=GEMSS_NB_WORD_GFqn;
            /* update the next row of S to use */
            S_cpi+=GEMSS_NB_WORD_GF2nv;
        }

        /* Next row of MQS2 */
        MQS_cpj+=GEMSS_NB_WORD_GFqn*GEMSS_HFEnv;
        /* Next row of S because of upper triangular */
        S_cpj+=GEMSS_NB_WORD_GF2nv;
    }

    /* Second: compute lower triangular result */

    MQS_cpj=MQS2;
    MQS2_cp=MQS;
    S_cpj=S;

    /* for each row j of S */
    for(j=0;j<GEMSS_HFEnv;++j)
    {
        /* i=j : the diagonal is already computing */
        MQS2_cp+=GEMSS_NB_WORD_GFqn;
        /* The line j of MQS2 is useless */
        MQS_cpj+=GEMSS_HFEnv*GEMSS_NB_WORD_GFqn;
        MQS_cpi=MQS_cpj;

        /* for each row >j of MQS2 */
       for(i=j+1;i<GEMSS_HFEnv;++i)
       {
           /* Compute a dot product with complete rows */
           GEMSS_vecMatProductnvn_gf2(tmp,S_cpj,MQS_cpi);
           GEMSS_add2_gf2n(MQS2_cp,tmp);
           MQS_cpi+=GEMSS_NB_WORD_GFqn*GEMSS_HFEnv;
           /* update the next element to compute */
           MQS2_cp+=GEMSS_NB_WORD_GFqn;
       }

        /* Next row of S */
        S_cpj+=GEMSS_NB_WORD_GF2nv;
    }


    free(MQS2);
    return 0;
}


/***************************************/
/*** Special fast version for 64-bit ***/
/***************************************/


/* Compute a dot product with one word of S */
#define GEMSS_LOOPKR(START,NB_IT) \
    for(kr=START;kr<NB_IT;++kr)\
    {\
        /* multiply one bit of S by one element of MQS_cpj */\
        mask=-(bit_kr&GEMSS_UINT_1); \
        GEMSS_xorLoadMask1_gf2n(MQS2_cp,MQS_cpj,mask);\
        MQS_cpj+=GEMSS_NB_WORD_GFqn;\
        bit_kr>>=1;\
    }

/* Compute a dot product for the last word of S */
#if (GEMSS_HFEnvr)
    #define GEMSS_LOOPKR_REMAINDER \
        bit_kr=S_cpj[kq];\
        GEMSS_LOOPKR(0,GEMSS_HFEnvr);
#else
    #define GEMSS_LOOPKR_REMAINDER
#endif

/* Compute a dot product for the last word of S */
#define GEMSS_LOOPK_REM \
    bit_kr=(*S_cpj)>>ir;\
    GEMSS_LOOPKR(ir,GEMSS_HFEnvr);


/* Compute a dot product with iq words equal to zero at the begin of the rows */
#define GEMSS_LOOPK \
    bit_kr=(*S_cpj)>>ir;\
    GEMSS_LOOPKR(ir,GEMSS_NB_BITS_UINT);\
\
    for(kq=1;kq<(GEMSS_HFEnvq-iq);++kq)\
    {\
        bit_kr=S_cpj[kq];\
        GEMSS_LOOPKR(0,GEMSS_NB_BITS_UINT);\
    }\
\
    GEMSS_LOOPKR_REMAINDER;


/* Compute a dot product with complete rows */
#define GEMSS_LOOPK_COMPLETE \
    for(kq=0;kq<GEMSS_HFEnvq;++kq)\
    {\
        bit_kr=S_cpj[kq];\
        GEMSS_LOOPKR(0,GEMSS_NB_BITS_UINT);\
    }\
    GEMSS_LOOPKR_REMAINDER;


/* Loop for a block of rows */
#define GEMSS_LOOPIR(STARTIR,NB_ITIR,GEMSS_LOOPK) \
    for(ir=STARTIR;ir<NB_ITIR;++ir)\
    {\
        /* Compute a dot product */\
        GEMSS_LOOPK;\
        /* update the next element to compute */\
        MQS2_cp+=GEMSS_NB_WORD_GFqn;\
    }


/* Loop for a block of rows */
/* Init to 0 the res */
#define GEMSS_LOOPIR_INIT(STARTIR,NB_ITIR) \
    for(ir=STARTIR;ir<NB_ITIR;++ir)\
    {\
        GEMSS_set0_gf2n(MQS2_cp);\
        MQS_cpj=MQS_cpi;\
        /* Compute a dot product */\
        GEMSS_LOOPK_COMPLETE;\
        /* update the next element to compute */\
        MQS2_cp+=GEMSS_NB_WORD_GFqn;\
        /* update the next row of S to use */\
        S_cpj+=GEMSS_NB_WORD_GF2nv;\
    }


/**
 * @brief   Apply the change of variables x'=xS to a MQS stored with a monomial
 * representation.
 * @details MQS = (c,Q), with c the constant part in GF(2^n) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2^n). We have MQS = c + xQxt
 * with x =  (x0 x1 ... x_(n+v)). At the end of the function, we have
 * MQS = c + xQ'xt with Q' = SQSt. We multiply S by Q, then SQ by St.
 * @param[in,out]   MQS A MQS in GF(2^n)[x1,...,x_(n+v)] (n equations,
 * n+v variables).
 * @param[in]   S   A matrix (n+v)*(n+v) in GF(2). S should be invertible
 * (by definition of a change of variables).
 * @return   0 if the result is correct, GEMSS_ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  This function should be faster than GEMSS_changeVariablesMQS_simd_gf2
 * when SIMD is not used.
 * @remark  Constant-time implementation.
 */
int GEMSS_PREFIX_NAME(GEMSS_changeVariablesMQS64_gf2)(mqsnv_gf2n MQS, cst_GLnv_gf2 S)
{
    mqsnv_gf2n MQS2, MQS2_cp;
    UINT bit_kr, mask;
    cst_mqsnv_gf2n MQS_cpi,MQS_cpj;
    cst_GLnv_gf2 S_cpi,S_cpj;
    unsigned int iq,ir,j,jq,jr,kq,kr;

    /* Tmp matrix (n+v)*(n+v) of quadratic terms to compute S*Q */
    MQS2=(UINT*)calloc(GEMSS_HFEnv*GEMSS_HFEnv*GEMSS_NB_WORD_GFqn,sizeof(UINT));
    GEMSS_VERIFY_ALLOC_RET(MQS2);

    /* To avoid the constant of MQS */
    MQS_cpi=MQS+GEMSS_NB_WORD_GFqn;

    MQS2_cp=MQS2;
    S_cpj=S;

    /* Step 1 : compute MQS2 = S*Q */
    /* Use multiplication by transpose (so by rows of Q) */
    /* It is possible because X*Q*tX = X*tQ*tX (with X = (x1 ... xn)) */
    /* Warning : Q is a upper triangular matrix in GF(q^n) */

    /* In this code, we have : */
    /* i = iq*GEMSS_NB_BITS_UINT + ir */
    /* k = kq*GEMSS_NB_BITS_UINT + kr */

    /* *MQS_cpi = MQS[GEMSS_NB_WORD_GFqn] */
    /* *MQS_cpj = MQS_cpi[(((i*(2n-i+1))/2) + k)*GEMSS_NB_WORD_GFqn] */
    /* The previous formula is a bit complicated, so the idea is :
       *MQS_cpj would equal MQS_cpi[i][i+k] if MQS used n*n in memory */
    /* *MQS2_cp = MQS2[i*GEMSS_NB_WORD_GFqn] */
    /* *S_cpj = S[j*GEMSS_NB_WORD_GFqn+iq] */

    /* for each row j of S */
    for(j=0;j<GEMSS_HFEnv;++j)
    {
        /* initialisation at the first row of Q */
        MQS_cpj=MQS_cpi;
        /* for each row of Q excepted the last block */
        for(iq=0;iq<GEMSS_HFEnvq;++iq)
        {
            GEMSS_LOOPIR(0,GEMSS_NB_BITS_UINT,GEMSS_LOOPK);
            /* 64 bits of zero in Q */
            ++S_cpj;
        }
        /* the last block */
        #if (GEMSS_HFEnvr)
            GEMSS_LOOPIR(0,GEMSS_HFEnvr,GEMSS_LOOPK_REM);
            /* Next row of S */
            ++S_cpj;
        #endif
    }

    /* Step 2 : compute MQS = MQS2*tS = (S*Q)*tS */
    /* Use multiplication by transpose (so by rows of S) */

    /* Permute MQS and MQS2 */
    MQS_cpi=MQS2;
    MQS2_cp=MQS+GEMSS_NB_WORD_GFqn;
    S_cpi=S;
 
    /* First : compute upper triangular result */


    /* In this code, we have : */
    /* *MQS_cpi = MQS2[j*n*GEMSS_NB_WORD_GFqn] */
    /* *MQS_cpj = MQS2[(j*n+k)*GEMSS_NB_WORD_GFqn] */
    /* *MQS2_cp = MQS[(((j*(2n-j+1))/2) + i-j)*GEMSS_NB_WORD_GFqn] */
    /* The previous formula is a bit complicated, so the idea is :
       *MQS2_cp would equal MQS[j][i] if MQS used n*n in memory */
    /* *S_cpi = S[j*GEMSS_NB_WORD_GFqn] */
    /* *S_cpj = S[i*GEMSS_NB_WORD_GFqn] */


    /* for each row j of MQS2 excepted the last block */
    for(jq=0;jq<GEMSS_HFEnvq;++jq)
    {
        for(jr=0;jr<GEMSS_NB_BITS_UINT;++jr)
        {
            S_cpj=S_cpi;
            /* for each row >=j of S */
            GEMSS_LOOPIR_INIT(jr,GEMSS_NB_BITS_UINT);
            for(iq=jq+1;iq<GEMSS_HFEnvq;++iq)
            {
                GEMSS_LOOPIR_INIT(0,GEMSS_NB_BITS_UINT);
            }
            /* the last block */
            #if (GEMSS_HFEnvr)
                GEMSS_LOOPIR_INIT(0,GEMSS_HFEnvr);
            #endif
            /* Next row of MQS2 */
            MQS_cpi=MQS_cpj;
            /* Next row of S because of upper triangular */
            S_cpi+=GEMSS_NB_WORD_GF2nv;
        }
    }
    /* the last block */
    #if (GEMSS_HFEnvr)
        for(jr=0;jr<GEMSS_HFEnvr;++jr)
        {
            S_cpj=S_cpi;
            MQS_cpj=MQS_cpi;
            /* for each row >=j of S, the last block */
            GEMSS_LOOPIR_INIT(jr,GEMSS_HFEnvr);
            MQS_cpi=MQS_cpj;
            S_cpi+=GEMSS_NB_WORD_GF2nv;
        }
    #endif

    /* Second : compute lower triangular result */

    MQS_cpi=MQS2;
    MQS2_cp=MQS+GEMSS_NB_WORD_GFqn;
    S_cpj=S;


    /* In this code, we have : */
    /* *MQS_cpi = MQS2[(j+1)*n*GEMSS_NB_WORD_GFqn] */
    /* *MQS_cpj = MQS2[(j+1)*n+k)*GEMSS_NB_WORD_GFqn] */
    /* *MQS2_cp = MQS[(((j*(2n-j+1))/2) + i-j)*GEMSS_NB_WORD_GFqn] */
    /* The previous formula is a bit complicated, so the idea is :
       *MQS2_cp would equal MQS[j][i] if MQS used n*n in memory */
    /* *S_cpj = S[j*GEMSS_NB_WORD_GFqn] */


    /* for each row j of S excepted the last block */
    for(jq=0;jq<GEMSS_HFEnvq;++jq)
    {
        for(jr=0;jr<GEMSS_NB_BITS_UINT;++jr)
        {
            /* i=j : the diagonal is already computing */
            MQS2_cp+=GEMSS_NB_WORD_GFqn;
            /* The line j of MQS2 is useless */
            MQS_cpi+=GEMSS_HFEnv*GEMSS_NB_WORD_GFqn;
            MQS_cpj=MQS_cpi;
            /* for each row >j of MQS2 */
            GEMSS_LOOPIR(jr+1,GEMSS_NB_BITS_UINT,GEMSS_LOOPK_COMPLETE);
            for(iq=jq+1;iq<GEMSS_HFEnvq;++iq)
            {
                GEMSS_LOOPIR(0,GEMSS_NB_BITS_UINT,GEMSS_LOOPK_COMPLETE);
            }
            /* the last block */
            #if (GEMSS_HFEnvr)
                GEMSS_LOOPIR(0,GEMSS_HFEnvr,GEMSS_LOOPK_COMPLETE);
            #endif
            /* Next row of S */
            S_cpj+=GEMSS_NB_WORD_GF2nv;
        }
    }
    /* the last block excepted the last row */
    #if (GEMSS_HFEnvr)
       for(jr=0;jr<GEMSS_HFEnvr-1;++jr)
       {
            /* i=j : the diagonal is already computing */
            MQS2_cp+=GEMSS_NB_WORD_GFqn;
            /* The line j of MQS2 is useless */
            MQS_cpi+=GEMSS_HFEnv*GEMSS_NB_WORD_GFqn;
            MQS_cpj=MQS_cpi;
            /* for each row >=j of S */
            /* the last block */
            GEMSS_LOOPIR(jr+1,GEMSS_HFEnvr,GEMSS_LOOPK_COMPLETE);
            /* Next row of S */
            S_cpj+=GEMSS_NB_WORD_GF2nv;
       }
    #endif


    free(MQS2);
    return 0;
}


