#include "gemss_randMatrix_gf2.h"
#include "gemss_randombytes.h"
#include "gemss_gf2.h"
#include "gemss_determinantn_gf2.h"
#include "gemss_determinantnv_gf2.h"
#include <stdlib.h>
#include "gemss_macro.h"
#include "gemss_bit.h"
#include "gemss_dotProduct_gf2.h"


#if GEMSS_HFEnr
void GEMSS_PREFIX_NAME(GEMSS_cleanMatrix_gf2_n)(Mn_gf2 S)
{
    cst_Mn_gf2 S_end;

    S_end=S+GEMSS_MATRIXn_SIZE;
    for(S+=GEMSS_NB_WORD_GFqn-1;S<S_end;S+=GEMSS_NB_WORD_GFqn)
    {
        /* Clean the last word */
        *S&=GEMSS_MASK_GF2n;
    }
}
#endif


/**
 * @brief   Generate a random matrix (n,n) in GF(2).
 * @param[out]  S   A random matrix (n,n) in GF(2).
 * @remark  Requires to allocate n elements of GF(2^n) for S.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_randMatrix_gf2_n)(Mn_gf2 S)
{
    GEMSS_randombytes((unsigned char*)S,GEMSS_MATRIXn_SIZE<<3);

    #if GEMSS_HFEnr
        unsigned int i;
        --S;
        for(i=0;i<GEMSS_HFEn;++i)
        {
            S+=GEMSS_NB_WORD_GFqn;
            /* Clean the last word */
            *S&=GEMSS_MASK_GF2n;
        }
    #endif
}


#if GEMSS_HFEnvr
    void GEMSS_PREFIX_NAME(GEMSS_cleanMatrix_gf2_nv)(Mnv_gf2 S)
    {
        cst_Mnv_gf2 S_end;

        S_end=S+GEMSS_MATRIXnv_SIZE;
        for(S+=GEMSS_NB_WORD_GF2nv-1;S<S_end;S+=GEMSS_NB_WORD_GF2nv)
        {
            /* Clean the last word */
            *S&=GEMSS_MASK_GF2nv;
        }
    }
#endif


#if GEMSS_HFEv
/**
 * @brief   Generate a random matrix (n+v,n+v) in GF(2).
 * @param[out]  S   A random matrix (n+v,n+v) in GF(2).
 * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_randMatrix_gf2_nv)(Mnv_gf2 S)
{
    GEMSS_randombytes((unsigned char*)S,GEMSS_MATRIXnv_SIZE<<3);

    #if GEMSS_HFEnvr
        unsigned int i;
        --S;
        for(i=0;i<GEMSS_HFEnv;++i)
        {
            S+=GEMSS_NB_WORD_GF2nv;
            /* Clean the last word */
            *S&=GEMSS_MASK_GF2nv;
        }
    #endif
}
#endif


/**
 * @brief   Generate a random invertible matrix (n,n) in GF(2).
 * @details Trial and error method.
 * @param[out]  S   A random invertible matrix (n,n) in GF(2).
 * @param[in]   S_cp    A matrix (n,n) in GF(2).
 * @return  An integer, different from 1 if the allocation fails.
 * @remark  Requires to allocate n elements of GF(2^n) for S.
 * @remark  Requires to allocate n elements of GF(2^n) for S_cp.
 * @remark  Constant-time implementation for S, we have an information leak 
 * only for the random non-invertible matrices (which are not used).
 */
void GEMSS_PREFIX_NAME(GEMSS_randInvMatrix_gf2_n)(GLn_gf2 S, Mn_gf2 S_cp)
{
    gf2 ret;

    do
    {
        GEMSS_randMatrix_gf2_n(S);
        ret=GEMSS_determinantn_gf2(S,S_cp);
    } while(!ret);
}


#if GEMSS_HFEv
/**
 * @brief   Generate a random invertible matrix (n+v,n+v) in GF(2).
 * @details Trial and error method.
 * @param[out]  S   A random invertible matrix (n+v,n+v) in GF(2).
 * @param[in]   S_cp    A matrix (n+v,n+v) in GF(2).
 * @return  An integer, different from 1 if the allocation fails.
 * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S.
 * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S_cp.
 * @remark  Constant-time implementation for S, we have an information leak 
 * only for the random non-invertible matrices (which are not used).
 */
void GEMSS_PREFIX_NAME(GEMSS_randInvMatrix_gf2_nv)(GLnv_gf2 S, Mnv_gf2 S_cp)
{
    gf2 ret;

    do
    {
        GEMSS_randMatrix_gf2_nv(S);
        ret=GEMSS_determinantnv_gf2(S,S_cp);
    } while(!ret);
}
#endif


#define GEMSS_CLEANLOWMATRIX_GF2(NAME,LTRIANGULAR_SIZE,nq,nr) \
void NAME(Tn_gf2 L) \
{\
    UINT mask;\
    unsigned int iq,ir;\
\
    /* for each row */\
    for(iq=1;iq<=nq;++iq)\
    {\
        mask=0;\
        for(ir=0;ir<GEMSS_NB_BITS_UINT;++ir)\
        {\
            /* Put the bit of diagonal to 1 + zeros after the diagonal */\
            *L&=mask;\
            *L^=GEMSS_UINT_1<<ir;\
            mask<<=1;\
            ++mask;\
\
            L+=iq;\
        }\
        /* Next column */\
        ++L;\
    }\
\
    /* iq = GEMSS_HFEnq */\
    mask=0;\
    for(ir=0;ir<nr;++ir)\
    {\
        /* Put the bit of diagonal to 1 + zeros after the diagonal */\
        *L&=mask;\
        *L^=GEMSS_UINT_1<<ir;\
        mask<<=1;\
        ++mask;\
\
        L+=iq;\
    }\
}


GEMSS_CLEANLOWMATRIX_GF2(GEMSS_PREFIX_NAME(GEMSS_cleanLowerMatrixn),GEMSS_LTRIANGULAR_N_SIZE,GEMSS_HFEnq,
                   GEMSS_HFEnr);
#if GEMSS_HFEv
    GEMSS_CLEANLOWMATRIX_GF2(GEMSS_PREFIX_NAME(GEMSS_cleanLowerMatrixnv),GEMSS_LTRIANGULAR_NV_SIZE,
                       GEMSS_HFEnvq,GEMSS_HFEnvr);
#endif


#define GEMSS_GENLOWMATRIX_GF2(NAME,LTRIANGULAR_SIZE,nq,nr) \
void NAME(Tn_gf2 L) \
{\
    UINT mask;\
    unsigned int iq,ir;\
\
    GEMSS_randombytes((unsigned char*)L,LTRIANGULAR_SIZE<<3);\
\
    /* for each row */\
    for(iq=1;iq<=nq;++iq)\
    {\
        mask=0;\
        for(ir=0;ir<GEMSS_NB_BITS_UINT;++ir)\
        {\
            /* Put the bit of diagonal to 1 + zeros after the diagonal */\
            *L&=mask;\
            *L^=GEMSS_UINT_1<<ir;\
            mask<<=1;\
            ++mask;\
\
            L+=iq;\
        }\
        /* Next column */\
        ++L;\
    }\
\
    /* iq = GEMSS_HFEnq */\
    mask=0;\
    for(ir=0;ir<nr;++ir)\
    {\
        /* Put the bit of diagonal to 1 + zeros after the diagonal */\
        *L&=mask;\
        *L^=GEMSS_UINT_1<<ir;\
        mask<<=1;\
        ++mask;\
\
        L+=iq;\
    }\
}

/**
 * @brief   Generate a random invertible lower triangular matrix (n,n) L in 
 * GF(2).
 * @param[out]  L   A random invertible lower triangular matrix (n,n) in GF(2).
 * @remark  Requires to allocate GEMSS_LTRIANGULAR_N_SIZE words for L.
 * @remark  Only the lower triangular part of L is stored. In particular, the 
 * words equal to zero in the upper trigular part are not stored.
 * @remark  Constant-time implementation.
 */
GEMSS_GENLOWMATRIX_GF2(GEMSS_PREFIX_NAME(GEMSS_genLowerMatrixn),GEMSS_LTRIANGULAR_N_SIZE,GEMSS_HFEnq,GEMSS_HFEnr);
#if GEMSS_HFEv
    /**
     * @brief   Generate a random invertible lower triangular matrix (n+v,n+v) L
     * in GF(2).
     * @param[out]  L   A random invertible lower triangular matrix (n+v,n+v) in
     * GF(2).
     * @remark  Requires to allocate GEMSS_LTRIANGULAR_NV_SIZE words for L.
     * @remark  Only the lower triangular part of L is stored. In particular,
     * the words equal to zero in the upper trigular part are not stored.
     * @remark  Constant-time implementation.
     */
    GEMSS_GENLOWMATRIX_GF2(GEMSS_PREFIX_NAME(GEMSS_genLowerMatrixnv),GEMSS_LTRIANGULAR_NV_SIZE,GEMSS_HFEnvq,
                     GEMSS_HFEnvr);
#endif


#define GEMSS_LOOPJR(NB_IT) \
    mini=GEMSS_MINI(iq,jq);\
    *S=0;\
    for(jr=0;jr<NB_IT;++jr)\
    {\
        /* Dot product */\
        tmp=L_cp[0]&U_cp[0];\
        for(k=1;k<mini;++k)\
        {\
            tmp^=L_cp[k]&U_cp[k];\
        }\
        GEMSS_XORBITS_UINT(tmp);\
        *S^=tmp<<jr;\
        U_cp+=jq;\
    }\
    ++S;


#define GEMSS_LOOPIR(NB_IT,nq,nr,REM) \
    for(ir=0;ir<NB_IT;++ir)\
    {\
        U_cp=U;\
        /* for each row of U (multiply by the transpose) */\
        for(jq=1;jq<=nq;++jq)\
        {\
            GEMSS_LOOPJR(GEMSS_NB_BITS_UINT);\
        }\
        REM;\
        L_cp+=iq;\
    }


#define GEMSS_MULMATRICESLU_GF2(NAME,nq,nr,REM) \
void NAME(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U) \
{\
    cst_Tn_gf2 L_cp,U_cp;\
    UINT tmp;\
    unsigned int iq,ir,jq,jr,k,mini;\
\
    /* Computation of S = L*U */\
    L_cp=L;\
    /* for each row of L (and S) */\
    for(iq=1;iq<=nq;++iq)\
    {\
        GEMSS_LOOPIR(GEMSS_NB_BITS_UINT,nq,nr,REM);\
    }\
    GEMSS_LOOPIR(nr,nq,nr,REM);\
}

/**
 * @brief   Compute the matrix (n,n) L*U in GF(2).
 * @param[out]  S   S=L*U is a matrix (n,n) in GF(2).
 * @remark  Requires to allocate n elements of GF(2^n) for S.
 * @remark  Constant-time implementation.
 */
#if GEMSS_HFEnr
GEMSS_MULMATRICESLU_GF2(GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_n),GEMSS_HFEnq,GEMSS_HFEnr,GEMSS_LOOPJR(GEMSS_HFEnr));
#else
GEMSS_MULMATRICESLU_GF2(GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_n),GEMSS_HFEnq,GEMSS_HFEnr,);
#endif

#if GEMSS_HFEv
    /**
     * @brief   Compute the matrix (n+v,n+v) L*U in GF(2).
     * @param[out]  S   S=L*U is a matrix (n+v,n+v) in GF(2).
     * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S.
     * @remark  Constant-time implementation.
     */
    #if GEMSS_HFEnvr
        GEMSS_MULMATRICESLU_GF2(GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_nv),GEMSS_HFEnvq,GEMSS_HFEnvr,
                          GEMSS_LOOPJR(GEMSS_HFEnvr));
    #else
        GEMSS_MULMATRICESLU_GF2(GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_nv),GEMSS_HFEnvq,GEMSS_HFEnvr,);
    #endif
#endif


