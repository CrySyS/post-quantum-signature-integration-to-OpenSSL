#ifndef _CHOOSEROOTHFE_H
#define _CHOOSEROOTHFE_H

#include <openssl/gemss_choice_crypto.h>
#include "gemss_config_HFE.h"


#ifdef GEMSS_UNIQUE_ROOT
#include "gemss_findRoots_gf2nx.h"
    #define GEMSS_chooseRootHFE_gf2nx GEMSS_findUniqRootHFE_gf2nx
#else
    /* Choose the method to choose the root */
    #ifdef GEMSS_QUARTZ
        #define GEMSS_FIRST_ROOT 0
        #define GEMSS_DETERMINIST_ROOT 0
        #define GEMSS_QUARTZ_ROOT 1
    #else
        #define GEMSS_FIRST_ROOT 0
        #define GEMSS_DETERMINIST_ROOT 1
        #define GEMSS_QUARTZ_ROOT 0
    #endif

    #if ((GEMSS_FIRST_ROOT+GEMSS_DETERMINIST_ROOT+GEMSS_QUARTZ_ROOT)!=1)
        #error "It needs a unique method to choose a root."
    #endif


#include "gemss_prefix_name.h"
#include "gemss_tools_gf2n.h"
#include "gemss_gf2nx.h"

    int GEMSS_PREFIX_NAME(GEMSS_chooseRootHFE_gf2nx)(gf2n root,
                                         const complete_sparse_monic_gf2nx F,
                                         cst_gf2n U);
    #define GEMSS_chooseRootHFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_chooseRootHFE_gf2nx)
#endif


#endif

