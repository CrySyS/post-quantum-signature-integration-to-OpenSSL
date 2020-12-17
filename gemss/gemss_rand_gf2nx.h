#ifndef _RAND_GF2NX_H
#define _RAND_GF2NX_H

#include "gemss_prefix_name.h"
#include "gemss_parameters_HFE.h"
#include "gemss_gf2nx.h"


void GEMSS_PREFIX_NAME(GEMSS_randMonic_gf2nx)(gf2nx F, unsigned int d);
void GEMSS_PREFIX_NAME(GEMSS_randMonicHFE_gf2nx)(sparse_monic_gf2nx F);

#define GEMSS_randMonic_gf2nx GEMSS_PREFIX_NAME(GEMSS_randMonic_gf2nx)
#define GEMSS_randMonicHFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_randMonicHFE_gf2nx)


#if GEMSS_HFEv
    void GEMSS_PREFIX_NAME(GEMSS_randMonicHFEv_gf2nx)(sparse_monic_gf2nx F);
    #define GEMSS_randMonicHFEv_gf2nx GEMSS_PREFIX_NAME(GEMSS_randMonicHFEv_gf2nx)
#else
    #define GEMSS_randMonicHFEv_gf2nx GEMSS_randMonicHFE_gf2nx
#endif


#if GEMSS_HFEnr
    void GEMSS_PREFIX_NAME(GEMSS_cleanMonicHFE_gf2nx)(sparse_monic_gf2nx F);
    #define GEMSS_cleanMonicHFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_cleanMonicHFE_gf2nx)
#else
    #define GEMSS_cleanMonicHFE_gf2nx
#endif


#if GEMSS_HFEv
    #if GEMSS_HFEnr
        void GEMSS_PREFIX_NAME(GEMSS_cleanMonicHFEv_gf2nx)(sparse_monic_gf2nx F);
        #define GEMSS_cleanMonicHFEv_gf2nx GEMSS_PREFIX_NAME(GEMSS_cleanMonicHFEv_gf2nx)
    #else
        #define GEMSS_cleanMonicHFEv_gf2nx
    #endif
#else
    #define GEMSS_cleanMonicHFEv_gf2nx GEMSS_cleanMonicHFE_gf2nx
#endif


#endif

