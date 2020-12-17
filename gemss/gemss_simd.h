#ifndef _SIMD_H
#define _SIMD_H

/* The code use generic macros for SIMD, in the way to choose these macros 
   in a specific file as simd_intel.h. */

#include "gemss_arch.h"

#if GEMSS_INTEL_PROCESSOR
#include "gemss_simd_intel.h"
#endif


#endif

