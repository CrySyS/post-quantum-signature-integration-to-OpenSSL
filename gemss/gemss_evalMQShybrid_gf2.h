#ifndef _EVALMQSHYBRID_GF2_H
#define _EVALMQSHYBRID_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_matrix_gf2.h"
#include "gemss_config_HFE.h"


void GEMSS_PREFIX_NAME(GEMSS_evalMQShybrid8_uncomp_nocst_gf2_m)(vecm_gf2 res,
                                                    cst_vecnv_gf2 x,
                                                    const uint8_t* mq_quo,
                                                    const UINT* mq_rem);

#define GEMSS_evalMQShybrid8_uncomp_nocst_gf2_m \
            GEMSS_PREFIX_NAME(GEMSS_evalMQShybrid8_uncomp_nocst_gf2_m)


#if GEMSS_FORMAT_HYBRID_CPK8
    #define GEMSS_evalMQShybrid8_nocst_gf2_m GEMSS_evalMQShybrid8_uncomp_nocst_gf2_m
#endif


#endif

