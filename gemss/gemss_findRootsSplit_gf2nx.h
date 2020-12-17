#ifndef _FINDROOTSSPLIT_GF2NX_H
#define _FINDROOTSSPLIT_GF2NX_H


#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2n.h"
#include "gemss_gf2nx.h"


void GEMSS_PREFIX_NAME(GEMSS_findRootsSplit_gf2nx)(vec_gf2n roots, gf2nx f,
                                       unsigned int deg);
#define GEMSS_findRootsSplit_gf2nx GEMSS_PREFIX_NAME(GEMSS_findRootsSplit_gf2nx)


#endif

