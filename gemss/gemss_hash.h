#ifndef _HASH_H
#define _HASH_H

#include "gemss_arch.h"
#include <openssl/gemss_choice_crypto.h>
#include "gemss_parameters_HFE.h"
#include "gemss_predicate.h"
#include "gemss_init.h"


/******************************************************************/
/****************** Choice of the hash functions ******************/
/******************************************************************/


/* Choice of the hash function */
/* The user is allowed to switch between GEMSS_SHA2 and GEMSS_SHA3 */
#if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))
    #define GEMSS_CHOICE_HASH_SHA1
#elif 0
    #define GEMSS_CHOICE_HASH_SHA2
#else
    #define GEMSS_CHOICE_HASH_SHA3
#endif


/******************************************************************/
/******************** Enable the hash functions *******************/
/******************************************************************/


/* Use of third libraries */
/* The user is allowed to switch between OpenSSL and XKCP */
/* The user can define several macros, while several GEMSS_SHA3 are not defined
   (if several GEMSS_SHA3 are defined, XKCP has priority). */
#ifdef GEMSS_CHOICE_HASH_SHA1
    #define GEMSS_ENABLED_SHA1_OPENSSL
#endif
#if defined(GEMSS_CHOICE_HASH_SHA2)
    #define GEMSS_ENABLED_SHA2_OPENSSL
#endif
#if defined(GEMSS_CHOICE_HASH_SHA3)
    /* XKCP is constant-time and faster than OpenSSL */
    #define GEMSS_ENABLED_SHA3_XKCP
    /* #define GEMSS_ENABLED_SHA3_OPENSSL */
#endif


#define GEMSS_ENABLED_SHAKE_XKCP
/* #define GEMSS_ENABLED_TUPLEHASH_XKCP XXX Disabled XXX */


/******************************************************************/
/***************** Include for the hash functions *****************/
/******************************************************************/


/* We minimize the numbers of #include to decrease the dependencies with the
   third libraries. */
#if (defined(GEMSS_ENABLED_SHA1_OPENSSL)||defined(GEMSS_ENABLED_SHA2_OPENSSL))
    #include <openssl/sha.h>
#endif


#ifdef GEMSS_ENABLED_SHA2_OPENSSL
#include "gemss_randombytes.h"

    #if GEMSS_ENABLED_OPENSSL_FIPS
        #include <openssl/err.h>
        #include <openssl/crypto.h>
    #endif
#endif


#ifdef GEMSS_ENABLED_SHA3_OPENSSL
    #include <stddef.h>
#include "gemss_prefix_name.h"
    int GEMSS_PREFIX_NAME(GEMSS_sha3_256)(unsigned char *output, const unsigned char *m,
                                                     size_t len);
    int GEMSS_PREFIX_NAME(GEMSS_sha3_384)(unsigned char *output, const unsigned char *m,
                                                     size_t len);
    int GEMSS_PREFIX_NAME(GEMSS_sha3_512)(unsigned char *output, const unsigned char *m,
                                                     size_t len);
    #define GEMSS_sha3_256 GEMSS_PREFIX_NAME(GEMSS_sha3_256)
    #define GEMSS_sha3_384 GEMSS_PREFIX_NAME(GEMSS_sha3_384)
    #define GEMSS_sha3_512 GEMSS_PREFIX_NAME(GEMSS_sha3_512)
#endif


#if (defined(GEMSS_ENABLED_SHA3_XKCP)||defined(GEMSS_ENABLED_SHAKE_XKCP))
    GEMSS_BEGIN_EXTERNC
        #include <XKCP/bin/generic64/libkeccak.a.headers/SimpleFIPS202.h>
    GEMSS_END_EXTERNC
#endif


#ifdef GEMSS_ENABLED_SHAKE_XKCP
    GEMSS_BEGIN_EXTERNC
        #include  <XKCP/bin/generic64/libkeccak.a.headers/KeccakHash.h>
    GEMSS_END_EXTERNC
#endif


#ifdef GEMSS_ENABLED_TUPLEHASH_XKCP
    GEMSS_BEGIN_EXTERNC
        #include <XKCP/bin/generic64/libkeccak.a.headers/SP800-185.h>
    GEMSS_END_EXTERNC
#endif


/******************************************************************/
/**************** Macro to call the hash functions ****************/
/******************************************************************/


#define GEMSS_SHA1_OPENSSL(output,m,len) SHA1(m,len,output)
#define GEMSS_SHA256_OPENSSL(output,m,len) SHA256(m,len,output)
#define GEMSS_SHA384_OPENSSL(output,m,len) SHA384(m,len,output)
#define GEMSS_SHA512_OPENSSL(output,m,len) SHA512(m,len,output)



/* Format: SHA3_*(output,m,len) */
#if 0
    #define GEMSS_SHA3_256_XKCP SHA3_256
    #define GEMSS_SHA3_384_XKCP SHA3_384
    #define GEMSS_SHA3_512_XKCP SHA3_512
#else
    /* SHA3_* is inlined from SimpleFIPS202.c */
    #define GEMSS_SHA3_256_XKCP(output,m,len) \
        KeccakWidth1600_Sponge(1088, 512, m, len, 0x06, output, 32)
    #define GEMSS_SHA3_384_XKCP(output,m,len) \
        KeccakWidth1600_Sponge(832, 768, m, len, 0x06, output, 48)
    #define GEMSS_SHA3_512_XKCP(output,m,len) \
        KeccakWidth1600_Sponge(576, 1024, m, len, 0x06, output, 64)
#endif

/* Format: GEMSS_SHAKE*(output,outputByteLen,input,inputByteLen) */
#if 0
    #define GEMSS_SHAKE128_XKCP SHAKE128
    #define GEMSS_SHAKE256_XKCP SHAKE256
#else
    /* GEMSS_SHAKE* is inlined from SimpleFIPS202.c */
    #define GEMSS_SHAKE128_XKCP(output,outputByteLen,m,len) \
        KeccakWidth1600_Sponge(1344, 256, m, len, 0x1F, output, outputByteLen)
    #define GEMSS_SHAKE256_XKCP(output,outputByteLen,m,len) \
        KeccakWidth1600_Sponge(1088, 512, m, len, 0x1F, output, outputByteLen)
#endif

/* To call with:
        Keccak_HashInstance hashInstance;
        GEMSS_Keccak_HashIUF_SHAKE*_XKCP(&hashInstance,data,databitlen);
   And after a call to GEMSS_Keccak_HashIUF_SHAKE*_XKCP, to use one or several times:
        Keccak_HashSqueeze(&hashInstance,output,outputbitlen);
  XXX Here, length in bits XXX
*/
#define GEMSS_Keccak_HashIUF_SHAKE128_XKCP(hashInstance,data,databitlen) \
    Keccak_HashInitialize_SHAKE128(hashInstance);\
    Keccak_HashUpdate(hashInstance,data,databitlen);\
    Keccak_HashFinal(hashInstance,0);
#define GEMSS_Keccak_HashIUF_SHAKE256_XKCP(hashInstance,data,databitlen) \
    Keccak_HashInitialize_SHAKE256(hashInstance);\
    Keccak_HashUpdate(hashInstance,data,databitlen);\
    Keccak_HashFinal(hashInstance,0);

#define GEMSS_TUPLEHASH128_XKCP TupleHash128
#define GEMSS_TUPLEHASH256_XKCP TupleHash256


/************************************************************************/
/* Macro to call the hash functions corresponding to the security level */
/************************************************************************/


/* Choice of the hash function */
#if (GEMSS_K<=128)
    #if GEMSS_ENABLED_OPENSSL_FIPS
        #define GEMSS_SHA2 GEMSS_SHA256_OPENSSL_FIPS
    #else
        #define GEMSS_SHA2 GEMSS_SHA256_OPENSSL
    #endif

    #ifdef GEMSS_ENABLED_SHA3_XKCP
        #define GEMSS_SHA3 GEMSS_SHA3_256_XKCP
    #elif defined(GEMSS_ENABLED_SHA3_OPENSSL)
        #define GEMSS_SHA3 GEMSS_sha3_256
    #endif
#elif (GEMSS_K<=192)
    #if GEMSS_ENABLED_OPENSSL_FIPS
        #define GEMSS_SHA2 GEMSS_SHA384_OPENSSL_FIPS
    #else
        #define GEMSS_SHA2 GEMSS_SHA384_OPENSSL
    #endif

    #ifdef GEMSS_ENABLED_SHA3_XKCP
        #define GEMSS_SHA3 GEMSS_SHA3_384_XKCP
    #elif defined(GEMSS_ENABLED_SHA3_OPENSSL)
        #define GEMSS_SHA3 GEMSS_sha3_384
    #endif
#else
    #if GEMSS_ENABLED_OPENSSL_FIPS
        #define GEMSS_SHA2 GEMSS_SHA512_OPENSSL_FIPS
    #else
        #define GEMSS_SHA2 GEMSS_SHA512_OPENSSL
    #endif

    #ifdef GEMSS_ENABLED_SHA3_XKCP
        #define GEMSS_SHA3 GEMSS_SHA3_512_XKCP
    #elif defined(GEMSS_ENABLED_SHA3_OPENSSL)
        #define GEMSS_SHA3 GEMSS_sha3_512
    #endif
#endif


/* Choice of GEMSS_SHAKE and TupleHash */
#if (GEMSS_K<=128)
    #define GEMSS_SHAKE GEMSS_SHAKE128_XKCP
    #define GEMSS_Keccak_HashIUF_SHAKE GEMSS_Keccak_HashIUF_SHAKE128_XKCP
    #define GEMSS_TUPLEHASH GEMSS_TUPLEHASH128_XKCP
#else
    #define GEMSS_SHAKE GEMSS_SHAKE256_XKCP
    #define GEMSS_Keccak_HashIUF_SHAKE GEMSS_Keccak_HashIUF_SHAKE256_XKCP
    #define GEMSS_TUPLEHASH GEMSS_TUPLEHASH256_XKCP
#endif


/******************************************************************/
/******** Macro to call the chosen hash function of MQsoft ********/
/******************************************************************/


#ifdef GEMSS_CHOICE_HASH_SHA1
    #define GEMSS_HASH SHA1
#elif defined(GEMSS_CHOICE_HASH_SHA2)
    #define GEMSS_HASH GEMSS_SHA2
#else
    #define GEMSS_HASH GEMSS_SHA3
#endif


/******************************************************************/
/************************** Other tools ***************************/
/******************************************************************/


GEMSS_BEGIN_EXTERNC
    /* For KeccakWidth1600_Sponge */
    #include <XKCP/bin/generic64/libkeccak.a.headers/KeccakSpongeWidth1600.h>
GEMSS_END_EXTERNC


#if (GEMSS_K<=80)
    #define GEMSS_SIZE_DIGEST 20
    #define GEMSS_SIZE_DIGEST_UINT 3
#elif (GEMSS_K<=128)
    #define GEMSS_SIZE_DIGEST 32
    #define GEMSS_SIZE_DIGEST_UINT 4
    #define GEMSS_SIZE_2_DIGEST 64
    #define GEMSS_EQUALHASH_NOCST GEMSS_ISEQUAL4_NOCST
    #define GEMSS_COPYHASH GEMSS_COPY4
#elif (GEMSS_K<=192)
    #define GEMSS_SIZE_DIGEST 48
    #define GEMSS_SIZE_DIGEST_UINT 6
    #define GEMSS_SIZE_2_DIGEST 96
    #define GEMSS_EQUALHASH_NOCST GEMSS_ISEQUAL6_NOCST
    #define GEMSS_COPYHASH GEMSS_COPY6
#else
    #define GEMSS_SIZE_DIGEST 64
    #define GEMSS_SIZE_DIGEST_UINT 8
    #define GEMSS_SIZE_2_DIGEST 128
    #define GEMSS_EQUALHASH_NOCST GEMSS_ISEQUAL8_NOCST
    #define GEMSS_COPYHASH GEMSS_COPY8
#endif


#define GEMSS_EQUALHASH(a,b) GEMSS_f_ISEQUAL(a,b,GEMSS_SIZE_DIGEST_UINT)


/* XXX Bytes XXX */
#define GEMSS_expandSeed(output,outputByteLen,seed,seedByteLen) \
        GEMSS_SHAKE(output,outputByteLen,seed,seedByteLen)

#define GEMSS_expandSeedCxtDeclaration Keccak_HashInstance hashInstance
#define GEMSS_expandSeedIUF GEMSS_Keccak_HashIUF_SHAKE
#define GEMSS_expandSeedSqueeze Keccak_HashSqueeze


#endif

