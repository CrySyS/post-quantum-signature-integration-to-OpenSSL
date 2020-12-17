#include "gemss_dotProduct_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_mul_gf2n.h"
#include "gemss_rem_gf2n.h"
#include "gemss_simd.h"


/**
 * @brief   Dot product of vectors in GF(2^n).
 * @details The modular reduction is done only at the end.
 * @param[in]   vec_x   A vector of len elements in GF(2^n).
 * @param[in]   vec_y   A vector of len elements in GF(2^n).
 * @param[out]  res res=vec_x.vec_y, in GF(2^n).
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_dotProduct_no_simd_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn],
                     const UINT* vec_x, const UINT* vec_y, unsigned int len)
{
    static_gf2n acc[GEMSS_NB_WORD_MUL], tmp_mul[GEMSS_NB_WORD_MUL];
    unsigned int i;

    /* i=0 */
    GEMSS_mul_gf2x(acc,vec_x,vec_y);

    for(i=1;i<len;++i)
    {
        vec_x+=GEMSS_NB_WORD_GFqn;
        vec_y+=GEMSS_NB_WORD_GFqn;
        GEMSS_mul_gf2x(tmp_mul,vec_x,vec_y);
        GEMSS_add2_product_gf2n(acc,tmp_mul);
    }

    GEMSS_rem_gf2n(res,acc);
}

/**
 * @brief   Sum of two dot products of vectors in GF(2^n).
 * @details The modular reduction is done only at the end.
 * @param[in]   vec_x   A vector of len elements in GF(2^n).
 * @param[in]   vec_y   A vector of len elements in GF(2^n).
 * @param[in]   vec2_x  A vector of len elements in GF(2^n).
 * @param[in]   vec2_y  A vector of len elements in GF(2^n).
 * @param[out]  res res=vec_x.vec_y + vec2_x.vec2_y, in GF(2^n).
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_doubleDotProduct_no_simd_gf2n)(uint64_t res[GEMSS_NB_WORD_GFqn],
                     const UINT* vec_x, const UINT* vec_y,
                     const UINT* vec2_x, const UINT* vec2_y, unsigned int len)
{
    static_gf2n acc[GEMSS_NB_WORD_MUL], tmp_mul[GEMSS_NB_WORD_MUL];
    unsigned int i;

    /* i=0 */
    GEMSS_mul_gf2x(acc,vec_x,vec_y);

    for(i=1;i<len;++i)
    {
        vec_x+=GEMSS_NB_WORD_GFqn;
        vec_y+=GEMSS_NB_WORD_GFqn;
        GEMSS_mul_gf2x(tmp_mul,vec_x,vec_y);
        GEMSS_add2_product_gf2n(acc,tmp_mul);
    }

    for(i=0;i<len;++i)
    {
        GEMSS_mul_gf2x(tmp_mul,vec2_x,vec2_y);
        GEMSS_add2_product_gf2n(acc,tmp_mul);
        vec2_x+=GEMSS_NB_WORD_GFqn;
        vec2_y+=GEMSS_NB_WORD_GFqn;
    }

    GEMSS_rem_gf2n(res,acc);
}


