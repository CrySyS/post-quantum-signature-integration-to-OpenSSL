#ifndef _MATRIX_GF2_H
#define _MATRIX_GF2_H

#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_tools_gf2m.h"


/* This type stores a vector of v elements of GF(2) */
typedef UINT* vecv_gf2;
typedef const UINT* cst_vecv_gf2;
/* to use data[length] */
typedef UINT static_vecv_gf2;

/* This type stores a vector of n elements of GF(2) */
typedef UINT* vecn_gf2;
typedef const UINT* cst_vecn_gf2;
/* to use data[length] */
typedef UINT static_vecn_gf2;

/* This type stores a vector of n+v elements of GF(2) */
typedef UINT* vecnv_gf2;
typedef const UINT* cst_vecnv_gf2;
/* to use data[length] */
typedef UINT static_vecnv_gf2;

/* This type stores a vector of m elements of GF(2) */
typedef UINT* vecm_gf2;
typedef const UINT* cst_vecm_gf2;
/* to use data[length] */
typedef UINT static_vecm_gf2;

/* This type stores a vector of (m%64) elements of GF(2) */
typedef UINT* vecmr_gf2;



/* This type stores a matrix n*n in GF(2). */
typedef UINT* Mn_gf2;
typedef const UINT* cst_Mn_gf2;

/* This type stores a matrix (n+v)*(n+v) in GF(2). */
typedef UINT* Mnv_gf2;
typedef const UINT* cst_Mnv_gf2;

/* This type stores a matrix (n+v)*n in GF(2). */
typedef UINT* Mnv_n_gf2;
typedef const UINT* cst_Mnv_n_gf2;

/* This type stores a matrix v*n in GF(2). */
typedef UINT* Mv_n_gf2;
typedef const UINT* cst_Mv_n_gf2;

/* This type stores an invertible matrix n*n in GF(2). */
typedef UINT* GLn_gf2;
typedef const UINT* cst_GLn_gf2;

/* This type stores an invertible matrix (n+v)*(n+v) in GF(2). */
typedef UINT* GLnv_gf2;
typedef const UINT* cst_GLnv_gf2;

/* This type stores a triangular matrix n*n in GF(2).*/
typedef UINT* Tn_gf2;
typedef const UINT* cst_Tn_gf2;

/* This type stores a triangular matrix (n+v)*(n+v) in GF(2).*/
typedef UINT* Tnv_gf2;
typedef const UINT* cst_Tnv_gf2;



/* Number of UINT of matrix n*n in GF(2) */
#define GEMSS_MATRIXn_SIZE (GEMSS_HFEn*GEMSS_NB_WORD_GFqn)
/* Number of UINT of matrix (n+v)*(n+v) in GF(2) */
#define GEMSS_MATRIXnv_SIZE (GEMSS_HFEnv*GEMSS_NB_WORD_GF2nv)
/* Number of UINT of matrix m*m in GF(2) */
#define GEMSS_MATRIXm_SIZE (GEMSS_HFEm*GEMSS_NB_WORD_GF2m)



#define GEMSS_MALLOC_MATRIXn (UINT*)malloc(GEMSS_MATRIXn_SIZE*sizeof(UINT));
#define GEMSS_CALLOC_MATRIXn (UINT*)calloc(GEMSS_MATRIXn_SIZE,sizeof(UINT));

#define GEMSS_MALLOC_MATRIXnv (UINT*)malloc(GEMSS_MATRIXnv_SIZE*sizeof(UINT));
#define GEMSS_CALLOC_MATRIXnv (UINT*)calloc(GEMSS_MATRIXnv_SIZE,sizeof(UINT));



/* Size of lower triangular matrix n*n (in words) */
#define GEMSS_LTRIANGULAR_N_SIZE (((GEMSS_HFEnq*(GEMSS_HFEnq+1))>>1)*GEMSS_NB_BITS_UINT+\
                            GEMSS_NB_WORD_GFqn*GEMSS_HFEnr)
/* Size of lower triangular matrix (n+v)*(n+v) (in words) */
#define GEMSS_LTRIANGULAR_NV_SIZE (((GEMSS_HFEnvq*(GEMSS_HFEnvq+1))>>1)*GEMSS_NB_BITS_UINT+\
                            GEMSS_NB_WORD_GF2nv*GEMSS_HFEnvr)



#endif

