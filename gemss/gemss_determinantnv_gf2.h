#ifndef _DETERMINANTNV_GF2_H
#define _DETERMINANTNV_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_gf2.h"
#include "gemss_matrix_gf2.h"
#include "gemss_arch.h"


gf2 GEMSS_PREFIX_NAME(GEMSS_determinantnv_nocst_gf2)(cst_Mnv_gf2 S, Mnv_gf2 S_cp);
#define GEMSS_determinantnv_nocst_gf2 GEMSS_PREFIX_NAME(GEMSS_determinantnv_nocst_gf2)

gf2 GEMSS_PREFIX_NAME(GEMSS_determinantnv_cst_gf2)(cst_Mnv_gf2 S, Mnv_gf2 S_cp);
#define GEMSS_determinantnv_cst_gf2 GEMSS_PREFIX_NAME(GEMSS_determinantnv_cst_gf2)


#if GEMSS_CONSTANT_TIME
    #define GEMSS_determinantnv_gf2 GEMSS_determinantnv_cst_gf2
#else
    #define GEMSS_determinantnv_gf2 GEMSS_determinantnv_nocst_gf2
#endif


#endif

