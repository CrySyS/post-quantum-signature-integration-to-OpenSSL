#ifndef _EVALMQNOCST_GF2_H
#define _EVALMQNOCST_GF2_H


#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_matrix_gf2.h"
#include "gemss_tools_gf2nv.h"


#if (GEMSS_NB_WORD_GF2nv<10)
    UINT GEMSS_PREFIX_NAME(GEMSS_evalMQnocst_unrolled_no_simd_gf2)(const UINT* m,
                                                       const UINT* mq);
    #define GEMSS_evalMQnocst_unrolled_no_simd_gf2 \
                GEMSS_PREFIX_NAME(GEMSS_evalMQnocst_unrolled_no_simd_gf2)
#endif



#ifdef GEMSS_MQSOFT_REF
    #if (GEMSS_NB_WORD_GF2nv<10)
        #define GEMSS_evalMQnocst_gf2 GEMSS_evalMQnocst_unrolled_no_simd_gf2
    #endif
#elif (GEMSS_NB_WORD_GF2nv<10)
    #define GEMSS_evalMQnocst_gf2 GEMSS_evalMQnocst_unrolled_no_simd_gf2
#endif



#endif

