#ifndef _RANDOMBYTES_H
#define _RANDOMBYTES_H

#include "gemss_debug.h"


#if GEMSS_DEBUG
    /* Set all to zero */
    #define GEMSS_ENABLED_OPENSSL_FIPS 0
    #define GEMSS_ENABLED_OPENSSL_NORMAL 0
#else
    /* The user can modify the value of the following macros */

    /* Set to 1 to enable the FIPS module from OpenSSL */
    #define GEMSS_ENABLED_OPENSSL_FIPS 0
    /* Set to 1 to use the standard RNG of OpenSSL */
    #define GEMSS_ENABLED_OPENSSL_NORMAL 1
#endif


#ifdef __cplusplus
    extern "C" {
#endif
extern int GEMSS_randombytes_NIST(unsigned char *x, unsigned long long xlen);
extern int randombytes_FIPS(unsigned char *x, unsigned long long xlen);
#ifdef __cplusplus
    }
#endif


#if GEMSS_DEBUG
    #define GEMSS_randombytes GEMSS_randombytes_NIST
#elif GEMSS_ENABLED_OPENSSL_FIPS
    #define GEMSS_randombytes randombytes_FIPS
#elif GEMSS_ENABLED_OPENSSL_NORMAL
    #include <openssl/rand.h>
    #define GEMSS_randombytes(x,xlen) RAND_bytes(x,(int)xlen)
#else
    #define GEMSS_randombytes GEMSS_randombytes_NIST
#endif


#endif

