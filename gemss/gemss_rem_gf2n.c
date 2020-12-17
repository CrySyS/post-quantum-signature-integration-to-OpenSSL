#include "gemss_rem_gf2n.h"
#include "gemss_rem_gf2x.h"
#include "gemss_simd.h"


/***********************************************************************/
/***********************************************************************/
/************************ Without SIMD version *************************/
/***********************************************************************/
/***********************************************************************/


/**
 * @brief   Reduction in GF(2^n) of a (2n-1)-coefficients polynomial in
 * GF(2)[x].
 * @param[in]   Pol A (2n-1)-coefficients polynomial in GF(2)[x].
 * @param[out]  P   P is Pol reduced in GF(2^n).
 * @remark  Requirement: the n-degree irreducible polynomial defining GF(2^n)
 * must be a trinomial or a pentanomial.
 * @remark  Constant-time implementation.
 * @todo    >>6 and &63 are not generic for the UINT type.
 */
void GEMSS_PREFIX_NAME(GEMSS_rem_gf2n_ref)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                               cst_static_gf2x Pol[GEMSS_NB_WORD_MUL])
{
    static_gf2x res[GEMSS_NB_WORD_MUL];
    UINT bit_i;
    unsigned int i,ind;

    for(i=0;i<GEMSS_NB_WORD_MUL;++i)
    {
        res[i]=Pol[i];
    }

    for(i=(GEMSS_HFEn-1)<<1;i>=GEMSS_HFEn;--i)
    {
        /* Extraction of bit_i x^i */
        bit_i=(res[i>>6]>>(i&63))&GEMSS_UINT_1;
        /* x^n = 1 + ... */
        ind=i-GEMSS_HFEn;
        res[ind>>6]^=bit_i<<(ind&63);
        #ifdef GEMSS___PENTANOMIAL_GF2N__
            /* ... + x^GEMSS_K1 + ... */
            ind=i-GEMSS_HFEn+GEMSS_K1;
            res[ind>>6]^=bit_i<<(ind&63);
            /* ... + x^GEMSS_K2 + ... */
            ind=i-GEMSS_HFEn+GEMSS_K2;
            res[ind>>6]^=bit_i<<(ind&63);
        #endif
        /* ... + x^GEMSS_K3 */
        ind=i-GEMSS_HFEn+GEMSS_K3;
        res[ind>>6]^=bit_i<<(ind&63);
    }

    for(i=0;i<GEMSS_NB_WORD_GFqn;++i)
    {
        P[i]=res[i];
    }

    #if GEMSS_HFEnr
        P[GEMSS_NB_WORD_GFqn-1]&=GEMSS_MASK_GF2n;
    #endif
}


#if ((GEMSS_K3<33) || (defined(GEMSS___TRINOMIAL_GF2N__)&&\
           (((GEMSS_HFEn==265)&&(GEMSS_K3==42)) || ((GEMSS_HFEn==266)&&(GEMSS_K3==47))\
         || ((GEMSS_HFEn==354)&&(GEMSS_K3==99)) || ((GEMSS_HFEn==358)&&(GEMSS_K3==57)))))
/**
 * @brief   Reduction in GF(2^n) of a (2n-1)-coefficients polynomial in
 * GF(2)[x].
 * @param[in]   Pol A (2n-1)-coefficients polynomial in GF(2)[x].
 * @param[out]  P   P is Pol reduced in GF(2^n).
 * @remark  Requirement: the n-degree irreducible polynomial defining GF(2^n)
 * must be a trinomial or a pentanomial.
 * @remark  Requirement: GEMSS_K3<33, or (n,GEMSS_K3) in {(265,42),(266,47),(354,99),
 * (358,57)}.
 * @remark  Requirement: GEMSS_K1<GEMSS_K2<33.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_rem_gf2n_ref2)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                cst_static_gf2x Pol[GEMSS_NB_WORD_MUL])
{
    uint64_t R;
    unsigned int i;


    #if GEMSS_KI
        static_gf2x Q[GEMSS_NB_WORD_GFqn];

        /* Q: Quotient of Pol/x^n, by word of 64-bit */
        for(i=GEMSS_NB_WORD_GFqn;i<GEMSS_NB_WORD_MMUL;++i)
        {
            Q[i-GEMSS_NB_WORD_GFqn]=(Pol[i-1]>>GEMSS_KI)^(Pol[i]<<GEMSS_KI64);
        }
        #if (GEMSS_NB_WORD_MMUL&1)
            Q[i-GEMSS_NB_WORD_GFqn]=Pol[i-1]>>GEMSS_KI;
        #endif

        #if ((GEMSS_HFEn==354)&&(GEMSS_K3==99))
            R=(Q[3]>>(GEMSS_K364+GEMSS_KI))^(Q[4]<<(GEMSS_K3mod64-GEMSS_KI));
            Q[0]^=R;
            Q[1]^=(Q[4]>>(GEMSS_K364+GEMSS_KI))^(Q[5]<<(GEMSS_K3mod64-GEMSS_KI));
        #elif ((GEMSS_HFEn==358)&&(GEMSS_K3==57))
            /* R: Quotient of Pol/x^(2n-GEMSS_K3), by word of 64-bit */
            R=(Q[4]>>(GEMSS_K364+GEMSS_KI))^(Q[5]<<(GEMSS_K3-GEMSS_KI));
            Q[0]^=R;
        #endif

        for(i=0;i<GEMSS_NB_WORD_GFqn;++i)
        {
            P[i]=Pol[i]^Q[i];
        }

        #ifdef GEMSS___PENTANOMIAL_GF2N__
            P[0]^=Q[0]<<GEMSS_K1;
            for(i=1;i<GEMSS_NB_WORD_GFqn;++i)
            {
                P[i]^=(Q[i-1]>>GEMSS_K164)^(Q[i]<<GEMSS_K1);
            }

            P[0]^=Q[0]<<GEMSS_K2;
            for(i=1;i<GEMSS_NB_WORD_GFqn;++i)
            {
                P[i]^=(Q[i-1]>>GEMSS_K264)^(Q[i]<<GEMSS_K2);
            }
        #endif

        #if ((GEMSS_HFEn==354)&&(GEMSS_K3==99))
            P[1]^=Q[0]<<GEMSS_K3mod64;
            P[2]^=(Q[0]>>GEMSS_K364)^(Q[1]<<GEMSS_K3mod64);
            P[3]^=(Q[1]>>GEMSS_K364)^(Q[2]<<GEMSS_K3mod64);
            P[4]^=(Q[2]>>GEMSS_K364)^(Q[3]<<GEMSS_K3mod64);
            P[5]^=Q[3]>>GEMSS_K364;
        #else
            P[0]^=Q[0]<<GEMSS_K3mod64;
            for(i=1;i<GEMSS_NB_WORD_GFqn;++i)
            {
                P[i]^=(Q[i-1]>>GEMSS_K364)^(Q[i]<<GEMSS_K3mod64);
            }
        #endif

        #if ((GEMSS_K3!=1) && (!((GEMSS_HFEn==354)&&(GEMSS_K3==99)))\
                     && (!((GEMSS_HFEn==358)&&(GEMSS_K3==57))))
            /* R: Quotient of Pol/x^(2n-GEMSS_K3), by word of 64-bit */
            #if (GEMSS_KI>=GEMSS_K3)
                R=Q[GEMSS_NB_WORD_GFqn-1]>>(GEMSS_KI-GEMSS_K3mod64);
            #else
                R=(Q[GEMSS_NB_WORD_GFqn-2]>>(GEMSS_K364+GEMSS_KI))
                 ^(Q[GEMSS_NB_WORD_GFqn-1]<<(GEMSS_K3mod64-GEMSS_KI));
            #endif

            #ifdef GEMSS___PENTANOMIAL_GF2N__
                #if (GEMSS_KI>=GEMSS_K2)
                    R^=Q[GEMSS_NB_WORD_GFqn-1]>>(GEMSS_KI-GEMSS_K2);
                #else
                    R^=(Q[GEMSS_NB_WORD_GFqn-2]>>(GEMSS_K264+GEMSS_KI))
                      ^(Q[GEMSS_NB_WORD_GFqn-1]<<(GEMSS_K2-GEMSS_KI));
                #endif

                #if(GEMSS_K1!=1)
                    #if (GEMSS_KI>=GEMSS_K1)
                        R^=Q[GEMSS_NB_WORD_GFqn-1]>>(GEMSS_KI-GEMSS_K1);
                    #else
                        R^=(Q[GEMSS_NB_WORD_GFqn-2]>>(GEMSS_K164+GEMSS_KI))
                          ^(Q[GEMSS_NB_WORD_GFqn-1]<<(GEMSS_K1-GEMSS_KI));
                    #endif
                #endif
            #endif

            P[0]^=R;
            #ifdef GEMSS___PENTANOMIAL_GF2N__
                P[0]^=R<<GEMSS_K1;
                P[0]^=R<<GEMSS_K2;
            #endif
            P[0]^=R<<GEMSS_K3mod64;
            #if (GEMSS_K3>32)
                (P)[1]^=R>>GEMSS_K364;
            #endif
        #endif
        P[GEMSS_NB_WORD_GFqn-1]&=GEMSS_MASK_GF2n;
    #else
        for(i=0;i<GEMSS_NB_WORD_GFqn;++i)
        {
            P[i]=Pol[i]^Pol[i+GEMSS_NB_WORD_GFqn];
        }

        #ifdef GEMSS___PENTANOMIAL_GF2N__
            P[0]^=Pol[GEMSS_NB_WORD_GFqn]<<GEMSS_K1;
            for(i=GEMSS_NB_WORD_GFqn+1;i<(GEMSS_NB_WORD_GFqn<<1);++i)
            {
                P[i-GEMSS_NB_WORD_GFqn]^=(Pol[i-1]>>GEMSS_K164)^(Pol[i]<<GEMSS_K1);
            }

            P[0]^=Pol[GEMSS_NB_WORD_GFqn]<<GEMSS_K2;
            for(i=GEMSS_NB_WORD_GFqn+1;i<(GEMSS_NB_WORD_GFqn<<1);++i)
            {
                P[i-GEMSS_NB_WORD_GFqn]^=(Pol[i-1]>>GEMSS_K264)^(Pol[i]<<GEMSS_K2);
            }
        #endif

        P[0]^=Pol[GEMSS_NB_WORD_GFqn]<<GEMSS_K3;
        for(i=GEMSS_NB_WORD_GFqn+1;i<(GEMSS_NB_WORD_GFqn<<1);++i)
        {
            P[i-GEMSS_NB_WORD_GFqn]^=(Pol[i-1]>>GEMSS_K364)^(Pol[i]<<GEMSS_K3);
        }

        R=Pol[(GEMSS_NB_WORD_GFqn<<1)-1]>>GEMSS_K364;
        #ifdef GEMSS___PENTANOMIAL_GF2N__
            R^=Pol[(GEMSS_NB_WORD_GFqn<<1)-1]>>GEMSS_K264;
            #if(GEMSS_K1!=1)
                R^=Pol[(GEMSS_NB_WORD_GFqn<<1)-1]>>GEMSS_K164;
            #endif
        #endif

        P[0]^=R;
        #ifdef GEMSS___PENTANOMIAL_GF2N__
            P[0]^=R<<GEMSS_K1;
            P[0]^=R<<GEMSS_K2;
        #endif
        P[0]^=R<<GEMSS_K3;
    #endif
}
#endif


/**
 * @brief   Reduction in GF(2^n) of a (2n-1)-coefficients square in GF(2)[x].
 * @details The odd degree terms are assumed to be null, and so are not
 * considered.
 * @param[in]   Pol A (2n-1)-coefficients square in GF(2)[x].
 * @param[out]  P   P is Pol reduced in GF(2^n).
 * @remark  Requirement: the odd degree terms of Pol are null.
 * @remark  Requirement: the n-degree irreducible polynomial defining GF(2^n)
 * must be a trinomial or a pentanomial.
 * @remark  Constant-time implementation.
 * @todo    >>6 and &63 are not generic for the UINT type.
 */
void GEMSS_PREFIX_NAME(GEMSS_remsqr_gf2n_ref)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                  cst_static_gf2x Pol[GEMSS_NB_WORD_MUL])
{
    static_gf2x res[GEMSS_NB_WORD_MUL];
    UINT bit_i;
    unsigned int i,ind;

    for(i=0;i<GEMSS_NB_WORD_MUL;++i)
    {
        res[i]=Pol[i];
    }

    /* Only the even degree terms are not zero */
    #if (GEMSS_K3==1)
    for(i=(GEMSS_HFEn-1)<<1;i>=GEMSS_HFEn;i-=2)
    #elif ((GEMSS_HFEn-2+GEMSS_K3)&1)
    for(i=(GEMSS_HFEn-1)<<1;i>=(GEMSS_HFEn-1+GEMSS_K3);i-=2)
    #else
    for(i=(GEMSS_HFEn-1)<<1;i>=(GEMSS_HFEn-2+GEMSS_K3);i-=2)
    #endif
    {
        /* Extraction of bit_i x^i */
        bit_i=(res[i>>6]>>(i&63))&GEMSS_UINT_1;
        /* x^n = 1 + ... */
        ind=i-GEMSS_HFEn;
        res[ind>>6]^=bit_i<<(ind&63);
        #ifdef GEMSS___PENTANOMIAL_GF2N__
            /* ... + x^GEMSS_K1 + ... */
            ind=i-GEMSS_HFEn+GEMSS_K1;
            res[ind>>6]^=bit_i<<(ind&63);
            /* ... + x^GEMSS_K2 + ... */
            ind=i-GEMSS_HFEn+GEMSS_K2;
            res[ind>>6]^=bit_i<<(ind&63);
        #endif
        /* ... + x^GEMSS_K3 */
        ind=i-GEMSS_HFEn+GEMSS_K3;
        res[ind>>6]^=bit_i<<(ind&63);
    }

    #if (GEMSS_K3>1)
        for(++i;i>=GEMSS_HFEn;--i)
        {
            /* Extraction of bit_i x^i */
            bit_i=(res[i>>6]>>(i&63))&GEMSS_UINT_1;
            /* x^n = 1 + ... */
            ind=i-GEMSS_HFEn;
            res[ind>>6]^=bit_i<<(ind&63);
            #ifdef GEMSS___PENTANOMIAL_GF2N__
                /* ... + x^GEMSS_K1 + ... */
                ind=i-GEMSS_HFEn+GEMSS_K1;
                res[ind>>6]^=bit_i<<(ind&63);
                /* ... + x^GEMSS_K2 + ... */
                ind=i-GEMSS_HFEn+GEMSS_K2;
                res[ind>>6]^=bit_i<<(ind&63);
            #endif
            /* ... + x^GEMSS_K3 */
            ind=i-GEMSS_HFEn+GEMSS_K3;
            res[ind>>6]^=bit_i<<(ind&63);
        }
    #endif

    for(i=0;i<GEMSS_NB_WORD_GFqn;++i)
    {
        P[i]=res[i];
    }

    #if GEMSS_HFEnr
        P[GEMSS_NB_WORD_GFqn-1]&=GEMSS_MASK_GF2n;
    #endif
}


#if (GEMSS_HFEn<33)
    /* TODO: no generic for the UINT type. */
    UINT GEMSS_PREFIX_NAME(GEMSS_rem_no_simd_gf2n)(UINT Pol)
    {
        uint64_t P,Q;
        #if(GEMSS_K3!=1)
            uint64_t R;
        #endif
        GEMSS_REM_GF2N(P,Pol,Q,R);
        return P;
    }
#elif (GEMSS_NB_WORD_GFqn==1)
    /* TODO: no generic for the UINT type. */
    void GEMSS_PREFIX_NAME(GEMSS_rem_no_simd_gf2n)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                       cst_static_gf2x Pol[GEMSS_NB_WORD_MUL])
    {
        #if GEMSS_HFEnr
            uint64_t Q,R;
            GEMSS_REM_GF2N(*P,Pol,Q,R);
        #else
            /* GEMSS_HFEn == 64 */
            uint64_t R;
            GEMSS_REM_GF2N(*P,Pol,,R);
        #endif
    }
#else
    /* TODO: no generic for the UINT type. */
    void GEMSS_PREFIX_NAME(GEMSS_rem_no_simd_gf2n)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                       cst_static_gf2x Pol[GEMSS_NB_WORD_MUL])
    {
        #if GEMSS_HFEnr
            uint64_t Q[GEMSS_NB_WORD_GFqn];
            #if ((GEMSS_HFEn!=312)&&(GEMSS_HFEn!=402)&&(GEMSS_HFEn!=544))
                uint64_t R;
                GEMSS_REM_GF2N(P,Pol,Q,R);
            #else
                GEMSS_REM_GF2N(P,Pol,Q,);
            #endif
        #else
            uint64_t R;
            GEMSS_REM_GF2N(P,Pol,,R);
        #endif
    }
#endif


