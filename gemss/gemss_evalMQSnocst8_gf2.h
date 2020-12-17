#ifndef _EVALMQSNOCST8_GF2_H
#define _EVALMQSNOCST8_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_tools_gf2m.h"
#include "gemss_matrix_gf2.h"
#include "gemss_MQS_gf2.h"


void GEMSS_PREFIX_NAME(GEMSS_evalMQSnocst8_unrolled_gf2)(vecm_gf2 c, cst_vecnv_gf2 m,
                                            cst_mqsnv8_gf2m pk);
#define GEMSS_evalMQSnocst8_unrolled_gf2 GEMSS_PREFIX_NAME(GEMSS_evalMQSnocst8_unrolled_gf2)


/* Choose the best evaluation */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_evalMQSnocst8_gf2 GEMSS_evalMQSnocst8_unrolled_gf2
#else
    #define GEMSS_evalMQSnocst8_gf2 GEMSS_evalMQSnocst8_unrolled_gf2
#endif


#endif

