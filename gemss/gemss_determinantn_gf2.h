#ifndef _DETERMINANTN_GF2_H
#define _DETERMINANTN_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_gf2.h"
#include "gemss_matrix_gf2.h"
#include "gemss_arch.h"


gf2 GEMSS_PREFIX_NAME(GEMSS_determinantn_nocst_gf2)(cst_Mn_gf2 S, Mn_gf2 S_cp);
#define GEMSS_determinantn_nocst_gf2 GEMSS_PREFIX_NAME(GEMSS_determinantn_nocst_gf2)

gf2 GEMSS_PREFIX_NAME(GEMSS_determinantn_cst_gf2)(cst_Mn_gf2 S, Mn_gf2 S_cp);
#define GEMSS_determinantn_cst_gf2 GEMSS_PREFIX_NAME(GEMSS_determinantn_cst_gf2)


#if GEMSS_CONSTANT_TIME
    #define GEMSS_determinantn_gf2 GEMSS_determinantn_cst_gf2
#else
    #define GEMSS_determinantn_gf2 GEMSS_determinantn_nocst_gf2
#endif


#endif

