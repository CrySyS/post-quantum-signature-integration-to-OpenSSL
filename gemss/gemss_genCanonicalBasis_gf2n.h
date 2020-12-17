#ifndef _GENCANONICALBASIS_GF2N_H
#define _GENCANONICALBASIS_GF2N_H


#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2n.h"


void GEMSS_PREFIX_NAME(GEMSS_genCanonicalBasis_gf2n)(vec_gf2n alpha_vec);
void GEMSS_PREFIX_NAME(GEMSS_genCanonicalBasisVertical_gf2n)(vec_gf2n alpha_vec);
#define GEMSS_genCanonicalBasis_gf2n GEMSS_PREFIX_NAME(GEMSS_genCanonicalBasis_gf2n)
#define GEMSS_genCanonicalBasisVertical_gf2n \
            GEMSS_PREFIX_NAME(GEMSS_genCanonicalBasisVertical_gf2n)


#endif

