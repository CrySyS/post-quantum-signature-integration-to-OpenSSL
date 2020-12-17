#ifndef _VECMATPRODUCT_GF2_H
#define _VECMATPRODUCT_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2v.h"
#include "gemss_matrix_gf2.h"


/* To choose the best vector matrix product */

/* (1,n+v)*(n+v,n+v) */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductnv_gf2 GEMSS_vecMatProductnv_64
#else
    #define GEMSS_vecMatProductnv_gf2 GEMSS_vecMatProductnv_64
#endif

/* (1,n+v)*(n+v,n) */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductnvn_gf2 GEMSS_vecMatProductnvn_64
#else
    #define GEMSS_vecMatProductnvn_gf2 GEMSS_vecMatProductnvn_64
#endif

/* (1,v)*(v,n) */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductv_gf2 GEMSS_vecMatProductv_64
#else
    #define GEMSS_vecMatProductv_gf2 GEMSS_vecMatProductv_64
#endif

/* (1,n)*(n,n) */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductn_gf2 GEMSS_vecMatProductn_64
#else
    #define GEMSS_vecMatProductn_gf2 GEMSS_vecMatProductn_64
#endif

/* (1,n)*(n,n) but the result is (1,m) with m <= n */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductm_gf2 GEMSS_vecMatProductm_64
#else
    #define GEMSS_vecMatProductm_gf2 GEMSS_vecMatProductm_64
#endif


/* (1,n+v)*(n+v,n) with "start" */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductnvn_start_gf2 GEMSS_vecMatProductnvn_start_64
#else
    #define GEMSS_vecMatProductnvn_start_gf2 GEMSS_vecMatProductnvn_start_64
#endif


/* (1,n)*(n,n) with "start" */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_vecMatProductn_start_gf2 GEMSS_vecMatProductn_start_64
#else
    #define GEMSS_vecMatProductn_start_gf2 GEMSS_vecMatProductn_start_64
#endif




/* Without SIMD */

/* (1,n+v)*(n+v,n+v) */
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductnv_64)(vecnv_gf2 res, cst_vecnv_gf2 vec,
                                                    cst_Mnv_gf2 S);
/* (1,n+v)*(n+v,n) */
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductnvn_64)(vecn_gf2 res, cst_vecnv_gf2 vec,
                                                    cst_Mnv_n_gf2 S);
/* (1,v)*(v,n) */
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductv_64)(vecn_gf2 res, cst_vecv_gf2 vec,
                                                  cst_Mv_n_gf2 S);
/* (1,n)*(n,n) */
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductn_64)(vecn_gf2 res, cst_vecn_gf2 vec,
                                                  cst_Mn_gf2 S);
/* (1,n)*(n,n) but the result is (1,m) with m <= n */
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductm_64)(vecn_gf2 res, cst_vecn_gf2 vec,
                                                  cst_Mn_gf2 S);

#define GEMSS_vecMatProductnv_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductnv_64)
#define GEMSS_vecMatProductnvn_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductnvn_64)
#define GEMSS_vecMatProductv_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductv_64)
#define GEMSS_vecMatProductn_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductn_64)
#define GEMSS_vecMatProductm_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductm_64)


/* (1,n+v)*(n+v,n) with "start" */
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductnvn_start_64)(vecn_gf2 res, cst_vecnv_gf2 vec,
                                           cst_Mnv_n_gf2 S, unsigned int start);
/* (1,n)*(n,n) with "start" */
/*
void GEMSS_PREFIX_NAME(GEMSS_vecMatProductn_start_64)(vecn_gf2 res, cst_vecn_gf2 vec,
                                          cst_Mn_gf2 S, unsigned int start);
*/
#define GEMSS_vecMatProductnvn_start_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductnvn_start_64)
/*
#define GEMSS_vecMatProductn_start_64 GEMSS_PREFIX_NAME(GEMSS_vecMatProductn_start_64)
*/


#endif

