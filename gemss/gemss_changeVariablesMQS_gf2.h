#ifndef _CHANGEVARIABLESMQS_GF2_H
#define _CHANGEVARIABLESMQS_GF2_H


#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2.h"
#include "gemss_MQS_gf2.h"
#include "gemss_arch.h"


int GEMSS_PREFIX_NAME(GEMSS_changeVariablesMQS_simd_gf2)(mqsnv_gf2n MQS, cst_GLnv_gf2 S);
int GEMSS_PREFIX_NAME(GEMSS_changeVariablesMQS64_gf2)(mqsnv_gf2n MQS, cst_GLnv_gf2 S);

#define GEMSS_changeVariablesMQS_simd_gf2 GEMSS_PREFIX_NAME(GEMSS_changeVariablesMQS_simd_gf2)
#define GEMSS_changeVariablesMQS64_gf2 GEMSS_PREFIX_NAME(GEMSS_changeVariablesMQS64_gf2)


#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_changeVariablesMQS_gf2 GEMSS_changeVariablesMQS_simd_gf2
#else
    #define GEMSS_changeVariablesMQS_gf2 GEMSS_changeVariablesMQS64_gf2
#endif



#endif

