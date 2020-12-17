#ifndef _XOR_H
#define _XOR_H

#include "gemss_arch.h"


/* Simple precision. */
#define GEMSS_XOR_WORD(c,a) (c)=(a)^(b);
#define GEMSS_XOR_WORD_2(c,a) (c)^=(a);


/* Xor of buffers. */
#define GEMSS_XOR(c,a,b,SIZE) \
    GEMSS_FOR_LOOP((c)[GEMSS_RESERVED_VARIABLE]=(a)[GEMSS_RESERVED_VARIABLE]\
                                   ^(b)[GEMSS_RESERVED_VARIABLE],SIZE);

#define GEMSS_XOR_2(c,a,SIZE) \
    GEMSS_FOR_LOOP((c)[GEMSS_RESERVED_VARIABLE]^=(a)[GEMSS_RESERVED_VARIABLE],SIZE);


/* Inlined version, c[i]=a[i]^b[i]. */
#define GEMSS_XOR1(c,a,b) \
    (c)[0]=(a)[0]^(b)[0];

#define GEMSS_XOR2(c,a,b) \
    GEMSS_XOR1(c,a,b);\
    (c)[1]=(a)[1]^(b)[1];

#define GEMSS_XOR3(c,a,b) \
    GEMSS_XOR2(c,a,b);\
    (c)[2]=(a)[2]^(b)[2];

#define GEMSS_XOR4(c,a,b) \
    GEMSS_XOR3(c,a,b);\
    (c)[3]=(a)[3]^(b)[3];

#define GEMSS_XOR5(c,a,b) \
    GEMSS_XOR4(c,a,b);\
    (c)[4]=(a)[4]^(b)[4];

#define GEMSS_XOR6(c,a,b) \
    GEMSS_XOR5(c,a,b);\
    (c)[5]=(a)[5]^(b)[5];

#define GEMSS_XOR7(c,a,b) \
    GEMSS_XOR6(c,a,b);\
    (c)[6]=(a)[6]^(b)[6];

#define GEMSS_XOR8(c,a,b) \
    GEMSS_XOR7(c,a,b);\
    (c)[7]=(a)[7]^(b)[7];

#define GEMSS_XOR9(c,a,b) \
    GEMSS_XOR8(c,a,b);\
    (c)[8]=(a)[8]^(b)[8];


/* Inlined version, c[i]^=a[i]. */
#define GEMSS_XOR1_2(c,a) \
    (c)[0]^=(a)[0];

#define GEMSS_XOR2_2(c,a) \
    GEMSS_XOR1_2(c,a);\
    (c)[1]^=(a)[1]; 

#define GEMSS_XOR3_2(c,a) \
    GEMSS_XOR2_2(c,a);\
    (c)[2]^=(a)[2];

#define GEMSS_XOR4_2(c,a) \
    GEMSS_XOR3_2(c,a);\
    (c)[3]^=(a)[3];

#define GEMSS_XOR5_2(c,a) \
    GEMSS_XOR4_2(c,a);\
    (c)[4]^=(a)[4];

#define GEMSS_XOR6_2(c,a) \
    GEMSS_XOR5_2(c,a);\
    (c)[5]^=(a)[5];

#define GEMSS_XOR7_2(c,a) \
    GEMSS_XOR6_2(c,a);\
    (c)[6]^=(a)[6];

#define GEMSS_XOR8_2(c,a) \
    GEMSS_XOR7_2(c,a);\
    (c)[7]^=(a)[7];

#define GEMSS_XOR9_2(c,a) \
    GEMSS_XOR8_2(c,a);\
    (c)[8]^=(a)[8];

#define GEMSS_XOR10_2(c,a) \
    GEMSS_XOR9_2(c,a);\
    (c)[9]^=(a)[9];

#define GEMSS_XOR11_2(c,a) \
    GEMSS_XOR10_2(c,a);\
    (c)[10]^=(a)[10];

#define GEMSS_XOR12_2(c,a) \
    GEMSS_XOR11_2(c,a);\
    (c)[11]^=(a)[11];

#define GEMSS_XOR13_2(c,a) \
    GEMSS_XOR12_2(c,a);\
    (c)[12]^=(a)[12];

#define GEMSS_XOR14_2(c,a) \
    GEMSS_XOR13_2(c,a);\
    (c)[13]^=(a)[13];

#define GEMSS_XOR15_2(c,a) \
    GEMSS_XOR14_2(c,a);\
    (c)[14]^=(a)[14];

#define GEMSS_XOR16_2(c,a) \
    GEMSS_XOR15_2(c,a);\
    (c)[15]^=(a)[15];

#define GEMSS_XOR17_2(c,a) \
    GEMSS_XOR16_2(c,a);\
    (c)[16]^=(a)[16];

#define GEMSS_XOR18_2(c,a) \
    GEMSS_XOR17_2(c,a);\
    (c)[17]^=(a)[17];


#endif

