#ifndef _INIT_H
#define _INIT_H

#include "gemss_xor.h"


/* Swap */
/* a,b = b,a */
#define GEMSS_SWAP(GEMSS_XOR_2,a,b,SIZE) \
    GEMSS_XOR_2(a,b,SIZE); \
    GEMSS_XOR_2(b,a,SIZE); \
    GEMSS_XOR_2(a,b,SIZE);


/* Inlined version */
#define GEMSS_SWAP_MACRO(GEMSS_XOR_2,a,b) \
    GEMSS_XOR_2(a,b); \
    GEMSS_XOR_2(b,a); \
    GEMSS_XOR_2(a,b);

#define GEMSS_SWAP_WORD(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR_WORD_2,a,b);
#define GEMSS_SWAP1(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR1_2,a,b);
#define GEMSS_SWAP2(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR2_2,a,b);
#define GEMSS_SWAP3(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR3_2,a,b);
#define GEMSS_SWAP4(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR4_2,a,b);
#define GEMSS_SWAP5(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR5_2,a,b);
#define GEMSS_SWAP6(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR6_2,a,b);
#define GEMSS_SWAP7(a,b) GEMSS_SWAP_MACRO(GEMSS_XOR7_2,a,b);


/* Copy */
#define GEMSS_COPY(c,a,SIZE) \
    GEMSS_FOR_LOOP((c)[GEMSS_RESERVED_VARIABLE]=(a)[GEMSS_RESERVED_VARIABLE],SIZE)


/* Inlined version */
#define GEMSS_COPY1(c,a) \
    (c)[0]=(a)[0];

#define GEMSS_COPY2(c,a) \
    GEMSS_COPY1(c,a);\
    (c)[1]=(a)[1];

#define GEMSS_COPY3(c,a) \
    GEMSS_COPY2(c,a); \
    (c)[2]=(a)[2];

#define GEMSS_COPY4(c,a) \
    GEMSS_COPY3(c,a); \
    (c)[3]=(a)[3];

#define GEMSS_COPY5(c,a) \
    GEMSS_COPY4(c,a); \
    (c)[4]=(a)[4];

#define GEMSS_COPY6(c,a) \
    GEMSS_COPY5(c,a); \
    (c)[5]=(a)[5];

#define GEMSS_COPY7(c,a) \
    GEMSS_COPY6(c,a); \
    (c)[6]=(a)[6];

#define GEMSS_COPY8(c,a) \
    GEMSS_COPY7(c,a); \
    (c)[7]=(a)[7];

#define GEMSS_COPY9(c,a) \
    GEMSS_COPY8(c,a); \
    (c)[8]=(a)[8];


/* Init to 0 */
#define GEMSS_SET0(c,SIZE) \
    GEMSS_FOR_LOOP((c)[GEMSS_RESERVED_VARIABLE]=0,SIZE)


/* Inlined version */
#define GEMSS_SET0_1(c) \
    (c)[0]=0;

#define GEMSS_SET0_2(c) \
    GEMSS_SET0_1(c);\
    (c)[1]=0;

#define GEMSS_SET0_3(c) \
    GEMSS_SET0_2(c);\
    (c)[2]=0;

#define GEMSS_SET0_4(c) \
    GEMSS_SET0_3(c);\
    (c)[3]=0;

#define GEMSS_SET0_5(c) \
    GEMSS_SET0_4(c);\
    (c)[4]=0;

#define GEMSS_SET0_6(c) \
    GEMSS_SET0_5(c);\
    (c)[5]=0;

#define GEMSS_SET0_7(c) \
    GEMSS_SET0_6(c);\
    (c)[6]=0;


/* Init to 1 */
#define GEMSS_SET1(c,SIZE) \
    (c)[0]=1;\
    GEMSS_FOR_LOOP((c)[GEMSS_RESERVED_VARIABLE+1]=0,(SIZE)-1)


/* Inlined version */
#define GEMSS_SET1_1(c) \
    (c)[0]=1; \

#define GEMSS_SET1_2(c) \
    GEMSS_SET1_1(c);\
    GEMSS_SET0_1(c+1);

#define GEMSS_SET1_3(c) \
    GEMSS_SET1_1(c);\
    GEMSS_SET0_2(c+1);

#define GEMSS_SET1_4(c) \
    GEMSS_SET1_1(c);\
    GEMSS_SET0_3(c+1);

#define GEMSS_SET1_5(c) \
    GEMSS_SET1_1(c);\
    GEMSS_SET0_4(c+1);

#define GEMSS_SET1_6(c) \
    GEMSS_SET1_1(c);\
    GEMSS_SET0_5(c+1);


#endif

