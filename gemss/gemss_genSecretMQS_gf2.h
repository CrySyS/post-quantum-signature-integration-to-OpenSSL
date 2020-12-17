#ifndef _GENSECRETMQS_GF2_H
#define _GENSECRETMQS_GF2_H

#include "gemss_prefix_name.h"
#include "gemss_MQS_gf2.h"
#include "gemss_gf2nx.h"
#include "gemss_arch.h"


int GEMSS_PREFIX_NAME(GEMSS_genSecretMQS_gf2_ref)(mqsnv_gf2n MQS, cst_sparse_monic_gf2nx F);
int GEMSS_PREFIX_NAME(GEMSS_genSecretMQS_gf2_opt)(mqsnv_gf2n MQS_res,
                                      cst_sparse_monic_gf2nx F);

#define GEMSS_genSecretMQS_gf2_ref GEMSS_PREFIX_NAME(GEMSS_genSecretMQS_gf2_ref)
#define GEMSS_genSecretMQS_gf2_opt GEMSS_PREFIX_NAME(GEMSS_genSecretMQS_gf2_opt)


#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_genSecretMQS_gf2 GEMSS_genSecretMQS_gf2_ref
#else
    #define GEMSS_genSecretMQS_gf2 GEMSS_genSecretMQS_gf2_opt
#endif


#endif

