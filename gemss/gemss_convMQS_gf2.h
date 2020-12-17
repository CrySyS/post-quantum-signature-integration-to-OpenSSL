#ifndef _CONVMQS_GF2_H
#define _CONVMQS_GF2_H


#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_tools_gf2m.h"
#include "gemss_MQS_gf2.h"
#include "gemss_config_HFE.h"


#if GEMSS_HFEmr8
    void GEMSS_PREFIX_NAME(GEMSS_convMQS_one_eq_to_hybrid_rep8_comp_gf2)(uint8_t* pk2,
                                                             const uint8_t* pk);
    #define GEMSS_convMQS_one_eq_to_hybrid_rep8_comp_gf2 \
        GEMSS_PREFIX_NAME(GEMSS_convMQS_one_eq_to_hybrid_rep8_comp_gf2)

    #if (GEMSS_EVAL_HYBRID_CPK8_UNCOMP&&GEMSS_HFENr8&&(GEMSS_HFEmr8>1))
        void GEMSS_PREFIX_NAME(GEMSS_convMQS_one_eq_to_hybrid_rep8_uncomp_gf2)(uint8_t* pk2,
                                                             const uint8_t* pk);
        #define GEMSS_convMQS_one_eq_to_hybrid_rep8_uncomp_gf2 \
            GEMSS_PREFIX_NAME(GEMSS_convMQS_one_eq_to_hybrid_rep8_uncomp_gf2)
    #else
        #define GEMSS_convMQS_one_eq_to_hybrid_rep8_uncomp_gf2 \
                GEMSS_convMQS_one_eq_to_hybrid_rep8_comp_gf2
    #endif

    #define GEMSS_convMQS_one_eq_to_hybrid_rep8_gf2 \
            GEMSS_convMQS_one_eq_to_hybrid_rep8_uncomp_gf2
#endif


#endif

