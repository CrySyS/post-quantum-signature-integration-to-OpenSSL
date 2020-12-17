#ifndef _SQR_GF2N_H
#define _SQR_GF2N_H

#include "gemss_sqr_gf2x.h"
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
/********************** Choice of sqr in GF(2)[x] **********************/
/***********************************************************************/
/***********************************************************************/


void GEMSS_PREFIX_NAME(GEMSS_sqr_no_simd_gf2x_ref2)(static_gf2x C[GEMSS_NB_WORD_MUL],
                                        cst_static_gf2n A[GEMSS_NB_WORD_GFqn]);
#define GEMSS_sqr_no_simd_gf2x_ref2 GEMSS_PREFIX_NAME(GEMSS_sqr_no_simd_gf2x_ref2)


/* Here, we define the squaring functions in GF2[x] */
#if (GEMSS_HFEn<33)
    #define GEMSS_sqr_no_simd_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(sqr),_no_simd_gf2x)
#elif (GEMSS_NB_WORD_GFqn==1)
    #define GEMSS_sqr_no_simd_gf2x(C,A) GEMSS_SQR64_NO_SIMD_GF2X((C),(*(A)))
#else
    #define GEMSS_sqr_no_simd_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(SQR),_NO_SIMD_GF2X)
#endif
#define GEMSS_psqr_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(psqr),_gf2x)
#define GEMSS_psqr_shuffle_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(psqr),_shuffle_gf2x)
#define GEMSS_vpsqr_shuffle_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(vpsqr),_shuffle_gf2x)

#if (GEMSS_NB_WORD_GFqn==1)
    #define GEMSS_sqr_pclmul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(sqr),\
                                   _inlined_pclmul_gf2x)
#else
    #define GEMSS_sqr_pclmul_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(sqr),_pclmul_gf2x)
#endif



/* This macro is used only in GEMSS_inv_gf2n.c */
#define GEMSS_SQR_GF2X GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MUL_SUP(SQR),_PCLMUL_GF2X)



/* Choice of the squaring in GF(2)[x] for the arithmetic in GF(2^n). */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_sqr_gf2x GEMSS_sqr_no_simd_gf2x_ref2
    #define GEMSS_sqr_nocst_gf2x GEMSS_sqr_gf2x
#elif (GEMSS_HFEn<33)
    #ifdef GEMSS_ENABLED_PCLMUL
        #define GEMSS_sqr_nocst_gf2x(C,A) GEMSS_best_sqr_nocst_32_gf2x(*(C),*(A));
    #else
        #define GEMSS_sqr_nocst_gf2x(C,A) (*(C))=GEMSS_best_sqr_nocst_32_gf2x(*(A));
    #endif

    #if GEMSS_CONSTANT_TIME
        #ifdef GEMSS_ENABLED_PCLMUL
            #define GEMSS_sqr_gf2x(C,A) GEMSS_best_sqr32_gf2x(*(C),*(A));
        #else
            #define GEMSS_sqr_gf2x(C,A) (*(C))=GEMSS_best_sqr32_gf2x(*(A));
        #endif
    #else
        /* Faster */
        #define GEMSS_sqr_gf2x GEMSS_sqr_nocst_gf2x
    #endif
#else
    #define GEMSS_sqr_nocst_gf2x \
                GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_best_sqr_nocst_),_gf2x)

    #if GEMSS_CONSTANT_TIME
        #define GEMSS_sqr_gf2x GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_best_sqr),_gf2x)
    #else
        /* Faster */
        #define GEMSS_sqr_gf2x GEMSS_sqr_nocst_gf2x
    #endif
#endif


/***********************************************************************/
/***********************************************************************/
/************************* sqr then rem version ************************/
/***********************************************************************/
/***********************************************************************/


/* Function sqr in GF(2^x), then modular reduction */
#define GEMSS_SQR_THEN_REM_GF2N void \
            GEMSS_PREFIX_NAME(GEMSS_sqr_then_rem_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn], \
                                     const uint64_t A[GEMSS_NB_WORD_GFqn])
#define GEMSS_SQR_NOCST_THEN_REM_GF2N void \
            GEMSS_PREFIX_NAME(GEMSS_sqr_nocst_then_rem_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn], \
                                           const uint64_t A[GEMSS_NB_WORD_GFqn])
GEMSS_SQR_THEN_REM_GF2N;
GEMSS_SQR_NOCST_THEN_REM_GF2N;
#define GEMSS_sqr_then_rem_gf2n GEMSS_PREFIX_NAME(GEMSS_sqr_then_rem_gf2n)
#define GEMSS_sqr_nocst_then_rem_gf2n GEMSS_PREFIX_NAME(GEMSS_sqr_nocst_then_rem_gf2n)


/***********************************************************************/
/***********************************************************************/
/********************** Choice of sqr in GF(2^n) ***********************/
/***********************************************************************/
/***********************************************************************/


/* Choice the best sqr */
#if ((GEMSS_HFEn<33)||defined(GEMSS_MQSOFT_REF))
    #define GEMSS_sqr_nocst_gf2n GEMSS_sqr_nocst_then_rem_gf2n
    #if GEMSS_CONSTANT_TIME
        #define GEMSS_sqr_gf2n GEMSS_sqr_then_rem_gf2n
    #else
        #define GEMSS_sqr_gf2n GEMSS_sqr_nocst_gf2n
    #endif
#else
    #define GEMSS_sqr_nocst_gf2n GEMSS_sqr_nocst_then_rem_gf2n
    #if GEMSS_CONSTANT_TIME
        #define GEMSS_sqr_gf2n GEMSS_sqr_then_rem_gf2n
    #else
        #define GEMSS_sqr_gf2n GEMSS_sqr_nocst_gf2n
    #endif
#endif



#endif

