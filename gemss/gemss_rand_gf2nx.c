#include "gemss_rand_gf2nx.h"
#include "gemss_randombytes.h"
#include "gemss_tools_gf2n.h"


/**
 * @brief   Generate a random monic d-degree polynomial in GF(2^n))[X].
 * @param[in]   d   The degree of F.
 * @param[out]  F   A random monic polynomial of GF(2^n)[X].
 * @remark  Requires to allocate d+1 elements of GF(2^n) for F.
 * @remark  Constant-time implementation when GEMSS_randombytes is constant-time and 
 * d is not secret.
 */
void GEMSS_PREFIX_NAME(GEMSS_randMonic_gf2nx)(gf2nx F, unsigned int d)
{
    /* Random generation of each coefficient excepted for the leading term */
    GEMSS_randombytes((unsigned char*)F,(d*GEMSS_NB_WORD_GFqn)<<3);
    /* The leading term is 1 */
    GEMSS_set1_gf2n(F+d*GEMSS_NB_WORD_GFqn);

    /* Clean the last word of each element of GF(2^n) */
    #if GEMSS_HFEnr
        unsigned int i;
        F-=1;
        for(i=0;i<d;++i)
        {
            F+=GEMSS_NB_WORD_GFqn;
            *F&=GEMSS_MASK_GF2n;
        }
    #endif
}


#if GEMSS_HFEnr
    void GEMSS_PREFIX_NAME(GEMSS_cleanMonicHFE_gf2nx)(sparse_monic_gf2nx F)
    {
        cst_sparse_monic_gf2nx F_end;

        /* zero padding for the last word of each element of GF(2^n) */
        F_end=F+GEMSS_NB_UINT_HFEPOLY;
        for(F+=GEMSS_NB_WORD_GFqn-1;F<F_end;F+=GEMSS_NB_WORD_GFqn)
        {
            *F&=GEMSS_MASK_GF2n;
        }
    }
#endif


/**
 * @brief   Generate a random monic D-degree GEMSS_HFE polynomial in GF(2^n))[X].
 * @param[out]  F   A random monic GEMSS_HFE polynomial of GF(2^n)[X].
 * @remark  Requires to allocate GEMSS_NB_UINT_HFEPOLY words for F.
 * @remark  Constant-time implementation when GEMSS_randombytes is constant-time.
 */
void GEMSS_PREFIX_NAME(GEMSS_randMonicHFE_gf2nx)(sparse_monic_gf2nx F)
{
    /* Random generation of each coefficient excepted for the leading term */
    GEMSS_randombytes((unsigned char*)F,GEMSS_NB_UINT_HFEPOLY<<3);
    /* The leading term is 1 and is not stored */

    /* Clean the last word of each element of GF(2^n) */
    #if GEMSS_HFEnr
        unsigned int i;
        F-=1;
        for(i=0;i<GEMSS_NB_COEFS_HFEPOLY;++i)
        {
            F+=GEMSS_NB_WORD_GFqn;
            *F&=GEMSS_MASK_GF2n;
        }
    #endif
}


#if GEMSS_HFEv
    #if GEMSS_HFEnr
        void GEMSS_PREFIX_NAME(GEMSS_cleanMonicHFEv_gf2nx)(sparse_monic_gf2nx F)
        {
            cst_sparse_monic_gf2nx F_end;

            /* zero padding for the last word of each element of GF(2^n) */
            F_end=F+GEMSS_NB_UINT_HFEVPOLY;
            for(F+=GEMSS_NB_WORD_GFqn-1;F<F_end;F+=GEMSS_NB_WORD_GFqn)
            {
                *F&=GEMSS_MASK_GF2n;
            }
        }
    #endif


/**
 * @brief   Generate a random monic D-degree GEMSS_HFEv polynomial in GF(2^n))[X].
 * @param[out]  F   A random monic GEMSS_HFEv polynomial of GF(2^n)[X].
 * @remark  Requires to allocate GEMSS_NB_UINT_HFEVPOLY words for F.
 * @remark  Constant-time implementation when GEMSS_randombytes is constant-time.
 */
void GEMSS_PREFIX_NAME(GEMSS_randMonicHFEv_gf2nx)(sparse_monic_gf2nx F)
{
    /* Random generation of each coefficient excepted for the leading term */
    GEMSS_randombytes((unsigned char*)F,GEMSS_NB_UINT_HFEVPOLY<<3);
    /* The leading term is 1 and is not stored */

    /* Clean the last word of each element of GF(2^n) */
    #if GEMSS_HFEnr
        unsigned int i;
        --F;
        for(i=0;i<GEMSS_NB_COEFS_HFEVPOLY;++i)
        {
            F+=GEMSS_NB_WORD_GFqn;
            *F&=GEMSS_MASK_GF2n;
        }
    #endif
}
#endif

