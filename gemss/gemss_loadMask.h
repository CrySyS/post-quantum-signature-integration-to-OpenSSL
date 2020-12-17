#ifndef _LOADMASK_H
#define _LOADMASK_H

#include "gemss_arch.h"


/* Apply the mask b to a, and xor this to res. */
#define GEMSS_XORLOADMASK1(res,a,b,SIZE) \
    GEMSS_FOR_LOOP((res)[GEMSS_RESERVED_VARIABLE]^=(a)[GEMSS_RESERVED_VARIABLE]&(b),SIZE);


/* Inlined version */
#define GEMSS_XORLOADMASK1_1(res,a,b) \
    (res)[0]^=(a)[0]&(b);

#define GEMSS_XORLOADMASK1_2(res,a,b) \
    GEMSS_XORLOADMASK1_1(res,a,b);\
    (res)[1]^=(a)[1]&(b);

#define GEMSS_XORLOADMASK1_3(res,a,b) \
    GEMSS_XORLOADMASK1_2(res,a,b);\
    (res)[2]^=(a)[2]&(b);

#define GEMSS_XORLOADMASK1_4(res,a,b) \
    GEMSS_XORLOADMASK1_3(res,a,b);\
    (res)[3]^=(a)[3]&(b);

#define GEMSS_XORLOADMASK1_5(res,a,b) \
    GEMSS_XORLOADMASK1_4(res,a,b);\
    (res)[4]^=(a)[4]&(b);

#define GEMSS_XORLOADMASK1_6(res,a,b) \
    GEMSS_XORLOADMASK1_5(res,a,b);\
    (res)[5]^=(a)[5]&(b);

#define GEMSS_XORLOADMASK1_7(res,a,b) \
    GEMSS_XORLOADMASK1_6(res,a,b);\
    (res)[6]^=(a)[6]&(b);


#endif

