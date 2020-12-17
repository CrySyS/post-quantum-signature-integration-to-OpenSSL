#ifndef _REM_GF2N_H
#define _REM_GF2N_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_gf2x.h"
#include "gemss_tools_gf2n.h"
#include "gemss_macro.h"
#include "gemss_rem_gf2x.h"
#include "gemss_rem5_gf2n.h"


/* Compute the modular reduction */


#define GEMSS_KI (GEMSS_HFEn&63U)
#define GEMSS_KI64 (64U-GEMSS_KI)

#if (GEMSS_K3>63)
    #define GEMSS_K3mod64 (GEMSS_K3&63U)
#else
    #define GEMSS_K3mod64 GEMSS_K3
#endif

#define GEMSS_K364 (64U-GEMSS_K3mod64)
/* Only to remove the warnings */
#define GEMSS_K364mod64 (GEMSS_K364&63U)


/***********************************************************************/
/***********************************************************************/
/****************** Macro without SIMD version *************************/
/***********************************************************************/
/***********************************************************************/


/* Automatic choice of GEMSS_REM_GF2N */

#if(GEMSS_NB_WORD_GFqn==1)
    #ifdef GEMSS___TRINOMIAL_GF2N__
        /* Example: GEMSS_REM64_TRINOMIAL_GF2X(P,Pol,GEMSS_HFEn,GEMSS_K3mod64,Q,R,GEMSS_MASK_GF2n) */
        #if(GEMSS_K3==1)
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_REM),\
_TRINOMIAL_K31_GF2X(P,Pol,GEMSS_HFEn,GEMSS_K3mod64,Q,R,GEMSS_MASK_GF2n))
        #else
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_REM),\
_TRINOMIAL_GF2X(P,Pol,GEMSS_HFEn,GEMSS_K3mod64,Q,R,GEMSS_MASK_GF2n))
        #endif
    #endif

    #ifdef GEMSS___PENTANOMIAL_GF2N__
        #if (GEMSS_HFEn!=64)
            /* Example: GEMSS_REM64_PENTANOMIAL_GF2X(P,Pol,GEMSS_HFEn,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,
                                               Q,R,GEMSS_MASK_GF2n) */
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_REM),\
_PENTANOMIAL_GF2X(P,Pol,GEMSS_HFEn,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,Q,R,GEMSS_MASK_GF2n))
        #else
            /* GEMSS_HFEn == 64 */
            #define GEMSS_REM_GF2N(P,Pol,Q,R) \
                GEMSS_REM64_PENTANOMIAL_K64_GF2X(P,Pol,64,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,R)
        #endif
    #endif

#elif(GEMSS_NB_WORD_GFqn==2)
    #if (GEMSS_HFEn<97)
        #ifdef GEMSS___TRINOMIAL_GF2N__
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM96_TRINOMIAL_GF2X(P,Pol,\
GEMSS_K3mod64,GEMSS_KI,Q,R,GEMSS_MASK_GF2n)
        #endif

        #ifdef GEMSS___PENTANOMIAL_GF2N__
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM96_PENTANOMIAL_GF2X(P,Pol,\
GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,GEMSS_KI,Q,R,GEMSS_MASK_GF2n)
        #endif
    #else
        #ifdef GEMSS___TRINOMIAL_GF2N__
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM128_TRINOMIAL_GF2X(P,Pol,\
GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,Q,R,GEMSS_MASK_GF2n)
        #endif

        #ifdef GEMSS___PENTANOMIAL_GF2N__
            #if (GEMSS_HFEnr)
                #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM128_PENTANOMIAL_GF2X(P,Pol,\
GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,Q,R,GEMSS_MASK_GF2n)
            #else
                /* GEMSS_HFEn == 128 */
                #define GEMSS_REM_GF2N(P,Pol,Q,R) \
                    GEMSS_REM128_PENTANOMIAL_K128_GF2X(P,Pol,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,R)
            #endif
        #endif
    #endif

#else
    #ifdef GEMSS___TRINOMIAL_GF2N__
        #if ((GEMSS_HFEn>256)&&(GEMSS_HFEn<289)&&(GEMSS_K3>32)&&(GEMSS_K3<64))
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM288_SPECIALIZED_TRINOMIAL_GF2X(P,Pol\
,GEMSS_K3,GEMSS_KI,GEMSS_KI64,GEMSS_K364,Q,R,GEMSS_MASK_GF2n)
        #elif (GEMSS_HFEn==313)
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM320_SPECIALIZED_TRINOMIAL_GF2X(\
P,Pol,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K364,Q,R,GEMSS_MASK_GF2n)
        #elif (GEMSS_HFEn==354)
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM384_SPECIALIZED_TRINOMIAL_GF2X(\
P,Pol,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K364,Q,R,GEMSS_MASK_GF2n)
        #elif (GEMSS_HFEn==358)
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM384_SPECIALIZED358_TRINOMIAL_GF2X(\
P,Pol,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K364,Q,R,GEMSS_MASK_GF2n)
        #elif (GEMSS_HFEn==402)
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM402_SPECIALIZED_TRINOMIAL_GF2X(\
P,Pol,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K364,Q,R,GEMSS_MASK_GF2n)
        #else
            /* Example: GEMSS_REM192_TRINOMIAL_GF2X(P,Pol,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K364mod64,
                                              Q,R,GEMSS_MASK_GF2n) */
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_REM),\
_TRINOMIAL_GF2X(P,Pol,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K364mod64,Q,R,GEMSS_MASK_GF2n))
        #endif
    #endif

    #ifdef GEMSS___PENTANOMIAL_GF2N__
        #if ((GEMSS_HFEn==312)&&(GEMSS_K3==128))
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM312_PENTANOMIAL_K3_IS_128_GF2X(\
P,Pol,GEMSS_K1,GEMSS_K2,,GEMSS_KI,GEMSS_KI64,GEMSS_K164,GEMSS_K264,,Q,R,GEMSS_MASK_GF2n)
        #elif ((GEMSS_HFEn==448)&&(GEMSS_K3==64))
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM448_PENTANOMIAL_K448_K3_IS_64_GF2X(\
P,Pol,GEMSS_K1,GEMSS_K2,,GEMSS_K164,GEMSS_K264,,R)
        #elif ((GEMSS_HFEn==544)&&(GEMSS_K3==128))
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_REM544_PENTANOMIAL_K3_IS_128_GF2X(\
P,Pol,GEMSS_K1,GEMSS_K2,,GEMSS_KI,GEMSS_KI64,GEMSS_K164,GEMSS_K264,,Q,R,GEMSS_MASK_GF2n)
        #elif (GEMSS_HFEnr)
            /* Example: GEMSS_REM192_PENTANOMIAL_GF2X(P,Pol,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,
                        GEMSS_K164,GEMSS_K264,GEMSS_K364mod64,Q,R,GEMSS_MASK_GF2n) */
            #define GEMSS_REM_GF2N(P,Pol,Q,R) GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_REM),\
_PENTANOMIAL_GF2X(P,Pol,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,GEMSS_KI,GEMSS_KI64,GEMSS_K164,GEMSS_K264,GEMSS_K364mod64,Q,R,\
GEMSS_MASK_GF2n))
        #else
            /* GEMSS_HFEn == GEMSS_NB_WORD_GFqn*64 */
            /* Example: GEMSS_REM192_PENTANOMIAL_K192_GF2X(P,Pol,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,\
                                                     GEMSS_K164,GEMSS_K264,GEMSS_K364mod64,R) */
            #define GEMSS_REM_GF2N_TMP GEMSS_CONCAT(GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_CONCAT(\
GEMSS_CONCAT_NB_BITS_MMUL_SUP(GEMSS_REM),_PENTANOMIAL_K)),_GF2X)
            #define GEMSS_REM_GF2N(P,Pol,Q,R) \
                GEMSS_REM_GF2N_TMP(P,Pol,GEMSS_K1,GEMSS_K2,GEMSS_K3mod64,GEMSS_K164,GEMSS_K264,GEMSS_K364mod64,R)
        #endif
    #endif
#endif


/***********************************************************************/
/***********************************************************************/
/************************ Without SIMD version *************************/
/***********************************************************************/
/***********************************************************************/


void GEMSS_PREFIX_NAME(GEMSS_rem_gf2n_ref)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                               cst_static_gf2x Pol[GEMSS_NB_WORD_MUL]);
void GEMSS_PREFIX_NAME(GEMSS_remsqr_gf2n_ref)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                  cst_static_gf2x Pol[GEMSS_NB_WORD_MUL]);
#define GEMSS_rem_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_rem_gf2n_ref)
#define GEMSS_remsqr_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_remsqr_gf2n_ref)

#if ((GEMSS_K3<33) || (defined(GEMSS___TRINOMIAL_GF2N__)&&\
           (((GEMSS_HFEn==265)&&(GEMSS_K3==42)) || ((GEMSS_HFEn==266)&&(GEMSS_K3==47))\
         || ((GEMSS_HFEn==354)&&(GEMSS_K3==99)) || ((GEMSS_HFEn==358)&&(GEMSS_K3==57)))))
    void GEMSS_PREFIX_NAME(GEMSS_rem_gf2n_ref2)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                    cst_static_gf2x Pol[GEMSS_NB_WORD_MUL]);
    #define GEMSS_rem_gf2n_ref2 GEMSS_PREFIX_NAME(GEMSS_rem_gf2n_ref2)
#endif


#if (GEMSS_HFEn<33)
    UINT GEMSS_PREFIX_NAME(GEMSS_rem_no_simd_gf2n)(UINT Pol);
#else
    void GEMSS_PREFIX_NAME(GEMSS_rem_no_simd_gf2n)(static_gf2n P[GEMSS_NB_WORD_GFqn],
                                       cst_static_gf2x Pol[GEMSS_NB_WORD_MUL]);
#endif

#define GEMSS_rem_no_simd_gf2n GEMSS_PREFIX_NAME(GEMSS_rem_no_simd_gf2n)


/***********************************************************************/
/***********************************************************************/
/******************* Choice of the modular reduction *******************/
/***********************************************************************/
/***********************************************************************/


/* To choose the GEMSS_rem_gf2n function like macro or like function in GEMSS_mul_gf2n.c and
   GEMSS_sqr_gf2n.c. */
#ifdef GEMSS_MQSOFT_REF
    /* It is set to 0 to use the reference implementation instead of macros. */
    #define GEMSS_REM_MACRO 0
#else
    /* The user can set to 0 ou 1 this macro. */
    #define GEMSS_REM_MACRO 1
#endif

/* Choice of the best rem */
#ifdef GEMSS_MQSOFT_REF
    #if ((GEMSS_K3<33) || (defined(GEMSS___TRINOMIAL_GF2N__)&&\
               (((GEMSS_HFEn==265)&&(GEMSS_K3==42)) || ((GEMSS_HFEn==266)&&(GEMSS_K3==47))\
             || ((GEMSS_HFEn==354)&&(GEMSS_K3==99)) || ((GEMSS_HFEn==358)&&(GEMSS_K3==57)))))
        /* Faster */
        #define GEMSS_rem_gf2n GEMSS_rem_gf2n_ref2
    #else
        #define GEMSS_rem_gf2n GEMSS_rem_gf2n_ref
    #endif
#elif (GEMSS_HFEn<33)
    #define GEMSS_rem_gf2n(P,Q) *(P)=GEMSS_rem_no_simd_gf2n(*(Q));
#else
    #define GEMSS_rem_gf2n GEMSS_rem_no_simd_gf2n
#endif

/* Choice of the best rem when the input is a square */
#if (defined(GEMSS_MQSOFT_REF)&&\
    (!((GEMSS_K3<33) || (defined(GEMSS___TRINOMIAL_GF2N__)&&\
           (((GEMSS_HFEn==265)&&(GEMSS_K3==42)) || ((GEMSS_HFEn==266)&&(GEMSS_K3==47))\
         || ((GEMSS_HFEn==354)&&(GEMSS_K3==99)) || ((GEMSS_HFEn==358)&&(GEMSS_K3==57)))))))
    #define GEMSS_remsqr_gf2n GEMSS_remsqr_gf2n_ref
#else
    #define GEMSS_remsqr_gf2n GEMSS_rem_gf2n
#endif





#endif

