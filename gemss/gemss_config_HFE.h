#ifndef _CONFIG_HFE_H
#define _CONFIG_HFE_H


//#include "gemss.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2m.h"


/* The public and secret keys are the same for encryption and signature */
#define GEMSS_encrypt_keypairHFE GEMSS_sign_keypairHFE


/***** Public-key *****/


#if (!GEMSS_HFEmr8)
    #define GEMSS_FORMAT_HYBRID_CPK8 0
    #define GEMSS_FORMAT_MONOMIAL_PK8 1
#else
    /* Compressed pk */
    #define GEMSS_FORMAT_HYBRID_CPK8 1
    #define GEMSS_FORMAT_MONOMIAL_PK8 1
#endif

#if GEMSS_FORMAT_HYBRID_CPK8
    #define GEMSS_EVAL_HYBRID_CPK8_UNCOMP 1
#endif

/* The verification does not need constant-time evaluation */
#if GEMSS_FORMAT_HYBRID_CPK8
    #define GEMSS_evalMQS_gf2_HFE GEMSS_evalMQShybrid8_nocst_gf2_m
#else
    #define GEMSS_evalMQS_gf2_HFE GEMSS_evalMQSnocst8_gf2
#endif


/***** Secret-key, seed? *****/


/* Generation of the secret-key with a seed */
#if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))
    /* In Quartz, the secret-key is generated from a seed */
    #define GEMSS_ENABLED_SEED_SK 1
#else
    /* This option can be set to 1 or 0 */
    #define GEMSS_ENABLED_SEED_SK 1
#endif


/***** Secret-key (S,s,T,t) *****/


/* Choose the method to generate random invertible matrices S and T */
/* Choose !=0 for LU and 0 for classical */
#if 0
    #define GEMSS_GEN_INV_MATRIX_TRIAL_ERROR 1
    #define GEMSS_GEN_INVERTIBLE_MATRIX_LU 0
#else
    #define GEMSS_GEN_INV_MATRIX_TRIAL_ERROR 0
    #define GEMSS_GEN_INVERTIBLE_MATRIX_LU 1
#endif

#if GEMSS_ENABLED_SEED_SK
    /* Set to 1 is faster for the signing process. */
    #define GEMSS_GEN_INVERSE_IN_FIRST 1
#else
    /* The signing process is not impacted, set to 0 is faster for the keypair
       generation when GEMSS_GEN_INV_MATRIX_TRIAL_ERROR is set to 1. */
    #define GEMSS_GEN_INVERSE_IN_FIRST 0
#endif

/* To use an affine transformation (change of variable): *S+s */
#if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))
    /* XXX Not implemented, equivalent to set to 0. XXX */
    #define GEMSS_AFFINE_TRANSFORMATION_BY_s 1
#else
    #define GEMSS_AFFINE_TRANSFORMATION_BY_s 0
#endif

/* To use an affine transformation (mix equations): pk = (MQS)*T +t */
#if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))
    #define GEMSS_AFFINE_TRANSFORMATION_BY_t 1
#else
    #define GEMSS_AFFINE_TRANSFORMATION_BY_t 0
#endif


/***** Secret-key F *****/


#if defined(GEMSS_QUARTZ_V1)
    /* To take a root only if it is unique */
    #define GEMSS_UNIQUE_ROOT
#endif


/****************** PARAMETERS FOR THE KEYPAIR GENERATION ******************/

/* To use precomputed canonical basis and these powers.
   Requires the prec_cbasis_gf2n.h file, which depends on GEMSS_HFEn. */
#define GEMSS_PRECOMPUTED_CBASIS 0

/* XXX This part is disabled XXX */

/* To use precomputed products of elements of canonical basis and these powers
   The compilation becomes very slow!
   GEMSS_PRECOMPUTE2 removes the effect of GEMSS_PRECOMPUTED_CBASIS. */
#define GEMSS_PRECOMPUTE2 0




#endif

