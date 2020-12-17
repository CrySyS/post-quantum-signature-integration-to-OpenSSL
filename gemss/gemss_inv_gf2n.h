#ifndef _INV_GF2N_H
#define _INV_GF2N_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"

#include "gemss_config_gf2n.h"


#define GEMSS_CONCAT4(a,b) a ## b
#define GEMSS_CONCAT3(a,b) GEMSS_CONCAT4(a,b)

#if ((GEMSS_HFEn>2)&&(GEMSS_HFEn<577))
    #define GEMSS_ITOH GEMSS_CONCAT3(GEMSS_ITOH,GEMSS_HFEn)
#endif


#define GEMSS_CHOOSE_ITMIA


#ifdef GEMSS_MQSOFT_REF
    #define GEMSS_inv_gf2n GEMSS_inv_ITMIA_gf2n_ref
    /* Slower */
/*    #define GEMSS_inv_gf2n GEMSS_inv_Fermat_gf2n_ref*/
#elif (GEMSS_HFEn==2)
    /* {0,1,2,3} --> {0,1,3,2} */
    #define GEMSS_inv_gf2n(res,A) (*(res))=(*(A))^((*(A))>>1);
#elif (defined(GEMSS_ENABLED_PCLMUL)&&(GEMSS_NB_WORD_GFqn<10))
    #define GEMSS_inv_gf2n GEMSS_inv_ITMIA_gf2n
#else
    #define GEMSS_inv_gf2n GEMSS_inv_ITMIA_gf2n_ref
#endif


void GEMSS_PREFIX_NAME(GEMSS_inv_Fermat_gf2n_ref)(uint64_t res[GEMSS_NB_WORD_GFqn],
                                      const uint64_t A[GEMSS_NB_WORD_GFqn]);
#define GEMSS_inv_Fermat_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_inv_Fermat_gf2n_ref)


void GEMSS_PREFIX_NAME(GEMSS_inv_ITMIA_gf2n_ref)(static_gf2n res[GEMSS_NB_WORD_GFqn],
                                     cst_static_gf2n A[GEMSS_NB_WORD_GFqn]);
#define GEMSS_inv_ITMIA_gf2n_ref GEMSS_PREFIX_NAME(GEMSS_inv_ITMIA_gf2n_ref)


#ifdef GEMSS_ITOH
    #if (defined(GEMSS_ENABLED_PCLMUL)&&(GEMSS_NB_WORD_GFqn<10))
        void GEMSS_PREFIX_NAME(GEMSS_inv_ITMIA_gf2n)(static_gf2n res[GEMSS_NB_WORD_GFqn],
                                     cst_static_gf2n A[GEMSS_NB_WORD_GFqn]);
        #define GEMSS_inv_ITMIA_gf2n GEMSS_PREFIX_NAME(GEMSS_inv_ITMIA_gf2n)
    #endif
#endif


#endif

