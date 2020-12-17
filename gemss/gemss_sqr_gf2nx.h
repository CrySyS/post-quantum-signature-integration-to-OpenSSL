#ifndef _SQR_GF2NX_H
#define _SQR_GF2NX_H

#include "gemss_prefix_name.h"
#include "gemss_gf2nx.h"


void GEMSS_PREFIX_NAME(GEMSS_sqr_gf2nx)(gf2nx poly, unsigned int d);
void GEMSS_PREFIX_NAME(GEMSS_sqr_HFE_gf2nx)(gf2nx poly);

#define GEMSS_sqr_gf2nx GEMSS_PREFIX_NAME(GEMSS_sqr_gf2nx)
#define GEMSS_sqr_HFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_sqr_HFE_gf2nx)


#endif

