#ifndef _REM5_GF2N_H
#define _REM5_GF2N_H

/* Tools for pentanomials in GEMSS_rem_gf2n.h */


#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"


#include "gemss_config_gf2n.h"


#ifdef GEMSS___PENTANOMIAL_GF2N__
    #define GEMSS_K164 (64U-GEMSS_K1)
    #define GEMSS_K264 (64U-GEMSS_K2)


    #if (GEMSS_K1>63)
        #define GEMSS_K1mod64 (GEMSS_K1&63U)
    #else
        #define GEMSS_K1mod64 GEMSS_K1
    #endif


    #if (GEMSS_K2>63)
        #define GEMSS_K2mod64 (GEMSS_K2&63U)
    #else
        #define GEMSS_K2mod64 GEMSS_K2
    #endif
#endif




#endif

