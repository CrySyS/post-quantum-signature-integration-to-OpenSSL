#include "gemss_div_gf2nx.h"
#include "gemss_arch.h"
#include "gemss_gf2nx.h"
#include "gemss_gf2x.h"
#include "gemss_add_gf2nx.h"
#include "gemss_sqr_gf2nx.h"

#include "gemss_tools_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_mul_gf2n.h"
#include "gemss_sqr_gf2n.h"
#include "gemss_rem_gf2n.h"
#include "gemss_inv_gf2n.h"
#include "gemss_macro.h"


/**
 * @brief   Euclidean division in GF(2^n)[X], in-place.
 * @details A = B*Q + R.
 * At the end of the algorithm, we have:
 * Q=A+db*GEMSS_NB_WORD_GFqn;
 * R=A;
 * @param[in,out]    A   An element of GF(2^n)[X], becomes R+Q*X^db at the end.
 * @param[in]   da  The degree of A is at most da.
 * @param[in]   B   A monic polynomial in GF(2^n)[X].
 * @param[in]   db  The degree of B.
 * @return  The degree of R.
 * @remark  Requirement: B is monic.
 * @remark  This implementation is not in constant-time.
 */
unsigned int GEMSS_PREFIX_NAME(GEMSS_div_qr_monic_gf2nx)(gf2nx A, unsigned int da,
                                         cst_gf2nx B, unsigned int db)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i;
    
    /* modular reduction */
    while((int)da>=(int)db)
    {
        /* Search the current degree of A */
        while(GEMSS_is0_gf2n(A+da*GEMSS_NB_WORD_GFqn)&&((int)da>=(int)db))
        {
            --da;
        }

        if((int)da<(int)db)
        {
            /* The computation of the remainder is finished */
            break;
        }

        leading_coef=A+da*GEMSS_NB_WORD_GFqn;
        res=leading_coef-db*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of B */
        GEMSS_mul_gf2n(mul_coef,leading_coef,B);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<db;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,B+i*GEMSS_NB_WORD_GFqn);
            res+=GEMSS_NB_WORD_GFqn;
            GEMSS_add2_gf2n(res,mul_coef);
        }

        /* The leading term of A is a term of the quotient */

        --da;
    }

    if((int)da==(-1))
    {
        ++da;
    }

    /* Here, da=db-1 */
    while(da&&GEMSS_is0_gf2n(A+da*GEMSS_NB_WORD_GFqn))
    {
        --da;
    }

    /* Degree of the remainder */
    return da;
}


/**
 * @brief   Quotient of the Euclidean division in GF(2^n)[X], in-place.
 * @details A = B*Q + R.
 * At the end of the algorithm, we have:
 * Q=A+db*GEMSS_NB_WORD_GFqn;
 * @param[in,out]    A   An element of GF(2^n)[X], becomes (A mod X^db)+Q*X^db.
 * @param[in]   da  The degree of A is at most da.
 * @param[in]   B   A monic polynomial in GF(2^n)[X].
 * @param[in]   db  The degree of B.
 * @return  The degree of R.
 * @remark  Requirement: B is monic.
 * @remark  This implementation is not in constant-time.
 */
unsigned int GEMSS_PREFIX_NAME(GEMSS_div_q_monic_gf2nx)(gf2nx A, unsigned int da,
                                        cst_gf2nx B, unsigned int db)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i;
    
    /* modular reduction */
    while((int)da>=(int)db)
    {
        /* Search the current degree of A */
        while(GEMSS_is0_gf2n(A+da*GEMSS_NB_WORD_GFqn)&&((int)da>=(int)db))
        {
            --da;
        }

        if((int)da<(int)db)
        {
            /* The computation of the remainder is finished */
            break;
        }

        leading_coef=A+da*GEMSS_NB_WORD_GFqn;
        i=(db<<1)-da;
        i=GEMSS_MAXI(0,(int)i);
        res=A+(da-db+i)*GEMSS_NB_WORD_GFqn;

        for(;i<db;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,B+i*GEMSS_NB_WORD_GFqn);
            GEMSS_add2_gf2n(res,mul_coef);
            res+=GEMSS_NB_WORD_GFqn;
        }

        /* The leading term of A is a term of the quotient */

        --da;
    }

    if((int)da==(-1))
    {
        ++da;
    }

    /* Here, da=db-1 */
    while(da&&GEMSS_is0_gf2n(A+da*GEMSS_NB_WORD_GFqn))
    {
        --da;
    }

    /* Degree of the remainder */
    return da;
}


/**
 * @brief   Remainder of the Euclidean division in GF(2^n)[X], in-place.
 * @details A = B*Q + R.
 * @param[in,out]    A   An element of GF(2^n)[X], becomes R at the end.
 * @param[in]   da  The degree of A is at most da.
 * @param[in]   B   An element of GF(2^n)[X].
 * @param[in]   db  The degree of B.
 * @return  The degree of R.
 * @remark  This implementation is not in constant-time.
 */
unsigned int GEMSS_PREFIX_NAME(GEMSS_div_r_gf2nx)(gf2nx A, unsigned int da,
                                  cst_gf2nx B, unsigned int db)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn], leading_coef[GEMSS_NB_WORD_GFqn],
                inv[GEMSS_NB_WORD_GFqn];
    gf2n res;
    unsigned int i;

    /* Compute the inverse of the leading term of B */
    GEMSS_inv_gf2n(inv,B+db*GEMSS_NB_WORD_GFqn);

    /* modular reduction */
    while(da>=db)
    {
        /* Search the current degree of A */
        while(GEMSS_is0_gf2n(A+da*GEMSS_NB_WORD_GFqn)&&(da>=db))
        {
            --da;
        }

        if(da<db)
        {
            /* The computation of the remainder is finished */
            break;
        }

        res=A+(da-db)*GEMSS_NB_WORD_GFqn;
        GEMSS_mul_gf2n(leading_coef,A+da*GEMSS_NB_WORD_GFqn,inv);

        /* i=0: Constant of B */
        GEMSS_mul_gf2n(mul_coef,leading_coef,B);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<db;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,B+i*GEMSS_NB_WORD_GFqn);
            res+=GEMSS_NB_WORD_GFqn;
            GEMSS_add2_gf2n(res,mul_coef);
        }

        /* The leading term becomes 0 */

        /* useless because every coefficients >= db will be never used */
        /* GEMSS_set0_gf2n(leading_coef); */
        --da;
    }

    /* Here, da=db-1 */
    while(GEMSS_is0_gf2n(A+da*GEMSS_NB_WORD_GFqn)&&da)
    {
        --da;
    }

    /* Degree of the remainder */
    return da;
}


/**
 * @brief   Remainder of the Euclidean division in GF(2^n)[X], in-place.
 * @details A = B*Q + R.
 * @param[in,out]    A   An element of GF(2^n)[X], becomes R at the end.
 * @param[in]   da  The degree of A is at most da.
 * @param[in]   B   A monic polynomial in GF(2^n)[X].
 * @param[in]   db  The degree of B.
 * @remark  Requirement: B is monic.
 * @remark  Requirement: db>0.
 * @remark  Constant-time implementation when da and db are not secret.
 */
void GEMSS_PREFIX_NAME(GEMSS_div_r_monic_cst_gf2nx)(gf2nx A, unsigned int da,
                                    cst_gf2nx B, unsigned int db)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n res;
    unsigned int i;

    /* Pointer on the current leading term of A */
    A+=da*GEMSS_NB_WORD_GFqn;

    for(;da>=db;--da)
    {
        res=A-db*GEMSS_NB_WORD_GFqn;

        for(i=0;i<db;++i)
        {
            GEMSS_mul_gf2n(mul_coef,A,B+i*GEMSS_NB_WORD_GFqn);
            GEMSS_add2_gf2n(res,mul_coef);
            res+=GEMSS_NB_WORD_GFqn;
        }

        /* useless because every coefficients >= db will be never used */
        /* GEMSS_set0_gf2n(leading_coef); */

        A-=GEMSS_NB_WORD_GFqn;
    }
}


/**
 * @brief   Remainder of the Euclidean division by a GEMSS_HFE polynomial in 
 * GF(2^n)[X], in-place.
 * @details poly = (F.poly-cst)*Q + R.
 * @param[in,out]    poly    An element of GF(2^n)[X], becomes R at the end.
 * @param[in]   dp  The degree of poly is at most dp.
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   cst An element of GF(2^n).
 * @return  The degree of R.
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  This implementation is not in constant-time.
 */
unsigned int GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_gf2nx)(gf2nx poly, unsigned int dp,
                                          const complete_sparse_monic_gf2nx F,
                                          cst_gf2n cst)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i;

    const unsigned int* L=F.L;

    while(dp>=GEMSS_HFEDeg)
    {
        /* Search the current degree of poly */
        while(GEMSS_is0_gf2n(poly+dp*GEMSS_NB_WORD_GFqn)&&(dp>=GEMSS_HFEDeg))
        {
            --dp;
        }

        if(dp<GEMSS_HFEDeg)
        {
            /* The computation of the remainder is finished */
            break;
        }

        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }

        /* The leading term becomes 0 */

        /* useless because every coefficients >= dp will be never used */
        /* GEMSS_set0_gf2n(leading_coef); */
        --dp;
    }

    /* Here, dp=GEMSS_HFEDeg-1 */
    while(GEMSS_is0_gf2n(poly+dp*GEMSS_NB_WORD_GFqn)&&dp)
    {
        --dp;
    }

    /* Degree of the remainder */
    return dp;
}


/**
 * @brief   Remainder of the Euclidean division by a GEMSS_HFE polynomial in 
 * GF(2^n)[X], in-place.
 * @details poly = (F.poly-cst)*Q + R.
 * @param[in,out]    poly    An element of GF(2^n)[X], becomes R at the end.
 * @param[in]   dp  The degree of poly is at most dp.
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   cst An element of GF(2^n).
 * @return  The degree of R.
 * @remark  Requires to allocate dp+1 elements of GF(2^n) for poly
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation when dp is not secret.
 */
void GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
                                         const complete_sparse_monic_gf2nx F,
                                         cst_gf2n cst)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i;

    const unsigned int* L=F.L;

    for(;dp>=GEMSS_HFEDeg;--dp)
    {
        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }
    }
}


/**
 * @brief   Remainder of the Euclidean division by a GEMSS_HFE polynomial in 
 * GF(2^n)[X], in-place.
 * @details poly = (F.poly-cst)*Q + R.
 * @param[in,out]    poly    An element of GF(2^n)[X], becomes R at the end.
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   cst An element of GF(2^n).
 * @return  The degree of R.
 * @remark  Requires to allocate 2*GEMSS_HFEDeg-1 elements of GF(2^n) for poly.
 * @remark  Requirement: The degree of poly is at most 2*(GEMSS_HFEDeg-1).
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cst_gf2nx)(gf2nx poly,
                                      const complete_sparse_monic_gf2nx F,
                                      cst_gf2n cst)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i,dp;

    const unsigned int* L=F.L;

    for(dp=(GEMSS_HFEDeg-1)<<1;dp>=GEMSS_HFEDeg;--dp)
    {
        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }
    }
}


#if GEMSS_ENABLED_REMOVE_ODD_DEGREE
/**
 * @brief   Remainder of the Euclidean division by a GEMSS_HFE polynomial in 
 * GF(2^n)[X], in-place.
 * @details poly = (F.poly-cst)*Q + R.
 * @param[in,out]    poly    A square in GF(2^n)[X], becomes R at the end.
 * @param[in]   dp  The degree of poly is at most dp, must be even.
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   cst An element of GF(2^n).
 * @return  The degree of R.
 * @remark  Requires to allocate dp+1 elements of GF(2^n) for poly
 * @remark  Requirement: dp is even.
 * @remark  Requirement: poly is a square.
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation when dp is not secret.
 */
void GEMSS_PREFIX_NAME(GEMSS_divsqr_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
                                           const complete_sparse_monic_gf2nx F,
                                           cst_gf2n cst)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i;

    const unsigned int* L=F.L;

    for(;dp>(GEMSS_HFEDeg+GEMSS_HFE_odd_degree);dp-=2)
    {
        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }
    }

    for(;dp>=GEMSS_HFEDeg;--dp)
    {
        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }
    }
}


/**
 * @brief   Remainder of the Euclidean division by a GEMSS_HFE polynomial in 
 * GF(2^n)[X], in-place.
 * @details poly = (F.poly-cst)*Q + R.
 * @param[in,out]    poly    A square in GF(2^n)[X], becomes R at the end.
 * @param[in]   F   A GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse rep.
 * @param[in]   cst An element of GF(2^n).
 * @return  The degree of R.
 * @remark  Requires to allocate 2*GEMSS_HFEDeg-1 elements of GF(2^n) for poly.
 * @remark  Requirement: The degree of poly is at most 2*(GEMSS_HFEDeg-1).
 * @remark  Requirement: poly is a square.
 * @remark  Requirement: F is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_divsqr_r_HFE_cst_gf2nx)(gf2nx poly,
                                         const complete_sparse_monic_gf2nx F,
                                         cst_gf2n cst)
{
    static_gf2n mul_coef[GEMSS_NB_WORD_GFqn];
    gf2n leading_coef,res;
    unsigned int i,dp;

    const unsigned int* L=F.L;

    for(dp=(GEMSS_HFEDeg-1)<<1;dp>(GEMSS_HFEDeg+GEMSS_HFE_odd_degree);dp-=2)
    {
        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }
    }

    /* Here, dp=GEMSS_HFEDeg+GEMSS_HFE_odd_degree-1 */
    for(;dp>=GEMSS_HFEDeg;--dp)
    {
        leading_coef=poly+dp*GEMSS_NB_WORD_GFqn;
        res=leading_coef-GEMSS_HFEDeg*GEMSS_NB_WORD_GFqn;
        /* i=0: Constant of F-U */
        GEMSS_mul_gf2n(mul_coef,leading_coef,cst);
        GEMSS_add2_gf2n(res,mul_coef);

        for(i=1;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            GEMSS_mul_gf2n(mul_coef,leading_coef,F.poly+i*GEMSS_NB_WORD_GFqn);
            res+=L[i];
            GEMSS_add2_gf2n(res,mul_coef);
        }
    }
}
#endif


