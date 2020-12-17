#ifndef _SORT_GF2N_H
#define _SORT_GF2N_H


#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include "gemss_matrix_gf2n.h"


void GEMSS_PREFIX_NAME(GEMSS_quickSort_nocst_gf2n)(vec_gf2n tab_start, vec_gf2n tab_last);
void GEMSS_PREFIX_NAME(GEMSS_selectionSort_nocst_gf2n)(vec_gf2n tab, int l);
void GEMSS_PREFIX_NAME(GEMSS_fast_sort_gf2n)(vec_gf2n tab, int l);
void GEMSS_PREFIX_NAME(GEMSS_selectionSort_gf2n)(vec_gf2n tab, int l);
#define GEMSS_quickSort_nocst_gf2n GEMSS_PREFIX_NAME(GEMSS_quickSort_nocst_gf2n)
#define GEMSS_selectionSort_nocst_gf2n GEMSS_PREFIX_NAME(GEMSS_selectionSort_nocst_gf2n)
#define GEMSS_fast_sort_gf2n GEMSS_PREFIX_NAME(GEMSS_fast_sort_gf2n)
#define GEMSS_selectionSort_gf2n GEMSS_PREFIX_NAME(GEMSS_selectionSort_gf2n)


#ifdef GEMSS_MQSOFT_REF
    /* The selection sort is the reference implementation. */
    #define GEMSS_sort_nocst_gf2n GEMSS_selectionSort_nocst_gf2n

    /* Constant-time */
    #if GEMSS_CONSTANT_TIME
        #define GEMSS_sort_gf2n GEMSS_selectionSort_gf2n
    #else
        #define GEMSS_sort_gf2n GEMSS_sort_nocst_gf2n
    #endif
#else
    /* The fastest function in variable-time */
    #define GEMSS_sort_nocst_gf2n(tab,l) \
                GEMSS_quickSort_nocst_gf2n(tab,(tab)+((l)-1)*GEMSS_NB_WORD_GFqn)

    /* Constant-time */
    #if GEMSS_CONSTANT_TIME
        #define GEMSS_sort_gf2n GEMSS_fast_sort_gf2n
    #else
        #define GEMSS_sort_gf2n GEMSS_sort_nocst_gf2n
    #endif
#endif


#endif

