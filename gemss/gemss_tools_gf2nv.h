#ifndef _TOOLS_GF2NV_H
#define _TOOLS_GF2NV_H

#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_macro.h"
#include "gemss_add_gf2x.h"
#include "gemss_init.h"
#include "gemss_bit.h"
#include "gemss_loadMask.h"
#include "gemss_tools_gf2m.h"


/* This type stores an element of GF(2^(n+v)). */
typedef UINT* gf2nv;
typedef const UINT* cst_gf2nv;
/* to use data[length] */
typedef UINT static_gf2nv;


/* n+v = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_HFEnvq (GEMSS_HFEnv/GEMSS_NB_BITS_UINT)
#define GEMSS_HFEnvr (GEMSS_HFEnv%GEMSS_NB_BITS_UINT)
/* The number of word that an element of GF(2^(n+v)) needs */
#if (GEMSS_HFEnvr)
    #define GEMSS_NB_WORD_GF2nv_TMP (GEMSS_HFEnvq+1)
#else
    #define GEMSS_NB_WORD_GF2nv_TMP GEMSS_HFEnvq
#endif

/* Mask for arithmetic in GF(2^(n+v)) */
#define GEMSS_MASK_GF2nv GEMSS_maskUINT(GEMSS_HFEnvr)

#define GEMSS_HFEnvq8 (GEMSS_HFEnv>>3)
#define GEMSS_HFEnvr8 (GEMSS_HFEnv&7)
#define GEMSS_MASK8_GF2nv ((1U<<GEMSS_HFEnvr8)-1)
/* Number of bytes that an element of GF(2^(n+v)) needs */
#define GEMSS_NB_BYTES_GFqnv (GEMSS_HFEnvq8+((GEMSS_HFEnvr8)?1:0))




/* To choose macro for GEMSS_NB_WORD_GF2nv*64 bits */
#if (GEMSS_NB_WORD_GF2nv_TMP == 1)
    #define GEMSS_NB_BITS_GFqnv_SUP 64
    #define GEMSS_NB_WORD_GF2nv 1
#elif (GEMSS_NB_WORD_GF2nv_TMP == 2)
    #define GEMSS_NB_BITS_GFqnv_SUP 128
    #define GEMSS_NB_WORD_GF2nv 2
#elif (GEMSS_NB_WORD_GF2nv_TMP == 3)
    #define GEMSS_NB_BITS_GFqnv_SUP 192
    #define GEMSS_NB_WORD_GF2nv 3
#elif (GEMSS_NB_WORD_GF2nv_TMP == 4)
    #define GEMSS_NB_BITS_GFqnv_SUP 256
    #define GEMSS_NB_WORD_GF2nv 4
#elif (GEMSS_NB_WORD_GF2nv_TMP == 5)
    #define GEMSS_NB_BITS_GFqnv_SUP 320
    #define GEMSS_NB_WORD_GF2nv 5
#elif (GEMSS_NB_WORD_GF2nv_TMP == 6)
    #define GEMSS_NB_BITS_GFqnv_SUP 384
    #define GEMSS_NB_WORD_GF2nv 6
#elif (GEMSS_NB_WORD_GF2nv_TMP == 7)
    #define GEMSS_NB_BITS_GFqnv_SUP 448
    #define GEMSS_NB_WORD_GF2nv 7
#elif (GEMSS_NB_WORD_GF2nv_TMP == 8)
    #define GEMSS_NB_BITS_GFqnv_SUP 512
    #define GEMSS_NB_WORD_GF2nv 8
#elif (GEMSS_NB_WORD_GF2nv_TMP == 9)
    #define GEMSS_NB_BITS_GFqnv_SUP 576
    #define GEMSS_NB_WORD_GF2nv 9
#elif (GEMSS_NB_WORD_GF2nv_TMP == 10)
    #define GEMSS_NB_BITS_GFqnv_SUP 640
    #define GEMSS_NB_WORD_GF2nv 10
#endif

#define GEMSS_CONCAT_NB_BITS_GFqnv_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_BITS_GFqnv_SUP)
#define GEMSS_CONCAT_NB_WORD_GF2nv_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_WORD_GF2nv)





#if (GEMSS_NB_WORD_GF2nv<7)
    #define GEMSS_add_gf2nv GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GF2nv_SUP(GEMSS_ADD),_GF2X)
    #define GEMSS_add2_gf2nv GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GF2nv_SUP(GEMSS_ADD),_2,_GF2X)
    #define GEMSS_swap_gf2nv GEMSS_CONCAT_NB_WORD_GF2nv_SUP(GEMSS_SWAP)
    #define GEMSS_set0_gf2nv GEMSS_CONCAT_NB_WORD_GF2nv_SUP(GEMSS_SET0_)
    #define GEMSS_xorLoadMask1_gf2nv GEMSS_CONCAT_NB_WORD_GF2nv_SUP(GEMSS_XORLOADMASK1_)
#else
    #define GEMSS_add_gf2nv(a,b,c) GEMSS_ADD_GF2X(a,b,c,GEMSS_NB_WORD_GF2nv)
    #define GEMSS_add2_gf2nv(a,b) GEMSS_ADD_2_GF2X(a,b,GEMSS_NB_WORD_GF2nv)
    #define GEMSS_swap_gf2nv(a,b) GEMSS_SWAP(GEMSS_XOR_2,a,b,GEMSS_NB_WORD_GF2nv)
    #define GEMSS_set0_gf2nv(c) GEMSS_SET0(c,GEMSS_NB_WORD_GF2nv)
    #define GEMSS_xorLoadMask1_gf2nv(res,a,b) GEMSS_XORLOADMASK1(res,a,b,GEMSS_NB_WORD_GF2nv)
#endif





#if ((GEMSS_HFEn==GEMSS_HFEm)&&(!GEMSS_HFEv))
    /* This case is never used */
    #define GEMSS_NB_WORD_GF2nvm 0U
#else
    #define GEMSS_NB_WORD_GF2nvm (GEMSS_NB_WORD_GF2nv-GEMSS_NB_WORD_GF2m+(GEMSS_HFEmr?1:0))
#endif

#define GEMSS_MASK_GF2nvm (~GEMSS_MASK_GF2m)


/* To choose macro for GEMSS_NB_WORD_GF2nvm*64 bits */
#if (GEMSS_NB_WORD_GF2nvm == 1)
    #define GEMSS_copy_gf2nvm GEMSS_COPY1
#elif (GEMSS_NB_WORD_GF2nvm == 2)
    #define GEMSS_copy_gf2nvm GEMSS_COPY2
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY1
#elif (GEMSS_NB_WORD_GF2nvm == 3)
    #define GEMSS_copy_gf2nvm GEMSS_COPY3
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY2
#elif (GEMSS_NB_WORD_GF2nvm == 4)
    #define GEMSS_copy_gf2nvm GEMSS_COPY4
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY3
#elif (GEMSS_NB_WORD_GF2nvm == 5)
    #define GEMSS_copy_gf2nvm GEMSS_COPY5
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY4
#elif (GEMSS_NB_WORD_GF2nvm == 6)
    #define GEMSS_copy_gf2nvm GEMSS_COPY6
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY5
#elif (GEMSS_NB_WORD_GF2nvm == 7)
    #define GEMSS_copy_gf2nvm GEMSS_COPY7
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY6
#elif (GEMSS_NB_WORD_GF2nvm == 8)
    #define GEMSS_copy_gf2nvm GEMSS_COPY8
    #define GEMSS_copy_gf2nvm1 GEMSS_COPY7
#endif





#endif

