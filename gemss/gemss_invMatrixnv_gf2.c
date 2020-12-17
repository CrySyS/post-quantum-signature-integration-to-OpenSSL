#include "gemss_invMatrixnv_gf2.h"
#include "gemss_init.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_initMatrixId_gf2.h"
#include "gemss_loadMask.h"


/* Operation between two rows.
   During the Gaussian elimination, we know that the i first columns are
   "triangular" (all coefficients under the diagonal of these columns are null).
   So, it is useless to update the iq first words of each row (we know these
   coefficients are null). */
#define GEMSS_LOOPK(op) \
    for(k=0;k<(GEMSS_NB_WORD_GF2nv-iq);++k)\
    {\
        op;\
    }\


#define GEMSS_PERMUT(GEMSS_LOOPK,LOOPKINV) \
        /* pivot == 1 ? */\
        if((*S_cpj)&bit_ir)\
        {\
            GEMSS_LOOPK;\
            LOOPKINV;\
            break;\
        }

#define GEMSS_ADDROW(GEMSS_LOOPK,LOOPKINV) \
        /* pivot */\
        mask=-(((*S_cpj)>>ir)&1);\
        GEMSS_LOOPK;\
        LOOPKINV;


/* operation GEMSS_LOOPK and LOOPKINV if the pivot of j-th row is 1 */
#define GEMSS_LOOPJ(OP) \
    S_cpj=S_cpi;\
    Sinv_cpj=Sinv_cpi;\
    /* for the next rows */\
    for(j=i+1;j<GEMSS_HFEnv;++j)\
    {\
        /* next row */\
        S_cpj+=GEMSS_NB_WORD_GF2nv;\
        Sinv_cpj+=GEMSS_NB_WORD_GF2nv;\
        OP;\
    }


#define GEMSS_LOOPIR(NB_IT,LOOPK1,LOOPK2) \
    bit_ir=GEMSS_UINT_1;\
    for(ir=0;ir<NB_IT;++ir,++i)\
    {\
        /* If the pivot is 0, search the pivot */\
        if(!((*S_cpi)&bit_ir))\
        {\
            /* permutation row i and j if the pivot of j-th row is 1 */\
            GEMSS_LOOPJ(GEMSS_PERMUT(LOOPK1,GEMSS_swap_gf2nv(Sinv_cpj,Sinv_cpi)));\
        }\
\
        /* add row i to row j if the pivot of j-th row is 1*/\
        GEMSS_LOOPJ(GEMSS_ADDROW(LOOPK2,GEMSS_xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask)));\
\
        /* Next row */\
        S_cpi+=GEMSS_NB_WORD_GF2nv;\
        Sinv_cpi+=GEMSS_NB_WORD_GF2nv;\
        bit_ir<<=1;\
    }


/* Only modify S_inv */
#define GEMSS_LOOPIR_DOWN_TO_UP(NB_IT) \
    for(ir=NB_IT-1;ir!=(unsigned int)(-1);--ir,--i)\
    {\
        S_cpj=S_cpi;\
        Sinv_cpj=Sinv_cpi;\
        /* for the previous rows (i-1 to 0) */\
        for(j=i;j>0;--j)\
        {\
            /* Previous row */\
            S_cpj-=GEMSS_NB_WORD_GF2nv;\
            Sinv_cpj-=GEMSS_NB_WORD_GF2nv;\
            /* pivot */\
            mask=-(((*S_cpj)>>ir)&1);\
            GEMSS_xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask);\
        }\
\
        /* Previous row */\
        S_cpi-=GEMSS_NB_WORD_GF2nv;\
        Sinv_cpi-=GEMSS_NB_WORD_GF2nv;\
    }


/**
 * @brief   Compute the inverse of a matrix (n+v,n+v) in GF(2).
 * @details Gauss-Jordan: transform S to Identity and Identity to S^(-1).
 * @param[in,out]    S   An invertible matrix (n+v,n+v) in GF(2), will modified
 * by the function (in particular, will be upper triangular).
 * @param[out]  S_inv   The inverse of S, matrix (n+v,n+v) in GF(2).
 * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S_inv.
 * @remark  Requirement: S is invertible.
 * @remark  This implementation is not in constant-time.
 */
void GEMSS_PREFIX_NAME(GEMSS_invMatrixnv_nocst_gf2)(GLnv_gf2 S_inv, GLnv_gf2 S)
{
    GLnv_gf2 S_cpi,S_cpj,Sinv_cpi,Sinv_cpj;
    UINT bit_ir,mask;
    unsigned int i=0,iq,ir,j,k;

    /* S_inv initialized to identity */
    GEMSS_initMatrixIdnv_gf2(S_inv);

    /* In this code, we have: */
    /* *S_cpi = S[i*GEMSS_NB_WORD_GF2nv+iq] */
    /* *S_cpj = S[j*GEMSS_NB_WORD_GF2nv+iq] */
    /* *Sinv_cpi = S_inv[i*GEMSS_NB_WORD_GF2nv] */
    /* *Sinv_cpj = S_inv[j*GEMSS_NB_WORD_GF2nv] */

    S_cpi=S;
    Sinv_cpi=S_inv;
    /* for each row of S and of S_inv, excepted the last block */
    for(iq=0;iq<GEMSS_HFEnvq;++iq)
    {
        GEMSS_LOOPIR(GEMSS_NB_BITS_UINT,GEMSS_LOOPK(GEMSS_SWAP_WORD(S_cpj[k],S_cpi[k])),
               GEMSS_LOOPK(S_cpj[k]^=S_cpi[k]&mask));
        /* Next block of column */
        ++S_cpi;
    }

    #if GEMSS_HFEnvr
        /* for each row of the last block excepted the last */
        /* iq = GEMSS_HFEnvq */
        GEMSS_LOOPIR(GEMSS_HFEnvr-1,GEMSS_SWAP_WORD(*S_cpj,*S_cpi),*S_cpj^=*S_cpi&mask);

        /* Step 2 */
        bit_ir=GEMSS_UINT_1<<(GEMSS_HFEnvr-1);
        GEMSS_LOOPIR_DOWN_TO_UP(GEMSS_HFEnvr);
    #else
        /* To begin to last row */
        --i;
        S_cpi-=GEMSS_NB_WORD_GF2nv;
        Sinv_cpi-=GEMSS_NB_WORD_GF2nv;
    #endif


    /* Step 2:
        S is upper triangular
        It uses operations which would transform S in Identity
        to transform S_inv in inverse of S
    */        


    /* A little modification (j becomes j-1): */
    /* *S_cpj = S[(j-1)*GEMSS_NB_WORD_GF2nv+iq] */
    /* *Sinv_cpj = Sinv[(j-1)*GEMSS_NB_WORD_GF2nv] */

    /* for each row excepted the last block */
    for(iq=GEMSS_HFEnvq;iq>0;--iq)
    {
        /* Previous block of column */
        --S_cpi;
        GEMSS_LOOPIR_DOWN_TO_UP(GEMSS_NB_BITS_UINT);
    }
}


/* for each row j > i, operation on the columns */
#define GEMSS_LOOPJ_CST(OP) \
    S_cpj=S_cpi;\
    Sinv_cpj=Sinv_cpi;\
    /* for the next rows */\
    for(j=i+1;j<GEMSS_HFEnv;++j)\
    {\
        /* next row */\
        S_cpj+=GEMSS_NB_WORD_GF2nv;\
        Sinv_cpj+=GEMSS_NB_WORD_GF2nv;\
        OP;\
    }

#define GEMSS_LOOPIR_CST(NB_IT) \
    for(ir=0;ir<NB_IT;++ir,++i)\
    {\
        /* row i += (1-pivot_i)* row j */\
        GEMSS_LOOPJ_CST({mask=(-(GEMSS_UINT_1-(((*S_cpi)>>ir)&GEMSS_UINT_1)));\
                   GEMSS_LOOPK(GEMSS_XORLOADMASK1_1(S_cpi+k,S_cpj+k,mask);)\
                   GEMSS_xorLoadMask1_gf2nv(Sinv_cpi,Sinv_cpj,mask);\
                  });\
\
        /* row j += (pivot_j) * row_i */\
        GEMSS_LOOPJ_CST({mask=(-(((*S_cpj)>>ir)&GEMSS_UINT_1));\
                   GEMSS_LOOPK(GEMSS_XORLOADMASK1_1(S_cpj+k,S_cpi+k,mask);)\
                   GEMSS_xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask);\
                  });\
\
        /* Next row */\
        S_cpi+=GEMSS_NB_WORD_GF2nv;\
        Sinv_cpi+=GEMSS_NB_WORD_GF2nv;\
    }


/**
 * @brief   Compute the inverse of a matrix (n+v,n+v) in GF(2).
 * @details Gauss-Jordan: transform S to Identity and Identity to S^(-1).
 * A constant-time Gauss elimination is used.
 * @param[in,out]    S   An invertible matrix (n+v,n+v) in GF(2), will modified
 * by the function (in particular, will be upper triangular).
 * @param[out]  S_inv   The inverse of S, matrix (n+v,n+v) in GF(2).
 * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S_inv.
 * @remark  Requirement: S is invertible.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_invMatrixnv_cst_gf2)(GLnv_gf2 S_inv, GLnv_gf2 S)
{
    GLnv_gf2 S_cpi,S_cpj,Sinv_cpi,Sinv_cpj;
    UINT mask;
    unsigned int i=0,iq,ir,j,k;

    /* S_inv initialized to identity */
    GEMSS_initMatrixIdnv_gf2(S_inv);

    /* In this code, we have: */
    /* *S_cpi = S[i*GEMSS_NB_WORD_GF2nv+iq] */
    /* *S_cpj = S[j*GEMSS_NB_WORD_GF2nv+iq] */
    /* *Sinv_cpi = S_inv[i*GEMSS_NB_WORD_GF2nv] */
    /* *Sinv_cpj = S_inv[j*GEMSS_NB_WORD_GF2nv] */

    S_cpi=S;
    Sinv_cpi=S_inv;
    /* for each row of S and of S_inv, excepted the last block */
    for(iq=0;iq<GEMSS_HFEnvq;++iq)
    {
        GEMSS_LOOPIR_CST(GEMSS_NB_BITS_UINT);
        /* Next block of column */
        ++S_cpi;
    }

    #if (GEMSS_HFEnvr)
        GEMSS_LOOPIR_CST(GEMSS_HFEnvr-1);

        /* Step 2 */
        GEMSS_LOOPIR_DOWN_TO_UP(GEMSS_HFEnvr);
    #else
        /* To begin to last row */
        --i;
        S_cpi-=GEMSS_NB_WORD_GF2nv;
        Sinv_cpi-=GEMSS_NB_WORD_GF2nv;
    #endif


    /* Step 2:
        S is upper triangular
        It uses operations which would transform S in Identity
        to transform S_inv in inverse of S
    */        


    /* A little modification (j becomes j-1): */
    /* *S_cpj = S[(j-1)*GEMSS_NB_WORD_GF2nv+iq] */
    /* *Sinv_cpj = Sinv[(j-1)*GEMSS_NB_WORD_GF2nv] */

    /* for each row excepted the last block */
    for(iq=GEMSS_HFEnvq;iq>0;--iq)
    {
        /* Previous block of column */
        --S_cpi;
        GEMSS_LOOPIR_DOWN_TO_UP(GEMSS_NB_BITS_UINT);
    }
}


/**
 * @brief   Compute the inverse of S=LU a matrix (n+v,n+v) in GF(2), in-place.
 * @details Gauss-Jordan: transform S to Identity and Identity to S^(-1).
 * Here, we do not need to transform S to Identity.
 * We use L to transform Identity to a lower triangular S',
 * then we use U to transform S' to S^(-1).
 * @param[in,out]    S_inv   S_inv=L*U, an invertible matrix (n+v,n+v) in GF(2),
 * its inverse will be computed in-place.
 * @param[in]   L   A lower triangular matrix (n+v,n+v) in GF(2).
 * @param[in]   U   An upper triangular matrix (n+v,n+v) in GF(2), but we 
 * require to store its transpose (i.e. contiguous following the columns).
 * @remark  Requirement: S is invertible.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_invMatrixLUnv_gf2)(GLnv_gf2 S_inv, cst_Tnv_gf2 L,
                                                    cst_Tnv_gf2 U)
{
    GLnv_gf2 Sinv_cpi,Sinv_cpj;
    cst_Tnv_gf2 L_cpj;
    UINT mask;
    unsigned int i,iq,ir,j,k;

    /* Initialize to 0 */
    for(i=0;i<GEMSS_MATRIXnv_SIZE;++i)
    {
        S_inv[i]=0;
    }


    Sinv_cpi=S_inv;
    /* for each row of S and of S_inv, excepted the last block */
    for(i=0,iq=0;iq<GEMSS_HFEnvq;++iq)
    {
        for(ir=0;ir<GEMSS_NB_BITS_UINT;++ir,++i)
        {
            /* The element of the diagonal is 1 */
            *(Sinv_cpi+iq)^=(GEMSS_UINT_1<<ir);

            Sinv_cpj=Sinv_cpi;
            L_cpj=L;
            /* for the next rows */
            for(j=i;j<(GEMSS_HFEnv-1);++j)
            {
                /* next row */
                Sinv_cpj+=GEMSS_NB_WORD_GF2nv;
                L_cpj+=(j>>6)+1;

                mask=(-(((*L_cpj)>>ir)&GEMSS_UINT_1));
                for(k=0;k<=iq;++k)
                {
                    GEMSS_XORLOADMASK1_1(Sinv_cpj+k,Sinv_cpi+k,mask);
                }
            }

            /* Next row */
            Sinv_cpi+=GEMSS_NB_WORD_GF2nv;
            L+=iq+1;
        }
        /* Next column */
        ++L;
    }
    #if (GEMSS_HFEnvr>1)
        for(ir=0;ir<(GEMSS_HFEnvr-1);++ir,++i)
        {
            /* The element of the diagonal is 1 */
            *(Sinv_cpi+iq)^=(GEMSS_UINT_1<<ir);

            Sinv_cpj=Sinv_cpi;
            L_cpj=L;
            /* for the next rows */
            for(j=i;j<(GEMSS_HFEnv-1);++j)
            {
                /* next row */
                Sinv_cpj+=GEMSS_NB_WORD_GF2nv;
                L_cpj+=(j>>6)+1;

                mask=(-(((*L_cpj)>>ir)&GEMSS_UINT_1));
                for(k=0;k<=iq;++k)
                {
                    GEMSS_XORLOADMASK1_1(Sinv_cpj+k,Sinv_cpi+k,mask);
                }
            }

            /* Next row */
            Sinv_cpi+=GEMSS_NB_WORD_GF2nv;
            L+=iq+1;
        }
        /* ir = GEMSS_HFEnvr-1 */
        *(Sinv_cpi+iq)^=(GEMSS_UINT_1<<ir);
        Sinv_cpi+=GEMSS_NB_WORD_GF2nv;
    #endif


    /* Here, Sinv_cpi is at the end of S_inv */

    /* End of U */
    U+=GEMSS_LTRIANGULAR_NV_SIZE;

    /* for each row excepted the first */
    for(i=GEMSS_HFEnv-1;i>0;--i)
    {
        /* Previous row */
        U-=1+(i>>6);

        /* Row i of Sinv */
        Sinv_cpi-=GEMSS_NB_WORD_GF2nv;

        /* Row j of Sinv */
        Sinv_cpj=S_inv;

        /* for the previous rows */
        for(j=0;j<i;++j)
        {
            /* pivot */
            mask=-(((U[j>>6])>>(j&63U))&1U);
            GEMSS_xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask);

            /* next row */
            Sinv_cpj+=GEMSS_NB_WORD_GF2nv;
        }
    }
}


