#ifndef _MIXEQUATIONSMQS_GF2_H
#define _MIXEQUATIONSMQS_GF2_H


#include "gemss_prefix_name.h"
#include "gemss_config_HFE.h"
#include "gemss_matrix_gf2.h"
#include "gemss_MQS_gf2.h"

#include <openssl/gemss_choice_crypto.h>


#define GEMSS_mixEquationsMQS8_gf2 GEMSS_mixEquationsMQS8_gf2_right


void GEMSS_PREFIX_NAME(GEMSS_mixEquationsMQS8_gf2_right)(mqsnv8_gf2m pk, cst_mqsnv_gf2n MQS,
                                             cst_Mn_gf2 T);
#define GEMSS_mixEquationsMQS8_gf2_right GEMSS_PREFIX_NAME(GEMSS_mixEquationsMQS8_gf2_right)


#endif

