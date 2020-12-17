#ifndef _ADD_GF2N_H
#define _ADD_GF2N_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_gf2x.h"
#include "gemss_add_gf2x.h"
#include "gemss_tools_gf2n.h"
#include "gemss_macro.h"


/* The following macros are used only in this file. */

/* Addition in GF(2^n). */
#if (GEMSS_NB_WORD_GFqn<7)
    #define GEMSS_ADD_GF2N GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_ADD),_GF2X)
    #define GEMSS_ADD2_GF2N GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_ADD),_2_GF2X)
#else
    #define GEMSS_ADD_GF2N(c,a,b) GEMSS_ADD_GF2X(c,a,b,GEMSS_NB_WORD_GFqn)
    #define GEMSS_ADD2_GF2N(c,a) GEMSS_ADD_2_GF2X(c,a,GEMSS_NB_WORD_GFqn)
#endif


/* Addition in GF(2)[x] for (2n-1)-coefficients polynomials. */
#if (GEMSS_NB_WORD_MMUL_TMP<19)
    #define GEMSS_ADD_PRODUCT_GF2N GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_MMUL(GEMSS_ADD),_GF2X)
    #define GEMSS_ADD2_PRODUCT_GF2N GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_MMUL(GEMSS_ADD),_2_GF2X)
#else
    #define GEMSS_ADD_PRODUCT_GF2N(c,a,b) GEMSS_ADD_GF2X(c,a,b,GEMSS_NB_WORD_MMUL)
    #define GEMSS_ADD2_PRODUCT_GF2N(c,a) GEMSS_ADD_2_GF2X(c,a,GEMSS_NB_WORD_MMUL)
#endif


void GEMSS_PREFIX_NAME(GEMSS_add_gf2n_ref)(gf2n c, cst_gf2n a, cst_gf2n b);
void GEMSS_PREFIX_NAME(GEMSS_add2_gf2n_ref)(gf2n c, cst_gf2n a);
void GEMSS_PREFIX_NAME(GEMSS_add_product_gf2n_ref)(gf2x c, cst_gf2x a, cst_gf2x b);
void GEMSS_PREFIX_NAME(GEMSS_add2_product_gf2n_ref)(gf2x c, cst_gf2x a);

#define GEMSS_add_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_add_gf2n_ref)
#define GEMSS_add2_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_add2_gf2n_ref)
#define GEMSS_add_product_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_add_product_gf2n_ref)
#define GEMSS_add2_product_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_add2_product_gf2n_ref)


#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_add_gf2n GEMSS_add_gf2n_ref
    #define GEMSS_add2_gf2n GEMSS_add2_gf2n_ref
    #define GEMSS_add_product_gf2n GEMSS_add_product_gf2n_ref
    #define GEMSS_add2_product_gf2n GEMSS_add2_product_gf2n_ref
#else
    /* The addition function is inlined. */
    #define GEMSS_add_gf2n GEMSS_ADD_GF2N
    #define GEMSS_add2_gf2n GEMSS_ADD2_GF2N
    #define GEMSS_add_product_gf2n GEMSS_ADD_PRODUCT_GF2N
    #define GEMSS_add2_product_gf2n GEMSS_ADD2_PRODUCT_GF2N
#endif




#endif

