#ifndef _EVALMQSV_GF2_H
#define _EVALMQSV_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_matrix_gf2.h"
#include "gemss_MQS_gf2.h"


/* n equations, v variables */
#if GEMSS_HFEv

void GEMSS_PREFIX_NAME(GEMSS_evalMQSv_classical_gf2)(vecm_gf2 c, cst_vecnv_gf2 m,
                                         cst_mqsnv_gf2m pk);
#define GEMSS_evalMQSv_classical_gf2 GEMSS_PREFIX_NAME(GEMSS_evalMQSv_classical_gf2)

#if (GEMSS_HFEv>2)
    void GEMSS_PREFIX_NAME(GEMSS_evalMQSv_unrolled_gf2)(vecm_gf2 c, cst_vecnv_gf2 m,
                                            cst_mqsnv_gf2m pk);
    #define GEMSS_evalMQSv_unrolled_gf2 GEMSS_PREFIX_NAME(GEMSS_evalMQSv_unrolled_gf2)
#endif


/* Choose the best function */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_evalMQSv_gf2 GEMSS_evalMQSv_classical_gf2
#elif (GEMSS_HFEv>2)
    #define GEMSS_evalMQSv_gf2 GEMSS_evalMQSv_unrolled_gf2
#else
    #define GEMSS_evalMQSv_gf2 GEMSS_evalMQSv_classical_gf2
#endif


#endif


#endif

