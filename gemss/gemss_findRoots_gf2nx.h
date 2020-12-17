#ifndef _FINDROOTS_GF2NX_H
#define _FINDROOTS_GF2NX_H

#include "gemss_prefix_name.h"
#include "gemss_matrix_gf2n.h"
#include "gemss_tools_gf2n.h"
#include "gemss_gf2nx.h"


#include "gemss_conv_gf2nx.h"


/* GCD(F-U, X^(2^n)-X mod (F-U)) */
/* To know the number of roots of F-U */
#define GEMSS_firstStepHFE_gf2nx(l,i,poly,poly2,F,U) \
    /* X^(2^n) - X mod (F-U) */\
    l=GEMSS_best_frobeniusMap_HFE_gf2nx(poly,F,U);\
    /* Initialize to F */\
    GEMSS_convHFEpolynomialSparseToDense_gf2nx(poly2,F);\
    /* Initialize to F-U */\
    GEMSS_add2_gf2n(poly2,U);\
    l=GEMSS_gcd_gf2nx(&i,poly2,d2,poly,l);


int GEMSS_PREFIX_NAME(GEMSS_findRootsHFE_gf2nx)(vec_gf2n* roots,
                                    const complete_sparse_monic_gf2nx F,
                                    cst_gf2n U);
int GEMSS_PREFIX_NAME(GEMSS_findUniqRootHFE_gf2nx)(gf2n root,
                                       const complete_sparse_monic_gf2nx F,
                                       cst_gf2n U);
#define GEMSS_findRootsHFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_findRootsHFE_gf2nx)
#define GEMSS_findUniqRootHFE_gf2nx GEMSS_PREFIX_NAME(GEMSS_findUniqRootHFE_gf2nx)


#endif

