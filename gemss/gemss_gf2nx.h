#ifndef _GF2NX_H
#define _GF2NX_H


#include "gemss_arch.h"
#include "gemss_parameters_HFE.h"
#include "gemss_MQS_gf2.h"
#include "gemss_matrix_gf2n.h"


/* This type stores an element of GF(2^n)[X]. Their coefficients are stored in 
   the lexicographic order. */
typedef UINT* gf2nx;
typedef const UINT* cst_gf2nx;
/* to use data[length]. */
typedef UINT static_gf2nx;


/* Version with a structure */
typedef struct _poly_gf2nx
{
    /* Vector of coefficients stored in the lexicographic order */
    vec_gf2n coefs;
    /* deg+1 coefficients */
    unsigned int deg;
} poly_gf2nx;


/* When a polynomial is stored with a sparse representation */
typedef UINT* sparse_gf2nx;
typedef const UINT* cst_sparse_gf2nx;


/* This type stores an element of GF(2^n)[X]. Their coefficients are stored in 
the lexicographic order. Only the coefficients which can be non null are stored. 
The leading coefficient in 1 and is not stored. */
typedef UINT* sparse_monic_gf2nx;
typedef const UINT* cst_sparse_monic_gf2nx;


/* This type stores a vector in GF(2^n)[X]. */
typedef UINT* vec_gf2nx;
typedef const UINT* cst_vec_gf2nx;


/****************** OPTION TO MODIFY THE GEMSS_HFE POLYNOMIAL ******************/


/* Remark: if GEMSS_HFEDeg is even, we can also optimize for s=0 */
#if (GEMSS_HFEs || (!(GEMSS_HFEDeg&1U)))
    /* Set to 1 to remove terms which have an odd degree strictly greater than
       GEMSS_HFE_odd_degree */
    #define GEMSS_ENABLED_REMOVE_ODD_DEGREE 1
#else
    #define GEMSS_ENABLED_REMOVE_ODD_DEGREE 0
#endif


#if GEMSS_ENABLED_REMOVE_ODD_DEGREE
    /* GEMSS_HFE_odd_degree = 1 + 2^GEMSS_LOG_odd_degree */
    #define GEMSS_LOG_odd_degree (GEMSS_HFEDegI-GEMSS_HFEs)
    #define GEMSS_HFE_odd_degree ((1U<<(GEMSS_LOG_odd_degree))+1)

    #if (GEMSS_HFEDeg&1)
        #error "GEMSS_HFEDeg is odd, so to remove the leading term would decrease \
                the degree."
    #endif

    #if (GEMSS_HFE_odd_degree>GEMSS_HFEDeg)
        #error "It is useless to remove 0 term."
    #endif

    #if (GEMSS_HFE_odd_degree<=1)
        #error "The case where the term X^3 is removing is not implemented."
    #endif
#endif


/****************** GEMSS_HFE POLYNOMIAL AND SPARSE REPRESENTATION ******************/


/* Number of stored coefficients of a GEMSS_HFEv polynomial */
/* Remark: when the vinegar variables of a GEMSS_HFEv polynomial are evaluated,
           we obtain a GEMSS_HFE polynomial. */
#if (GEMSS_HFEDeg==1)
    /* Do not store the leading term <=> only constant coefficient is stored */
    #define GEMSS_NB_COEFS_HFEPOLY 1U
    #define GEMSS_NB_COEFS_HFEVPOLY GEMSS_NB_MONOMIAL_VINEGAR
#else
    #if (GEMSS_GFq==2)
        /* Set i=GEMSS_HFEDegI and j=GEMSS_HFEDegJ, the number of non zero monomials is:
           1 (X^0) + 1 (X^1) + i(i+1)/2 (X^2 to X^(2*2^(i-1))) + 
                                  (j+1) (X^(2^i + 2^0) to X^(2^i + 2^j))
                                     -1 (leading term == 1 is not stored) */
        #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
            #define GEMSS_NB_COEFS_HFEPOLY \
                        (2+GEMSS_HFEDegJ+((GEMSS_HFEDegI*(GEMSS_HFEDegI-1))>>1)+GEMSS_LOG_odd_degree)
        #else
            #define GEMSS_NB_COEFS_HFEPOLY \
                        (2+GEMSS_HFEDegJ+((GEMSS_HFEDegI*(GEMSS_HFEDegI+1))>>1))
        #endif

        #define GEMSS_NB_COEFS_HFEVPOLY \
                    (GEMSS_NB_COEFS_HFEPOLY+(GEMSS_NB_MONOMIAL_VINEGAR-1)+(GEMSS_HFEDegI+1)*GEMSS_HFEv)
    #else
        /* Not implemented */
    #endif
#endif


#define GEMSS_NB_UINT_HFEVPOLY (GEMSS_NB_COEFS_HFEVPOLY*GEMSS_NB_WORD_GFqn)
#define GEMSS_NB_UINT_HFEPOLY (GEMSS_NB_COEFS_HFEPOLY*GEMSS_NB_WORD_GFqn)


/* Allocation */
#define GEMSS_MALLOC_HFEPOLY (UINT*)malloc(GEMSS_NB_UINT_HFEPOLY*sizeof(UINT));
#define GEMSS_MALLOC_HFEVPOLY (UINT*)malloc(GEMSS_NB_UINT_HFEVPOLY*sizeof(UINT));


/* A structure with a special list to find the exponents of the monomials */
typedef struct {
    cst_sparse_monic_gf2nx poly;
    /* List of the successive differences of the exponents of the monomials of
       poly multiplied by GEMSS_NB_WORD_GFqn */
    unsigned int L[GEMSS_NB_COEFS_HFEPOLY];
} complete_sparse_monic_gf2nx;


#endif

