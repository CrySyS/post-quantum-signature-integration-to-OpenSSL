#ifndef _DOTPRODUCT_GF2_H
#define _DOTPRODUCT_GF2_H

#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_macro.h"
#include "gemss_tools_gf2n.h"
#include "gemss_bit.h"


/* Dot product of vector of bits */
#define GEMSS_DOTPRODUCT(res,a,b,SIZE) \
    res=(a)[0]&(b)[0];\
    GEMSS_FOR_LOOP_COMPLETE(1,GEMSS_RESERVED_VARIABLE<(SIZE),++GEMSS_RESERVED_VARIABLE,\
                        res^=(a)[GEMSS_RESERVED_VARIABLE]&(b)[GEMSS_RESERVED_VARIABLE])\
    GEMSS_XORBITS_UINT(res);


/* Inlined version */
#define GEMSS_DOTPRODUCT1(res,a,b) \
    res=(a)[0]&(b)[0];\
    GEMSS_XORBITS_UINT(res);

#define GEMSS_DOTPRODUCT2(res,a,b) \
    res=(a)[0]&(b)[0];\
    res^=(a)[1]&(b)[1];\
    GEMSS_XORBITS_UINT(res);

#define GEMSS_DOTPRODUCT3(res,a,b) \
    res=(a)[0]&(b)[0];\
    res^=(a)[1]&(b)[1];\
    res^=(a)[2]&(b)[2];\
    GEMSS_XORBITS_UINT(res);

#define GEMSS_DOTPRODUCT4(res,a,b) \
    res=(a)[0]&(b)[0];\
    res^=(a)[1]&(b)[1];\
    res^=(a)[2]&(b)[2];\
    res^=(a)[3]&(b)[3];\
    GEMSS_XORBITS_UINT(res);

#define GEMSS_DOTPRODUCT5(res,a,b) \
    res=(a)[0]&(b)[0];\
    res^=(a)[1]&(b)[1];\
    res^=(a)[2]&(b)[2];\
    res^=(a)[3]&(b)[3];\
    res^=(a)[4]&(b)[4];\
    GEMSS_XORBITS_UINT(res);

#define GEMSS_DOTPRODUCT6(res,a,b) \
    res=(a)[0]&(b)[0];\
    res^=(a)[1]&(b)[1];\
    res^=(a)[2]&(b)[2];\
    res^=(a)[3]&(b)[3];\
    res^=(a)[4]&(b)[4];\
    res^=(a)[5]&(b)[5];\
    GEMSS_XORBITS_UINT(res);


#if (GEMSS_NB_WORD_GFqn<7)
    #define GEMSS_dotProduct_gf2_n GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_DOTPRODUCT)
#else
    #define GEMSS_dotProduct_gf2_n(res,a,b) GEMSS_DOTPRODUCT(res,a,b,GEMSS_NB_WORD_GFqn)
#endif


#endif

