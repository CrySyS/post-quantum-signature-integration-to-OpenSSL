#ifndef _SIZES_HFE_H
#define _SIZES_HFE_H

//#include "gemss.h"
#include "gemss_arch.h"
#include "gemss_macro.h"
#include "gemss_config_HFE.h"
#include "gemss_bit.h"
#include "gemss_hash.h"
#include "gemss_KAT_int.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_tools_gf2v.h"
#include "gemss_gf2nx.h"
#include "gemss_matrix_gf2.h"
#include "gemss_MQS_gf2.h"


#if GEMSS_EUF_CMA_PROPERTY
    #define GEMSS_SIZE_SALT_BITS 128
    /* Size of the salt in bytes */
    #define GEMSS_SIZE_SALT 16
    #define GEMSS_SIZE_SALT_WORD 2
#else
    #define GEMSS_SIZE_SALT_BITS 0
    /* Size of the salt in bytes */
    #define GEMSS_SIZE_SALT 0
    #define GEMSS_SIZE_SALT_WORD 0
#endif


#if GEMSS_ENABLED_SEED_SK
    /* Size of the secret seed in bytes */
    #if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))
        #define GEMSS_SIZE_SEED_SK 16
    #else
        /* GEMSS_K bits */
        #define GEMSS_SIZE_SEED_SK (GEMSS_K>>3)
    #endif
#endif


/****************** THEORETICAL SIZES ******************/

/* Sizes in bits */
#define GEMSS_SIZE_PK_THEORETICAL_HFE (GEMSS_HFEm*(((GEMSS_HFEnv*(GEMSS_HFEnv+1))>>1)+1))

#if GEMSS_ENABLED_SEED_SK
    #define GEMSS_SIZE_SK_THEORETICAL_HFE (GEMSS_SIZE_SEED_SK<<3)
#else
    #define GEMSS_SIZE_SK_THEORETICAL_HFE \
                ((GEMSS_HFEnv*GEMSS_HFEnv)+(GEMSS_HFEn*GEMSS_HFEn)+GEMSS_NB_COEFS_HFEVPOLY*GEMSS_HFEn)
#endif

#define GEMSS_SIZE_SIGN_THEORETICAL_HFE (GEMSS_HFEnv+(GEMSS_NB_ITE-1)*(GEMSS_HFEnv-GEMSS_HFEm)+GEMSS_SIZE_SALT_BITS)


/****************** PRACTICAL SIZES ******************/

/* Public-key (words) */
#if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
    #define GEMSS_SIZE_PK_HFE_WORD ((((GEMSS_NB_MONOMIAL_PK*GEMSS_HFEm+7)>>3)+7)>>3)
#elif GEMSS_FORMAT_MONOMIAL_PK8
    #define GEMSS_SIZE_PK_HFE_WORD ((GEMSS_MQ_GFqm8_SIZE>>3)+((GEMSS_MQ_GFqm8_SIZE&7)?1:0))
#endif

/* Public-key (bytes) */
#if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
    /* Minimal size */
    #define GEMSS_SIZE_PK_HFE ((GEMSS_NB_MONOMIAL_PK*GEMSS_HFEm+7)>>3)
#elif GEMSS_FORMAT_MONOMIAL_PK8
    /* Minimal when m mod 8 == 0 */
    #define GEMSS_SIZE_PK_HFE GEMSS_MQ_GFqm8_SIZE
#endif

/* Secret-key: GEMSS_HFE polynomial + matrix S_inv + matrix T_inv (+ vector -t) */

#if GEMSS_AFFINE_TRANSFORMATION_BY_t
    #define GEMSS_SIZE_VECTOR_t GEMSS_NB_WORD_GF2m
#else
    #define GEMSS_SIZE_VECTOR_t 0
#endif

#define GEMSS_ACCESS_MATRIX_S GEMSS_NB_UINT_HFEVPOLY
#define GEMSS_ACCESS_MATRIX_T (GEMSS_ACCESS_MATRIX_S+GEMSS_MATRIXnv_SIZE)
#define GEMSS_ACCESS_VECTOR_t (GEMSS_ACCESS_MATRIX_T+GEMSS_MATRIXn_SIZE)

/* Secret-key (words) */
#define GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD (GEMSS_ACCESS_VECTOR_t+GEMSS_SIZE_VECTOR_t)
/* Secret-key (bytes) */
#define GEMSS_SIZE_SK_HFE_UNCOMPRESSED (GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD<<3)

#if GEMSS_ENABLED_SEED_SK
    /* Secret-key (bytes) */
    #define GEMSS_SIZE_SK_HFE GEMSS_SIZE_SEED_SK
    /* Secret-key (words) */
    #define GEMSS_SIZE_SK_HFE_WORD ((GEMSS_SIZE_SK_HFE+7)>>3)
#else
    /* Secret-key (words) */
    #define GEMSS_SIZE_SK_HFE_WORD GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD
    /* Secret-key (bytes) */
    #define GEMSS_SIZE_SK_HFE GEMSS_SIZE_SK_HFE_UNCOMPRESSED
#endif


/* Signature: GEMSS_NB_WORD_GF2nv for signature GEMSS_NB_ITE, GEMSS_NB_WORD_GF2nvm for others */

/* Size of signature (words): */
#define GEMSS_SIZE_SIGN_UNCOMPRESSED \
            (GEMSS_NB_WORD_GF2nv+(GEMSS_NB_ITE-1)*GEMSS_NB_WORD_GF2nvm+GEMSS_SIZE_SALT_WORD)
/* Size of signature (bytes): */
/* (x+7)/8 = Ceiling(x/8) */ 
#define GEMSS_SIZE_SIGN_HFE ((GEMSS_SIZE_SIGN_THEORETICAL_HFE+7)>>3)


#endif

