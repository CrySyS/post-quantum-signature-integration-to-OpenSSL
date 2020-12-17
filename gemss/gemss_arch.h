#ifndef _ARCH_H
#define _ARCH_H

#include <stdint.h>
/* For a portable format of printf. */
#include <inttypes.h>
#include "gemss_macro.h"


/****************** uintXX_t for compatibility  ******************/

/* Minus one */
#define GEMSS_MONE64 ((uint64_t)0xFFFFFFFFFFFFFFFF)
#define GEMSS_ZERO64 ((uint64_t)0)
#define GEMSS_ONE64  ((uint64_t)1)

#define GEMSS_MONE32 ((uint32_t)0xFFFFFFFF)
#define GEMSS_ZERO32 ((uint32_t)0)
#define GEMSS_ONE32  ((uint32_t)1)

#define GEMSS_MONE16 ((uint16_t)0xFFFF)
#define GEMSS_ZERO16 ((uint16_t)0)
#define GEMSS_ONE16  ((uint16_t)1)

#define GEMSS_MONE8 ((uint8_t)0xFF)
#define GEMSS_ZERO8 ((uint8_t)0)
#define GEMSS_ONE8  ((uint8_t)1)

/* 0x... */
#define GEMSS_PRINT_X64(a) printf("0x%"PRIx64,a);
#define GEMSS_PRINT_X32(a) printf("0x%"PRIx32,a);
#define GEMSS_PRINT_X16(a) printf("0x%"PRIx16,a);
#define GEMSS_PRINT_X8(a) printf("0x%"PRIx8,a);
/* ... */
#define GEMSS_PRINT_U64(a) printf("%"PRIx64,a);
#define GEMSS_PRINT_U32(a) printf("%"PRIx32,a);
#define GEMSS_PRINT_U16(a) printf("%"PRIx16,a);
#define GEMSS_PRINT_U8(a) printf("%"PRIx8,a);


/****************** Definition of an UINT  ******************/

/* XXX For the moment, this parameter cannot be modified. XXX */
/** Number of bits of an UINT. */
#define GEMSS_NB_BITS_UINT 64


#if (GEMSS_NB_BITS_UINT==64)
    /** Type of an UINT. */
    typedef uint64_t UINT;
    /** Size of an UINT in bytes. */
    #define GEMSS_SIZEOF_UINT 8
    #define GEMSS_LOG2_SIZE_UINT 6
#elif (GEMSS_NB_BITS_UINT==32)
    /** Type of an UINT. */
    typedef uint32_t UINT;
    /** Size of an UINT in bytes. */
    #define GEMSS_SIZEOF_UINT 4
    #define GEMSS_LOG2_SIZE_UINT 5
#elif (GEMSS_NB_BITS_UINT==16)
    /** Type of an UINT. */
    typedef uint16_t UINT;
    /** Size of an UINT in bytes. */
    #define GEMSS_SIZEOF_UINT 2
    #define GEMSS_LOG2_SIZE_UINT 4
#elif (GEMSS_NB_BITS_UINT==8)
    /** Type of an UINT. */
    typedef uint8_t UINT;
    /** Size of an UINT in bytes. */
    #define GEMSS_SIZEOF_UINT 1
    #define GEMSS_LOG2_SIZE_UINT 3
#else
    #error "Not Supported."
#endif


#define GEMSS_UINT_M1 ((UINT)-1)
#define GEMSS_UINT_0 ((UINT)0)
#define GEMSS_UINT_1 ((UINT)1)

/** Print an UINT. */
#define GEMSS_PRINT_UINT(a) GEMSS_CONCAT(PRINT_X,GEMSS_NB_BITS_UINT)(a);




/** A reserved variable to do a for loop on a buffer of UINT. */
#define GEMSS_RESERVED_VARIABLE reserved_variable

#define GEMSS_FOR_LOOP(OP,SIZE) \
    {unsigned int GEMSS_RESERVED_VARIABLE; \
        for(GEMSS_RESERVED_VARIABLE=0U;GEMSS_RESERVED_VARIABLE<(SIZE);++GEMSS_RESERVED_VARIABLE) \
        { \
            OP;\
        } \
    }

#define GEMSS_FOR_LOOP_COMPLETE(INIT,CMP,INC,OP) \
    {unsigned int GEMSS_RESERVED_VARIABLE; \
        for(GEMSS_RESERVED_VARIABLE=INIT;CMP;INC) \
        { \
            OP;\
        } \
    }



/****************** C++ compatibility ******************/

#ifdef __cplusplus
    /** Compatibility with C++. */
    #define GEMSS_BEGIN_EXTERNC extern "C" {
    /** Compatibility with C++. */
    #define GEMSS_END_EXTERNC }
#else
    /** Compatibility with C++. */
    #define GEMSS_BEGIN_EXTERNC
    /** Compatibility with C++. */
    #define GEMSS_END_EXTERNC
#endif


/********************** Security **********************/

/** To enable a constant-time implementation (when it is possible) */
#define GEMSS_CONSTANT_TIME 1


/********************** Memory optimization **********************/

/** Set to 1 to optimize the memory, else 0 to optimize the speed */
#define GEMSS_OPT_MEM 0


/********************** Architecture **********************/

#ifdef __x86_64__
    #define GEMSS_MODE_64_BITS
#elif defined(__i386__)
    #define GEMSS_MODE_32_BITS
#else
    #define GEMSS_MODE_64_BITS
#endif


/********************** Reference implementation **********************/

/** To enable the reference implementation of MQsoft (option in progress) */
/* #define GEMSS_MQSOFT_REF*/


/****************** To choose vectorial optimizations ******************/

/* Choice of the processor */
#define GEMSS_INTEL_PROCESSOR 1

/* To choose the best algorithm in function of the processor */
#define GEMSS_PROC_HASWELL 1
#define GEMSS_PROC_SKYLAKE 0


#ifdef __SSE__
    #include <xmmintrin.h>
    /** To use sse. */
    #define GEMSS_ENABLED_SSE
#endif

#ifdef __SSE2__
    #include <emmintrin.h>
    /** To use sse2. */
    #define GEMSS_ENABLED_SSE2
#endif

#ifdef __SSSE3__
    #include <tmmintrin.h>
    /** To use ssse3. */
    #define GEMSS_ENABLED_SSSE3
#endif

#ifdef __SSE4_1__
    #include <smmintrin.h>
    /** To use sse4.1. */
    #define GEMSS_ENABLED_SSE4_1
#endif

#ifdef __AVX__
    #include <immintrin.h>
    /** To use avx. */
    #define GEMSS_ENABLED_AVX
#endif

#ifdef __AVX2__
    /** To use avx2. */
    #define GEMSS_ENABLED_AVX2
#endif

#if (defined(__PCLMUL__) && defined(GEMSS_ENABLED_SSE))
    #include <wmmintrin.h>
    /** To use multiplication in binary field with PCLMULQDQ and sse. */
    #define GEMSS_ENABLED_PCLMUL
#endif

#if (defined(GEMSS_ENABLED_PCLMUL) && defined(GEMSS_ENABLED_SSE2))
    #include <wmmintrin.h>
    /** To use multiplication in binary field with PCLMULQDQ and sse2. */
    #define GEMSS_ENABLED_PCLMUL_SSE2
#endif

#if (defined(GEMSS_ENABLED_PCLMUL) && defined(GEMSS_ENABLED_AVX2))
    #include <wmmintrin.h>
    /** To use multiplication in binary field with PCLMULQDQ and avx2. */
    #define GEMSS_ENABLED_PCLMUL_AVX2
#endif

#ifdef __POPCNT__
    #include <nmmintrin.h>
    /** Improve the computation of the number of bits set to 1 in a 64-bit 
     *  or 32-bit integer. */
    #define GEMSS_ENABLED_POPCNT
#endif


/****************** gf2x library ******************/

/** Set to 1 to use the multiplication in GF(2)[x] of the gf2x library. */
/* Only when set to 1, the installation of gf2x is required */
/* Be careful because this library can be in variable-time and so vulnerable 
   to the timing attacks. */
#define GEMSS_ENABLED_GF2X 0


/********************* Allocation *********************/

/** A negative integer for the failure of a memory allocation. */
#define GEMSS_ERROR_ALLOC (-2)

/** Verify if the allocation by malloc or calloc succeeds. 
 *  Exit in the failure case. */
#define GEMSS_VERIFY_ALLOC(p) \
    if(!p) \
    {\
        exit(GEMSS_ERROR_ALLOC);\
    }

/** Verify if the allocation by malloc or calloc succeeds. 
 *  Return GEMSS_ERROR_ALLOC in the failure case. */
#define GEMSS_VERIFY_ALLOC_RET(p) \
    if(!p) \
    {\
        return(GEMSS_ERROR_ALLOC);\
    }


/****************** Memory alignment ******************/

#include <string.h>


/** Free an aligned memory. */
#ifdef GEMSS_ENABLED_SSE
    #define GEMSS_ALIGNED_FREE(p) _mm_free(p);
#else
    #define GEMSS_ALIGNED_FREE(p) free(p);
#endif


/** Align the data on 16 bytes, useful for sse. */
#define GEMSS_ALIGNED16 __attribute__((aligned(16)))

#ifdef GEMSS_ENABLED_SSE
    #define GEMSS_ALIGNED16_MALLOC(p,type,nmemb,size) \
                p=(type)_mm_malloc((nmemb)*(size),16);
#else
    #define GEMSS_ALIGNED16_MALLOC(p,type,nmemb,size) \
                if(posix_memalign((void**)(&p),16,(nmemb)*(size)))\
                {\
                    exit(1);\
                }
#endif

#define GEMSS_ALIGNED16_CALLOC(p,type,nmemb,size) \
            GEMSS_ALIGNED16_MALLOC(p,type,nmemb,size);\
            memset((void*)p,0,(nmemb)*(size))


/** Align the data on 32 bytes, useful for avx. */
#define GEMSS_ALIGNED32 __attribute__((aligned(32)))

#ifdef GEMSS_ENABLED_SSE
    #define GEMSS_ALIGNED32_MALLOC(p,type,nmemb,size) \
                p=(type)_mm_malloc((nmemb)*(size),32);
#else
    #define GEMSS_ALIGNED32_MALLOC(p,type,nmemb,size) \
                if(posix_memalign((void**)(&p),32,(nmemb)*(size)))\
                {\
                    exit(1);\
                }
#endif

#define GEMSS_ALIGNED32_CALLOC(p,type,nmemb,size) \
            GEMSS_ALIGNED32_MALLOC(p,type,nmemb,size);\
            memset((void*)p,0,(nmemb)*(size));


#define GEMSS_NO_ALIGNED_MALLOC(p,type,nmemb,size) p=(type)malloc((nmemb)*(size));
#define GEMSS_NO_ALIGNED_CALLOC(p,type,nmemb,size) p=(type)calloc(nmemb,size);
/** Free a no aligned memory. */
#define GEMSS_NO_ALIGNED_FREE(p) free(p);



#endif

