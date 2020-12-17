#ifndef _INITMATRIXID_GF2_H
#define _INITMATRIXID_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2.h"


void GEMSS_PREFIX_NAME(GEMSS_initMatrixIdn_gf2)(Mn_gf2 S);
void GEMSS_PREFIX_NAME(GEMSS_initMatrixIdnv_gf2)(Mnv_gf2 S);

#define GEMSS_initMatrixIdn_gf2 GEMSS_PREFIX_NAME(GEMSS_initMatrixIdn_gf2)
#define GEMSS_initMatrixIdnv_gf2 GEMSS_PREFIX_NAME(GEMSS_initMatrixIdnv_gf2)


#endif

