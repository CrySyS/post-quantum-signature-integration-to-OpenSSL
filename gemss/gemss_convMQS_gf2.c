#include "gemss_convMQS_gf2.h"
#include "gemss_convMQ_gf2.h"
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2nv.h"
#include "gemss_MQS_gf2.h"
#if GEMSS_HFEmr8
    #include <stdlib.h>
#endif


#if GEMSS_HFEmr8
/**
 * @brief   Extraction of the (m mod 8) last equations from a MQS stored with
 * the monomial representation (GF(2^m)[x1,...,x_(n+v)]).
 * @details pk = (c,Q), with c the constant part in GF(2^m) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2^m). The (m mod 8) last
 * equations are stored separately in pk2. The last equations are compressed.
 * pk2 = (c_(m-(m mod 8)),Q_(m-(m mod 8)),...,c_(m-1),Q_(m-1)).
 * The (m mod 8) Qi are upper triangular of size (n+v)*(n+v) in GF(2).
 * The (ci,Qi) are compressed (we take new bytes for each new equation).
 * @param[in]   pk  A MQS stored as one equation in GF(2^m)[x1,...,x_(n+v)],
 * such as each element requires to allocate a multiple of 8 bits.
 * @param[out]  pk2 A MQS in GF(2) with (m mod 8) quadratic equations and n+v
 * variables, in (GF(2)[x1,...,x_(n+v)])^(m mod 8).
 * @remark  Requires to allocate GEMSS_HFEmr8*GEMSS_NB_BYTES_EQUATION bytes for pk2.
 * @remark  Constant-time implementation.
 */
static void convMQS_one_to_last_mr8_equations_gf2(uint8_t* pk2,
                                                  const uint8_t* pk)
{
    const uint8_t* pk_cp;
    unsigned int ir,jq,jr;

    /* To have equivalence between *pk and pk[iq] */
    pk+=GEMSS_HFEmq8;

    /* For each equation of result */
    for(ir=0;ir<GEMSS_HFEmr8;++ir)
    {
        /* Loop on every monomials */

        pk_cp=pk;
        for(jq=0;jq<GEMSS_HFENq8;++jq)
        {
            /* jr=0 */ 
            *pk2=((*pk_cp)>>ir)&GEMSS_ONE8;
            pk_cp+=GEMSS_NB_BYTES_GFqm;
            for(jr=1;jr<8;++jr)
            {
                *pk2^=(((*pk_cp)>>ir)&GEMSS_ONE8)<<jr;
                pk_cp+=GEMSS_NB_BYTES_GFqm;
            }
            ++pk2;
        }

        #if GEMSS_HFENr8
            /* jr=0 */ 
            *pk2=((*pk_cp)>>ir)&GEMSS_ONE8;
            pk_cp+=GEMSS_NB_BYTES_GFqm;
            for(jr=1;jr<GEMSS_HFENr8;++jr)
            {
                *pk2^=(((*pk_cp)>>ir)&GEMSS_ONE8)<<jr;
                pk_cp+=GEMSS_NB_BYTES_GFqm;
            }
            ++pk2;
        #endif
    }
}


/**
 * @brief   Cast from the monomial representation (GF(2^m)[x1,...,x_(n+v)])
 * to a hybrid representation of a MQS.
 * @details pk = (c,Q), with c the constant part in GF(2^m) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2^m). The GEMSS_FORMAT_HYBRID_CPK8 is
 * used for pk2. The (m-(m mod 8)) first equations are stored as one
 * multivariate quadratic equation in GF(2^(m-(m mod 8)))[x1,...,x_(n+v)], i.e.
 * the monomial representation is used. The (m mod 8) last equations are stored
 * separately. Here, the EVAL_HYBRID_CPK8_COMP format is used, i.e. the last
 * equations are compressed with a small padding (when useful) at the end of
 * each equation.
 * mqs = (c',Q',c_(m-(m mod 8)),Q_(m-(m mod 8)),...,c_(m-1),Q_(m-1)).
 * c' is in GF(2^(m-(m mod 8))).
 * Q' is upper triangular of size (n+v)*(n+v) in GF(2^(m-(m mod 8))).
 * The (m mod 8) ci are in GF(2).
 * The (m mod 8) Qi are lower triangular of size (n+v)*(n+v) in GF(2).
 * Here, the ci Qi are compressed.
 * @param[in]   pk  A MQS stored as one equation in GF(2^m)[x1,...,x_(n+v)],
 * such as each element requires to allocate a multiple of 8 bits.
 * @param[out]  pk2 A MQS in GF(2) with m quadratic equations and n+v variables.
 * The (m-(m mod 8)) first equations are stored as an element of 
 * GF(2^(m-(m mod 8)))[x1,...,x_(n+v)]. They are followed by the (m mod 8) last
 * equations, stored as an element of in (GF(2)[x1,...,x_(n+v)])^(m mod 8).
 * @remark  Requires to allocate (GEMSS_NB_MONOMIAL_PK*GEMSS_HFEmq8+GEMSS_NB_BYTES_EQUATION*GEMSS_HFEmr8
 * +((8-(GEMSS_NB_BYTES_EQUATION&7))&7)) bytes for pk2. This size is close to the
 * theoretical size.
 * @remark  Requirement: at least GEMSS_ACCESS_last_equations8 + ((8-(GEMSS_HFEmq8 mod 8))
 * mod 8) bytes have to be allocated for pk2 (because of the future use of
 * GEMSS_evalMQSnocst8_quo_gf2).
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_convMQS_one_eq_to_hybrid_rep8_comp_gf2)(uint8_t* pk2,
                                                         const uint8_t* pk)
{
    #if GEMSS_HFEmq8
        unsigned int i;
    #endif
    unsigned int j;

    #if GEMSS_HFEmr8
        uint8_t *pk_U=(uint8_t*)malloc(GEMSS_HFEmr8*GEMSS_NB_BYTES_EQUATION
                                             *sizeof(uint8_t));

        convMQS_one_to_last_mr8_equations_gf2(pk_U,pk);
        for(j=0;j<GEMSS_HFEmr8;++j)
        {
            GEMSS_convMQ_UL_gf2(pk2+GEMSS_ACCESS_last_equations8+j*GEMSS_NB_BYTES_EQUATION,
                          pk_U+j*GEMSS_NB_BYTES_EQUATION);
        }

        free(pk_U);
    #endif

    #if GEMSS_HFEmq8
        /* Monomial representation */
        for(i=0;i<GEMSS_NB_MONOMIAL_PK;++i)
        {
            for(j=0;j<GEMSS_HFEmq8;++j)
            {
                *pk2=*pk;
                ++pk2;
                ++pk;
            }
            /* Jump the coefficients of the GEMSS_HFEmr8 last equations */
            #if GEMSS_HFEmr8
                ++pk;
            #endif
        }
    #endif
}


#if (GEMSS_EVAL_HYBRID_CPK8_UNCOMP&&GEMSS_HFENr8&&(GEMSS_HFEmr8>1))
/**
 * @brief   Cast from the monomial representation (GF(2^m)[x1,...,x_(n+v)])
 * to a hybrid representation of a MQS.
 * @details pk = (c,Q), with c the constant part in GF(2^m) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2^m). The GEMSS_FORMAT_HYBRID_CPK8 is
 * used for pk2. The (m-(m mod 8)) first equations are stored as one
 * multivariate quadratic equation in GF(2^(m-(m mod 8)))[x1,...,x_(n+v)], i.e.
 * the monomial representation is used. The (m mod 8) last equations are stored
 * separately. Here, the GEMSS_EVAL_HYBRID_CPK8_UNCOMP format is used, i.e. the last
 * equations are compressed, with the goal to have a very easy/fast
 * decompression. The idea is to use the EVAL_HYBRID_CPK8_COMP format, then
 * just to fill the 0 padding of the end of each equation (expected the last),
 * with the bytes of the last equation.
 * mqs = (c',Q',c_(m-(m mod 8)),Q_(m-(m mod 8)),...,c_(m-1),Q_(m-1)).
 * c' is in GF(2^(m-(m mod 8))).
 * Q' is upper triangular of size (n+v)*(n+v) in GF(2^(m-(m mod 8))).
 * The (m mod 8) ci are in GF(2).
 * The (m mod 8) Qi are lower triangular of size (n+v)*(n+v) in GF(2).
 * Here, the ci Qi are compressed.
 * @param[in]   pk  A MQS stored as one equation in GF(2^m)[x1,...,x_(n+v)],
 * such as each element requires to allocate a multiple of 8 bits.
 * @param[out]  pk2 A MQS in GF(2) with m quadratic equations and n+v variables.
 * The (m-(m mod 8)) first equations are stored as an element of 
 * GF(2^(m-(m mod 8)))[x1,...,x_(n+v)]. They are followed by the (m mod 8) last
 * equations, stored as an element of in (GF(2)[x1,...,x_(n+v)])^(m mod 8).
 * @remark  Requires to allocate ((GEMSS_NB_MONOMIAL_PK*GEMSS_HFEm+7)>>3) bytes for pk2.
 * This size is the theoretical size.
 * @remark  Requirement: at least GEMSS_ACCESS_last_equations8 + ((8-(GEMSS_HFEmq8 mod 8))
 * mod 8) bytes have to be allocated for pk2 (because of the future use of
 * GEMSS_evalMQSnocst8_quo_gf2).
 * @remark  This function is equivalent to
 * GEMSS_convMQS_one_eq_to_hybrid_rep8_comp_gf2 when N mod 8 = 0 (the last byte of
 * each equation is already filled) or when m mod 8 = 1 (the equation is
 * already compressed).
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_convMQS_one_eq_to_hybrid_rep8_uncomp_gf2)(uint8_t* pk2,
                                                           const uint8_t* pk)
{
    #if GEMSS_HFEmq8
        unsigned int i;
    #endif
    unsigned int j;

    #if GEMSS_HFEmr8
        uint8_t *pk_U=(uint8_t*)malloc(GEMSS_HFEmr8*GEMSS_NB_BYTES_EQUATION
                                             *sizeof(uint8_t));

        convMQS_one_to_last_mr8_equations_gf2(pk_U,pk);
    
        uint8_t *pk2_cp;
        /* size of val <= 42 bits */
        uint64_t val;

        for(j=0;j<(GEMSS_HFEmr8-1);++j)
        {
            GEMSS_convMQ_UL_gf2(pk2+GEMSS_ACCESS_last_equations8+j*GEMSS_NB_BYTES_EQUATION,
                          pk_U+j*GEMSS_NB_BYTES_EQUATION);
        }

        /* The last equation is smaller because compressed */
        val=GEMSS_convMQ_last_UL_gf2(pk2+GEMSS_ACCESS_last_equations8
                               +j*GEMSS_NB_BYTES_EQUATION,pk_U+j*GEMSS_NB_BYTES_EQUATION);


        /* We put the last bits (stored in val) and we put it in the zero
           padding of each equation (excepted in the last since it is not
           complete since we use its last bits to fill the paddings) */
        pk2_cp=pk2+GEMSS_ACCESS_last_equations8-1;
        for(j=0;j<(GEMSS_HFEmr8-1);++j)
        {
            /* Last byte of the equation */
            pk2_cp+=GEMSS_NB_BYTES_EQUATION;
            *pk2_cp^=((uint8_t)(val>>(j*GEMSS_HFENr8c)))<<GEMSS_HFENr8;
        }

        free(pk_U);
    #endif

    #if GEMSS_HFEmq8
        /* Monomial representation */
        for(i=0;i<GEMSS_NB_MONOMIAL_PK;++i)
        {
            for(j=0;j<GEMSS_HFEmq8;++j)
            {
                *pk2=*pk;
                ++pk2;
                ++pk;
            }
            /* Jump the coefficients of the GEMSS_HFEmr8 last equations */
            #if GEMSS_HFEmr8
                ++pk;
            #endif
        }
    #endif
}
#endif
#endif


