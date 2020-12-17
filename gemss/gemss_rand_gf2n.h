#ifndef _RAND_GF2N_H
#define _RAND_GF2N_H

#include "gemss_tools_gf2n.h"
#include "gemss_randombytes.h"


#if GEMSS_HFEnr
    #define GEMSS_rand_gf2n(A) \
        GEMSS_randombytes((unsigned char*)(A),GEMSS_NB_BYTES_GFqn);\
        /* Clean the last word (included the zero padding) */\
        (A)[GEMSS_NB_WORD_GFqn-1]&=GEMSS_MASK_GF2n;
#else
    #define GEMSS_rand_gf2n(A) \
        GEMSS_randombytes((unsigned char*)(A),GEMSS_NB_BYTES_GFqn);
#endif




#endif

