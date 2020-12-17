#ifndef _FROBENIUSMAP_GF2NX_H
#define _FROBENIUSMAP_GF2NX_H


#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_gf2nx.h"


unsigned int GEMSS_PREFIX_NAME(GEMSS_frobeniusMap_HFE_gf2nx)(gf2nx Xqn, const
                                    complete_sparse_monic_gf2nx F, cst_gf2n U);
#define GEMSS_frobeniusMap_HFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_frobeniusMap_HFE_gf2nx)


/* Multi-squaring at the power 2^GEMSS_II */
/* A script has been used to find the value of GEMSS_II which minimizes the number 
   of multiplication in GF(2^n). */
#if ((GEMSS_HFEDeg==17)||(GEMSS_HFEDeg==18))
    #if(GEMSS_HFEn<40)
        #define GEMSS_II 2
    #elif(GEMSS_HFEn<112)
        #define GEMSS_II 3
    #else
        #define GEMSS_II 4
    #endif
#elif ((GEMSS_HFEDeg==33)||(GEMSS_HFEDeg==34))
    #if(GEMSS_HFEn<32)
        #define GEMSS_II 2
    #elif(GEMSS_HFEn<77)
        #define GEMSS_II 3
    #elif(GEMSS_HFEn<210)
        #define GEMSS_II 4
    #else
        #define GEMSS_II 5
    #endif
#elif ((GEMSS_HFEDeg==129)||(GEMSS_HFEDeg==130))
    #if(GEMSS_HFEn<19)
        #define GEMSS_II 2
    #elif(GEMSS_HFEn<40)
        #define GEMSS_II 3
    #elif(GEMSS_HFEn<102)
        #define GEMSS_II 4
    #elif(GEMSS_HFEn<259)
        #define GEMSS_II 5
    #else
        #define GEMSS_II 6
    #endif
#elif ((GEMSS_HFEDeg==513)||(GEMSS_HFEDeg==514))
    #if(GEMSS_HFEn<11)
        #define GEMSS_II 2
    #elif(GEMSS_HFEn<27)
        #define GEMSS_II 3
    #elif(GEMSS_HFEn<41)
        #define GEMSS_II 4
    #elif(GEMSS_HFEn<109)
        #define GEMSS_II 5
    #elif(GEMSS_HFEn<279)
        #define GEMSS_II 6
    #else
        #define GEMSS_II 7
    #endif
/* Old Gui */
#elif ((GEMSS_HFEn==240)&&(GEMSS_HFEDeg==9))
    #define GEMSS_II 3
#elif ((GEMSS_HFEn==241)&&(GEMSS_HFEDeg==9))
    #define GEMSS_II 3
#elif ((GEMSS_HFEn==249)&&(GEMSS_HFEDeg==9))
    #define GEMSS_II 3
#else
    /* Heuristic for the multi-squaring at the power 2^GEMSS_II */
    #if((!GEMSS_HFEDegI)||(GEMSS_HFEDegI==1))
        #define GEMSS_II 1
    #elif (GEMSS_HFEDegI<9)
        #define GEMSS_II (GEMSS_HFEDegI-1)
    #else
        #define GEMSS_II 7
    #endif
#endif

#define GEMSS_POW_II (GEMSS_ONE32<<GEMSS_II)

/* First k s.t. k*(2^GEMSS_II) >= D, i.e. k = Ceil(D/2^GEMSS_II) */
#define GEMSS_KP ((GEMSS_HFEDeg>>GEMSS_II)+((GEMSS_HFEDeg%GEMSS_POW_II)?1:0))
/* Number of coefficients k s.t. k*(2^GEMSS_II) >= D and k < D */
#define GEMSS_KX (GEMSS_HFEDeg-GEMSS_KP)


unsigned int GEMSS_PREFIX_NAME(GEMSS_frobeniusMap_multisqr_HFE_gf2nx)(gf2nx Xqn, const
                                    complete_sparse_monic_gf2nx F, cst_gf2n U);
#define GEMSS_frobeniusMap_multisqr_HFE_gf2nx \
            GEMSS_PREFIX_NAME(GEMSS_frobeniusMap_multisqr_HFE_gf2nx)


/* Heuristic to choose the fastest function */
/* In particular, it is optimal for GeMSS, Gui and GEMSS_DualModeMS parameters */
#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_HFE_gf2nx
#elif (GEMSS_HFEDeg>=256)
    /* It is the best choice for all n<=576 (or more) */
    #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_HFE_gf2nx

#elif (GEMSS_HFEDeg<=34)
    #if(GEMSS_HFEn>=17)
        /* It is the best choice for all n>=17 */
        #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_multisqr_HFE_gf2nx
    #else
        /* Not necessarily the best choice for D<33 */
        #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_HFE_gf2nx
    #endif

#elif ((GEMSS_HFEDeg==129)||(GEMSS_HFEDeg==130))
    /* Here, we have counted the number of multiplications to choose */
    #if(GEMSS_HFEn<=196)
        #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_HFE_gf2nx
    #elif GEMSS_ENABLED_REMOVE_ODD_DEGREE
        #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_HFE_gf2nx
    #else
        #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_multisqr_HFE_gf2nx
    #endif

#elif (GEMSS_HFEDeg<129)
    /* We need a default choice ... */
    #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_multisqr_HFE_gf2nx

#else
    /* We need a default choice ... */
    #define GEMSS_best_frobeniusMap_HFE_gf2nx GEMSS_frobeniusMap_HFE_gf2nx
#endif


#endif

