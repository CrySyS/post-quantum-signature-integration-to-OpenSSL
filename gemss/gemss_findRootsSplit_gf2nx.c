#include "gemss_findRootsSplit_gf2nx.h"
#include <stdlib.h>
#include "gemss_arch.h"
#include "gemss_rand_gf2n.h"
#include "gemss_add_gf2nx.h"
#include "gemss_sqr_gf2nx.h"
#include "gemss_gcd_gf2nx.h"
#include "gemss_inv_gf2n.h"
#include "gemss_tools_gf2n.h"
#include "gemss_sqr_gf2n.h"
#include "gemss_mul_gf2n.h"
#include "gemss_div_gf2nx.h"
#include <string.h>


/**
 * @brief   Computation of the sum from i=0 to n-1 of ((rX)^(2^i)) mod f
 * @param[in,out]    poly_trace  An element of GF(2^n)[X], initialized to rX
 * with r in GF(2^n). The ouput value is the sum from i=0 to n-1 of 
 * ((rX)^(2^i) mod f), in GF(2^n)[X].
 * @param[in]   poly_frob   An intermediate buffer, becomes (rX)^(2^(n-1)) mod f
 * @param[in]   f   A monic polynomial in GF(2^n)[X].
 * @param[in]   deg The degree of f.
 * @remark  Requires to allocate deg elements of GF(2^n) for poly_trace.
 * @remark  Requires to allocate ((deg<<1)-1)*GEMSS_NB_WORD_GFqn words for poly_frob,
 * initialized to zero.
 * @remark  Requirement: f is monic.
 * @remark  Requirement: deg>1.
 * @remark  Constant-time implementation when deg is not secret and when 
 * GEMSS_CONSTANT_TIME!=0.
 */
static void traceMap_gf2nx(gf2nx poly_trace, gf2nx poly_frob,
                           cst_gf2nx f, unsigned int deg)
{
    #if (!GEMSS_CONSTANT_TIME)
        /* d is the degree of poly_frob */
        unsigned int d;
    #endif
    unsigned int j,i;

    i=1;
    /* (2^i) < deg does not require modular reduction by f */
    #if(GEMSS_HFEn<33)
        const unsigned int min=(deg<(1U<<GEMSS_HFEn))?deg:GEMSS_HFEn;
        while((1U<<i)<min)
    #else
        while((1U<<i)<deg)
    #endif
    {
        /* poly_trace += ((rX)^(2^i)) mod f
           Here, ((rX)^(2^i)) mod f == (rX)^(2^i) since (2^i) < deg */
        GEMSS_sqr_gf2n(poly_trace+(GEMSS_NB_WORD_GFqn<<i),poly_trace+(GEMSS_NB_WORD_GFqn<<(i-1)));
        ++i;
    }

    /* Here, (rX)^(2^i) is the first time where we need modular reduction */
    if(i<GEMSS_HFEn)
    {
        /* poly_frob = (rX)^(2^i) = ((rX)^(2^(i-1)))^2 */
        GEMSS_sqr_gf2n(poly_frob+(GEMSS_NB_WORD_GFqn<<i),poly_trace+(GEMSS_NB_WORD_GFqn<<(i-1)));

        #if GEMSS_CONSTANT_TIME
            /* poly_frob = ((rX)^(2^i)) mod f */
            GEMSS_div_r_monic_cst_gf2nx(poly_frob,1U<<i,f,deg);
            /* poly_trace += ((rX)^(2^i)) mod f */
            GEMSS_add2_gf2nx(poly_trace,poly_frob,deg,j);
        #else
            /* poly_frob = ((rX)^(2^i)) mod f */
            d=GEMSS_div_r_monic_gf2nx(poly_frob,1U<<i,f,deg);
            /* poly_trace += ((rX)^(2^i)) mod f */
            GEMSS_add2_gf2nx(poly_trace,poly_frob,d+1,j);
        #endif
        ++i;

        for(;i<GEMSS_HFEn;++i)
        {
            #if GEMSS_CONSTANT_TIME
                /* poly_frob = (rX)^(2^i) = ((rX)^(2^(i-1)) mod f)^2 */
                GEMSS_sqr_gf2nx(poly_frob,deg-1);
                /* poly_frob = ((rX)^(2^i)) mod f */
                GEMSS_div_r_monic_cst_gf2nx(poly_frob,(deg-1)<<1U,f,deg);
                /* poly_trace += ((rX)^(2^i)) mod f */
                GEMSS_add2_gf2nx(poly_trace,poly_frob,deg,j);
            #else
                /* poly_frob = (rX)^(2^i) = ((rX)^(2^(i-1)) mod f)^2 */
                GEMSS_sqr_gf2nx(poly_frob,d);
                /* poly_frob = ((rX)^(2^i)) mod f */
                d=GEMSS_div_r_monic_gf2nx(poly_frob,d<<1U,f,deg);
                /* poly_trace += ((rX)^(2^i)) mod f */
                GEMSS_add2_gf2nx(poly_trace,poly_frob,d+1,j);
            #endif
        }
    }
}


/**
 * @brief   Computation of the roots of f, when f is split and monic.
 * @param[out]  roots   The vector of the roots of f, in GF(2^n).
 * @param[in]   f   A monic and split polynomial in GF(2^n)[X].
 * @param[in]   deg The degree of f.
 * @remark  Requires to allocate deg elements of GF(2^n) for roots.
 * @remark  Requirement: f is monic and split.
 * @remark  Requirement: deg>0.
 * @remark  This implementation is not in constant-time.
 */
void GEMSS_PREFIX_NAME(GEMSS_findRootsSplit_gf2nx)(vec_gf2n roots, gf2nx f,
                                       unsigned int deg)
{
    gf2nx poly_trace,f_cp,tmp_p;
    gf2nx poly_frob;
    static_gf2n inv[GEMSS_NB_WORD_GFqn];
    unsigned int b,i,l,d;

    if(deg==1)
    {
        /* Extract the unique root which is the constant of f */
        GEMSS_copy_gf2n(roots,f);
        return;
    }

    poly_frob=(UINT*)malloc(((deg<<1)-1)*GEMSS_NB_WORD_GFqn*sizeof(UINT));
    /* poly_trace is modulo f, this degree is strictly less than deg */
    poly_trace=(UINT*)malloc(deg*GEMSS_NB_WORD_GFqn*sizeof(UINT));
    /* f_cp a copy of f */
    f_cp=(UINT*)malloc((deg+1)*GEMSS_NB_WORD_GFqn*sizeof(UINT));
    do
    {
        /* Set poly_frob to zero */
        GEMSS_set0_gf2nx(poly_frob,(deg<<1)-1,l);
        /* Set poly_trace to zero */
        GEMSS_set0_gf2nx(poly_trace,deg,l);

        /* Initialization to rX */
        /* Probability 2^(-n) to find 0 with a correct RNG */
        do
        {
            GEMSS_rand_gf2n(poly_trace+GEMSS_NB_WORD_GFqn);
        } while(GEMSS_is0_gf2n(poly_trace+GEMSS_NB_WORD_GFqn));

        /* copy of f because the gcd modifies f */
        GEMSS_copy_gf2nx(f_cp,f,deg+1,l);

        traceMap_gf2nx(poly_trace,poly_frob,f_cp,deg);
        /* Degree of poly_trace */
        d=deg-1;
        while(GEMSS_is0_gf2n(poly_trace+d*GEMSS_NB_WORD_GFqn)&&d)
        {
            --d;
        }
        l=GEMSS_gcd_gf2nx(&b,f_cp,deg,poly_trace,d);

    } while((!l)||(l==deg));
    free(poly_frob);

    if(b)
    {
        tmp_p=poly_trace;
        poly_trace=f_cp;
        f_cp=tmp_p;
    }
    /* Here, f_cp is a non-trivial divisor of degree l */
    free(poly_trace);

    /* f_cp is the gcd */
    /* Here, it becomes monic */
    GEMSS_inv_gf2n(inv,f_cp+l*GEMSS_NB_WORD_GFqn);
    GEMSS_set1_gf2n(f_cp+l*GEMSS_NB_WORD_GFqn);
    for(i=l-1;i!=(unsigned int)(-1);--i)
    {
        GEMSS_mul_gf2n(f_cp+i*GEMSS_NB_WORD_GFqn,f_cp+i*GEMSS_NB_WORD_GFqn,inv);
    }


    /* f = f_cp * Q */
    /* This function destroyes f */
    GEMSS_div_q_monic_gf2nx(f,deg,f_cp,l);
    /* Necessarily, the polynomial f is null here */

    /* f_cp is monic */
    /* We can apply GEMSS_findRootsSplit_gf2nx recursively */
    GEMSS_findRootsSplit_gf2nx(roots,f_cp,l);
    free(f_cp);

    /* f is monic and f_cp is monic so Q is monic */
    /* We can apply GEMSS_findRootsSplit_gf2nx recursively */
    GEMSS_findRootsSplit_gf2nx(roots+l*GEMSS_NB_WORD_GFqn,f+l*GEMSS_NB_WORD_GFqn,deg-l);
}


