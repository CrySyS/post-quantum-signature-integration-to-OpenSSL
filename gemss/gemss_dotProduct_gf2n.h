#ifndef _DOTPRODUCT_GF2N_H
#define _DOTPRODUCT_GF2N_H


#include "gemss_prefix_name.h"
#include "gemss_tools_gf2n.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_macro.h"
/* Really important include for the definition of 
   GEMSS___TRINOMIAL_GF2N__ and GEMSS___PENTANOMIAL_GF2N__ */
#include "gemss_rem_gf2n.h"


/* Choice the best dotProduct */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_dotProduct_gf2n GEMSS_dotProduct_no_simd_gf2n
    #define GEMSS_doubleDotProduct_gf2n GEMSS_doubleDotProduct_no_simd_gf2n
#else
    #define GEMSS_dotProduct_gf2n GEMSS_dotProduct_no_simd_gf2n
    #define GEMSS_doubleDotProduct_gf2n GEMSS_doubleDotProduct_no_simd_gf2n
#endif


void GEMSS_PREFIX_NAME(GEMSS_dotProduct_no_simd_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn],
                     const UINT* vec_x, const UINT* vec_y, unsigned int len);
void GEMSS_PREFIX_NAME(GEMSS_doubleDotProduct_no_simd_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn],
                     const UINT* vec_x, const UINT* vec_y,
                     const UINT* vec2_x, const UINT* vec2_y, unsigned int len);

#define GEMSS_dotProduct_no_simd_gf2n GEMSS_PREFIX_NAME(GEMSS_dotProduct_no_simd_gf2n)
#define GEMSS_doubleDotProduct_no_simd_gf2n GEMSS_PREFIX_NAME(GEMSS_doubleDotProduct_no_simd_gf2n)


#endif

