#include "gemss_evalMQShybrid_gf2.h"
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2n.h"
#include "gemss_dotProduct_gf2.h"
#include "gemss_MQ_gf2.h"

#if GEMSS_HFEmr
#include "gemss_bit.h"
#include "gemss_evalMQnocst_gf2.h"
#endif

#if GEMSS_HFEmq8
#include "gemss_evalMQSnocst8_quo_gf2.h"
#endif


/**
 * @brief   Variable-time evaluation of a MQS in a vector. The MQS is stored
 * with a hybrid representation.
 * @details The GEMSS_FORMAT_HYBRID_CPK8 have to be used. The (m-(m mod 8)) first
 * equations are stored as one multivariate quadratic equation in
 * GF(2^(m-(m mod 8)))[x1,...,x_(n+v)], i.e. the monomial representation is
 * used. This corresponds to mq_quo. The (m mod 8) last equations are stored
 * separately in mq_rem. Here, the GEMSS_EVAL_HYBRID_CPK8_UNCOMP have to be used, i.e.
 * the last equations are uncompressed.
 * mq_quo = (c',Q').
 * mq_rem = (c_(m-(m mod 8)),Q_(m-(m mod 8)),...,c_(m-1),Q_(m-1)).
 * c' is in GF(2^(m-(m mod 8))).
 * Q' is upper triangular of size (n+v)*(n+v) in GF(2^(m-(m mod 8))).
 * The (m mod 8) ci are in GF(2).
 * The (m mod 8) Qi are lower triangular of size (n+v)*(n+v) in GF(2).
 * For each Qi, the rows are stored separately (we take new words for each new
 * row).
 * @param[in]   x   A vector of n+v elements in GF(2).
 * @param[in]   mq_quo  The (m-(m mod 8)) first equations,
 * in GF(2^(m-(m mod 8)))[x1,...,x_(n+v)].
 * @param[in]   mq_rem  The (m mod 8) last equations,
 * in (GF(2)[x1,...,x_(n+v)])^(m mod 8).
 * @param[out]  res A vector of m elements in GF(2), evaluation of the MQS in x.
 * @remark  Requirement: at least GEMSS_ACCESS_last_equations8 + ((8-(GEMSS_HFEmq8 mod 8))
 * mod 8) bytes have to be allocated for mq_quo (because of the use of
 * GEMSS_evalMQSnocst8_quo_gf2).
 * @remark  If a vector version of GEMSS_evalMQnocst_gf2 is used, maybe the last
 * vector load read outside of memory. So, if this load reads z bits, let
 * B be ceiling(z/64). The last equation requires GEMSS_NB_WORD_UNCOMP_EQ
 * + ((B-(GEMSS_NB_WORD_GF2nv mod B)) mod B) 64-bit words.
 * @remark  Variable-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_evalMQShybrid8_uncomp_nocst_gf2_m)(vecm_gf2 res,
                                                    cst_vecnv_gf2 x,
                                                    const uint8_t* mq_quo,
                                                    const UINT* mq_rem)
{
    #if GEMSS_HFEmq8
        GEMSS_evalMQSnocst8_quo_gf2(res,x,mq_quo);
    #endif
    #if GEMSS_HFEmr8
        #if (GEMSS_HFEmr<8)
            res[GEMSS_HFEmq]=0;
        #endif
        unsigned int i;

        for(i=GEMSS_HFEmr-GEMSS_HFEmr8;i<GEMSS_HFEmr;++i)
        {
            res[GEMSS_HFEmq]^=GEMSS_evalMQnocst_gf2(x,mq_rem)<<i;
            mq_rem+=GEMSS_NB_WORD_UNCOMP_EQ;
        }
    #endif
}


