#ifndef _TOOLS_GF2N_H
#define _TOOLS_GF2N_H

#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_macro.h"
#include "gemss_init.h"
#include "gemss_bit.h"
#include "gemss_predicate.h"
#include "gemss_loadMask.h"


/* This type stores an element of GF(2^n). */
typedef UINT* gf2n;
typedef const UINT* cst_gf2n;
/* to use data[length] */
typedef UINT static_gf2n;
typedef const UINT cst_static_gf2n;


/* Floor(Log(2,n)) */
#if (GEMSS_HFEn<2)
    #define GEMSS_LOG2_N 0
#elif (GEMSS_HFEn<4)
    #define GEMSS_LOG2_N 1
#elif (GEMSS_HFEn<8)
    #define GEMSS_LOG2_N 2
#elif (GEMSS_HFEn<16)
    #define GEMSS_LOG2_N 3
#elif (GEMSS_HFEn<32)
    #define GEMSS_LOG2_N 4
#elif (GEMSS_HFEn<64)
    #define GEMSS_LOG2_N 5
#elif (GEMSS_HFEn<128)
    #define GEMSS_LOG2_N 6
#elif (GEMSS_HFEn<256)
    #define GEMSS_LOG2_N 7
#elif (GEMSS_HFEn<512)
    #define GEMSS_LOG2_N 8
#elif (GEMSS_HFEn<1024)
    #define GEMSS_LOG2_N 9
#elif (GEMSS_HFEn<2048)
    #define GEMSS_LOG2_N 10
#endif

#define GEMSS_POW_FLOG2_N (1<<GEMSS_LOG2_N)


/* n = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_HFEnq (GEMSS_HFEn/GEMSS_NB_BITS_UINT)
#define GEMSS_HFEnr (GEMSS_HFEn%GEMSS_NB_BITS_UINT)
/* The number of word that an element of GF(2^n) needs */
#if (GEMSS_HFEnr)
    #define GEMSS_NB_WORD_GFqn_TMP (GEMSS_HFEnq+1)
#else
    #define GEMSS_NB_WORD_GFqn_TMP GEMSS_HFEnq
#endif

/* Mask for arithmetic in GF(2^n) */
#define GEMSS_MASK_GF2n GEMSS_maskUINT(GEMSS_HFEnr)

#define GEMSS_HFEnr8 (GEMSS_HFEn&7)
#define GEMSS_MASK8_GF2n ((1U<<GEMSS_HFEnr8)-1)
/* Number of bytes that an element of GF(2^n) needs */
#define GEMSS_NB_BYTES_GFqn ((GEMSS_HFEn>>3)+((GEMSS_HFEnr8)?1:0))




/* To choose macro for GEMSS_NB_WORD_GFqn*64 bits */
#if (GEMSS_NB_WORD_GFqn_TMP == 1)
    #define GEMSS_NB_BITS_GFqn_SUP 64
    #define GEMSS_NB_WORD_GFqn 1
#elif (GEMSS_NB_WORD_GFqn_TMP == 2)
    #define GEMSS_NB_BITS_GFqn_SUP 128
    #define GEMSS_NB_WORD_GFqn 2
#elif (GEMSS_NB_WORD_GFqn_TMP == 3)
    #define GEMSS_NB_BITS_GFqn_SUP 192
    #define GEMSS_NB_WORD_GFqn 3
#elif (GEMSS_NB_WORD_GFqn_TMP == 4)
    #define GEMSS_NB_BITS_GFqn_SUP 256
    #define GEMSS_NB_WORD_GFqn 4
#elif (GEMSS_NB_WORD_GFqn_TMP == 5)
    #define GEMSS_NB_BITS_GFqn_SUP 320
    #define GEMSS_NB_WORD_GFqn 5
#elif (GEMSS_NB_WORD_GFqn_TMP == 6)
    #define GEMSS_NB_BITS_GFqn_SUP 384
    #define GEMSS_NB_WORD_GFqn 6
#elif (GEMSS_NB_WORD_GFqn_TMP == 7)
    #define GEMSS_NB_BITS_GFqn_SUP 448
    #define GEMSS_NB_WORD_GFqn 7
#elif (GEMSS_NB_WORD_GFqn_TMP == 8)
    #define GEMSS_NB_BITS_GFqn_SUP 512
    #define GEMSS_NB_WORD_GFqn 8
#elif (GEMSS_NB_WORD_GFqn_TMP == 9)
    #define GEMSS_NB_BITS_GFqn_SUP 576
    #define GEMSS_NB_WORD_GFqn 9
#endif

#define GEMSS_CONCAT_NB_BITS_GFqn_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_BITS_GFqn_SUP)
#define GEMSS_CONCAT_NB_WORD_GFqn_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_WORD_GFqn)





#define GEMSS_PINIT_GF2N GEMSS_CONCAT_NB_BITS_GFqn_SUP(PINIT)
#define GEMSS_isEqual_gf2n(a,b) GEMSS_f_ISEQUAL(a,b,GEMSS_NB_WORD_GFqn)
#define GEMSS_is0_gf2n(a) GEMSS_f_ISZERO(a,GEMSS_NB_WORD_GFqn)
#define GEMSS_isNot0_gf2n(a) GEMSS_f_ISNOTZERO(a,GEMSS_NB_WORD_GFqn)
#define GEMSS_is1_gf2n(a) GEMSS_f_ISONE(a,GEMSS_NB_WORD_GFqn)
#define GEMSS_cmp_lt_gf2n(a,b) GEMSS_f_CMP_LT(a,b,GEMSS_NB_WORD_GFqn)
#define GEMSS_cmp_gt_gf2n(a,b) GEMSS_f_CMP_GT(a,b,GEMSS_NB_WORD_GFqn)

#if (GEMSS_NB_WORD_GFqn<7)
    #define GEMSS_swap_gf2n GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_SWAP)
    #define GEMSS_copy_gf2n GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_COPY)
    #define GEMSS_set0_gf2n GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_SET0_)
    #define GEMSS_set1_gf2n GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_SET1_)
    #define GEMSS_xorLoadMask1_gf2n GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_XORLOADMASK1_)
#else
    #define GEMSS_swap_gf2n(a,b) GEMSS_SWAP(GEMSS_XOR_2,a,b,GEMSS_NB_WORD_GFqn)
    #define GEMSS_copy_gf2n(c,a) GEMSS_COPY(c,a,GEMSS_NB_WORD_GFqn)
    #define GEMSS_set0_gf2n(c) GEMSS_SET0(c,GEMSS_NB_WORD_GFqn)
    #define GEMSS_set1_gf2n(c) GEMSS_SET1(c,GEMSS_NB_WORD_GFqn)
    #define GEMSS_xorLoadMask1_gf2n(res,a,b) GEMSS_XORLOADMASK1(res,a,b,GEMSS_NB_WORD_GFqn)
#endif

#if (GEMSS_NB_WORD_GFqn<10)
    #define GEMSS_isEqual_nocst_gf2n GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_ISEQUAL),_NOCST)
    #define GEMSS_cmp_lt_nocst_gf2n GEMSS_CONCAT(GEMSS_CONCAT_NB_WORD_GFqn_SUP(GEMSS_CMP_LT),_NOCST)
#else
    #define GEMSS_isEqual_nocst_gf2n(a,b) GEMSS_f_ISEQUAL_NOCST(a,b,GEMSS_NB_WORD_GFqn)
    #define GEMSS_cmp_lt_nocst_gf2n(a,b) GEMSS_f_CMP_LT_NOCST(a,b,GEMSS_NB_WORD_GFqn)
#endif

#define GEMSS_cmp_gt_nocst_gf2n(a,b) GEMSS_cmp_lt_nocst_gf2n(b,a)




/****************** MEMORY ALIGNMENT ***************************/


/* Size of the alignment in byte */
/* XXX Disabled XXX */
#if (!(GEMSS_NB_WORD_GFqn&3))
    #define GEMSS_SIZE_ALIGNED_GFqn 0/*32*/
#elif (!(GEMSS_NB_WORD_GFqn&1))
    #define GEMSS_SIZE_ALIGNED_GFqn 0/*16*/
#else
    #define GEMSS_SIZE_ALIGNED_GFqn 0
#endif

#if GEMSS_SIZE_ALIGNED_GFqn
    #define GEMSS_ALIGNED_GFqn_FREE GEMSS_ALIGNED_FREE
#else
    #define GEMSS_ALIGNED_GFqn_FREE GEMSS_NO_ALIGNED_FREE
#endif

#if (GEMSS_SIZE_ALIGNED_GFqn==16)
    #define GEMSS_ALIGNED_GFqn GEMSS_ALIGNED16
    #define GEMSS_ALIGNED_GFqn_MALLOC GEMSS_ALIGNED16_MALLOC
    #define GEMSS_ALIGNED_GFqn_CALLOC GEMSS_ALIGNED16_CALLOC

    #define GEMSS_LOAD128_GFqn GEMSS_PLOAD
    #define GEMSS_STORE128_GFqn GEMSS_PSTORE
    /* The both are unaligned */
    #define GEMSS_LOAD256_GFqn GEMSS_VPLOADU
    #define GEMSS_STORE256_GFqn GEMSS_VPSTOREU
#elif (GEMSS_SIZE_ALIGNED_GFqn==32)
    #define GEMSS_ALIGNED_GFqn GEMSS_ALIGNED32
    #define GEMSS_ALIGNED_GFqn_MALLOC GEMSS_ALIGNED32_MALLOC
    #define GEMSS_ALIGNED_GFqn_CALLOC GEMSS_ALIGNED32_CALLOC

    #define GEMSS_LOAD128_GFqn GEMSS_PLOAD
    #define GEMSS_STORE128_GFqn GEMSS_PSTORE
    #define GEMSS_LOAD256_GFqn GEMSS_VPLOAD
    #define GEMSS_STORE256_GFqn GEMSS_VPSTORE
#else
    /* No alignment */
    #define GEMSS_ALIGNED_GFqn
    #define GEMSS_ALIGNED_GFqn_MALLOC GEMSS_NO_ALIGNED_MALLOC
    #define GEMSS_ALIGNED_GFqn_CALLOC GEMSS_NO_ALIGNED_CALLOC

    #define GEMSS_LOAD128_GFqn GEMSS_PLOADU
    #define GEMSS_LOAD256_GFqn GEMSS_VPLOADU
    #define GEMSS_STORE128_GFqn GEMSS_PSTOREU
    #define GEMSS_STORE256_GFqn GEMSS_VPSTOREU
#endif

#define GEMSS_INIT128_GFqn(A128,A) A128=GEMSS_LOAD128_GFqn(A);
#define GEMSS_INIT256_GFqn(A256,A) A256=GEMSS_LOAD256_GFqn(A);





/* Number of words of the result of a multiplication */
#if (GEMSS_HFEn<33)
    #define GEMSS_NB_WORD_MUL 1
#elif ((GEMSS_ENABLED_GF2X&&(!defined(GEMSS_MODE_64_BITS)))||(!GEMSS_ENABLED_GF2X))
    /* Only the multiplication of gf2x in 64 bits does not 
       support an odd number of words for the product */
    /* The squaring supports the minimal number of words for the product */
    /* The mod reduction supports the minimal number of words for the product */

    /* Minimal number of words:
       The leading monomial is X^(2*(n-1)), so it needs sup(((2*(n-1)+1)/64)) 
       words. sup(((2*(n-1)+1)/64)) = inf(((2*(n-1)+1)/64) + 1) because 
       (2*(n-1)+1) is odd. A little trick: it is equal to 
       inf(((2*(n-1))/64) + 1) */
    #define GEMSS_NB_WORD_MUL ((((GEMSS_HFEn-1)<<1)/GEMSS_NB_BITS_UINT)+1)
#else
    #define GEMSS_NB_WORD_MUL (GEMSS_NB_WORD_GFqn<<1)
#endif



/* To choose macro for GEMSS_NB_WORD_MUL*32 bits */
#if (GEMSS_NB_WORD_MUL == 1)
    #define GEMSS_NB_BITS_MUL_SUP 32
#elif (GEMSS_NB_WORD_MUL == 2)
    #define GEMSS_NB_BITS_MUL_SUP 64
#elif (GEMSS_NB_WORD_MUL == 3)
    #define GEMSS_NB_BITS_MUL_SUP 96
#elif (GEMSS_NB_WORD_MUL == 4)
    #define GEMSS_NB_BITS_MUL_SUP 128
#elif (GEMSS_NB_WORD_MUL == 5)
    #define GEMSS_NB_BITS_MUL_SUP 160
#elif (GEMSS_NB_WORD_MUL == 6)
    #define GEMSS_NB_BITS_MUL_SUP 192
#elif (GEMSS_NB_WORD_MUL == 7)
    #define GEMSS_NB_BITS_MUL_SUP 224
#elif (GEMSS_NB_WORD_MUL == 8)
    #define GEMSS_NB_BITS_MUL_SUP 256
#elif (GEMSS_NB_WORD_MUL == 9)
    #define GEMSS_NB_BITS_MUL_SUP 288
#elif (GEMSS_NB_WORD_MUL == 10)
    #define GEMSS_NB_BITS_MUL_SUP 320
#elif (GEMSS_NB_WORD_MUL == 11)
    #define GEMSS_NB_BITS_MUL_SUP 352
#elif (GEMSS_NB_WORD_MUL == 12)
    #define GEMSS_NB_BITS_MUL_SUP 384
#elif (GEMSS_NB_WORD_MUL == 13)
    #define GEMSS_NB_BITS_MUL_SUP 416
#elif (GEMSS_NB_WORD_MUL == 14)
    #define GEMSS_NB_BITS_MUL_SUP 448
#elif (GEMSS_NB_WORD_MUL == 15)
    #define GEMSS_NB_BITS_MUL_SUP 480
#elif (GEMSS_NB_WORD_MUL == 16)
    #define GEMSS_NB_BITS_MUL_SUP 512
#elif (GEMSS_NB_WORD_MUL == 17)
    #define GEMSS_NB_BITS_MUL_SUP 544
#elif (GEMSS_NB_WORD_MUL == 18)
    #define GEMSS_NB_BITS_MUL_SUP 576
#endif

#define GEMSS_CONCAT_NB_BITS_MUL_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_BITS_MUL_SUP)



/* Minimum number of words to store the product of 2 (n-1)-elements of GF2[x] */
#define GEMSS_NB_WORD_MMUL_TMP ((((GEMSS_HFEn-1)<<1)/GEMSS_NB_BITS_UINT)+1)


#if (GEMSS_NB_WORD_MMUL_TMP == 1)
    #define GEMSS_NB_WORD_MMUL 1
    #define GEMSS_NB_BITS_MMUL_SUP 32
#elif (GEMSS_NB_WORD_MMUL_TMP == 2)
    #define GEMSS_NB_WORD_MMUL 2
    #define GEMSS_NB_BITS_MMUL_SUP 64
#elif (GEMSS_NB_WORD_MMUL_TMP == 3)
    #define GEMSS_NB_WORD_MMUL 3
    #define GEMSS_NB_BITS_MMUL_SUP 96
#elif (GEMSS_NB_WORD_MMUL_TMP == 4)
    #define GEMSS_NB_WORD_MMUL 4
    #define GEMSS_NB_BITS_MMUL_SUP 128
#elif (GEMSS_NB_WORD_MMUL_TMP == 5)
    #define GEMSS_NB_WORD_MMUL 5
    #define GEMSS_NB_BITS_MMUL_SUP 160
#elif (GEMSS_NB_WORD_MMUL_TMP == 6)
    #define GEMSS_NB_WORD_MMUL 6
    #define GEMSS_NB_BITS_MMUL_SUP 192
#elif (GEMSS_NB_WORD_MMUL_TMP == 7)
    #define GEMSS_NB_WORD_MMUL 7
    #define GEMSS_NB_BITS_MMUL_SUP 224
#elif (GEMSS_NB_WORD_MMUL_TMP == 8)
    #define GEMSS_NB_WORD_MMUL 8
    #define GEMSS_NB_BITS_MMUL_SUP 256
#elif (GEMSS_NB_WORD_MMUL_TMP == 9)
    #define GEMSS_NB_WORD_MMUL 9
    #define GEMSS_NB_BITS_MMUL_SUP 288
#elif (GEMSS_NB_WORD_MMUL_TMP == 10)
    #define GEMSS_NB_WORD_MMUL 10
    #define GEMSS_NB_BITS_MMUL_SUP 320
#elif (GEMSS_NB_WORD_MMUL_TMP == 11)
    #define GEMSS_NB_WORD_MMUL 11
    #define GEMSS_NB_BITS_MMUL_SUP 352
#elif (GEMSS_NB_WORD_MMUL_TMP == 12)
    #define GEMSS_NB_WORD_MMUL 12
    #define GEMSS_NB_BITS_MMUL_SUP 384
#elif (GEMSS_NB_WORD_MMUL_TMP == 13)
    #define GEMSS_NB_WORD_MMUL 13
    #define GEMSS_NB_BITS_MMUL_SUP 416
#elif (GEMSS_NB_WORD_MMUL_TMP == 14)
    #define GEMSS_NB_WORD_MMUL 14
    #define GEMSS_NB_BITS_MMUL_SUP 448
#elif (GEMSS_NB_WORD_MMUL_TMP == 15)
    #define GEMSS_NB_WORD_MMUL 15
    #define GEMSS_NB_BITS_MMUL_SUP 480
#elif (GEMSS_NB_WORD_MMUL_TMP == 16)
    #define GEMSS_NB_WORD_MMUL 16
    #define GEMSS_NB_BITS_MMUL_SUP 512
#elif (GEMSS_NB_WORD_MMUL_TMP == 17)
    #define GEMSS_NB_WORD_MMUL 17
    #define GEMSS_NB_BITS_MMUL_SUP 544
#elif (GEMSS_NB_WORD_MMUL_TMP == 18)
    #define GEMSS_NB_WORD_MMUL 18
    #define GEMSS_NB_BITS_MMUL_SUP 576
#else
    #define GEMSS_NB_WORD_MMUL GEMSS_NB_WORD_MMUL_TMP
#endif


#define GEMSS_CONCAT_NB_WORD_MMUL(name) GEMSS_CONCAT(name,GEMSS_NB_WORD_MMUL)
#define GEMSS_CONCAT_NB_BITS_MMUL_SUP(name) GEMSS_CONCAT(name,GEMSS_NB_BITS_MMUL_SUP)



#if (GEMSS_NB_WORD_MMUL<7)
    #define GEMSS_set0_product_gf2n GEMSS_CONCAT_NB_WORD_MMUL(GEMSS_SET0_)
#else
    #define GEMSS_set0_product_gf2n(c) GEMSS_SET0(c,GEMSS_NB_WORD_MMUL)
#endif

#if (GEMSS_NB_WORD_MMUL==GEMSS_NB_WORD_GFqn)
    /* Nothing to set to 0 */
    #define GEMSS_set0_high_product_gf2n(c)
#else
    #define GEMSS_set0_high_product_gf2n(c) \
            GEMSS_SET0((c)+GEMSS_NB_WORD_GFqn,GEMSS_NB_WORD_MMUL-GEMSS_NB_WORD_GFqn)
#endif



#endif

