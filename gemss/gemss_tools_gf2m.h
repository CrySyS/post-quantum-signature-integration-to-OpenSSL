#ifndef _TOOLS_GF2M_H
#define _TOOLS_GF2M_H

#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_macro.h"
#include "gemss_add_gf2x.h"
#include "gemss_init.h"
#include "gemss_bit.h"
#include "gemss_predicate.h"
#include "gemss_loadMask.h"
#include "gemss_dotProduct_gf2.h"


/* This type stores an element of GF(2^m). */
typedef UINT* gf2m;
typedef const UINT* cst_gf2m;
/* to use data[length] */
typedef UINT static_gf2m;


/* m = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_HFEmq (GEMSS_HFEm/GEMSS_NB_BITS_UINT)
#define GEMSS_HFEmr (GEMSS_HFEm%GEMSS_NB_BITS_UINT)
/* The number of word that an element of GF(2^m) needs */
#if (GEMSS_HFEmr)
    #define GEMSS_NB_WORD_GF2m_TMP (GEMSS_HFEmq+1)
#else
    #define GEMSS_NB_WORD_GF2m_TMP GEMSS_HFEmq
#endif

/* Mask to truncate the last word */
#define GEMSS_MASK_GF2m GEMSS_maskUINT(GEMSS_HFEmr)

#define GEMSS_HFEmq8 (GEMSS_HFEm>>3)
#define GEMSS_HFEmr8 (GEMSS_HFEm&7U)
#define GEMSS_HFEmr8c ((8-GEMSS_HFEmr8)&7)

/* Number of bytes that an element of GF(2^m) needs */
#define GEMSS_NB_BYTES_GFqm (GEMSS_HFEmq8+((GEMSS_HFEmr8)?1:0))

/* To choose macro for GEMSS_NB_WORD_GF2m*64 bits */
#if (GEMSS_NB_WORD_GF2m_TMP == 1)
    #define GEMSS_NB_BITS_GFqm_SUP 64
    #define GEMSS_NB_WORD_GF2m 1
#elif (GEMSS_NB_WORD_GF2m_TMP == 2)
    #define GEMSS_NB_BITS_GFqm_SUP 128
    #define GEMSS_NB_WORD_GF2m 2
#elif (GEMSS_NB_WORD_GF2m_TMP == 3)
    #define GEMSS_NB_BITS_GFqm_SUP 192
    #define GEMSS_NB_WORD_GF2m 3
#elif (GEMSS_NB_WORD_GF2m_TMP == 4)
    #define GEMSS_NB_BITS_GFqm_SUP 256
    #define GEMSS_NB_WORD_GF2m 4
#elif (GEMSS_NB_WORD_GF2m_TMP == 5)
    #define GEMSS_NB_BITS_GFqm_SUP 320
    #define GEMSS_NB_WORD_GF2m 5
#elif (GEMSS_NB_WORD_GF2m_TMP == 6)
    #define GEMSS_NB_BITS_GFqm_SUP 384
    #define GEMSS_NB_WORD_GF2m 6
#elif (GEMSS_NB_WORD_GF2m_TMP == 7)
    #define GEMSS_NB_BITS_GFqm_SUP 448
    #define GEMSS_NB_WORD_GF2m 7
#elif (GEMSS_NB_WORD_GF2m_TMP == 8)
    #define GEMSS_NB_BITS_GFqm_SUP 512
    #define GEMSS_NB_WORD_GF2m 8
#endif

#define GEMSS_CONCAT_NB_BITS_GFqm_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_BITS_GFqm_SUP)
#define GEMSS_CONCAT_NB_WORD_GF2m_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_WORD_GF2m)





#define GEMSS_isEqual_gf2m(a,b) GEMSS_f_ISEQUAL(a,b,GEMSS_NB_WORD_GF2m)

#if (GEMSS_NB_WORD_GF2m<7)
    #define GEMSS_add_gf2m GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_ADD),_GF2X)
    #define GEMSS_add2_gf2m GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_ADD),_2_GF2X)
    #define GEMSS_copy_gf2m GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_COPY)
    #define GEMSS_set0_gf2m GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_SET0_)
    #define GEMSS_xorLoadMask1_gf2m GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_XORLOADMASK1_)
    #define GEMSS_dotProduct_gf2_m GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_DOTPRODUCT)
#else
    #define GEMSS_add_gf2m(a,b,c) GEMSS_ADD_GF2X(a,b,c,GEMSS_NB_WORD_GF2m); 
    #define GEMSS_add2_gf2m(a,b) GEMSS_ADD_2_GF2X(a,b,GEMSS_NB_WORD_GF2m); 
    #define GEMSS_copy_gf2m(c,a) GEMSS_COPY(c,a,GEMSS_NB_WORD_GF2m)
    #define GEMSS_set0_gf2m(c) GEMSS_SET0(c,GEMSS_NB_WORD_GF2m)
    #define GEMSS_xorLoadMask1_gf2m(res,a,b) GEMSS_XORLOADMASK1(res,a,b,GEMSS_NB_WORD_GF2m)
    #define GEMSS_dotProduct_gf2_m(res,a,b) GEMSS_DOTPRODUCT(res,a,b,GEMSS_NB_WORD_GF2m)
#endif

#if (GEMSS_NB_WORD_GF2m<10)
    #define GEMSS_isEqual_nocst_gf2m GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GF2m_SUP(GEMSS_ISEQUAL),_NOCST)
#else
    #define GEMSS_isEqual_nocst_gf2m(a,b) GEMSS_f_ISEQUAL_NOCST(a,b,GEMSS_NB_WORD_GF2m)
#endif




/* To choose macro for GEMSS_HFEmq*64 bits */
#if (GEMSS_HFEmq == 1)
    #define GEMSS_NB_BITS_mq_SUP 64
#elif (GEMSS_HFEmq == 2)
    #define GEMSS_NB_BITS_mq_SUP 128
#elif (GEMSS_HFEmq == 3)
    #define GEMSS_NB_BITS_mq_SUP 192
#elif (GEMSS_HFEmq == 4)
    #define GEMSS_NB_BITS_mq_SUP 256
#elif (GEMSS_HFEmq == 5)
    #define GEMSS_NB_BITS_mq_SUP 320
#elif (GEMSS_HFEmq == 6)
    #define GEMSS_NB_BITS_mq_SUP 384
#elif (GEMSS_HFEmq == 7)
    #define GEMSS_NB_BITS_mq_SUP 448
#elif (GEMSS_HFEmq == 8)
    #define GEMSS_NB_BITS_mq_SUP 512
#endif

#define GEMSS_CONCAT_NB_BITS_mq_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_BITS_mq_SUP)





/****************** MEMORY ALIGNMENT ***************************/


/* Size of the alignment in byte */
/* XXX Disabled XXX */
#if (!(GEMSS_NB_WORD_GF2m&3))
    #define GEMSS_SIZE_ALIGNED_GFqm 0/*32*/
#elif (!(GEMSS_NB_WORD_GF2m&1))
    #define GEMSS_SIZE_ALIGNED_GFqm 0/*16*/
#else
    #define GEMSS_SIZE_ALIGNED_GFqm 0
#endif

#if GEMSS_SIZE_ALIGNED_GFqm
    #define GEMSS_ALIGNED_TMP_BUF16 GEMSS_ALIGNED16
    #define GEMSS_ALIGNED_TMP_BUF32 GEMSS_ALIGNED32
    #define GEMSS_STORE128_TMP_BUF GEMSS_PSTORE
    #define GEMSS_STORE256_TMP_BUF GEMSS_VPSTORE
    #define GEMSS_ALIGNED_GFqm_FREE GEMSS_ALIGNED_FREE
#else
    #define GEMSS_ALIGNED_TMP_BUF16
    #define GEMSS_ALIGNED_TMP_BUF32
    #define GEMSS_STORE128_TMP_BUF GEMSS_PSTOREU
    #define GEMSS_STORE256_TMP_BUF GEMSS_VPSTOREU
    #define GEMSS_ALIGNED_GFqm_FREE GEMSS_NO_ALIGNED_FREE
#endif

#if (GEMSS_SIZE_ALIGNED_GFqm==16)
    #define GEMSS_ALIGNED_GFqm GEMSS_ALIGNED16
    #define GEMSS_ALIGNED_GFqm_MALLOC GEMSS_ALIGNED16_MALLOC
    #define GEMSS_ALIGNED_GFqm_CALLOC GEMSS_ALIGNED16_CALLOC

    #define GEMSS_LOAD128_GFqm GEMSS_PLOAD
    #define GEMSS_STORE128_GFqm GEMSS_PSTORE
    /* The both are unaligned */
    #define GEMSS_LOAD256_GFqm GEMSS_VPLOADU
    #define GEMSS_STORE256_GFqm GEMSS_VPSTOREU
#elif (GEMSS_SIZE_ALIGNED_GFqm==32)
    #define GEMSS_ALIGNED_GFqm GEMSS_ALIGNED32
    #define GEMSS_ALIGNED_GFqm_MALLOC GEMSS_ALIGNED32_MALLOC
    #define GEMSS_ALIGNED_GFqm_CALLOC GEMSS_ALIGNED32_CALLOC

    #define GEMSS_LOAD128_GFqm GEMSS_PLOAD
    #define GEMSS_STORE128_GFqm GEMSS_PSTORE
    #define GEMSS_LOAD256_GFqm GEMSS_VPLOAD
    #define GEMSS_STORE256_GFqm GEMSS_VPSTORE
#else
    /* No alignment */
    #define GEMSS_ALIGNED_GFqm
    #define GEMSS_ALIGNED_GFqm_MALLOC GEMSS_NO_ALIGNED_MALLOC
    #define GEMSS_ALIGNED_GFqm_CALLOC GEMSS_NO_ALIGNED_CALLOC

    #define GEMSS_LOAD128_GFqm GEMSS_PLOADU
    #define GEMSS_LOAD256_GFqm GEMSS_VPLOADU
    #define GEMSS_STORE128_GFqm GEMSS_PSTOREU
    #define GEMSS_STORE256_GFqm GEMSS_VPSTOREU
#endif

#define GEMSS_INIT128_GFqm(A128,A) A128=GEMSS_LOAD128_GFqm(A);
#define GEMSS_INIT256_GFqm(A256,A) A256=GEMSS_LOAD256_GFqm(A);





#endif

