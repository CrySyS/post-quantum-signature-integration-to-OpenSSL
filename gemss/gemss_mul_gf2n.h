#ifndef _MUL_GF2N_H
#define _MUL_GF2N_H

#include "gemss_mul_gf2x.h"
/* Really important include for the definition of 
   GEMSS___TRINOMIAL_GF2N__ and GEMSS___PENTANOMIAL_GF2N__ */
#include "gemss_rem_gf2n.h"
#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_macro.h"


/***********************************************************************/
/***********************************************************************/
/****** Mul in GF(2)[x] specialized in n-coefficients polynomials ******/
/***********************************************************************/
/***********************************************************************/


void GEMSS_PREFIX_NAME(GEMSS_mul_no_simd_gf2x_ref)(uint64_t C[GEMSS_NB_WORD_MUL],
                                       const uint64_t A[GEMSS_NB_WORD_GFqn],
                                       const uint64_t B[GEMSS_NB_WORD_GFqn]);
#define GEMSS_mul_no_simd_gf2x_ref GEMSS_PREFIX_NAME(GEMSS_mul_no_simd_gf2x_ref)


/***********************************************************************/
/***********************************************************************/
/********************** Choice of mul in GF(2)[x] **********************/
/***********************************************************************/
/***********************************************************************/


#define GEMSS_mul_no_simd_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(mul),_no_simd_gf2x)
#define GEMSS_pmul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(pmul),_gf2x)

#if (GEMSS_NB_WORD_GFqn==1)
    #define GEMSS_pclmul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(pclmul),_inlined_gf2x)
#else
    #define GEMSS_pclmul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(pclmul),_gf2x)
#endif

/* This macro is used only in GEMSS_inv_gf2n.c */
#define GEMSS_MUL_GF2X GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MUL_SUP(GEMSS_PCLMUL),_GF2X)


/* Choice of the multiplication in GF(2)[x] for the arithmetic in GF(2^n). */
#if (GEMSS_HFEn<33)
    /* The gf2x library has the priority when enabled. */
    #if GEMSS_ENABLED_GF2X&&defined(GEMSS_MODE_32_BITS)
        #define GEMSS_mul_gf2x(C,A,B) GEMSS_best_mul32_gf2x(C,A,B);
    #elif GEMSS_ENABLED_GF2X
        #define GEMSS_mul_gf2x(C,A,B) (*(C))=GEMSS_best_mul32_gf2x(*(A),*(B));
    #elif defined(GEMSS_MQSOFT_REF)
        #define GEMSS_mul_gf2x GEMSS_mul_no_simd_gf2x_ref
    #elif (!GEMSS_ENABLED_GF2X)&&(defined(GEMSS_ENABLED_PCLMUL))
        #define GEMSS_mul_gf2x(C,A,B) GEMSS_best_mul32_gf2x(*(C),*(A),*(B));
    #else
        #define GEMSS_mul_gf2x(C,A,B) (*(C))=GEMSS_best_mul32_gf2x(*(A),*(B));
    #endif
#else
    /* The gf2x library has the priority when enabled. */
    #if GEMSS_ENABLED_GF2X
        #define GEMSS_mul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MUL_SUP(GEMSS_best_mul),_gf2x)
    #elif defined(GEMSS_MQSOFT_REF)
        #define GEMSS_mul_gf2x GEMSS_mul_no_simd_gf2x_ref
    #else
        #define GEMSS_mul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MUL_SUP(GEMSS_best_mul),_gf2x)
    #endif
#endif


/***********************************************************************/
/***********************************************************************/
/************************* mul then rem version ************************/
/***********************************************************************/
/***********************************************************************/


/* Function mul in GF(2^x), then modular reduction */
#define GEMSS_MUL_THEN_REM_GF2N void \
            GEMSS_PREFIX_NAME(GEMSS_mul_then_rem_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn], \
                                    const uint64_t A[GEMSS_NB_WORD_GFqn], \
                                    const uint64_t B[GEMSS_NB_WORD_GFqn])
GEMSS_MUL_THEN_REM_GF2N;
#define GEMSS_mul_then_rem_gf2n GEMSS_PREFIX_NAME(GEMSS_mul_then_rem_gf2n)


/***********************************************************************/
/***********************************************************************/
/********************** Choice of mul in GF(2^n) ***********************/
/***********************************************************************/
/***********************************************************************/


/* Choice the best GEMSS_mul_gf2n */
#if (GEMSS_ENABLED_GF2X||defined(GEMSS_MQSOFT_REF))
    /* The gf2x library has the priority when enabled.
       In this case, the chosen muliplication is not necessarily the fastest. */
    #define GEMSS_mul_gf2n GEMSS_mul_then_rem_gf2n
#elif (GEMSS_HFEn<33)
    #define GEMSS_mul_gf2n GEMSS_mul_then_rem_gf2n
#else
    #define GEMSS_mul_gf2n GEMSS_mul_then_rem_gf2n
#endif



#endif

