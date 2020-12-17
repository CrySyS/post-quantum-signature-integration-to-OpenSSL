#ifndef _MQ_GF2_H
#define _MQ_GF2_H


#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"


/* This type stores a quadratic equation in GF(2)[x1,...,x_(n+v)]. */
typedef UINT* mqnv_gf2;
typedef const UINT* cst_mqnv_gf2;


/* Number of monomial */
#if (GEMSS_GFq==2)
    #define GEMSS_NB_MONOMIAL (((GEMSS_HFEn*(GEMSS_HFEn+1))>>1)+1)
    #define GEMSS_NB_MONOMIAL_VINEGAR (((GEMSS_HFEv*(GEMSS_HFEv+1))>>1)+1)
    #define GEMSS_NB_MONOMIAL_PK (((GEMSS_HFEnv*(GEMSS_HFEnv+1))>>1)+1)
#else
    #define GEMSS_NB_MONOMIAL (((GEMSS_HFEn*(GEMSS_HFEn+3))>>1)+1)
    #define GEMSS_NB_MONOMIAL_VINEGAR (((GEMSS_HFEv*(GEMSS_HFEv+3))>>1)+1)
    #define GEMSS_NB_MONOMIAL_PK (((GEMSS_HFEnv*(GEMSS_HFEnv+3))>>1)+1)
#endif


/* GEMSS_NB_MONOMIAL_PK = GEMSS_NB_BITS_UINT*quo + rem */
#define GEMSS_HFENq (GEMSS_NB_MONOMIAL_PK/GEMSS_NB_BITS_UINT)
#define GEMSS_HFENr (GEMSS_NB_MONOMIAL_PK%GEMSS_NB_BITS_UINT)

#define GEMSS_HFENq8 (GEMSS_NB_MONOMIAL_PK>>3)
#define GEMSS_HFENr8 (GEMSS_NB_MONOMIAL_PK&7)
#define GEMSS_NB_BYTES_EQUATION ((GEMSS_NB_MONOMIAL_PK+7)>>3)
#define GEMSS_HFENr8c ((8-GEMSS_HFENr8)&7)


/** Size for a compressed equation. A term requires Log_2(q) bits. */
#if (GEMSS_GFq==2)
    #if (GEMSS_HFENr)
        #define GEMSS_NB_WORD_EQUATION (GEMSS_HFENq+1)
    #else
        #define GEMSS_NB_WORD_EQUATION GEMSS_HFENq
    #endif
#endif


/* Size for an uncompressed equation */
#define GEMSS_NB_WORD_UNCOMP_EQ \
    ((((GEMSS_HFEnvq*(GEMSS_HFEnvq+1))>>1)*GEMSS_NB_BITS_UINT)+(GEMSS_HFEnvq+1)*GEMSS_HFEnvr)



#endif

