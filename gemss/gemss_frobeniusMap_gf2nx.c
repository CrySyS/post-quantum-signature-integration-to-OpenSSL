#include "gemss_frobeniusMap_gf2nx.h"
#include "gemss_arch.h"
#include "gemss_gf2x.h"
#include <stdlib.h>
#include "gemss_add_gf2nx.h"
#include "gemss_sqr_gf2nx.h"
#include "gemss_div_gf2nx.h"

#include "gemss_tools_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_sqr_gf2n.h"
#include "gemss_mul_gf2n.h"
#include "gemss_rem_gf2n.h"


/**
 * @brief   Computation of (X^(2^n) - X) mod (F-U).
 * @param[out]  Xqn Xqn = (X^(2^n) - X) mod (F.poly-U) in GF(2^n)[X].
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   U   An element of GF(2^n).
 * @return  The degree of Xqn.
 * @remark  Requires to allocate (2*GEMSS_HFEDeg-1)*GEMSS_NB_WORD_GFqn words for Xqn,
 * initialized to zero.
 * @remark  Requirement: F is monic.
 * @remark  Requirement: D>1 (if D==1, X^(2^n)-X == 0 mod (F-U)).
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation when GEMSS_CONSTANT_TIME!=0.
 */
unsigned int GEMSS_PREFIX_NAME(GEMSS_frobeniusMap_HFE_gf2nx)(gf2nx Xqn, const
                                    complete_sparse_monic_gf2nx F, cst_gf2n U)
{
    static_gf2n cst[GEMSS_NB_WORD_GFqn];
    #if (GEMSS_HFEDegI==GEMSS_HFEDegJ)
        cst_sparse_monic_gf2nx F_cp;
        gf2nx Xqn_cp;
    #endif
    #if GEMSS_CONSTANT_TIME
        UINT b,mask;
    #endif
    unsigned int d,i;

    /* Constant term of F-U */
    GEMSS_add_gf2n(cst,F.poly,U);

    /* For i=GEMSS_HFEDegI, we have X^(2^i) mod (F-U) = X^(2^i).
       The first term of degree >= GEMSS_HFEDeg is X^(2^(GEMSS_HFEDegI+1)):
       2^(GEMSS_HFEDegI+1) >= GEMSS_HFEDeg but 2^GEMSS_HFEDegI < GEMSS_HFEDeg.
       So, we begin at the step i=GEMSS_HFEDegI+1 */
    #if (GEMSS_HFEDegI==GEMSS_HFEDegJ)
        /* Compute X^(2^(GEMSS_HFEDegI+2)) mod (F-U) */

        /* We have X^D = X^(2^GEMSS_HFEDegI + 2^GEMSS_HFEDegJ) = X^(2^(GEMSS_HFEDegI+1)).
           So, X^(2^(GEMSS_HFEDegI+1)) mod (F-U) = F-U - X^D.
           Then, X^(2^(GEMSS_HFEDegI+2)) = (F-U - X^D)^2 mod (F-U) */

        /* Step 1: compute (F-U - X^D)^2 */
        F_cp=F.poly;
        Xqn_cp=Xqn;

        GEMSS_sqr_gf2n(Xqn_cp,cst);
        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            F_cp+=GEMSS_NB_WORD_GFqn;
            /* Multiplication by 2 to have the coefficient of the square */
            Xqn_cp+=(F.L[i])<<1;
            GEMSS_sqr_gf2n(Xqn_cp,F_cp);
        }
        /* Degree of (F-U - X^D)^2 */
        #if(GEMSS_HFEDeg==2)
            d=2;
        #else
            d=GEMSS_HFEDeg+(1U<<GEMSS_HFEDegI);
        #endif

        /* Step 2: reduction of (F-U - X^D)^2 modulo (F-U) */
        #if GEMSS_CONSTANT_TIME
            GEMSS_divsqr_r_HFE_cstdeg_gf2nx(Xqn,d,F,cst);
        #else
            d=GEMSS_div_r_HFE_gf2nx(Xqn,d,F,cst);
        #endif

    for(i=GEMSS_HFEDegI+2;i<GEMSS_HFEn;++i)
    #else
        /* Compute X^(2^(GEMSS_HFEDegI+1)) mod (F-U) */

        /* Step 1: compute X^(2^(GEMSS_HFEDegI+1)) */
        d=2U<<GEMSS_HFEDegI;
        /* Xqn is initialized to 0 with calloc, so the multiprecision word is 
           initialized to 1 just by setting the first word */
        Xqn[d*GEMSS_NB_WORD_GFqn]=1;

        /* Step 2: reduction of X^(2^(GEMSS_HFEDegI+1)) modulo (F-U) */
        #if GEMSS_CONSTANT_TIME
            GEMSS_divsqr_r_HFE_cstdeg_gf2nx(Xqn,d,F,cst);
        #else
            d=GEMSS_div_r_HFE_gf2nx(Xqn,d,F,cst);
        #endif

    for(i=GEMSS_HFEDegI+1;i<GEMSS_HFEn;++i)
    #endif
    {
        #if GEMSS_CONSTANT_TIME
            /* Step 1: (X^(2^i) mod (F-U))^2 = X^(2^(i+1)) */
            GEMSS_sqr_HFE_gf2nx(Xqn);
            /* Step 2: X^(2^(i+1)) mod (F-U) */
            GEMSS_divsqr_r_HFE_cst_gf2nx(Xqn,F,cst);
        #else
            /* Step 1: (X^(2^i) mod (F-U))^2 = X^(2^(i+1)) */
            GEMSS_sqr_gf2nx(Xqn,d);
            /* Step 2: X^(2^(i+1)) mod (F-U) */
            d=GEMSS_div_r_HFE_gf2nx(Xqn,d<<1U,F,cst);
        #endif
    }

    /* (X^(2^n) mod (F-U)) - X */
    Xqn[GEMSS_NB_WORD_GFqn]^=1;

    /* Search the degree of X^(2^n) - X mod (F-U) */
    #if GEMSS_CONSTANT_TIME
        d=0;
        mask=0;

        for(i=GEMSS_HFEDeg-1;i>0;--i)
        {
            b=GEMSS_isNot0_gf2n(Xqn+i*GEMSS_NB_WORD_GFqn);
            mask|=b;
            /* We add 1 to d as soon as we exceed all left zero coefficients */
            d+=mask;
        }
    #else
        if(d==1)
        {
            if(GEMSS_is0_gf2n(Xqn+GEMSS_NB_WORD_GFqn))
            {
                d=0;
            }
        }
    #endif

    return d;
}


/**
 * @brief   Table of the X^(k*2^GEMSS_II) mod F, for Ceil(D/2^GEMSS_II) <= k < D.
 * @details We do not store X^(k*2^GEMSS_II) mod F when k*2^GEMSS_II < D, since
 * X^(k*2^GEMSS_II) mod F = X^(k*2^GEMSS_II) is already reduced.
 * @param[out]  table   A vector of GEMSS_KX (D-1)-degree polynomials in GF(2^n)[X].
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   cst The constant of F, an element of GF(2^n).
 * @return  The degree of Xqn.
 * @remark  Requires to allocate (GEMSS_KX*GEMSS_HFEDeg+GEMSS_POW_II)*GEMSS_NB_WORD_GFqn words for table.
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation.
 */
static void precompute_table(vec_gf2nx table,
                             const complete_sparse_monic_gf2nx F,
                             cst_gf2n cst)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef;
    vec_gf2nx table_cp;
    unsigned int k,j,i;

    /* First element of the table: X^(GEMSS_KP*(2^GEMSS_II)) mod F. */


    /* First step: X^(GEMSS_KP*(2^GEMSS_II)) mod F = X^(GEMSS_KP*(2^GEMSS_II)-D)*(F - X^D) mod F. */

    /* The first polynomial is initialized to 0. */
    for(i=0;i<(GEMSS_HFEDeg+GEMSS_POW_II);++i)
    {
        GEMSS_set0_gf2n(table+i*GEMSS_NB_WORD_GFqn);
    }

    /* j=GEMSS_POW_II*GEMSS_KP-D, we reduce X^(D+j) mod F. */
    j=GEMSS_POW_II*GEMSS_KP-GEMSS_HFEDeg;

    /* i=0: constant of F */
    table_cp=table+GEMSS_NB_WORD_GFqn*j;
    GEMSS_copy_gf2n(table_cp,cst);
    for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
    {
        table_cp+=F.L[i];
        GEMSS_copy_gf2n(table_cp,F.poly+i*GEMSS_NB_WORD_GFqn);
    }

    /* Second step: we compute X^(GEMSS_KP*(2^GEMSS_II)-D)*(F - X^D) mod F */

    /* We reduce one by one the coefficients leading_coef*X^(D+j) mod F,
       by using X^(D+j) = X^j * X^D = X^j * (F-X^D) mod F. */
    leading_coef=table+(j-1+GEMSS_HFEDeg)*GEMSS_NB_WORD_GFqn;
    for(--j;j!=(unsigned int)(-1);--j)
    {
        /* i=0: constant of F */
        table_cp=table+GEMSS_NB_WORD_GFqn*j;
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(table_cp,mul_coef);
        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            table_cp+=F.L[i];
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            GEMSS_add2_gf2n(table_cp,mul_coef);
        }
        leading_coef-=GEMSS_NB_WORD_GFqn;
    }


    /* Computation of the other elements of the table: X^(k*(2^GEMSS_II)) mod F.
       X^(k*(2^GEMSS_II)) = (X^((k-1)*(2^GEMSS_II)) mod F) * X^(2^GEMSS_II) mod F. */
    for(k=GEMSS_KP+1;k<GEMSS_HFEDeg;++k)
    {
        /* Update the current polynomial */
        table_cp=table+GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;

        /* Multiplication of (X^((k-1)*(2^GEMSS_II)) mod F) by X^(2^GEMSS_II) */
        for(j=0;j<GEMSS_POW_II;++j)
        {
            GEMSS_set0_gf2n(table_cp+j*GEMSS_NB_WORD_GFqn);
        }

        table_cp+=GEMSS_POW_II*GEMSS_NB_WORD_GFqn;
        for(j=0;j<GEMSS_HFEDeg;++j)
        {
            GEMSS_copy_gf2n(table_cp+j*GEMSS_NB_WORD_GFqn,table+j*GEMSS_NB_WORD_GFqn);
        }
        table_cp-=GEMSS_POW_II*GEMSS_NB_WORD_GFqn;


        /* Update the current polynomial */
        table=table_cp;


        /* Reduction of (X^((k-1)*(2^GEMSS_II)) mod F) * X^(2^GEMSS_II) modulo F */

        /* We reduce one by one the coefficients leading_coef*X^(D+j) mod F,
           by using X^(D+j) = X^j * X^D = X^j * (F-X^D) mod F. */
        leading_coef=table+(GEMSS_POW_II-1+GEMSS_HFEDeg)*GEMSS_NB_WORD_GFqn;
        for(j=GEMSS_POW_II-1;j!=(unsigned int)(-1);--j)
        {
            /* i=0: constant of F */
            table_cp=table+GEMSS_NB_WORD_GFqn*j;
            GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
            GEMSS_add2_gf2n(table_cp,mul_coef);
            for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
            {
                table_cp+=F.L[i];
                GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
                GEMSS_add2_gf2n(table_cp,mul_coef);
            }
            leading_coef-=GEMSS_NB_WORD_GFqn;
        }
    }
}


/**
 * @brief   Computation of (X^(2^n) - X) mod (F-U).
 * @param[out]  Xqn Xqn = (X^(2^n) - X) mod (F.poly-U) in GF(2^n)[X].
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   U   An element of GF(2^n).
 * @return  The degree of Xqn.
 * @remark  Requires to allocate (2*GEMSS_HFEDeg-1)*GEMSS_NB_WORD_GFqn words for Xqn.
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation.
 */
unsigned int GEMSS_PREFIX_NAME(GEMSS_frobeniusMap_multisqr_HFE_gf2nx)(gf2nx Xqn, const
                                    complete_sparse_monic_gf2nx F, cst_gf2n U)
{
    static_gf2n cst[GEMSS_NB_WORD_GFqn];
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2nx Xqn_cp;
    vec_gf2nx table,table_cp;
    gf2nx Xqn_sqr;
    gf2n current_coef;
    #if GEMSS_CONSTANT_TIME
        UINT b,mask;
    #endif
    unsigned int d,i,j,k;

    /* Constant of F-U */
    GEMSS_add_gf2n(cst,F.poly,U);

    /* Table of the X^(k*2^GEMSS_II) mod F. */
    table=(UINT*)malloc((GEMSS_KX*GEMSS_HFEDeg+GEMSS_POW_II)*GEMSS_NB_WORD_GFqn*sizeof(UINT));
    precompute_table(table,F,cst);

    /* X^(2^(GEMSS_HFEDegI+GEMSS_II)) = X^( (2^GEMSS_HFEDegI) * (2^GEMSS_II)) */
    /* We take the polynomial from the table */
    table+=(((GEMSS_ONE32<<GEMSS_HFEDegI)-GEMSS_KP)*GEMSS_HFEDeg)*GEMSS_NB_WORD_GFqn;
    GEMSS_copy_gf2nx(Xqn,table,GEMSS_HFEDeg,i);
    table-=(((GEMSS_ONE32<<GEMSS_HFEDegI)-GEMSS_KP)*GEMSS_HFEDeg)*GEMSS_NB_WORD_GFqn;

    Xqn_sqr=(UINT*)calloc(GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn,sizeof(UINT));
    for(i=0;i<((GEMSS_HFEn-GEMSS_HFEDegI-GEMSS_II)/GEMSS_II);++i)
    {
        /* Step 1: Xqn^(2^GEMSS_II) with GEMSS_II squarings */
        /* Xqn_sqr is the list of the coefficients of Xqn at the power 2^GEMSS_II */

        /* j=0, first squaring */
        for(k=0;k<GEMSS_HFEDeg;++k)
        {
            GEMSS_sqr_gf2n(Xqn_sqr+k*GEMSS_NB_WORD_GFqn,Xqn+k*GEMSS_NB_WORD_GFqn);
        }

        /* The other squarings */
        for(j=1;j<GEMSS_II;++j)
        {
            for(k=0;k<GEMSS_HFEDeg;++k)
            {
                GEMSS_sqr_gf2n(Xqn_sqr+k*GEMSS_NB_WORD_GFqn,Xqn_sqr+k*GEMSS_NB_WORD_GFqn);
            }
        }

        /* Step 2: Reduction of Xqn^(2^GEMSS_II) modulo F, by using the table.
           Multiplication of ((X^(k*2^GEMSS_II)) mod F) by the current coefficient. */

        /* j=GEMSS_KP, initialization of the new Xqn */
        current_coef=Xqn_sqr+GEMSS_KP*GEMSS_NB_WORD_GFqn;
        table_cp=table;
        Xqn_cp=Xqn;
        for(k=0;k<GEMSS_HFEDeg;++k)
        {
            GEMSS_mul_gf2n(Xqn_cp,table_cp,current_coef);
            Xqn_cp+=GEMSS_NB_WORD_GFqn;
            table_cp+=GEMSS_NB_WORD_GFqn;
        }

        for(j=GEMSS_KP+1;j<GEMSS_HFEDeg;++j)
        {
            current_coef+=GEMSS_NB_WORD_GFqn;
            Xqn_cp=Xqn;
            for(k=0;k<GEMSS_HFEDeg;++k)
            {
                GEMSS_mul_gf2n(mul_coef,table_cp,current_coef);
                GEMSS_add2_gf2n(Xqn_cp,mul_coef);
                Xqn_cp+=GEMSS_NB_WORD_GFqn;
                table_cp+=GEMSS_NB_WORD_GFqn;
            }
        }

        /* The coefficients such as X^(k*2^GEMSS_II) mod F = X^(k*2^GEMSS_II). */
        for(j=0;j<GEMSS_KP;++j)
        {
            /* (X^j)^GEMSS_II */
            GEMSS_add2_gf2n(Xqn+j*GEMSS_POW_II*GEMSS_NB_WORD_GFqn,Xqn_sqr+j*GEMSS_NB_WORD_GFqn);
        }
    }

    free(table);
    free(Xqn_sqr);

    #if ((GEMSS_HFEn-GEMSS_HFEDegI)%GEMSS_II)
        #if (!GEMSS_CONSTANT_TIME)
            d=GEMSS_HFEDeg-1;
            while(GEMSS_is0_gf2n(Xqn+d*GEMSS_NB_WORD_GFqn)&&d)
            {
                --d;
            }
        #endif

        for(i=0;i<((GEMSS_HFEn-GEMSS_HFEDegI)%GEMSS_II);++i)
        {
            #if GEMSS_CONSTANT_TIME
                /* Step 1: (X^(2^i) mod (F-U))^2 = X^(2^(i+1)) */
                GEMSS_sqr_HFE_gf2nx(Xqn);
                /* Step 2: X^(2^(i+1)) mod (F-U) */
                GEMSS_divsqr_r_HFE_cst_gf2nx(Xqn,F,cst);
            #else
                /* Step 1: (X^(2^i) mod (F-U))^2 = X^(2^(i+1)) */
                GEMSS_sqr_gf2nx(Xqn,d);
                /* Step 2: X^(2^(i+1)) mod (F-U) */
                d=GEMSS_div_r_HFE_gf2nx(Xqn,d<<1U,F,cst);
            #endif
        }
    #endif

    /* X^(2^n) - X */
    Xqn[GEMSS_NB_WORD_GFqn]^=1;

    #if GEMSS_CONSTANT_TIME
        d=0;
        mask=0;

        for(i=GEMSS_HFEDeg-1;i>0;--i)
        {
            b=GEMSS_isNot0_gf2n(Xqn+i*GEMSS_NB_WORD_GFqn);
            mask|=b;
            /* We add 1 to d as soon as we exceed all left zero coefficients */
            d+=mask;
        }
    #elif ((GEMSS_HFEn-GEMSS_HFEDegI)%GEMSS_II)
        if(d==1)
        {
            if(GEMSS_is0_gf2n(Xqn+GEMSS_NB_WORD_GFqn))
            {
                d=0;
            }
        }
    #else
        d=GEMSS_HFEDeg-1;
        while(GEMSS_is0_gf2n(Xqn+d*GEMSS_NB_WORD_GFqn)&&d)
        {
            --d;
        }
    #endif

    return d;
}


