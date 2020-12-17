#ifndef _INVMATRIXNV_GF2_H
#define _INVMATRIXNV_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2.h"
#include "gemss_arch.h"


void GEMSS_PREFIX_NAME(GEMSS_invMatrixnv_nocst_gf2)(GLnv_gf2 S_inv, GLnv_gf2 S);
#define GEMSS_invMatrixnv_nocst_gf2 GEMSS_PREFIX_NAME(GEMSS_invMatrixnv_nocst_gf2)

void GEMSS_PREFIX_NAME(GEMSS_invMatrixnv_cst_gf2)(GLnv_gf2 S_inv, GLnv_gf2 S);
#define GEMSS_invMatrixnv_cst_gf2 GEMSS_PREFIX_NAME(GEMSS_invMatrixnv_cst_gf2)

void GEMSS_PREFIX_NAME(GEMSS_invMatrixLUnv_gf2)(GLnv_gf2 S_inv, cst_Tnv_gf2 L,
                                                    cst_Tnv_gf2 U);
#define GEMSS_invMatrixLUnv_gf2 GEMSS_PREFIX_NAME(GEMSS_invMatrixLUnv_gf2)


#if GEMSS_CONSTANT_TIME
    #define GEMSS_invMatrixnv_gf2 GEMSS_invMatrixnv_cst_gf2
#else
    #define GEMSS_invMatrixnv_gf2 GEMSS_invMatrixnv_nocst_gf2
#endif


#endif

