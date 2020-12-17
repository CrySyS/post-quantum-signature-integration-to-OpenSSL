#ifndef _RANDMATRIX_GF2_H
#define _RANDMATRIX_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_parameters_HFE.h"
#include "gemss_matrix_gf2.h"


#if GEMSS_HFEnr
    void GEMSS_PREFIX_NAME(GEMSS_cleanMatrix_gf2_n)(Mn_gf2 S);
    #define GEMSS_cleanMatrix_gf2_n GEMSS_PREFIX_NAME(GEMSS_cleanMatrix_gf2_n)
#endif
#if GEMSS_HFEnvr
    void GEMSS_PREFIX_NAME(GEMSS_cleanMatrix_gf2_nv)(Mnv_gf2 S);
    #define GEMSS_cleanMatrix_gf2_nv GEMSS_PREFIX_NAME(GEMSS_cleanMatrix_gf2_nv)
#else
    #define GEMSS_cleanMatrix_gf2_nv GEMSS_cleanMatrix_gf2_n
#endif


void GEMSS_PREFIX_NAME(GEMSS_randMatrix_gf2_n)(Mn_gf2 S);
#define GEMSS_randMatrix_gf2_n GEMSS_PREFIX_NAME(GEMSS_randMatrix_gf2_n)
#if GEMSS_HFEv
    void GEMSS_PREFIX_NAME(GEMSS_randMatrix_gf2_nv)(Mnv_gf2 S);
    #define GEMSS_randMatrix_gf2_nv GEMSS_PREFIX_NAME(GEMSS_randMatrix_gf2_nv)
#else
    #define GEMSS_randMatrix_gf2_nv GEMSS_randMatrix_gf2_n
#endif

void GEMSS_PREFIX_NAME(GEMSS_cleanLowerMatrixn)(Tn_gf2 L);
void GEMSS_PREFIX_NAME(GEMSS_genLowerMatrixn)(Tn_gf2 L);
#define GEMSS_cleanLowerMatrixn GEMSS_PREFIX_NAME(GEMSS_cleanLowerMatrixn)
#define GEMSS_genLowerMatrixn GEMSS_PREFIX_NAME(GEMSS_genLowerMatrixn)
#if GEMSS_HFEv
    void GEMSS_PREFIX_NAME(GEMSS_cleanLowerMatrixnv)(Tnv_gf2 L);
    void GEMSS_PREFIX_NAME(GEMSS_genLowerMatrixnv)(Tnv_gf2 L);
    #define GEMSS_cleanLowerMatrixnv GEMSS_PREFIX_NAME(GEMSS_cleanLowerMatrixnv)
    #define GEMSS_genLowerMatrixnv GEMSS_PREFIX_NAME(GEMSS_genLowerMatrixnv)
#else
    #define GEMSS_cleanLowerMatrixnv GEMSS_cleanLowerMatrixn
    #define GEMSS_genLowerMatrixnv GEMSS_genLowerMatrixn
#endif

#define GEMSS_GEN_LU_Tn(L,U) \
    GEMSS_genLowerMatrixn(L);\
    /* Generate the transpose of U */\
    GEMSS_genLowerMatrixn(U);

#define GEMSS_GEN_LU_Tnv(L,U) \
    GEMSS_genLowerMatrixnv(L);\
    /* Generate the transpose of U */\
    GEMSS_genLowerMatrixnv(U);

void GEMSS_PREFIX_NAME(GEMSS_randInvMatrix_gf2_n)(GLn_gf2 S, Mn_gf2 S_cp);
#define GEMSS_randInvMatrix_gf2_n GEMSS_PREFIX_NAME(GEMSS_randInvMatrix_gf2_n)
#if GEMSS_HFEv
    void GEMSS_PREFIX_NAME(GEMSS_randInvMatrix_gf2_nv)(GLnv_gf2 S, Mnv_gf2 S_cp);
    #define GEMSS_randInvMatrix_gf2_nv GEMSS_PREFIX_NAME(GEMSS_randInvMatrix_gf2_nv)
#else
    #define GEMSS_randInvMatrix_gf2_nv GEMSS_randInvMatrix_gf2_n
#endif

void GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_n)(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U);
#define GEMSS_mulMatricesLU_gf2_n GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_n)
#if GEMSS_HFEv
    void GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_nv)(Mnv_gf2 S, cst_Tnv_gf2 L,
                                                        cst_Tnv_gf2 U);
    #define GEMSS_mulMatricesLU_gf2_nv GEMSS_PREFIX_NAME(GEMSS_mulMatricesLU_gf2_nv)
#else
    #define GEMSS_mulMatricesLU_gf2_nv GEMSS_mulMatricesLU_gf2_n
#endif


#define GEMSS_randInvMatrixLU_gf2_n(S,L,U) \
            GEMSS_GEN_LU_Tn(L,U);\
            GEMSS_mulMatricesLU_gf2_n(S,L,U);

#define GEMSS_randInvMatrixLU_gf2_nv(S,L,U) \
            GEMSS_GEN_LU_Tnv(L,U);\
            GEMSS_mulMatricesLU_gf2_nv(S,L,U);


#endif

