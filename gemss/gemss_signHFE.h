#ifndef _SIGNHFE_H
#define _SIGNHFE_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_gf2nx.h"
#include "gemss_config_HFE.h"
#include "gemss_matrix_gf2.h"
#include <stddef.h>


typedef struct _secret_key_HFE
{
    complete_sparse_monic_gf2nx F_struct;
    #if GEMSS_ENABLED_SEED_SK
        sparse_monic_gf2nx F_HFEv;
        GLnv_gf2 S;
        GLn_gf2 T;
        #if GEMSS_AFFINE_TRANSFORMATION_BY_t
            vecm_gf2 t;
        #endif
    #else
        cst_sparse_monic_gf2nx F_HFEv;
        cst_GLnv_gf2 S;
        cst_GLn_gf2 T;
        #if GEMSS_AFFINE_TRANSFORMATION_BY_t
            cst_vecm_gf2 t;
        #endif
    #endif

    #if GEMSS_ENABLED_SEED_SK
        UINT *sk_uncomp;
    #endif
} secret_key_HFE;


#if GEMSS_ENABLED_SEED_SK
    void GEMSS_PREFIX_NAME(GEMSS_precSignHFESeed)(secret_key_HFE *sk_HFE, const UINT *sk);
    #define GEMSS_precSignHFESeed GEMSS_PREFIX_NAME(GEMSS_precSignHFESeed)
#endif

/* Precomputation for one secret-key */
int GEMSS_PREFIX_NAME(GEMSS_precSignHFE)(secret_key_HFE* sk_HFE, const UINT** linear_coefs,
                                                     const UINT *sk);

/* Sign a message: sm is the signed message, m is the original message,
 *                 and sk is the secret-key. */

/* Function for nb_ite>0 */
int GEMSS_PREFIX_NAME(GEMSS_signHFE_FeistelPatarin)(unsigned char* sm8,
                                        const unsigned char* m, size_t len,
                                        const UINT* sk);


#define GEMSS_precSignHFE GEMSS_PREFIX_NAME(GEMSS_precSignHFE)
#define GEMSS_signHFE_FeistelPatarin GEMSS_PREFIX_NAME(GEMSS_signHFE_FeistelPatarin)


#define GEMSS_signHFE GEMSS_signHFE_FeistelPatarin



#endif

