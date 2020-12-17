#include "gemss_genCanonicalBasis_gf2n.h"
#include "gemss_sqr_gf2n.h"


/**
 * @brief   Build a matrix in GF(2^n), in-place, such as:
 * The first row is the canonical basis of GF(2^n), i.e. (1,a,a^2,...,a^(n-1)),
 * and 1 is not stored.
 * The i-th row is the first row at the power (2^i).
 * @param[in,out]    alpha_vec   A (n-1)*Floor(Log_2(D)) matrix in GF(2^n).
 * @remark  Requires to allocate (n-1)*Floor(Log_2(D)) elements of GF(2^n) for
 * alpha_vec. The (n-1) first elements must be set to zero.
 * @remark  This function does not require a constant-time implementation.
 * @remark  Ths matrix can be precomputed once n is fixed.
 */
void GEMSS_PREFIX_NAME(GEMSS_genCanonicalBasis_gf2n)(vec_gf2n alpha_vec)
{
    vec_gf2n a_vec;
    unsigned int i,j;

    /* Current row */
    a_vec=alpha_vec;

    /* The first row of alpha_vec is set to (a,a^2,...,a^(n-1)) */
    /* The element a^0 = 1 is implicit, and so is not stored */
    /* n = q*GEMSS_NB_BITS_UINT + r */
    /* Each element has the form a^(i*GEMSS_NB_BITS_UINT + j) */

    #if(GEMSS_NB_WORD_GFqn==1)
        for(j=1;j<GEMSS_HFEn;++j)
        {
            /* a^j */
            *a_vec=GEMSS_UINT_1<<j;
            ++a_vec;
        }
    #else
        /* i=0 */
        /* j=0 is the case a^0 */
        /* Put the bit 1 at the position j */
        for(j=1;j<GEMSS_NB_BITS_UINT;++j)
        {
            /* It is a^(i*GEMSS_NB_BITS_UINT + j) */
            *a_vec=GEMSS_UINT_1<<j;
            a_vec+=GEMSS_NB_WORD_GFqn;
        }
        ++a_vec;

        for(i=1;i<GEMSS_HFEnq;++i)
        {
            *a_vec=GEMSS_UINT_1;
            a_vec+=GEMSS_NB_WORD_GFqn;
            /* Put the bit 1 at the position j */
            for(j=1;j<GEMSS_NB_BITS_UINT;++j)
            {
                /* It is a^(i*GEMSS_NB_BITS_UINT + j) */
                *a_vec=GEMSS_UINT_1<<j;
                a_vec+=GEMSS_NB_WORD_GFqn;
            }
            ++a_vec;
        }
        /* i = GEMSS_NB_WORD_GFqn-1 */
        #if (GEMSS_HFEnr)
            *a_vec=GEMSS_UINT_1;
            a_vec+=GEMSS_NB_WORD_GFqn;
            for(j=1;j<GEMSS_HFEnr;++j)
            {
                *a_vec=GEMSS_UINT_1<<j;
                a_vec+=GEMSS_NB_WORD_GFqn;
            }
            ++a_vec;
        #endif
        a_vec-=GEMSS_NB_WORD_GFqn;
    #endif

    /* Here, a_vec is the row i+1 and alpha_vec is the row i.
       We compute the row i+1 at the step i.
       The row i is: (a^(2^i),a^(2*(2^i)),...,a^((n-1)*(2^i))) */
    #if(GEMSS_HFEDegI!=GEMSS_HFEDegJ)
        for(i=0;i<GEMSS_HFEDegI;++i)
    #else
        for(i=0;i<=GEMSS_HFEDegI;++i)
    #endif
    {
        /* j=0 is the case (a^0)^(2^i)=1, and is not stored */
        for(j=1;j<GEMSS_HFEn;++j)
        {
            /* a^(2^(i+1)) = (a^(2^i))^2 */
            GEMSS_sqr_nocst_gf2n(a_vec,alpha_vec);
            a_vec+=GEMSS_NB_WORD_GFqn;
            alpha_vec+=GEMSS_NB_WORD_GFqn;
        }
    }
}


/**
 * @brief   Compute the transpose of the matrix built by GEMSS_genCanonicalBasis_gf2n:
 * The first column is the canonical basis of GF(2^n), i.e. 
 * transpose((1,a,a^2,...,a^(n-1))), and 1 is not stored.
 * The i-th column is the first column at the power (2^i).
 * @param[in,out]    alpha_vec   A Floor(Log_2(D))*(n-1) matrix in GF(2^n).
 * @remark  Requires to allocate Floor(Log_2(D))*(n-1) elements of GF(2^n) for
 * alpha_vec. The first column must be set to zero.
 * @remark  This function does not require a constant-time implementation.
 * @remark  Ths matrix can be precomputed once n is fixed.
 */
void GEMSS_PREFIX_NAME(GEMSS_genCanonicalBasisVertical_gf2n)(vec_gf2n alpha_vec)
{
    unsigned int i;
    #if(GEMSS_HFEDeg!=1)
        unsigned int j;
    #endif

    /* For each element of the canonical basis */
    for(i=1;i<GEMSS_HFEn;++i)
    {
        /* j=0: a^i */
        alpha_vec[i>>6]=GEMSS_UINT_1<<(i&63);

        #if(GEMSS_HFEDeg!=1)
            /* Compute (a^i)^(2^j) */
            #if(GEMSS_HFEDegI!=GEMSS_HFEDegJ)
                for(j=0;j<GEMSS_HFEDegI;++j)
            #else
                for(j=0;j<=GEMSS_HFEDegI;++j)
            #endif
            {
                GEMSS_sqr_nocst_gf2n(alpha_vec+GEMSS_NB_WORD_GFqn,alpha_vec);
                alpha_vec+=GEMSS_NB_WORD_GFqn;
            }
        #endif
        alpha_vec+=GEMSS_NB_WORD_GFqn;
    }
}


