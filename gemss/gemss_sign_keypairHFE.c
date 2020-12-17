#include "gemss_sign_keypairHFE.h"

#include "gemss_arch.h"
#include "gemss_config_HFE.h"
#include "gemss_sizes_HFE.h"
#include <stdlib.h>
#include "gemss_rand_gf2nx.h"
#if GEMSS_PRECOMPUTE2
#include "gemss_genSecretMQSprec.h"
#else
#include "gemss_genSecretMQS_gf2.h"
#endif
#include "gemss_invMatrixn_gf2.h"
#include "gemss_invMatrixnv_gf2.h"
#include "gemss_changeVariablesMQS_gf2.h"
#include "gemss_mixEquationsMQS_gf2.h"

#if GEMSS_AFFINE_TRANSFORMATION_BY_t
#include "gemss_randombytes.h"
#endif

#if GEMSS_FORMAT_HYBRID_CPK8
#include "gemss_convMQS_gf2.h"
#endif
#include "gemss_randMatrix_gf2.h"

#if GEMSS_ENABLED_SEED_SK
    /* For the RBG */
#include "gemss_randombytes.h"
    /* For the GEMSS_expandSeed */
#include "gemss_hash.h"

    #if GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
#include "gemss_determinantn_gf2.h"
#include "gemss_determinantnv_gf2.h"
    #endif
#endif


/* Format of the public-key:
    pk is stored as the concatenation of a constant and a triangular upper 
    quadratic matrix, both in GF(2^m): the m-th bit of a coefficient is the bit
    of m-th equation.
    The quadratic matrix is the concatenation of the rows, 
    without to take the 0 coefficient of the lower part.

    Example with n=4, v=0 and m=2:
    constant: 1+a
    quadratic matrix (n,n) in GF(2^m):
    1   a   1+a a
    0   a   0   1
    0   0   1+a a
    0   0   0   1
    (the term i,j is the monomial xi*xj, and xi^2=xi)

    pk[0]=0x3 (constant term)
    pk[1]=0x1,pk[2]=0x2,pk[3]=0x3,pk[4]=0x2 (first row)
    pk[5]=0x2,pk[6]=0x0,pk[7]=0x1 (second row)
    pk[8]=0x3,pk[9]=0x2 (third row)
    pk[10]=0x1 (fourth row) 

    The two equations are:
    1+x0+x0x2+x1x3+x2+x3 (terms with 1)
    1+x0x1+x0x2+x0x3+x1+x2+x2x3 (terms with a)
*/
/* Format of the secret-key:
    sk  is the concatenation of the GEMSS_HFEv polynomial F + the matrix S^(-1) + the 
    matrix T^(-1).
    - the GEMSS_HFEv polynomial in sk is just the concatenation of the useful
    coefficients:
    the coefficients of X^0,X^1, and X^(2^i + 2^j) is ascending order (j <= i)

    - The matrices S and T are the concatenation of the rows, and a row uses 
    several words: for example, a row of 128 elements of GF(2) is just two
    64-bit words.

    Example of T with n=4:
    1 0 0 1
    1 1 1 1
    0 0 1 0
    0 1 0 1

    T[0]=0x9
    T[1]=0xF
    T[2]=0x4
    T[3]=0xA

    In the code, it is the inverse of S and T which are stored in the
    secret-key.
*/


/**
 * @brief   Generate the secret-key then the public-key of the (GEMSS_HFEv-)-based
 * schemes.
 * @details When GEMSS_ENABLED_SEED_SK is set to 1, sk is a seed.
 * @param[out]  pk  The public-key, a MQ system with m equations in
 * GF(2)[x1,...,x_(n+v)].
 * @param[out]  sk  The secret-key, which is the concatenation of a GEMSS_HFEv
 * polynomial in GF(2^n)[X], the S^(-1) matrix (n+v,n+v) in GL_{n+v}(GF(2))
 * and the T^(-1) matrix (n,n) in GLn(GF(2)).
 * @return   0 if the result is correct, GEMSS_ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  Requires to allocate GEMSS_SIZE_PK_HFE_WORD words for the public-key.
 * @remark  The theoretical minimum size of pk is GEMSS_SIZE_PK_THEORETICAL_HFE bits.
 * @remark  Requires to allocate GEMSS_SIZE_SK_HFE_WORD words for the secret-key.
 * @remark  The theoretical minimum size of sk is GEMSS_SIZE_SK_THEORETICAL_HFE bits.
 * @remark  Constant-time implementation.
 */
int GEMSS_PREFIX_NAME(GEMSS_sign_keypairHFE)(uint8_t* pk, UINT* sk)
{
    #if (GEMSS_ENABLED_SEED_SK&&GEMSS_GEN_INV_MATRIX_TRIAL_ERROR)
        GEMSS_expandSeedCxtDeclaration;
    #endif
    mqsnv_gf2n Q;
    sparse_monic_gf2nx F;
    GLnv_gf2 S;
    GLn_gf2 T;
    #if GEMSS_AFFINE_TRANSFORMATION_BY_t
        vecm_gf2 t;
    #endif
    #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
        Tnv_gf2 L, U;
    #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        Mnv_gf2 S_buf;
    #endif
    #if GEMSS_ENABLED_SEED_SK
        UINT *sk_uncomp;
    #endif
    #if (GEMSS_GEN_INV_MATRIX_TRIAL_ERROR&&(!GEMSS_ENABLED_SEED_SK)&&GEMSS_GEN_INVERSE_IN_FIRST)
        unsigned int i;
    #endif
    int ret;


    #if GEMSS_ENABLED_SEED_SK
        GEMSS_randombytes((uint8_t*)sk,GEMSS_SIZE_SEED_SK);
    #endif


    #if GEMSS_ENABLED_SEED_SK
        #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
            /* The seed generates L,U and L',U' such as S=LU and T=L'U' */
            sk_uncomp=(UINT*)malloc((GEMSS_NB_UINT_HFEVPOLY+(GEMSS_LTRIANGULAR_NV_SIZE<<1)
                                     +(GEMSS_LTRIANGULAR_N_SIZE<<1)+GEMSS_SIZE_VECTOR_t)
                                    *sizeof(UINT));
            GEMSS_VERIFY_ALLOC_RET(sk_uncomp);
            GEMSS_expandSeed((uint8_t*)sk_uncomp,(GEMSS_NB_UINT_HFEVPOLY
                                     +(GEMSS_LTRIANGULAR_NV_SIZE<<1)
                                     +(GEMSS_LTRIANGULAR_N_SIZE<<1)+GEMSS_SIZE_VECTOR_t)<<3,
                 (uint8_t*)sk,GEMSS_SIZE_SEED_SK);
        #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
            /* The seed generates S and T */
            sk_uncomp=(UINT*)malloc(GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD*sizeof(UINT));
            GEMSS_VERIFY_ALLOC_RET(sk_uncomp);
            GEMSS_expandSeedIUF(&hashInstance,(uint8_t*)sk,GEMSS_SIZE_SEED_SK<<3);
            GEMSS_expandSeedSqueeze(&hashInstance,(uint8_t*)sk_uncomp,
                               GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD<<6);

            S=sk_uncomp+GEMSS_ACCESS_MATRIX_S;
            T=S+GEMSS_MATRIXnv_SIZE;
        #endif

        /* zero padding for the GEMSS_HFEv polynomial F */
        F=sk_uncomp;
        GEMSS_cleanMonicHFEv_gf2nx(F);
    #else
        /* Generate the GEMSS_HFEv polynomial F */
        F=sk;
        GEMSS_randMonicHFEv_gf2nx(F);
    #endif

    /* Generate f a secret MQ system, 
       with the representation phi^-1(f) = cst + xQxt */

    /* Here, the first element (of GF(2^n)) of Q is reserved to store cst.
       The matrix Q is stored as upper triangular matrix. */

    Q=(UINT*)malloc(GEMSS_MQnv_GFqn_SIZE*sizeof(UINT));
    if(!Q)
    {
        #if GEMSS_ENABLED_SEED_SK
            free(sk_uncomp);
        #endif
        return GEMSS_ERROR_ALLOC;
    }
    #if GEMSS_PRECOMPUTE2
        genSecretMQSprec(Q,F);
    #else
        ret=GEMSS_genSecretMQS_gf2(Q,F);
        if(ret)
        {
            #if GEMSS_ENABLED_SEED_SK
                free(sk_uncomp);
            #endif
            free(Q);
            return ret;
        }
    #endif

    /* Generate S for the linear transformation on variables */
    #if ((!GEMSS_ENABLED_SEED_SK)||GEMSS_GEN_INVERTIBLE_MATRIX_LU)
        S=GEMSS_MALLOC_MATRIXnv;
        if(!S)
        {
            #if GEMSS_ENABLED_SEED_SK
                free(sk_uncomp);
            #endif
            free(Q);
            return GEMSS_ERROR_ALLOC;
        }
        /* The allocated memory for S will be use for T */
        T=S;
    #endif


    #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
        #if GEMSS_ENABLED_SEED_SK
            /* The random bytes are already generated from a seed */
            L=sk_uncomp+GEMSS_NB_UINT_HFEVPOLY;
        #else
            /* Allocation of L and U */
            L=(UINT*)malloc((GEMSS_LTRIANGULAR_NV_SIZE<<1)*sizeof(UINT));
            if(!L)
            {
                free(Q);
                free(S);
                return GEMSS_ERROR_ALLOC;
            }
        #endif
        U=L+GEMSS_LTRIANGULAR_NV_SIZE;

        #if GEMSS_ENABLED_SEED_SK
            GEMSS_cleanLowerMatrixnv(L);
            GEMSS_cleanLowerMatrixnv(U);
        #elif GEMSS_GEN_INVERSE_IN_FIRST
            /* S^(-1) = L*U is stored in the secret-key */
            GEMSS_randInvMatrixLU_gf2_nv(sk+GEMSS_ACCESS_MATRIX_S,L,U);
        #else
            /* S = L*U */
            GEMSS_randInvMatrixLU_gf2_nv(S,L,U);
        #endif

        #if GEMSS_GEN_INVERSE_IN_FIRST
            /* Generate S the inverse of S^(-1) */
            GEMSS_invMatrixLUnv_gf2(S,L,U);
        #elif GEMSS_ENABLED_SEED_SK
            /* Generate S^(-1) = L*U */
            GEMSS_mulMatricesLU_gf2_nv(S,L,U);
        #else
            /* Compute S^(-1), stored in the secret-key */
            GEMSS_invMatrixLUnv_gf2(sk+GEMSS_ACCESS_MATRIX_S,L,U);
        #endif
    #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        S_buf=GEMSS_MALLOC_MATRIXnv;

        if(!S_buf)
        {
            #if GEMSS_ENABLED_SEED_SK
                free(sk_uncomp);
            #endif
            free(Q);
            #if (!GEMSS_ENABLED_SEED_SK)
                free(S);
            #endif
            return GEMSS_ERROR_ALLOC;
        }

        #if GEMSS_ENABLED_SEED_SK
            /* The random bytes are already generated from a seed */
            GEMSS_cleanMatrix_gf2_nv(S);
            while(!GEMSS_determinantnv_gf2(S,S_buf))
            {
                GEMSS_expandSeedSqueeze(&hashInstance,(uint8_t*)S,GEMSS_MATRIXnv_SIZE<<6);
                GEMSS_cleanMatrix_gf2_nv(S);
            }

            #if GEMSS_GEN_INVERSE_IN_FIRST
                GEMSS_invMatrixnv_gf2(S_buf,S);
                S=S_buf;
/*          #else
                   Useless to generate S^(-1) here */
            #endif
        #elif GEMSS_GEN_INVERSE_IN_FIRST
            GEMSS_randInvMatrix_gf2_nv(sk+GEMSS_ACCESS_MATRIX_S,S_buf);

            /* Copy of S^(-1) in S_buf */
            for(i=0;i<GEMSS_MATRIXnv_SIZE;++i)
            {
                S_buf[i]=sk[GEMSS_ACCESS_MATRIX_S+i];
            }

            /* Computation of S (S_buf is modified) */
            GEMSS_invMatrixnv_gf2(S,S_buf);
        #else
            GEMSS_randInvMatrix_gf2_nv(S,S_buf);
            /* S^(-1) will be generated later in sk */
        #endif
    #endif


    /* Compute Q'=S*Q*St (with Q an upper triangular matrix) */
    GEMSS_changeVariablesMQS_gf2(Q,S);


    #if (GEMSS_GEN_INV_MATRIX_TRIAL_ERROR&&(!GEMSS_ENABLED_SEED_SK)\
                                   &&(!GEMSS_GEN_INVERSE_IN_FIRST))
        /* Compute S^(-1), stored in the secret-key */
        GEMSS_invMatrixnv_gf2(sk+GEMSS_ACCESS_MATRIX_S,S);
    #endif


    #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
        #if GEMSS_ENABLED_SEED_SK
            /* The random bytes are already generated from a seed */
            L+=(GEMSS_LTRIANGULAR_NV_SIZE<<1);
            U=L+GEMSS_LTRIANGULAR_N_SIZE;
        #elif GEMSS_HFEv
            U=L+GEMSS_LTRIANGULAR_N_SIZE;
        #endif

        #if GEMSS_ENABLED_SEED_SK
            GEMSS_cleanLowerMatrixn(L);
            GEMSS_cleanLowerMatrixn(U);
        #elif GEMSS_GEN_INVERSE_IN_FIRST
            /* T^(-1) = L*U is stored in the secret-key */
            GEMSS_randInvMatrixLU_gf2_n(sk+GEMSS_ACCESS_MATRIX_T,L,U);
        #else
            /* T = L*U */
            GEMSS_randInvMatrixLU_gf2_n(T,L,U);
        #endif

        #if GEMSS_GEN_INVERSE_IN_FIRST
            /* Generate T the inverse of T^(-1) */
            GEMSS_invMatrixLUn_gf2(T,L,U);
        #elif GEMSS_ENABLED_SEED_SK
            /* Generate T^(-1) = L*U */
            GEMSS_mulMatricesLU_gf2_n(T,L,U);
        #else
            /* Compute T^(-1), stored in the secret-key */
            GEMSS_invMatrixLUn_gf2(sk+GEMSS_ACCESS_MATRIX_T,L,U);
        #endif

        #if (!GEMSS_ENABLED_SEED_SK)
            free(L);
        #endif
    #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        #if GEMSS_ENABLED_SEED_SK
            /* The random bytes are already generated from a seed */
            GEMSS_cleanMatrix_gf2_n(T);
            while(!GEMSS_determinantn_gf2(T,S_buf))
            {
                GEMSS_expandSeedSqueeze(&hashInstance,(uint8_t*)T,GEMSS_MATRIXn_SIZE<<6);
                GEMSS_cleanMatrix_gf2_n(T);
            }

            #if GEMSS_GEN_INVERSE_IN_FIRST
                GEMSS_invMatrixn_gf2(S_buf,T);
                T=S_buf;
/*          #else
                   Useless to generate T^(-1) here */
            #endif
        #elif GEMSS_GEN_INVERSE_IN_FIRST
            GEMSS_randInvMatrix_gf2_n(sk+GEMSS_ACCESS_MATRIX_T,S_buf);

            /* Copy of T^(-1) in S_buf */
            for(i=0;i<GEMSS_MATRIXn_SIZE;++i)
            {
                S_buf[i]=sk[GEMSS_ACCESS_MATRIX_T+i];
            }

            /* Computation of T (S_buf is modified) */
            GEMSS_invMatrixn_gf2(T,S_buf);
        #else
            /* Generate T for linear transformation on equations */
            GEMSS_randInvMatrix_gf2_n(T,S_buf);
            /* T^(-1) will be generated later in sk */
        #endif

        #if !(GEMSS_ENABLED_SEED_SK&&GEMSS_GEN_INVERSE_IN_FIRST)
            free(S_buf);
        #endif
    #endif


    #if (GEMSS_ENABLED_SEED_SK&&GEMSS_GEN_INVERTIBLE_MATRIX_LU\
                        &&(!GEMSS_AFFINE_TRANSFORMATION_BY_t))
        free(sk_uncomp);
    #endif


    #if (GEMSS_FORMAT_HYBRID_CPK8)
        uint8_t* pk_tmp=(uint8_t*)malloc(GEMSS_MQ_GFqm8_SIZE*sizeof(uint8_t));
    #endif

    #if (GEMSS_FORMAT_HYBRID_CPK8)
        if(!pk_tmp)
        {
            #if (GEMSS_ENABLED_SEED_SK&&\
                 (GEMSS_GEN_INV_MATRIX_TRIAL_ERROR||GEMSS_AFFINE_TRANSFORMATION_BY_t))
                free(sk_uncomp);
            #endif
            free(Q);
            #if ((!GEMSS_ENABLED_SEED_SK)||GEMSS_GEN_INVERTIBLE_MATRIX_LU)
                /* T is stored in S. free(S) would have the same effect. */
                free(T);
            #endif
            #if (GEMSS_GEN_INV_MATRIX_TRIAL_ERROR&&GEMSS_ENABLED_SEED_SK\
                                           &&GEMSS_GEN_INVERSE_IN_FIRST)
                /* T is stored in S_buf */
                free(S_buf);
            #endif
            return GEMSS_ERROR_ALLOC;
        }
    #endif


    /* Use T (variable S) to compute cst_pk and Q_pk */
    #if (GEMSS_FORMAT_HYBRID_CPK8)
        GEMSS_mixEquationsMQS8_gf2(pk_tmp,Q,T);
    #elif GEMSS_FORMAT_MONOMIAL_PK8
        GEMSS_mixEquationsMQS8_gf2(pk,Q,T);
    #endif
    free(Q);


    #if (GEMSS_ENABLED_SEED_SK&&GEMSS_GEN_INV_MATRIX_TRIAL_ERROR\
                        &&(!GEMSS_AFFINE_TRANSFORMATION_BY_t))
        free(sk_uncomp);
    #endif
    #if (GEMSS_GEN_INV_MATRIX_TRIAL_ERROR&&GEMSS_ENABLED_SEED_SK&&GEMSS_GEN_INVERSE_IN_FIRST)
        /* T is stored in S_buf */
        free(S_buf);
    #endif


    /* Generate the inverse of T */
    #if (GEMSS_GEN_INV_MATRIX_TRIAL_ERROR&&(!GEMSS_ENABLED_SEED_SK)\
                                   &&(!GEMSS_GEN_INVERSE_IN_FIRST))
        GEMSS_invMatrixn_gf2(sk+GEMSS_ACCESS_MATRIX_T,T);
    #endif


    #if ((!GEMSS_ENABLED_SEED_SK)||GEMSS_GEN_INVERTIBLE_MATRIX_LU)
        /* T is stored in S */
        free(S);
    #endif


    #if GEMSS_AFFINE_TRANSFORMATION_BY_t
        #if GEMSS_ENABLED_SEED_SK
            #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
                t=L+(GEMSS_LTRIANGULAR_N_SIZE<<1);
            #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
                t=sk_uncomp+GEMSS_ACCESS_VECTOR_t;
            #endif
        #else
            t=sk+GEMSS_ACCESS_VECTOR_t;
            GEMSS_randombytes((unsigned char*)t,GEMSS_NB_WORD_GF2m<<3);
        #endif
        #if GEMSS_HFEmr
            t[GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
        #endif
        #if (GEMSS_FORMAT_HYBRID_CPK8)
            GEMSS_add2_gf2m((UINT*)pk_tmp,t);
        #else
            GEMSS_add2_gf2m((UINT*)pk,t);
        #endif

        #if GEMSS_ENABLED_SEED_SK
            free(sk_uncomp);
        #endif
    #endif


    #if GEMSS_FORMAT_HYBRID_CPK8
        GEMSS_convMQS_one_eq_to_hybrid_rep8_gf2(pk,pk_tmp);
    #endif

    #if (GEMSS_FORMAT_HYBRID_CPK8)
        free(pk_tmp);
    #endif

    return 0;
}


