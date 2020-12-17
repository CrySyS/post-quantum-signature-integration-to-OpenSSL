#include "gemss_mul_gf2n.h"
#include "gemss_rem_gf2n.h"
#include "gemss_arch.h"
#include "gemss_simd.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"


/**
 * @brief   Multiplication in GF(2)[x].
 * @param[in]   A   An element of GF(2^n).
 * @param[in]   B   An element of GF(2^n).
 * @param[out]  C   C=A*B in GF(2)[x] (the result is not reduced).
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_mul_no_simd_gf2x_ref)(uint64_t C[GEMSS_NB_WORD_MUL],
                                       const uint64_t A[GEMSS_NB_WORD_GFqn],
                                       const uint64_t B[GEMSS_NB_WORD_GFqn])
{
    uint64_t mask_B,tmp_A;
    unsigned int i,j,k,jc;

    for(i=0;i<GEMSS_NB_WORD_MUL;++i)
    {
        C[i]=0;
    }

    for(i=0;i<GEMSS_HFEnq;++i)
    {
        /* j=0 */
        mask_B=-((*B)&GEMSS_ONE64);
        for(k=0;k<GEMSS_NB_WORD_GFqn;++k)
        {
            C[k]^=A[k]&mask_B;
        }

        #if GEMSS_HFEnr
            /* The last 64-bit block BL of A contains GEMSS_HFEnr bits.
               So, there is not overflow for BL<<j while j<=(64-GEMSS_HFEnr). */
            for(j=1;j<=(64-GEMSS_HFEnr);++j)
            {
                jc=64-j;
                mask_B=-(((*B)>>j)&GEMSS_ONE64);
                /* k=0 */
                tmp_A=(*A)&mask_B;
                C[0]^=tmp_A<<j;
                for(k=1;k<GEMSS_NB_WORD_GFqn;++k)
                {
                    C[k]^=tmp_A>>jc;
                    tmp_A=A[k]&mask_B;
                    C[k]^=tmp_A<<j;
                }
            }
        for(;j<64;++j)
        #else
        for(j=1;j<64;++j)
        #endif
        {
            jc=64-j;
            mask_B=-(((*B)>>j)&GEMSS_ONE64);
            /* k=0 */
            tmp_A=(*A)&mask_B;
            C[0]^=tmp_A<<j;
            for(k=1;k<GEMSS_NB_WORD_GFqn;++k)
            {
                C[k]^=tmp_A>>jc;
                tmp_A=A[k]&mask_B;
                C[k]^=tmp_A<<j;
            }
            /* "overflow" from the last 64-bit block of A */
            C[k]^=tmp_A>>jc;
        }

        ++B;
        ++C;
    }

    #if GEMSS_HFEnr
        /* j=0 */
        mask_B=-((*B)&GEMSS_ONE64);
        for(k=0;k<GEMSS_NB_WORD_GFqn;++k)
        {
            C[k]^=A[k]&mask_B;
        }

        /* The last 64-bit block BL of A contains GEMSS_HFEnr bits.
           So, there is not overflow for BL<<j while j<=(64-GEMSS_HFEnr). */
        #if (GEMSS_HFEnr>32)
        for(j=1;j<=(64-GEMSS_HFEnr);++j)
        #else
        for(j=1;j<GEMSS_HFEnr;++j)
        #endif
        {
            jc=64-j;
            mask_B=-(((*B)>>j)&GEMSS_ONE64);
            /* k=0 */
            tmp_A=(*A)&mask_B;
            C[0]^=tmp_A<<j;
            for(k=1;k<GEMSS_NB_WORD_GFqn;++k)
            {
                C[k]^=tmp_A>>jc;
                tmp_A=A[k]&mask_B;
                C[k]^=tmp_A<<j;
            }
        }

        #if (GEMSS_HFEnr>32)
            for(;j<GEMSS_HFEnr;++j)
            {
                jc=64-j;
                mask_B=-(((*B)>>j)&GEMSS_ONE64);
                /* k=0 */
                tmp_A=(*A)&mask_B;
                C[0]^=tmp_A<<j;
                for(k=1;k<GEMSS_NB_WORD_GFqn;++k)
                {
                    C[k]^=tmp_A>>jc;
                    tmp_A=A[k]&mask_B;
                    C[k]^=tmp_A<<j;
                }
                /* "overflow" from the last 64-bit block of A */
                C[k]^=tmp_A>>jc;
            }
        #endif
    #endif
}


/***********************************************************************/
/***********************************************************************/
/************************* mul then rem version ************************/
/***********************************************************************/
/***********************************************************************/


/* When rem is a macro */
#if (GEMSS_K3!=1)
    #define GEMSS_MUL_MOD_MACRO32(name_function,mul_function,GEMSS_rem_function) \
        name_function\
        {\
            uint64_t res_mul,Q,R;\
            mul_function;\
            GEMSS_rem_function;\
        }
#else
    #define GEMSS_MUL_MOD_MACRO32(name_function,mul_function,GEMSS_rem_function) \
        name_function\
        {\
            uint64_t res_mul,Q;\
            mul_function;\
            GEMSS_rem_function;\
        }
#endif

#define GEMSS_MUL_MOD_MACRO64(name_function,mul_function,GEMSS_rem_function,size) \
    name_function\
    {\
        uint64_t res_mul[size],Q,R;\
        mul_function;\
        GEMSS_rem_function;\
    }

/* GEMSS_HFEn == 64 */
#define GEMSS_MUL_MOD_MACRO64_K64(name_function,mul_function,GEMSS_rem_function,size) \
    name_function\
    {\
        uint64_t res_mul[size],R;\
        mul_function;\
        GEMSS_rem_function;\
    }


#if GEMSS_HFEnr
    #define GEMSS_INIT_Q(size2) uint64_t Q[size2];
#else
    /* Q is useless for REM */
    #define GEMSS_INIT_Q(size2)
#endif

#if ((GEMSS_HFEn==312)||(GEMSS_HFEn==402)||(GEMSS_HFEn==544))
    #define GEMSS_MUL_MOD_MACRO(name_function,mul_function,GEMSS_rem_function,size,size2) \
        name_function\
        {\
            uint64_t res_mul[size];\
            GEMSS_INIT_Q(size2);\
            mul_function;\
            GEMSS_rem_function;\
        }
#else
    #define GEMSS_MUL_MOD_MACRO(name_function,mul_function,GEMSS_rem_function,size,size2) \
        name_function\
        {\
            uint64_t res_mul[size],R;\
            GEMSS_INIT_Q(size2);\
            mul_function;\
            GEMSS_rem_function;\
        }
#endif

/* When rem is a function */
#define GEMSS_MUL_MOD_FUNCTION32(name_function,mul_function,GEMSS_rem_function) \
    name_function\
    {\
        uint64_t res_mul;\
        mul_function;\
        GEMSS_rem_function;\
    }

#define GEMSS_MUL_MOD_FUNCTION(name_function,mul_function,GEMSS_rem_function,size) \
    name_function\
    {\
        uint64_t res_mul[size];\
        mul_function;\
        GEMSS_rem_function;\
    }

#if (GEMSS_REM_MACRO)
    #if (GEMSS_NB_WORD_GFqn!=1)
        GEMSS_MUL_MOD_MACRO(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(res_mul,A,B),
                      GEMSS_REM_GF2N(res,res_mul,Q,R),GEMSS_NB_WORD_MUL,GEMSS_NB_WORD_GFqn);
    #elif (GEMSS_HFEn<33)
        GEMSS_MUL_MOD_MACRO32(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(&res_mul,A,B),
                        GEMSS_REM_GF2N(*res,res_mul,Q,R));
    #elif GEMSS_HFEnr
        GEMSS_MUL_MOD_MACRO64(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(res_mul,A,B),
                        GEMSS_REM_GF2N(*res,res_mul,Q,R),GEMSS_NB_WORD_MUL);
    #else
        /* GEMSS_HFEn == 64 */
        GEMSS_MUL_MOD_MACRO64_K64(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(res_mul,A,B),
                            GEMSS_REM_GF2N(*res,res_mul,,R),GEMSS_NB_WORD_MUL);
    #endif
#elif (GEMSS_NB_WORD_GFqn!=1)
    GEMSS_MUL_MOD_FUNCTION(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(res_mul,A,B),
                     GEMSS_rem_gf2n(res,res_mul),GEMSS_NB_WORD_MUL);
#elif (GEMSS_HFEn<33)
    GEMSS_MUL_MOD_FUNCTION32(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(&res_mul,A,B),
                       GEMSS_rem_gf2n(res,&res_mul));
#else
    GEMSS_MUL_MOD_FUNCTION(GEMSS_MUL_THEN_REM_GF2N,GEMSS_mul_gf2x(res_mul,A,B),
                     GEMSS_rem_gf2n(res,res_mul),GEMSS_NB_WORD_MUL);
#endif


