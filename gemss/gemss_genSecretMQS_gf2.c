#include "gemss_genSecretMQS_gf2.h"
#include <stdlib.h>
#include "gemss_tools_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_mul_gf2n.h"
#include "gemss_rem_gf2n.h"
#include "gemss_gf2nx.h"
#include "gemss_config_HFE.h"
#include "gemss_arch.h"

#if GEMSS_PRECOMPUTED_CBASIS
#include "gemss_prec_cbasis_gf2n.h"
#else
#include "gemss_genCanonicalBasis_gf2n.h"
#endif


/*****************************************************************************/
/*****************************************************************************/
/********************************* REFERENCE *********************************/
/*****************************************************************************/
/*****************************************************************************/


/* Compute a secret MQ System from a GEMSS_HFE polynomial */
/* This version replaces directly X by sum a_i x_i in the GEMSS_HFE polynomial F. */
/* For each term of F, X is replaced by sum a_i x_i. */
/* This version is the slowest, because each multiplication is following by a 
modular reduction. */

#if GEMSS_HFEv
    #define GEMSS_LINEAR_VCASE_REF(a_veci) \
        a_veci-=(GEMSS_HFEn-1)*GEMSS_NB_WORD_GFqn;\
        MQS_cp=MQS+(GEMSS_HFEn+1)*GEMSS_NB_WORD_GFqn;\
        for(j=0;j<GEMSS_HFEv;++j)\
        {\
            GEMSS_add2_gf2n(MQS_cp,F_cp+j*GEMSS_NB_WORD_GFqn);\
            MQS_cp+=GEMSS_NB_WORD_GFqn;\
        }\
\
        for(ja=1;ja<GEMSS_HFEn;++ja)\
        {\
            MQS_cp+=(GEMSS_HFEn-ja)*GEMSS_NB_WORD_GFqn;\
            for(j=0;j<GEMSS_HFEv;++j)\
            {\
                GEMSS_mul_gf2n(tmp1,F_cp+j*GEMSS_NB_WORD_GFqn,a_veci);\
                GEMSS_add2_gf2n(MQS_cp,tmp1);\
                MQS_cp+=GEMSS_NB_WORD_GFqn;\
            }\
            a_veci+=GEMSS_NB_WORD_GFqn;\
        }\
        F_cp+=GEMSS_HFEv*GEMSS_NB_WORD_GFqn;
#else
    #define GEMSS_LINEAR_VCASE_REF(a_veci)
#endif


#define GEMSS_LINEAR_CASE_INIT_REF(a_vec) \
    lin_cp=lin;\
    /* j=0 : mul(*F_cp,1) */\
    GEMSS_copy_gf2n(lin_cp,F_cp);\
    lin_cp+=GEMSS_NB_WORD_GFqn;\
\
    for(j=1;j<GEMSS_HFEn;++j)\
    {\
        GEMSS_mul_gf2n(lin_cp,F_cp,a_vec);\
        a_vec+=GEMSS_NB_WORD_GFqn;\
        lin_cp+=GEMSS_NB_WORD_GFqn;\
    }\
    F_cp+=GEMSS_NB_WORD_GFqn;


#define GEMSS_LINEAR_CASE_REF(a_vec) \
    lin_cp=lin;\
    /* j=0 : mul(*F_cp,1)=*F_cp */\
    GEMSS_add2_gf2n(lin_cp,F_cp);\
    lin_cp+=GEMSS_NB_WORD_GFqn;\
\
    for(j=1;j<GEMSS_HFEn;++j)\
    {\
        GEMSS_mul_gf2n(tmp1,F_cp,a_vec);\
        GEMSS_add2_gf2n(lin_cp,tmp1);\
        a_vec+=GEMSS_NB_WORD_GFqn;\
        lin_cp+=GEMSS_NB_WORD_GFqn;\
    }\
    F_cp+=GEMSS_NB_WORD_GFqn;\
    GEMSS_LINEAR_VCASE_REF(a_vec);


/* Replace *F_cp by 1 */
#define GEMSS_LINEAR_MONIC_CASE_REF(a_vec) \
    lin_cp=lin;\
    /* j=0 : mul(*F_cp,1)=*F_cp */\
    *lin_cp^=1;\
    lin_cp+=GEMSS_NB_WORD_GFqn;\
\
    for(j=1;j<GEMSS_HFEn;++j)\
    {\
        GEMSS_add2_gf2n(lin_cp,a_vec);\
        a_vec+=GEMSS_NB_WORD_GFqn;\
        lin_cp+=GEMSS_NB_WORD_GFqn;\
    }


#if GEMSS_HFEv
    #define GEMSS_JUMP_VINEGAR_REF MQS_cp+=GEMSS_HFEv*GEMSS_NB_WORD_GFqn;
#else
    #define GEMSS_JUMP_VINEGAR_REF
#endif

/* Compute (*F_cp)*a_vec[ia]*a_vec[ja] */
/* a_vec[ia]*a_vec[ja] is the term x_ia * x_(ja+1) */
#define GEMSS_QUADRATIC_CASE_INIT_REF(a_vec,a_vecj) \
    /* One term */\
    MQS_cp=MQS+GEMSS_NB_WORD_GFqn;\
\
    /* ia = 0 */\
\
    /* Compute the coefficient of x_0^2 : it is (a^0)^2 = 1 */\
    GEMSS_copy_gf2n(MQS_cp,F_cp);\
    MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
    /* Compute the coefficient of x_0*x_(ja+1) : it is 1 for x_0 */\
    for(ja=0;ja<GEMSS_HFEn-1;++ja)\
    {\
        /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
        GEMSS_add_gf2n(tmp1,a_vecj+ja*GEMSS_NB_WORD_GFqn,a_vec+ja*GEMSS_NB_WORD_GFqn);\
        GEMSS_mul_gf2n(MQS_cp,tmp1,F_cp);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
    }\
\
    GEMSS_JUMP_VINEGAR_REF;\
    for(ia=1;ia<GEMSS_HFEn;++ia)\
    {\
        GEMSS_mul_gf2n(tmp_i,a_vec,F_cp);\
        GEMSS_mul_gf2n(tmp_j,a_vecj,F_cp);\
\
        /* Compute the coefficient of x_ia^2 */\
        GEMSS_mul_gf2n(MQS_cp,a_vec,tmp_j);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
        /* Compute the coefficient of x_ia*x_(ja+1) */\
        for(ja=1;ja<(GEMSS_HFEn-ia);++ja)\
        {\
            /* Compute the coefficient of x_ia*x_(ja+1) */\
            GEMSS_mul_gf2n(tmp1,tmp_i,a_vecj+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_copy_gf2n(MQS_cp,tmp1);\
            /* Compute the coefficient of x_(ja+1)*x_ia */\
            GEMSS_mul_gf2n(tmp1,tmp_j,a_vec+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_add2_gf2n(MQS_cp,tmp1);\
            MQS_cp+=GEMSS_NB_WORD_GFqn;\
        }\
        GEMSS_JUMP_VINEGAR_REF;\
        a_vec+=GEMSS_NB_WORD_GFqn;\
        a_vecj+=GEMSS_NB_WORD_GFqn;\
    }\
    F_cp+=GEMSS_NB_WORD_GFqn;


/* Compute (*F_cp)*a_vec[ia]*a_vec[ja] */
/* a_vec[ia]*a_vec[ja] is the term x_ia * x_(ja+1) */
#define GEMSS_QUADRATIC_CASE_REF(a_veci,a_vecj) \
    /* One term */\
    MQS_cp=MQS+GEMSS_NB_WORD_GFqn;\
    /* Here a_veci = row i */\
    /* Here, a_vecj = row j */\
\
    /* ia = 0 */\
\
    /* Compute the coefficient of x_0^2 : it is (a^0)^2 = 1 */\
    GEMSS_add2_gf2n(MQS_cp,F_cp);\
    MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
    /* Compute the coefficient of x_0*x_(ja+1) : it is 1 for x_0 */\
    for(ja=0;ja<GEMSS_HFEn-1;++ja)\
    {\
        /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
        GEMSS_add_gf2n(tmp1,a_vecj+ja*GEMSS_NB_WORD_GFqn,a_veci+ja*GEMSS_NB_WORD_GFqn);\
        GEMSS_mul_gf2n(tmp_i,tmp1,F_cp);\
        GEMSS_add2_gf2n(MQS_cp,tmp_i);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
    }\
\
    GEMSS_JUMP_VINEGAR_REF;\
    for(ia=1;ia<GEMSS_HFEn;++ia)\
    {\
        GEMSS_mul_gf2n(tmp_i,a_veci,F_cp);\
        GEMSS_mul_gf2n(tmp_j,a_vecj,F_cp);\
\
        /* Compute the coefficient of x_ia^2 */\
        GEMSS_mul_gf2n(tmp1,a_veci,tmp_j);\
        GEMSS_add2_gf2n(MQS_cp,tmp1);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
        /* Compute the coefficient of x_ia*x_(ja+1) */\
        for(ja=1;ja<(GEMSS_HFEn-ia);++ja)\
        {\
            /* Compute the coefficient of x_ia*x_(ja+1) */\
            GEMSS_mul_gf2n(tmp1,tmp_i,a_vecj+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_add2_gf2n(MQS_cp,tmp1);\
            /* Compute the coefficient of x_(ja+1)*x_ia */\
            GEMSS_mul_gf2n(tmp1,tmp_j,a_veci+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_add2_gf2n(MQS_cp,tmp1);\
            MQS_cp+=GEMSS_NB_WORD_GFqn;\
        }\
        GEMSS_JUMP_VINEGAR_REF;\
        a_veci+=GEMSS_NB_WORD_GFqn;\
        a_vecj+=GEMSS_NB_WORD_GFqn;\
    }\
    /* Here, a_veci = row i+1 */\
    /* Here, a_vecj = row j+1 */\
    F_cp+=GEMSS_NB_WORD_GFqn;


/* Replace *F_cp by 1 */
#define GEMSS_QUADRATIC_MONIC_CASE_REF(a_veci,a_vecj) \
    /* One term */\
    MQS_cp=MQS+GEMSS_NB_WORD_GFqn;\
    /* Here a_veci = row i */\
    /* Here, a_vecj = row j */\
\
    /* ia = 0 */\
\
    /* Compute the coefficient of x_0^2 : it is (a^0)^2 = 1 */\
    *MQS_cp^=1;\
    MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
    /* Compute the coefficient of x_0*x_(ja+1) : it is 1 for x_0 */\
    for(ja=0;ja<GEMSS_HFEn-1;++ja)\
    {\
        /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
        GEMSS_add_gf2n(tmp1,a_vecj+ja*GEMSS_NB_WORD_GFqn,a_veci+ja*GEMSS_NB_WORD_GFqn);\
        GEMSS_add2_gf2n(MQS_cp,tmp1);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
    }\
\
    GEMSS_JUMP_VINEGAR_REF;\
    for(ia=1;ia<GEMSS_HFEn;++ia)\
    {\
        /* Compute the coefficient of x_ia^2 */\
        GEMSS_mul_gf2n(tmp1,a_veci,a_vecj);\
        GEMSS_add2_gf2n(MQS_cp,tmp1);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
        /* Compute the coefficient of x_ia*x_(ja+1) */\
        for(ja=1;ja<(GEMSS_HFEn-ia);++ja)\
        {\
            /* Compute the coefficient of x_ia*x_(ja+1) */\
            GEMSS_mul_gf2n(tmp1,a_veci,a_vecj+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_add2_gf2n(MQS_cp,tmp1);\
            /* Compute the coefficient of x_(ja+1)*x_ia */\
            GEMSS_mul_gf2n(tmp1,a_vecj,a_veci+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_add2_gf2n(MQS_cp,tmp1);\
            MQS_cp+=GEMSS_NB_WORD_GFqn;\
        }\
        GEMSS_JUMP_VINEGAR_REF;\
        a_veci+=GEMSS_NB_WORD_GFqn;\
        a_vecj+=GEMSS_NB_WORD_GFqn;\
    }\
    /* Here, a_veci = row i+1 */\
    /* Here, a_vecj = row j+1 */


/* Replace *F_cp by 1 */
#define GEMSS_QUADRATIC_MONIC_CASE_INIT_REF(a_vec,a_vecj) \
    /* One term */\
    MQS_cp=MQS+GEMSS_NB_WORD_GFqn;\
\
    /* ia = 0 */\
\
    /* Compute the coefficient of x_0^2 : it is (a^0)^2 = 1 */\
    GEMSS_set1_gf2n(MQS_cp);\
    MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
    /* Compute the coefficient of x_0*x_(ja+1) : it is 1 for x_0 */\
    for(ja=0;ja<GEMSS_HFEn-1;++ja)\
    {\
        /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
        GEMSS_add_gf2n(MQS_cp,a_vecj+ja*GEMSS_NB_WORD_GFqn,a_vec+ja*GEMSS_NB_WORD_GFqn);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
    }\
\
    GEMSS_JUMP_VINEGAR_REF;\
    for(ia=1;ia<GEMSS_HFEn;++ia)\
    {\
        /* Compute the coefficient of x_ia^2 */\
        GEMSS_mul_gf2n(MQS_cp,a_vec,a_vecj);\
        MQS_cp+=GEMSS_NB_WORD_GFqn;\
\
        /* Compute the coefficient of x_ia*x_(ja+1) */\
        for(ja=1;ja<(GEMSS_HFEn-ia);++ja)\
        {\
            /* Compute the coefficient of x_ia*x_(ja+1) */\
            GEMSS_mul_gf2n(tmp1,a_vec,a_vecj+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_copy_gf2n(MQS_cp,tmp1);\
            /* Compute the coefficient of x_(ja+1)*x_ia */\
            GEMSS_mul_gf2n(tmp1,a_vecj,a_vec+ja*GEMSS_NB_WORD_GFqn);\
            GEMSS_add2_gf2n(MQS_cp,tmp1);\
            MQS_cp+=GEMSS_NB_WORD_GFqn;\
        }\
        GEMSS_JUMP_VINEGAR_REF;\
        a_vec+=GEMSS_NB_WORD_GFqn;\
        a_vecj+=GEMSS_NB_WORD_GFqn;\
    }



/**
 * @brief   Computation of the multivariate representation of a GEMSS_HFEv polynomial.
 * @details Here, for each term of F, X is replaced by sum a_i x_i.
 * @param[in]   F   A monic GEMSS_HFEv polynomial in GF(2^n)[X,x_(n+1),...,x_(n+v)]
 * stored with a sparse representation.
 * @param[out]  MQS The multivariate representation of F, a MQ system with
 * n equations in GF(2)[x1,...,x_(n+v)]. MQS is stored as one equation in
 * GF(2^n)[x1,...,x_(n+v)] (monomial representation + quadratic form cst||Q).
 * @return   0 if the result is correct, GEMSS_ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  Requires to allocate GEMSS_MQnv_GFqn_SIZE words for MQS.
 * @remark  Requirement: F is monic.
 * @remark  Constant-time implementation.
 */
int GEMSS_PREFIX_NAME(GEMSS_genSecretMQS_gf2_ref)(mqsnv_gf2n MQS, cst_sparse_monic_gf2nx F)
{
    /* if there is not quadratic terms X^(2^i + 2^j) */
    #if (GEMSS_HFEDeg<3)
        #if (GEMSS_HFEDeg==2)
            cst_vec_gf2n a_veci;
        #endif
        #if ((GEMSS_HFEDeg==2)||(GEMSS_HFEv))
            cst_sparse_monic_gf2nx F_cp;
        #endif
        mqsnv_gf2n MQS_cp;
        vecn_gf2n lin,lin_cp;
        cst_vec_gf2n a_vec;
        unsigned int i,j;
    #else
        mqsnv_gf2n MQS_cp;
        vecn_gf2n lin,lin_cp;
        static_gf2n tmp1[GEMSS_NB_WORD_GFqn];
        #if (GEMSS_HFEDeg!=3)
            static_gf2n tmp_i[GEMSS_NB_WORD_GFqn],tmp_j[GEMSS_NB_WORD_GFqn];
        #endif
        cst_sparse_monic_gf2nx F_cp;
        cst_vec_gf2n a_vec,a_veci,a_vecj;
        unsigned int i,j,ia,ja;
    #endif

    #if(GEMSS_HFEDeg<3)
        /* there are not quadratic terms X^(2^i + 2^j) */
        for(i=0;i<GEMSS_MQnv_GFqn_SIZE;++i)
        {
            MQS[i]=0;
        }
    #endif

    /* Precompute alpha_vec is disabled in the submission */
    #if GEMSS_PRECOMPUTED_CBASIS
        static cst_vec_gf2n alpha_vec=cbasis_h;
    #else
        vec_gf2n alpha_vec;

        /* Matrix in GF(2^n) with (GEMSS_HFEDegI+1) rows and GEMSS_HFEn-1 columns */
        /* calloc is useful when it initialises a multiple precision element
           to 1 */
        #if(GEMSS_HFEDegI!=GEMSS_HFEDegJ)
            alpha_vec=(UINT*)calloc((GEMSS_HFEDegI+1)*(GEMSS_HFEn-1)*GEMSS_NB_WORD_GFqn,
                                    sizeof(UINT));
        #else
            /* An additional row for the leading term X^(2^i + 2^j)
                                                    = X^(2^(i+1)) */
            alpha_vec=(UINT*)calloc((GEMSS_HFEDegI+2)*(GEMSS_HFEn-1)*GEMSS_NB_WORD_GFqn,
                                    sizeof(UINT));
        #endif
        GEMSS_VERIFY_ALLOC_RET(alpha_vec);

        GEMSS_genCanonicalBasis_gf2n(alpha_vec);
    #endif

    /* Temporary linear vector */
    lin=(UINT*)calloc(GEMSS_HFEn*GEMSS_NB_WORD_GFqn,sizeof(UINT));
    if(!lin)
    {
        #if (!GEMSS_PRECOMPUTED_CBASIS)
            free(alpha_vec);
        #endif
        return GEMSS_ERROR_ALLOC;
    }


    /* Constant : copy the first coefficient of F in MQS */
    GEMSS_copy_gf2n(MQS,F);

    /* The case X^0 is just the coef of X^0 of F,
       so it is useless to return the constant of MQ System */
    #if (GEMSS_HFEv)
        F_cp=F+GEMSS_NB_WORD_GFqn;
        /* +GEMSS_NB_WORD_GFqn because the constant is counted 2 times */
        MQS_cp=MQS+GEMSS_MQnv_GFqn_SIZE-GEMSS_MQv_GFqn_SIZE+GEMSS_NB_WORD_GFqn;
        /* Copy the linear and quadratic terms of the constant in 
           GF(2^n)[y1,...,yv] */
        for(i=1;i<GEMSS_NB_MONOMIAL_VINEGAR;++i)
        {
            GEMSS_copy_gf2n(MQS_cp,F_cp);
            MQS_cp+=GEMSS_NB_WORD_GFqn;
            F_cp+=GEMSS_NB_WORD_GFqn;
        }
    #endif

    a_vec=alpha_vec;
    /* Linear term X */

    /* Monic case */
    #if (GEMSS_HFEDeg==1)
        lin_cp=lin;
        /* j=0 : mul(*F_cp,1) */
        GEMSS_set1_gf2n(lin_cp);
        lin_cp+=GEMSS_NB_WORD_GFqn;

        for(j=1;j<GEMSS_HFEn;++j)
        {
            GEMSS_copy_gf2n(lin_cp,a_vec);
            a_vec+=GEMSS_NB_WORD_GFqn;
            lin_cp+=GEMSS_NB_WORD_GFqn;
        }
    #else

    #if(!GEMSS_HFEv)
        F_cp=F+GEMSS_NB_WORD_GFqn;
    #endif
    GEMSS_LINEAR_CASE_INIT_REF(a_vec);
    #if GEMSS_HFEv
        a_veci=alpha_vec;
        MQS_cp=MQS+(GEMSS_HFEn+1)*GEMSS_NB_WORD_GFqn;
        for(j=0;j<GEMSS_HFEv;++j)
        {
            GEMSS_copy_gf2n(MQS_cp,F_cp+j*GEMSS_NB_WORD_GFqn);
            MQS_cp+=GEMSS_NB_WORD_GFqn;
        }

        for(i=1;i<GEMSS_HFEn;++i)
        {
            MQS_cp+=(GEMSS_HFEn-i)*GEMSS_NB_WORD_GFqn;
            for(j=0;j<GEMSS_HFEv;++j)
            {
                GEMSS_mul_gf2n(MQS_cp,F_cp+j*GEMSS_NB_WORD_GFqn,a_veci);
                MQS_cp+=GEMSS_NB_WORD_GFqn;
            }
            a_veci+=GEMSS_NB_WORD_GFqn;
        }
        F_cp+=GEMSS_HFEv*GEMSS_NB_WORD_GFqn;
    #else
        a_veci=a_vec;
    #endif

    /* Linear term X^2 */
    /* Here a_vec = row 1 */
    #if (GEMSS_HFEDeg==2)
        /* Monic case */
        GEMSS_LINEAR_MONIC_CASE_REF(a_veci);
    #else
    GEMSS_LINEAR_CASE_REF(a_veci);

    /* Quadratic term X^3 */
    /* The quadratic terms of MQS are not initialised */
    a_vecj=alpha_vec;
    #if (GEMSS_HFEDeg==3)
        GEMSS_QUADRATIC_MONIC_CASE_INIT_REF(a_vec,a_vecj);
    #else
    GEMSS_QUADRATIC_CASE_INIT_REF(a_vec,a_vecj);

    /* Here a_vec = row 2 */
    /* Here a_veci = row 2 */

    /* Linear term X^4 */
    #if (GEMSS_HFEDeg==4)
        /* Monic case */
        GEMSS_LINEAR_MONIC_CASE_REF(a_veci);
    #else
    GEMSS_LINEAR_CASE_REF(a_veci);

    /* Other terms, begin at X^5 */
    /* The current term is X^(q^i + q^j) */
    for(i=2;i<GEMSS_HFEDegI;++i)
    {
        /* Here a_vec = row i */
        #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
        j=(((GEMSS_ONE32<<i)+GEMSS_ONE32)<=GEMSS_HFE_odd_degree)?0:1;
        a_vecj=alpha_vec+j*(GEMSS_HFEn-1)*GEMSS_NB_WORD_GFqn;
        for(;j<i;++j)
        #else
        /* Here a_vec = row i */
        a_vecj=alpha_vec;
        for(j=0;j<i;++j)
        #endif
        {
            a_veci=a_vec;
            GEMSS_QUADRATIC_CASE_REF(a_veci,a_vecj);
        }
        a_vec=a_veci;
        /* Here a_vec = row i+1 */

        /* j=i */
        GEMSS_LINEAR_CASE_REF(a_veci);
    }


    /* Remainder */
    /* i = HFEDegi */
    /* The current term is X^(q^HFEDegi + q^j) */

    /* Here a_vec = row i */
    #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
    j=(((GEMSS_ONE32<<i)+GEMSS_ONE32)<=GEMSS_HFE_odd_degree)?0:1;
    a_vecj=alpha_vec+j*(GEMSS_HFEn-1)*GEMSS_NB_WORD_GFqn;
    for(;j<GEMSS_HFEDegJ;++j)
    #else
    /* Here a_vec = row i */
    a_vecj=alpha_vec;
    for(j=0;j<GEMSS_HFEDegJ;++j)
    #endif
    {
        a_veci=a_vec;
        GEMSS_QUADRATIC_CASE_REF(a_veci,a_vecj);
    }
    /* Here a_veci = row i+1 */

    /* j=GEMSS_HFEDegJ */
    #if(GEMSS_HFEDegI==GEMSS_HFEDegJ)
        /* j=i */
        /* It is the leading term and F is monic, so the coefficient is 1 */
        GEMSS_LINEAR_MONIC_CASE_REF(a_veci);
    #else
        a_veci=a_vec;
        GEMSS_QUADRATIC_MONIC_CASE_REF(a_veci,a_vecj);
    #endif

    #endif
    #endif
    #endif
    #endif

    #if (!GEMSS_PRECOMPUTED_CBASIS)
        free(alpha_vec);
    #endif

    /* Put linear part on "diagonal" of MQS */
    lin_cp=lin;
    MQS_cp=MQS+GEMSS_NB_WORD_GFqn;
    for(i=GEMSS_HFEnv;i>GEMSS_HFEv;--i)
    {
        GEMSS_add2_gf2n(MQS_cp,lin_cp);
        lin_cp+=GEMSS_NB_WORD_GFqn;
        MQS_cp+=i*GEMSS_NB_WORD_GFqn;
    }

    free(lin);
    return 0;
}




/*****************************************************************************/
/*****************************************************************************/
/********************************* OPTIMIZED *********************************/
/*****************************************************************************/
/*****************************************************************************/


/* Compute a secret MQ System from a GEMSS_HFE polynomial */
/* The complexity of the used algorithm is the best:
   O(n Log(D) * (n + v + Log(D))) multiplications in GF(2)[x]
   and O(n * (n + v + Log(D))) modular reductions.
*/


#if(GEMSS_HFEDegI!=GEMSS_HFEDegJ)
    #define GEMSS_SIZE_ROW (GEMSS_HFEDegI+1)
#else
    #define GEMSS_SIZE_ROW (GEMSS_HFEDegI+2)
#endif



#include "gemss_dotProduct_gf2n.h"

#if (GEMSS_HFEDeg>2)
static void special_buffer(UINT* buf, cst_sparse_monic_gf2nx F,
                           cst_vec_gf2n alpha_vec)
{
    #if(GEMSS_HFEDeg!=3)
        cst_sparse_monic_gf2nx F_cp;
        unsigned int i,j;
    #endif
    unsigned int k;


    /* Special case: alpha^0 */
    #if(GEMSS_HFEDeg==3)
        /* Monic case */
        GEMSS_set1_gf2n(buf);
        buf+=GEMSS_NB_WORD_GFqn;
    #else
        /* F begins to X^3, the first "quadratic" term */
        F+=(GEMSS_NB_WORD_GFqn*(GEMSS_HFEv+1))<<1;

        F_cp=F;

        /* X^3 */
        #if ((!GEMSS_ENABLED_REMOVE_ODD_DEGREE)||(1<=GEMSS_LOG_odd_degree))
            GEMSS_copy_gf2n(buf,F);
            buf+=GEMSS_NB_WORD_GFqn;
        #endif

        /* X^5: we jump X^4 because it is linear */
        F_cp=F+GEMSS_NB_WORD_GFqn*(GEMSS_HFEv+2);
        /* A_i,j X^(2^i + 2^j) */
        #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
        /* min(L,GEMSS_SIZE_ROW-1) */
        for(i=2;i<((GEMSS_LOG_odd_degree<(GEMSS_SIZE_ROW-1))?(GEMSS_LOG_odd_degree+1)
                                                :(GEMSS_SIZE_ROW-1));++i)
        #else
        for(i=2;i<(GEMSS_SIZE_ROW-1);++i)
        #endif
        {
            /* j=0: A_i,0 */
            GEMSS_copy_gf2n(buf,F_cp);
            for(j=1;j<i;++j)
            {
                F_cp+=GEMSS_NB_WORD_GFqn;
                GEMSS_add2_gf2n(buf,F_cp);
            }
            buf+=GEMSS_NB_WORD_GFqn;
            /* To jump a linear term X^(2^i) */
            F_cp+=GEMSS_NB_WORD_GFqn*(GEMSS_HFEv+2);
        }

        #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
        for(;i<(GEMSS_SIZE_ROW-1);++i)
        {
            /* j=0 is removed because the term is odd */
            /* j=1: A_i,1 */
            GEMSS_copy_gf2n(buf,F_cp);
            for(j=2;j<i;++j)
            {
                F_cp+=GEMSS_NB_WORD_GFqn;
                GEMSS_add2_gf2n(buf,F_cp);
            }
            buf+=GEMSS_NB_WORD_GFqn;
            /* To jump a linear term X^(2^i) */
            F_cp+=GEMSS_NB_WORD_GFqn*(GEMSS_HFEv+2);
        }
        #endif


        #if(GEMSS_HFEDegI!=GEMSS_HFEDegJ)
            /* Monic case */
            GEMSS_set1_gf2n(buf);
            #if ((!GEMSS_ENABLED_REMOVE_ODD_DEGREE)||(GEMSS_LOG_odd_degree>=GEMSS_HFEDegI))
            for(j=0;j<GEMSS_HFEDegJ;++j)
            #else
            for(j=1;j<GEMSS_HFEDegJ;++j)
            #endif
            {
                GEMSS_add2_gf2n(buf,F_cp);
                F_cp+=GEMSS_NB_WORD_GFqn;
            }
            buf+=GEMSS_NB_WORD_GFqn;
        #endif
    #endif


    /* Squares of (alpha^(k+1)) */
    for(k=0;k<(GEMSS_HFEn-1);++k)
    {
        #if(GEMSS_HFEDeg!=3)
        #if ((!GEMSS_ENABLED_REMOVE_ODD_DEGREE)||(1<=GEMSS_LOG_odd_degree))
        /* X^3: i=1,j=0 */
        GEMSS_mul_gf2n(buf,alpha_vec,F);
        buf+=GEMSS_NB_WORD_GFqn;
        #endif

        /* X^5: we jump X^4 because it is linear */
        F_cp=F+GEMSS_NB_WORD_GFqn*(GEMSS_HFEv+2);
        #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
        /* min(L,GEMSS_SIZE_ROW-1) */
        for(i=2;i<((GEMSS_LOG_odd_degree<(GEMSS_SIZE_ROW-1))?(GEMSS_LOG_odd_degree+1)
                                                :(GEMSS_SIZE_ROW-1));++i)
        #else
        /* A_i,j X^(2^i + 2^j) */
        for(i=2;i<(GEMSS_SIZE_ROW-1);++i)
        #endif
        {
            GEMSS_dotProduct_gf2n(buf,alpha_vec,F_cp,i);
            buf+=GEMSS_NB_WORD_GFqn;

            /* To jump quadratic terms + a linear term X^(2^i) */
            F_cp+=(i+GEMSS_HFEv+1)*GEMSS_NB_WORD_GFqn;
        }
        #endif

        #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
        for(;i<(GEMSS_SIZE_ROW-1);++i)
        {
            GEMSS_dotProduct_gf2n(buf,alpha_vec+GEMSS_NB_WORD_GFqn,F_cp,i-1);
            buf+=GEMSS_NB_WORD_GFqn;

            /* To jump quadratic terms + a linear term X^(2^i) */
            F_cp+=(i+GEMSS_HFEv)*GEMSS_NB_WORD_GFqn;
        }
        #endif

        /* j=0: A_i,0 */
        #if (!GEMSS_HFEDegJ)
            /* Monic case */
            GEMSS_copy_gf2n(buf,alpha_vec);
            buf+=GEMSS_NB_WORD_GFqn;

            /* To change the row of alpha_vec */
            alpha_vec+=GEMSS_SIZE_ROW*GEMSS_NB_WORD_GFqn;

        #elif(GEMSS_HFEDegI!=GEMSS_HFEDegJ)
            #if ((!GEMSS_ENABLED_REMOVE_ODD_DEGREE)||(GEMSS_LOG_odd_degree>=GEMSS_HFEDegI))
                #if(GEMSS_HFEDegJ==1)
                    GEMSS_mul_gf2n(buf,alpha_vec,F_cp);
                #else
                    GEMSS_dotProduct_gf2n(buf,alpha_vec,F_cp,GEMSS_HFEDegJ);
                #endif
            #else
                #if(GEMSS_HFEDegJ>1)
                    GEMSS_dotProduct_gf2n(buf,alpha_vec+GEMSS_NB_WORD_GFqn,F_cp,GEMSS_HFEDegJ-1);
                #endif
            #endif
            /* j=GEMSS_HFEDegJ: monic case */
            alpha_vec+=GEMSS_HFEDegJ*GEMSS_NB_WORD_GFqn;
            GEMSS_add2_gf2n(buf,alpha_vec);
            /* To change the row of alpha_vec */
            alpha_vec+=(GEMSS_SIZE_ROW-GEMSS_HFEDegJ)*GEMSS_NB_WORD_GFqn;
            buf+=GEMSS_NB_WORD_GFqn;
        #else
            /* To change the row of alpha_vec */
            alpha_vec+=GEMSS_SIZE_ROW*GEMSS_NB_WORD_GFqn;
        #endif
    }
}
#endif



/**
 * @brief   Computation of the multivariate representation of a GEMSS_HFEv polynomial.
 * @details This transformation is achieved with matrix products.
 * It requires O(n Log(D) * (n + v + Log(D))) multiplications in GF(2)[x]
 * and O(n * (n + v + Log(D))) modular reductions.
 * @param[in]   F   A monic GEMSS_HFEv polynomial in GF(2^n)[X,x_(n+1),...,x_(n+v)]
 * stored with a sparse representation.
 * @param[out]  MQS The multivariate representation of F, a MQ system with
 * n equations in GF(2)[x1,...,x_(n+v)]. MQS is stored as one equation in
 * GF(2^n)[x1,...,x_(n+v)] (monomial representation + quadratic form cst||Q).
 * @return   0 if the result is correct, GEMSS_ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  Requires to allocate GEMSS_MQnv_GFqn_SIZE words for MQS.
 * @remark  Requirement: F is monic.
 * @remark  Constant-time implementation.
 */
int GEMSS_PREFIX_NAME(GEMSS_genSecretMQS_gf2_opt)(mqsnv_gf2n MQS, cst_sparse_monic_gf2nx F)
{
    cst_vec_gf2n a_vec_k;
    #if(GEMSS_HFEDeg<3)
    unsigned int k;
        #if ((GEMSS_HFEDeg==2)&&GEMSS_HFEv)
            unsigned int kp;
        #endif
    #else
    cst_vec_gf2n a_vec_kp,buf_k,buf_kp;
    cst_sparse_monic_gf2nx F_cp;
    static_gf2n tmp1[GEMSS_NB_WORD_MUL], tmp2[GEMSS_NB_WORD_MUL], tmp3[GEMSS_NB_WORD_GFqn];
    unsigned int i,k,kp;
    #endif

    #if(GEMSS_HFEDeg<3)
        /* there are not quadratic terms X^(2^i + 2^j) */
        for(k=0;k<GEMSS_MQnv_GFqn_SIZE;++k)
        {
            MQS[k]=0;
        }
    #endif

    #if(GEMSS_HFEDeg>2)
        /* Vector with linear terms of F */
        UINT* F_lin;

        F_lin=(UINT*)calloc((GEMSS_HFEDegI+1)*(GEMSS_HFEv+1)*GEMSS_NB_WORD_GFqn,sizeof(UINT));
        GEMSS_VERIFY_ALLOC_RET(F_lin);

        F_cp=F+GEMSS_MQv_GFqn_SIZE;

        #if ((!GEMSS_ENABLED_REMOVE_ODD_DEGREE)||(GEMSS_LOG_odd_degree>=GEMSS_HFEDegI))
        for(i=0;i<=GEMSS_HFEDegI;++i)
        #else
        for(i=0;i<=GEMSS_LOG_odd_degree;++i)
        #endif
        {
            for(k=0;k<=GEMSS_HFEv;++k)
            {
                GEMSS_copy_gf2n(F_lin+(k*(GEMSS_HFEDegI+1)+i)*GEMSS_NB_WORD_GFqn,F_cp);
                F_cp+=GEMSS_NB_WORD_GFqn;
            }
            F_cp+=i*GEMSS_NB_WORD_GFqn;
        }

        #if !((!GEMSS_ENABLED_REMOVE_ODD_DEGREE)||(GEMSS_LOG_odd_degree>=GEMSS_HFEDegI))
        for(;i<=GEMSS_HFEDegI;++i)
        {
            for(k=0;k<=GEMSS_HFEv;++k)
            {
                GEMSS_copy_gf2n(F_lin+(k*(GEMSS_HFEDegI+1)+i)*GEMSS_NB_WORD_GFqn,F_cp);
                F_cp+=GEMSS_NB_WORD_GFqn;
            }
            F_cp+=(i-1)*GEMSS_NB_WORD_GFqn;
        }
        #endif


    #endif

    /* Precompute alpha_vec is disabled in the submission */
    #if GEMSS_PRECOMPUTED_CBASIS
        static cst_vec_gf2n alpha_vec=cbasis_v;
    #else
        vec_gf2n alpha_vec;

        /* Matrix in GF(2^n) with GEMSS_HFEn-1 rows and (GEMSS_HFEDegI+1) columns */
        /* calloc is useful when it initialises a multiple precision element
           to 1 */
        alpha_vec=(UINT*)calloc(GEMSS_SIZE_ROW*(GEMSS_HFEn-1)*GEMSS_NB_WORD_GFqn,sizeof(UINT));
        GEMSS_VERIFY_ALLOC_RET(alpha_vec);

        GEMSS_genCanonicalBasisVertical_gf2n(alpha_vec);
    #endif


    /* Constant: copy the first coefficient of F in MQS */
    GEMSS_copy_gf2n(MQS,F);
    F+=GEMSS_MQv_GFqn_SIZE;
    MQS+=GEMSS_NB_WORD_GFqn;


    /* Precompute an other table */
    #if(GEMSS_HFEDeg>2)
        UINT* buf;
        buf=(UINT*)calloc(GEMSS_HFEDegI*GEMSS_HFEn*GEMSS_NB_WORD_GFqn,sizeof(UINT));
        GEMSS_VERIFY_ALLOC_RET(buf);

        special_buffer(buf,F,alpha_vec);
    #endif



    /* Monic case */
    #if (GEMSS_HFEDeg==1)
        a_vec_k=alpha_vec;
        *MQS^=1;
        for(k=GEMSS_HFEnv;k>(GEMSS_HFEv+1);--k)
        {
            MQS+=k*GEMSS_NB_WORD_GFqn;
            GEMSS_copy_gf2n(MQS,a_vec_k);
            a_vec_k+=GEMSS_NB_WORD_GFqn;
        }
    #elif (GEMSS_HFEDeg==2)
        /* x_0: sum of coefficients of F excepted the constant */
        GEMSS_copy_gf2n(MQS,F);
        /* Monic case */
        *MQS^=1;
        MQS+=GEMSS_HFEn*GEMSS_NB_WORD_GFqn;

        /* Vinegar case */
        #if GEMSS_HFEv
            for(kp=1;kp<=GEMSS_HFEv;++kp)
            {
                GEMSS_copy_gf2n(MQS,F+kp*GEMSS_NB_WORD_GFqn);
                MQS+=GEMSS_NB_WORD_GFqn;
            }
        #endif

        a_vec_k=alpha_vec;
        /* Compute the term x_k */
        for(k=1;k<GEMSS_HFEn;++k)
        {
            /* dot_product(a_vec_k,buf_k) */
            GEMSS_mul_gf2n(MQS,F,a_vec_k);
            a_vec_k+=GEMSS_NB_WORD_GFqn;
            GEMSS_add2_gf2n(MQS,a_vec_k);

            MQS+=(GEMSS_HFEn-k)*GEMSS_NB_WORD_GFqn;

            /* Vinegar case */
            #if GEMSS_HFEv
                a_vec_k-=GEMSS_NB_WORD_GFqn;
                for(kp=1;kp<=GEMSS_HFEv;++kp)
                {
                    GEMSS_mul_gf2n(MQS,F+kp*GEMSS_NB_WORD_GFqn,a_vec_k);
                    MQS+=GEMSS_NB_WORD_GFqn;
                }
                a_vec_k+=(GEMSS_NB_WORD_GFqn<<1);
            #else
                a_vec_k+=GEMSS_NB_WORD_GFqn;
            #endif
        }
    #else
        /* k=0 */
        buf_k=buf;
        /* kp=0 */
        buf_kp=buf;

        /* x_0*x_0: quadratic terms of F */
        /* i=0 */
        GEMSS_copy_gf2n(MQS,buf_kp);
        buf_kp+=GEMSS_NB_WORD_GFqn;
        for(i=1;i<GEMSS_HFEDegI;++i)
        {
            GEMSS_add2_gf2n(MQS,buf_kp);
            buf_kp+=GEMSS_NB_WORD_GFqn;
        }
        /* At this step, buf_kp corresponds to kp=1 */

        /* x_0: linear terms of F */
        #if(GEMSS_HFEDegI==GEMSS_HFEDegJ)
            /* Monic case */
            *MQS^=1;
        #endif
        F_cp=F_lin;
        /* X^(2^i) */
        for(i=0;i<=GEMSS_HFEDegI;++i)
        {
            /* Next linear term of F: X^(2^i) */            
            GEMSS_add2_gf2n(MQS,F_cp);
            F_cp+=GEMSS_NB_WORD_GFqn;
        }
        MQS+=GEMSS_NB_WORD_GFqn;

        /* kp=1 (because kp=0 is not stored, it is just (1,1,1,...,1) */
        /* +GEMSS_NB_WORD_GFqn to jump (alpha^kp)^(2^0) */
        a_vec_kp=alpha_vec+GEMSS_NB_WORD_GFqn;


        /* k=0: x_0 x_kp */
        for(kp=1;kp<GEMSS_HFEn;++kp)
        {
            /* dot_product(a_vec_kp, buf_k) */
            #if (GEMSS_HFEDegI==1)
                GEMSS_mul_gf2n(MQS,a_vec_kp,buf_k);
            #else
                GEMSS_dotProduct_gf2n(MQS,a_vec_kp,buf_k,GEMSS_HFEDegI);
            #endif
            a_vec_kp+=GEMSS_SIZE_ROW*GEMSS_NB_WORD_GFqn;

            /* dot_product(a_vec_k=(1,1,...,1) , buf_kp) */
            for(i=0;i<GEMSS_HFEDegI;++i)
            {
                GEMSS_add2_gf2n(MQS,buf_kp);
                buf_kp+=GEMSS_NB_WORD_GFqn;
            }

            MQS+=GEMSS_NB_WORD_GFqn;
        }

        /* Vinegar variables */
        for(;kp<GEMSS_HFEnv;++kp)
        {
            GEMSS_copy_gf2n(MQS,F_cp);
            F_cp+=GEMSS_NB_WORD_GFqn;
            for(i=1;i<=GEMSS_HFEDegI;++i)
            {
                GEMSS_add2_gf2n(MQS,F_cp);
                F_cp+=GEMSS_NB_WORD_GFqn;
            }
            MQS+=GEMSS_NB_WORD_GFqn;
        }


        /* k=0 becomes k=1 */
        /* +GEMSS_NB_WORD_GFqn to jump (alpha^k)^(2^0) */
        a_vec_k=alpha_vec+GEMSS_NB_WORD_GFqn;

        /* Compute the term x_k x_kp */
        for(k=1;k<GEMSS_HFEn;++k)
        {
            /* k=0 becomes k=1 */
            buf_k+=GEMSS_HFEDegI*GEMSS_NB_WORD_GFqn;

            /* kp=k: x_k + x_k*x_k */
            a_vec_kp=a_vec_k;
            buf_kp=buf_k;

            /* Term X^(2^0) of F */
            GEMSS_mul_gf2x(tmp1,F_lin,a_vec_kp-GEMSS_NB_WORD_GFqn);

            /* dot_product(a_vec_k,buf_k) */
            /* i=0 */
            for(i=1;i<=GEMSS_HFEDegI;++i)
            {
                /* Next linear term of F: X^(2^i) */
                GEMSS_add_gf2n(tmp3,buf_kp,F_lin+i*GEMSS_NB_WORD_GFqn);
                GEMSS_mul_gf2x(tmp2,tmp3,a_vec_kp);
                GEMSS_add2_product_gf2n(tmp1,tmp2);
                buf_kp+=GEMSS_NB_WORD_GFqn;
                a_vec_kp+=GEMSS_NB_WORD_GFqn;
            }

            /* Monic case */
            #if(GEMSS_HFEDegI==GEMSS_HFEDegJ)
                GEMSS_add2_gf2n(tmp1,a_vec_kp);
                a_vec_kp+=GEMSS_NB_WORD_GFqn<<1;
            #else
                /* To jump (alpha^kp)^(2^0) */
                a_vec_kp+=GEMSS_NB_WORD_GFqn;
            #endif

            GEMSS_rem_gf2n(MQS,tmp1);
            MQS+=GEMSS_NB_WORD_GFqn;


            /* x_k*x_kp */
            for(kp=k+1;kp<GEMSS_HFEn;++kp)
            {
                GEMSS_doubleDotProduct_gf2n(MQS,a_vec_kp,buf_k,a_vec_k,buf_kp,
                                      GEMSS_HFEDegI);
                a_vec_kp+=GEMSS_SIZE_ROW*GEMSS_NB_WORD_GFqn;
                buf_kp+=GEMSS_HFEDegI*GEMSS_NB_WORD_GFqn;
                MQS+=GEMSS_NB_WORD_GFqn;
            }

            /* Vinegar variables */
            F_cp=F_lin;
            a_vec_k-=GEMSS_NB_WORD_GFqn;
            for(;kp<GEMSS_HFEnv;++kp)
            {
                F_cp+=(GEMSS_HFEDegI+1)*GEMSS_NB_WORD_GFqn;
                GEMSS_dotProduct_gf2n(MQS,a_vec_k,F_cp,GEMSS_HFEDegI+1);
                MQS+=GEMSS_NB_WORD_GFqn;
            }
            a_vec_k+=GEMSS_NB_WORD_GFqn;

            /* k becomes k+1 */
            a_vec_k+=GEMSS_SIZE_ROW*GEMSS_NB_WORD_GFqn;
        }
        free(buf);
        free(F_lin);
    #endif

    #if (!GEMSS_PRECOMPUTED_CBASIS)
        free(alpha_vec);
    #endif

    /* MQS with v vinegar variables */
    #if (GEMSS_HFEv)
        F-=GEMSS_MQv_GFqn_SIZE;
        #if(GEMSS_HFEDeg==1)
            MQS+=(GEMSS_HFEv+1)*GEMSS_NB_WORD_GFqn;
        #endif

        /* Copy the linear and quadratic terms of the constant 
           in GF(2^n)[y1,...,yv] */
        for(k=1;k<GEMSS_NB_MONOMIAL_VINEGAR;++k)
        {
            F+=GEMSS_NB_WORD_GFqn;
            GEMSS_copy_gf2n(MQS,F);
            MQS+=GEMSS_NB_WORD_GFqn;
        }
    #endif

    return 0;
}




