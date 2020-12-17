#ifndef _MQS_GF2_H
#define _MQS_GF2_H


#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_config_HFE.h"
#include "gemss_MQ_gf2.h"
#include "gemss_tools_gf2m.h"
#include <openssl/gemss_choice_crypto.h>


/* This type stores a multivariate quadratic system with n equations in 
GF(2)[x1,...,xn]. It is stored like one equation in GF(2^n)[x1,...,xn]. */
typedef UINT* mqsn_gf2n;
typedef const UINT* cst_mqsn_gf2n;

/* This type stores a multivariate quadratic system with n equations in 
GF(2)[x1,...,x_(n+v)]. It is stored like one equation in 
GF(2^n)[x1,...,x_(n+v)]. */
typedef UINT* mqsnv_gf2n;
typedef const UINT* cst_mqsnv_gf2n;

/* This type stores a multivariate quadratic system with n equations in 
GF(2)[x1,...,xv]. It is stored like one equation in GF(2^n)[x1,...,xv]. */
typedef UINT* mqsv_gf2n;
typedef const UINT* cst_mqsv_gf2n;

/* This type stores a multivariate quadratic system with m equations in 
GF(2)[x1,...,xn]. It is stored like one equation in GF(2^m)[x1,...,xn]. */
typedef UINT* mqsn_gf2m;
typedef const UINT* cst_mqsn_gf2m;

/* This type stores a multivariate quadratic system with m equations in 
 * GF(2)[x1,...,x_(n+v)]. It is stored like one equation in 
 * GF(2^n)[x1,...,x_(n+v)]. */
typedef UINT* mqsnv_gf2m;
typedef const UINT* cst_mqsnv_gf2m;
typedef uint8_t* mqsnv8_gf2m;
typedef const uint8_t* cst_mqsnv8_gf2m;

/* This type stores a multivariate quadratic system with m equations in 
GF(2)[x1,...,x_(n+v)]. It is stored like m equations in GF(2)[x1,...,x_(n+v)].*/
typedef UINT* mqnv_gf2_m;
typedef const UINT* cst_mqnv_gf2_m;




/* Size for m compressed equations */
#define GEMSS_NB_WORD_mEQUATIONS (GEMSS_NB_WORD_EQUATION*GEMSS_HFEm)
/* Size for m uncompressed equations */
#define GEMSS_NB_WORD_UNCOMP_m_EQ (GEMSS_NB_WORD_UNCOMP_EQ*GEMSS_HFEm+GEMSS_NB_WORD_GF2m)


/* Remove the last word of each coefficient in GF(2^m),
   excepted for the constant */
#define GEMSS_ACCESS_last_equations ((GEMSS_NB_MONOMIAL_PK-1)*GEMSS_HFEmq+GEMSS_NB_WORD_GF2m)
/* It is padded to avoid to load data outside of memory 
   during the public-key evaluation */
/* XXX We remove the padding here XXX */
#define GEMSS_NB_WORD_HYBRID_EQUATIONS (GEMSS_ACCESS_last_equations+\
            GEMSS_NB_WORD_UNCOMP_EQ*GEMSS_HFEmr/*+((4-(GEMSS_NB_WORD_GF2nv&3))&3)*/)


#define GEMSS_ACCESS_last_equations8 (GEMSS_NB_MONOMIAL_PK*GEMSS_HFEmq8)


/* Size of a MQ polynomial with n+v variables and with coefficients 
   in GF(2^n) */
#define GEMSS_MQnv_GFqn_SIZE (GEMSS_NB_MONOMIAL_PK*GEMSS_NB_WORD_GFqn)
/* Size of a MQ polynomial with v variables and with coefficients in GF(2^n) */
#define GEMSS_MQv_GFqn_SIZE (GEMSS_NB_MONOMIAL_VINEGAR*GEMSS_NB_WORD_GFqn)
/* Size of a multivariate linear polynomial with v variables and with 
 * coefficients in GF(2^n) */
#define GEMSS_MLv_GFqn_SIZE ((GEMSS_HFEv+1)*GEMSS_NB_WORD_GFqn)

#define GEMSS_MALLOC_MQSn (UINT*)malloc(GEMSS_MQnv_GFqn_SIZE*sizeof(UINT))
#define GEMSS_CALLOC_MQSn (UINT*)calloc(GEMSS_MQnv_GFqn_SIZE,sizeof(UINT))




/* Size of a MQ polynomial with coefficients in GF(2^m) */
/* It is padded to avoid to load data outside of memory 
   during the public-key evaluation */
/* XXX We remove the padding here XXX */
#define GEMSS_MQ_GFqm_SIZE ((GEMSS_NB_MONOMIAL_PK*GEMSS_NB_WORD_GF2m)/*+((4-(GEMSS_NB_WORD_GF2m&3))&3)*/)
/* XXX 64-bit padding XXX */
#define GEMSS_MQ_GFqm8_SIZE \
            (GEMSS_NB_MONOMIAL_PK*GEMSS_NB_BYTES_GFqm+((8-(GEMSS_NB_BYTES_GFqm&7))&7))

#define GEMSS_MALLOC_MQSm (UINT*)malloc(GEMSS_MQ_GFqm_SIZE*sizeof(UINT))
#define GEMSS_CALLOC_MQSm (UINT*)calloc(GEMSS_MQ_GFqm_SIZE,sizeof(UINT))




#endif

