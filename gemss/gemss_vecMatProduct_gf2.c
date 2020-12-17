#include "gemss_vecMatProduct_gf2.h"
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2n.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_tools_gf2v.h"

/* Compute the vector matrix product */


/* for a block of bits of vec */
#define GEMSS_LOOPIR_M(NB_IT) \
    for(ir=0;ir<NB_IT;++ir)\
    {\
        /* multiply the (iq*GEMSS_NB_BITS_UINT)+ir bit of vec
            by the (iq*GEMSS_NB_BITS_UINT)+ir row of S */\
        vec_ir=-(bit_ir&1);\
        GEMSS_xorLoadMask1_gf2m(res,S_cp,vec_ir);\
        /* next row of S */\
        S_cp+=GEMSS_NB_WORD_GFqn;\
        bit_ir>>=1;\
    }

/* for a block of bits of vec */
#define GEMSS_LOOPIR_N(NB_IT) \
    for(ir=0;ir<NB_IT;++ir)\
    {\
        /* multiply the (iq*GEMSS_NB_BITS_UINT)+ir bit of vec
            by the (iq*GEMSS_NB_BITS_UINT)+ir row of S */\
        vec_ir=-(bit_ir&1);\
        GEMSS_xorLoadMask1_gf2n(res,S_cp,vec_ir);\
        /* next row of S */\
        S_cp+=GEMSS_NB_WORD_GFqn;\
        bit_ir>>=1;\
    }

/* for a block of bits of vec */
#define GEMSS_LOOPIR_START_N(NB_IT) \
    for(;ir<NB_IT;++ir)\
    {\
        /* multiply the (iq*GEMSS_NB_BITS_UINT)+ir bit of vec
            by the (iq*GEMSS_NB_BITS_UINT)+ir row of S */\
        vec_ir=-(bit_ir&1);\
        GEMSS_xorLoadMask1_gf2n(res,S_cp,vec_ir);\
        /* next row of S */\
        S_cp+=GEMSS_NB_WORD_GFqn;\
        bit_ir>>=1;\
    }

/* for a block of bits of vec */
#define GEMSS_LOOPIR_NV(NB_IT) \
    for(ir=0;ir<NB_IT;++ir)\
    {\
        /* multiply the (iq*GEMSS_NB_BITS_UINT)+ir bit of vec
            by the (iq*GEMSS_NB_BITS_UINT)+ir row of S */\
        vec_ir=-(bit_ir&1);\
        GEMSS_xorLoadMask1_gf2nv(res,S_cp,vec_ir);\
        /* next row of S */\
        S_cp+=GEMSS_NB_WORD_GF2nv;\
        bit_ir>>=1;\
    }


#if GEMSS_HFEvr
    #define GEMSS_REM_V(GEMSS_LOOPIR) \
        bit_ir=vec[GEMSS_HFEvq]; \
        GEMSS_LOOPIR(GEMSS_HFEvr);
#else
    #define GEMSS_REM_V(GEMSS_LOOPIR)
#endif

#if GEMSS_HFEmr
    #define GEMSS_CLEAN_M (res)[GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
#else
    #define GEMSS_CLEAN_M
#endif

#if GEMSS_HFEnr
    #define GEMSS_REM_N(GEMSS_LOOPIR) \
        bit_ir=vec[GEMSS_HFEnq]; \
        GEMSS_LOOPIR(GEMSS_HFEnr);

    #define GEMSS_REM_START_N(GEMSS_LOOPIR) \
        bit_ir=vec[GEMSS_HFEnq]>>ir; \
        GEMSS_LOOPIR(GEMSS_HFEnr);

    #define GEMSS_REM_M(GEMSS_LOOPIR) \
        bit_ir=vec[GEMSS_HFEnq]; \
        GEMSS_LOOPIR(GEMSS_HFEnr); \
        GEMSS_CLEAN_M
#else
    #define GEMSS_REM_N(GEMSS_LOOPIR)
    #define GEMSS_REM_START_N(GEMSS_LOOPIR)
    #define GEMSS_REM_M(GEMSS_LOOPIR) GEMSS_CLEAN_M
#endif

#if GEMSS_HFEnvr
    #define GEMSS_REM_NV(GEMSS_LOOPIR) \
        bit_ir=vec[GEMSS_HFEnvq]; \
        GEMSS_LOOPIR(GEMSS_HFEnvr);

    #define GEMSS_REM_START_NV(GEMSS_LOOPIR) \
        bit_ir=vec[GEMSS_HFEnvq]>>ir; \
        GEMSS_LOOPIR(GEMSS_HFEnvr);
#else
    #define GEMSS_REM_NV(GEMSS_LOOPIR)
    #define GEMSS_REM_START_NV(GEMSS_LOOPIR)
#endif


/*  Input:
        vec a vector of length n in GF(2)
        S a matrix n*n in GF(2)

    Output:
        res a vector of length n in GF(2)
        res = dotproduct(v,S) = v.S
*/
#define GEMSS_VECMATPROD(NAME,GEMSS_SET0,GEMSS_LOOPIR,REM,nq) \
void NAME(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S)\
{\
    cst_Mn_gf2 S_cp;\
    UINT bit_ir, vec_ir;\
    unsigned int iq,ir;\
\
    /* initialization of res to 0 */\
    GEMSS_SET0(res);\
\
    S_cp=S;\
    /* for each bit of vec excepted the last block */\
    for(iq=0;iq<nq;++iq)\
    {\
        bit_ir=vec[iq];\
        GEMSS_LOOPIR(GEMSS_NB_BITS_UINT);\
    }\
    /* the last block */\
    REM(GEMSS_LOOPIR);\
}


GEMSS_VECMATPROD(GEMSS_PREFIX_NAME(GEMSS_vecMatProductnv_64),GEMSS_set0_gf2nv,GEMSS_LOOPIR_NV,GEMSS_REM_NV,GEMSS_HFEnvq)
GEMSS_VECMATPROD(GEMSS_PREFIX_NAME(GEMSS_vecMatProductnvn_64),GEMSS_set0_gf2n,GEMSS_LOOPIR_N,GEMSS_REM_NV,GEMSS_HFEnvq)
GEMSS_VECMATPROD(GEMSS_PREFIX_NAME(GEMSS_vecMatProductv_64),GEMSS_set0_gf2n,GEMSS_LOOPIR_N,GEMSS_REM_V,GEMSS_HFEvq)
GEMSS_VECMATPROD(GEMSS_PREFIX_NAME(GEMSS_vecMatProductn_64),GEMSS_set0_gf2n,GEMSS_LOOPIR_N,GEMSS_REM_N,GEMSS_HFEnq)
GEMSS_VECMATPROD(GEMSS_PREFIX_NAME(GEMSS_vecMatProductm_64),GEMSS_set0_gf2m,GEMSS_LOOPIR_M,GEMSS_REM_M,GEMSS_HFEnq)


#define GEMSS_VECMATPROD_START(NAME,GEMSS_SET0,LOOPIR_START,REM_START,nq) \
void NAME(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S, unsigned int start)\
{\
    cst_Mn_gf2 S_cp;\
    UINT bit_ir, vec_ir;\
    unsigned int iq,ir;\
\
    /* initialization of res to 0 */\
    GEMSS_SET0(res);\
\
    S_cp=S;\
    ir=start&63U;\
    /* for each bit of vec excepted the last block */\
    for(iq=start>>6;iq<nq;++iq)\
    {\
        bit_ir=vec[iq]>>ir;\
        LOOPIR_START(GEMSS_NB_BITS_UINT);\
        ir=0;\
    }\
    /* the last block */\
    REM_START(LOOPIR_START);\
}


GEMSS_VECMATPROD_START(GEMSS_PREFIX_NAME(GEMSS_vecMatProductnvn_start_64),GEMSS_set0_gf2n,
                 GEMSS_LOOPIR_START_N,GEMSS_REM_START_NV,GEMSS_HFEnvq)
/*
GEMSS_VECMATPROD_START(GEMSS_PREFIX_NAME(GEMSS_vecMatProductn_start_64),GEMSS_set0_gf2n,
                 GEMSS_LOOPIR_START_N,GEMSS_REM_START_N,GEMSS_HFEnq)
*/



