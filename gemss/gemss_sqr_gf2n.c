#include "gemss_sqr_gf2n.h"
#include "gemss_rem_gf2n.h"
#include "gemss_arch.h"
#include "gemss_simd.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"


/***********************************************************************/
/***********************************************************************/
/*************************** sqr without rem ***************************/
/***********************************************************************/
/***********************************************************************/


/**
 * @brief   Squaring in GF(2)[x].
 * @details For each 32-bit block on the input, we use the following strategy:
   Assume we want to insert a null bit between each bit of 0x00000000FFFFFFFF.
   We do as following:
    0x00000000FFFFFFFF (it is already an insertion of a zero 32-bit packed)
    0x0000FFFF0000FFFF (insertion by pack of 16 bits)
    0x00FF00FF00FF00FF (insertion by pack of 8 bits)
    0x0F0F0F0F0F0F0F0F (insertion by pack of 4 bits)
    0x3333333333333333 (insertion by pack of 2 bits)
    0x5555555555555555 (insertion by pack of 1 bit).
 * @param[in]   A   An element of GF(2^n).
 * @param[out]  C   C=A*A in GF(2)[x] (the result is not reduced).
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_sqr_no_simd_gf2x_ref2)(static_gf2x C[GEMSS_NB_WORD_MUL],
                                        cst_static_gf2n A[GEMSS_NB_WORD_GFqn])
{
    uint64_t Ci;
    unsigned int i;

    C+=GEMSS_NB_WORD_MUL-1;
    #if (GEMSS_NB_WORD_MUL&1)
        i=GEMSS_NB_WORD_GFqn-1;
        /* Lower 32 bits of A[i] */
        Ci=(A[i]^(A[i]<<16))&((uint64_t)0x0000FFFF0000FFFF);
        Ci=(Ci^(Ci<<8))&((uint64_t)0x00FF00FF00FF00FF);
        Ci=(Ci^(Ci<<4))&((uint64_t)0x0F0F0F0F0F0F0F0F);
        Ci=(Ci^(Ci<<2))&((uint64_t)0x3333333333333333);
        Ci=(Ci^(Ci<<1))&((uint64_t)0x5555555555555555);
        *C=Ci;
        --C;
    for(i=GEMSS_NB_WORD_GFqn-2;i!=(unsigned int)(-1);--i)
    #else
    for(i=GEMSS_NB_WORD_GFqn-1;i!=(unsigned int)(-1);--i)
    #endif
    {
        /* Higher 32 bits of A[i] */
        Ci=((A[i]>>32)^((A[i]>>32)<<16))&((uint64_t)0x0000FFFF0000FFFF);
        Ci=(Ci^(Ci<<8))&((uint64_t)0x00FF00FF00FF00FF);
        Ci=(Ci^(Ci<<4))&((uint64_t)0x0F0F0F0F0F0F0F0F);
        Ci=(Ci^(Ci<<2))&((uint64_t)0x3333333333333333);
        Ci=(Ci^(Ci<<1))&((uint64_t)0x5555555555555555);
        *C=Ci;
        --C;

        /* Lower 32 bits of A[i] */
        Ci=((A[i]&((uint64_t)0xFFFFFFFF))^(A[i]<<16))
           &((uint64_t)0x0000FFFF0000FFFF);
        Ci=(Ci^(Ci<<8))&((uint64_t)0x00FF00FF00FF00FF);
        Ci=(Ci^(Ci<<4))&((uint64_t)0x0F0F0F0F0F0F0F0F);
        Ci=(Ci^(Ci<<2))&((uint64_t)0x3333333333333333);
        Ci=(Ci^(Ci<<1))&((uint64_t)0x5555555555555555);
        *C=Ci;
        --C;
    }
}


/***********************************************************************/
/***********************************************************************/
/***************************** sqr with rem ****************************/
/***********************************************************************/
/***********************************************************************/


/***********************************************************************/
/***********************************************************************/
/************************* sqr then rem version ************************/
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
        GEMSS_MUL_MOD_MACRO(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(res_mul,A),
                      GEMSS_REM_GF2N(res,res_mul,Q,R),GEMSS_NB_WORD_MUL,GEMSS_NB_WORD_GFqn);
        GEMSS_MUL_MOD_MACRO(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(res_mul,A),
                      GEMSS_REM_GF2N(res,res_mul,Q,R),GEMSS_NB_WORD_MUL,GEMSS_NB_WORD_GFqn);
    #elif (GEMSS_HFEn<33)
        GEMSS_MUL_MOD_MACRO32(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(&res_mul,A),
                        GEMSS_REM_GF2N(*res,res_mul,Q,R));
        GEMSS_MUL_MOD_MACRO32(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(&res_mul,A),
                        GEMSS_REM_GF2N(*res,res_mul,Q,R));
    #elif GEMSS_HFEnr
        GEMSS_MUL_MOD_MACRO64(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(res_mul,A),
                        GEMSS_REM_GF2N(*res,res_mul,Q,R),GEMSS_NB_WORD_MUL);
        GEMSS_MUL_MOD_MACRO64(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(res_mul,A),
                        GEMSS_REM_GF2N(*res,res_mul,Q,R),GEMSS_NB_WORD_MUL);
    #else
        /* GEMSS_HFEn == 64 */
        GEMSS_MUL_MOD_MACRO64_K64(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(res_mul,A),
                            GEMSS_REM_GF2N(*res,res_mul,,R),GEMSS_NB_WORD_MUL);
        GEMSS_MUL_MOD_MACRO64_K64(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(res_mul,A),
                            GEMSS_REM_GF2N(*res,res_mul,,R),GEMSS_NB_WORD_MUL);
    #endif
#elif (GEMSS_NB_WORD_GFqn!=1)
    GEMSS_MUL_MOD_FUNCTION(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(res_mul,A),
                     GEMSS_remsqr_gf2n(res,res_mul),GEMSS_NB_WORD_MUL);
    GEMSS_MUL_MOD_FUNCTION(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(res_mul,A),
                     GEMSS_remsqr_gf2n(res,res_mul),GEMSS_NB_WORD_MUL);
#elif (GEMSS_HFEn<33)
    GEMSS_MUL_MOD_FUNCTION32(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(&res_mul,A),
                       GEMSS_remsqr_gf2n(res,&res_mul));
    GEMSS_MUL_MOD_FUNCTION32(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(&res_mul,A),
                       GEMSS_remsqr_gf2n(res,&res_mul));
#else
    GEMSS_MUL_MOD_FUNCTION(GEMSS_SQR_THEN_REM_GF2N,GEMSS_sqr_gf2x(res_mul,A),
                     GEMSS_remsqr_gf2n(res,res_mul),GEMSS_NB_WORD_MUL);
    GEMSS_MUL_MOD_FUNCTION(GEMSS_SQR_NOCST_THEN_REM_GF2N,GEMSS_sqr_nocst_gf2x(res_mul,A),
                     GEMSS_remsqr_gf2n(res,res_mul),GEMSS_NB_WORD_MUL);
#endif


