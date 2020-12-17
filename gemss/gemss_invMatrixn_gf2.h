#ifndef _INVMATRIXN_GF2_H
#define _INVMATRIXN_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2.h"
#include "gemss_arch.h"


void GEMSS_PREFIX_NAME(GEMSS_invMatrixn_nocst_gf2)(GLn_gf2 S_inv, GLn_gf2 S);
#define GEMSS_invMatrixn_nocst_gf2 GEMSS_PREFIX_NAME(GEMSS_invMatrixn_nocst_gf2)

void GEMSS_PREFIX_NAME(GEMSS_invMatrixn_cst_gf2)(GLn_gf2 S_inv, GLn_gf2 S);
#define GEMSS_invMatrixn_cst_gf2 GEMSS_PREFIX_NAME(GEMSS_invMatrixn_cst_gf2)

void GEMSS_PREFIX_NAME(GEMSS_invMatrixLUn_gf2)(GLn_gf2 S_inv, cst_Tn_gf2 L, cst_Tn_gf2 U);
#define GEMSS_invMatrixLUn_gf2 GEMSS_PREFIX_NAME(GEMSS_invMatrixLUn_gf2)


#if GEMSS_CONSTANT_TIME
    #define GEMSS_invMatrixn_gf2 GEMSS_invMatrixn_cst_gf2
#else
    #define GEMSS_invMatrixn_gf2 GEMSS_invMatrixn_nocst_gf2
#endif


#endif

