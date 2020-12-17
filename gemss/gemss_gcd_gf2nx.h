#ifndef _GCD_GF2NX_H
#define _GCD_GF2NX_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_gf2nx.h"


unsigned int GEMSS_PREFIX_NAME(GEMSS_gcd_gf2nx)(unsigned int* b, gf2nx A, unsigned int da,
                                                     gf2nx B, unsigned int db);
#define GEMSS_gcd_gf2nx GEMSS_PREFIX_NAME(GEMSS_gcd_gf2nx)


#endif

