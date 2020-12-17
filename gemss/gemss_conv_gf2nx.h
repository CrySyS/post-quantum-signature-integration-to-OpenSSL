#ifndef _CONV_GF2NX_H
#define _CONV_GF2NX_H

#include "gemss_prefix_name.h"
#include "gemss_gf2nx.h"


void GEMSS_PREFIX_NAME(GEMSS_convMonic_gf2nx)(gf2nx F, unsigned int d);
#define GEMSS_convMonic_gf2nx GEMSS_PREFIX_NAME(GEMSS_convMonic_gf2nx)


void GEMSS_PREFIX_NAME(GEMSS_convHFEpolynomialSparseToDense_gf2nx)(gf2nx F_dense,
                                          const complete_sparse_monic_gf2nx F);
#define GEMSS_convHFEpolynomialSparseToDense_gf2nx \
            GEMSS_PREFIX_NAME(GEMSS_convHFEpolynomialSparseToDense_gf2nx)


#endif

