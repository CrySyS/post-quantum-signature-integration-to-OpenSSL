#ifndef _TOOLS_GF2V_H
#define _TOOLS_GF2V_H

#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_bit.h"


/* v = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_HFEvq (GEMSS_HFEv/GEMSS_NB_BITS_UINT)
#define GEMSS_HFEvr (GEMSS_HFEv%GEMSS_NB_BITS_UINT)
/* The number of word that an element of GF(2^v) needs */
#if (GEMSS_HFEvr)
    #define GEMSS_NB_WORD_GFqv_TMP (GEMSS_HFEvq+1)
#else
    #define GEMSS_NB_WORD_GFqv_TMP GEMSS_HFEvq
#endif

#if (GEMSS_NB_WORD_GFqv_TMP == 1)
    #define GEMSS_NB_WORD_GFqv 1
#elif (GEMSS_NB_WORD_GFqv_TMP == 2)
    #define GEMSS_NB_WORD_GFqv 2
#else
    #define GEMSS_NB_WORD_GFqv GEMSS_NB_WORD_GFqv_TMP
#endif


/* Mask for arithmetic in GF(2^v) */
#define GEMSS_HFE_MASKv GEMSS_maskUINT(GEMSS_HFEvr)

#define GEMSS_HFEvr8 (GEMSS_HFEv&7)
/* Number of bytes that an element of GF(2^(n+v)) needs */
#define GEMSS_NB_BYTES_GFqv ((GEMSS_HFEv>>3)+((GEMSS_HFEvr8)?1:0))




#endif

