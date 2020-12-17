#ifndef _DIV_GF2NX_H
#define _DIV_GF2NX_H


#include "gemss_prefix_name.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_gf2nx.h"


unsigned int GEMSS_PREFIX_NAME(GEMSS_div_qr_monic_gf2nx)(gf2nx A, unsigned int da,
                                         cst_gf2nx B, unsigned int db);
unsigned int GEMSS_PREFIX_NAME(GEMSS_div_q_monic_gf2nx)(gf2nx A, unsigned int da,
                                        cst_gf2nx B, unsigned int db);
unsigned int GEMSS_PREFIX_NAME(GEMSS_div_r_gf2nx)(gf2nx A, unsigned int da,
                                  cst_gf2nx B, unsigned int db);
void GEMSS_PREFIX_NAME(GEMSS_div_r_monic_cst_gf2nx)(gf2nx A, unsigned int da,
                                    cst_gf2nx B, unsigned int db);
#define GEMSS_div_qr_monic_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_qr_monic_gf2nx)
#define GEMSS_div_r_monic_gf2nx GEMSS_div_qr_monic_gf2nx
#define GEMSS_div_q_monic_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_q_monic_gf2nx)
#define GEMSS_div_r_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_gf2nx)
#define GEMSS_div_r_monic_cst_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_monic_cst_gf2nx)


unsigned int GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_gf2nx)(gf2nx poly, unsigned int dp,
                                          const complete_sparse_monic_gf2nx F,
                                          cst_gf2n cst);
void GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
                                         const complete_sparse_monic_gf2nx F,
                                         cst_gf2n cst);
void GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cst_gf2nx)(gf2nx poly,
                                      const complete_sparse_monic_gf2nx F,
                                      cst_gf2n cst);
#define GEMSS_div_r_HFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_gf2nx)
#define GEMSS_div_r_HFE_cstdeg_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cstdeg_gf2nx)
#define GEMSS_div_r_HFE_cst_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cst_gf2nx)


#if GEMSS_ENABLED_REMOVE_ODD_DEGREE
    void GEMSS_PREFIX_NAME(GEMSS_divsqr_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
                                           const complete_sparse_monic_gf2nx F,
                                           cst_gf2n cst);
    void GEMSS_PREFIX_NAME(GEMSS_divsqr_r_HFE_cst_gf2nx)(gf2nx poly,
                                         const complete_sparse_monic_gf2nx F,
                                         cst_gf2n cst);
    #define GEMSS_divsqr_r_HFE_cstdeg_gf2nx GEMSS_PREFIX_NAME(GEMSS_divsqr_r_HFE_cstdeg_gf2nx)
    #define GEMSS_divsqr_r_HFE_cst_gf2nx GEMSS_PREFIX_NAME(GEMSS_divsqr_r_HFE_cst_gf2nx)
#else
    #define GEMSS_divsqr_r_HFE_cstdeg_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cstdeg_gf2nx)
    #define GEMSS_divsqr_r_HFE_cst_gf2nx GEMSS_PREFIX_NAME(GEMSS_div_r_HFE_cst_gf2nx)
#endif


#endif

