#ifndef _CONVMQ_GF2_H
#define _CONVMQ_GF2_H


#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_tools_gf2m.h"
#include "gemss_MQ_gf2.h"


void GEMSS_PREFIX_NAME(GEMSS_convMQ_UL_gf2)(uint8_t* pk2, const uint8_t* pk);
UINT GEMSS_PREFIX_NAME(GEMSS_convMQ_uncompressL_gf2)(uint64_t* pk2, const uint8_t* pk);
UINT GEMSS_PREFIX_NAME(GEMSS_convMQ_last_uncompressL_gf2)(uint64_t* pk2, const uint8_t* pk);

#define GEMSS_convMQ_UL_gf2 GEMSS_PREFIX_NAME(GEMSS_convMQ_UL_gf2)
#define GEMSS_convMQ_uncompressL_gf2 GEMSS_PREFIX_NAME(GEMSS_convMQ_uncompressL_gf2)
#define GEMSS_convMQ_last_uncompressL_gf2 GEMSS_PREFIX_NAME(GEMSS_convMQ_last_uncompressL_gf2)

#if (GEMSS_HFENr8&&(GEMSS_HFEmr8>1))
    uint64_t GEMSS_PREFIX_NAME(GEMSS_convMQ_last_UL_gf2)(uint8_t* pk2, const uint8_t* pk);
    #define GEMSS_convMQ_last_UL_gf2 GEMSS_PREFIX_NAME(GEMSS_convMQ_last_UL_gf2)
#endif



#endif

