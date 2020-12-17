#include "gemss_initMatrixId_gf2.h"


#define GEMSS_INITMATID_GF2(NAME,MATRIX_SIZE,nq,nr,NB_WORD_n) \
void NAME(Mn_gf2 S)\
{\
    UINT bit_ir;\
    unsigned int iq,ir;\
\
    /* Initialize to 0 */\
    for(iq=0;iq<MATRIX_SIZE;++iq)\
    {\
        S[iq]=0;\
    }\
\
    /* for each row excepted the last block */\
    for(iq=0;iq<nq;++iq)\
    {\
        bit_ir=1;\
        for(ir=0;ir<GEMSS_NB_BITS_UINT;++ir)\
        {\
            *S=bit_ir;\
            /* Next row */\
            S+=NB_WORD_n;\
            bit_ir<<=1;\
        }\
        /* Next block of column */\
        ++S;\
    }\
\
    /* for each row of the last block */\
    bit_ir=1;\
    for(ir=0;ir<nr;++ir)\
    {\
        *S=bit_ir;\
        /* Next row */\
        S+=NB_WORD_n;\
        bit_ir<<=1;\
    }\
}

/**
 * @brief   Generate the identity matrix (n,n) in GF(2).
 * @param[out]  S   The identity matrix (n,n) in GF(2).
 * @remark  Requires to allocate n elements of GF(2^n) for S.
 * @remark  This function does not require a constant-time implementation.
 */
GEMSS_INITMATID_GF2(GEMSS_PREFIX_NAME(GEMSS_initMatrixIdn_gf2),GEMSS_MATRIXn_SIZE,GEMSS_HFEnq,GEMSS_HFEnr,
              GEMSS_NB_WORD_GFqn);
/**
 * @brief   Generate the identity matrix (n+v,n+v) in GF(2).
 * @param[out]  S   The identity matrix (n+v,n+v) in GF(2).
 * @remark  Requires to allocate n+v elements of GF(2^(n+v)) for S.
 * @remark  This function does not require a constant-time implementation.
 */
GEMSS_INITMATID_GF2(GEMSS_PREFIX_NAME(GEMSS_initMatrixIdnv_gf2),GEMSS_MATRIXnv_SIZE,GEMSS_HFEnvq,GEMSS_HFEnvr,
              GEMSS_NB_WORD_GF2nv);


