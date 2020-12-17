#ifndef _API_H
#define _API_H
#include <stdint.h>

/** Set to 1 if you want to use MQsoft in GEMSS_SUPERCOP. */
#define GEMSS_SUPERCOP 0

#include "gemss_choice_crypto.h"

/** Size of the secret-key in bytes. */
#define GEMSS_CRYPTO_SECRETKEYBYTES GEMSS_SIZE_SK
/** Size of the public-key in bytes. */
#define GEMSS_CRYPTO_PUBLICKEYBYTES GEMSS_SIZE_PK
/** Size of the signature (without the document) in bytes. */
#define GEMSS_CRYPTO_BYTES GEMSS_SIZE_SIGN

/** Name of the current used cryptosystem. */
#ifdef GeMSS
    #define GEMSS_CRYPTO_ALGNAME "GeMSS"
#elif defined(GEMSS_BlueGeMSS)
    #define GEMSS_CRYPTO_ALGNAME "GEMSS_BlueGeMSS"
#elif defined(GEMSS_RedGeMSS)
    #define GEMSS_CRYPTO_ALGNAME "GEMSS_RedGeMSS"
#elif defined(GEMSS_FGeMSS)
    #define GEMSS_CRYPTO_ALGNAME "GEMSS_FGeMSS"
#elif defined(GEMSS_DualModeMS)
    #if GEMSS_INNER_DualModeMS
        #define GEMSS_CRYPTO_ALGNAME "Inner_DualModeMS"
    #else
        #define GEMSS_CRYPTO_ALGNAME "GEMSS_DualModeMS"
    #endif
#elif defined(GEMSS_QUARTZ)
    #define GEMSS_CRYPTO_ALGNAME QUARTZ_
#elif defined(GEMSS_QUARTZ_V1)
    #define GEMSS_CRYPTO_ALGNAME QUARTZ_V1_
#else
    #define GEMSS_CRYPTO_ALGNAME "MQsoft"
#endif


#if GEMSS_SUPERCOP
int
GEMSS_crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

int
GEMSS_crypto_sign(unsigned char *sm, unsigned long long *smlen,
            const unsigned char *m, unsigned long long mlen,
            const unsigned char *sk);

int
GEMSS_crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                 const unsigned char *sm, unsigned long long smlen,
                 const unsigned char *pk);
#else



int
GEMSS_PREFIX_NAME(GEMSS_crypto_sign_keypair)(unsigned char *pk, unsigned char *sk);

int
GEMSS_PREFIX_NAME(GEMSS_crypto_sign)(unsigned char *sm, unsigned long long *smlen,
                         const unsigned char *m, unsigned long long mlen,
                         const unsigned char *sk);

int
GEMSS_PREFIX_NAME(GEMSS_crypto_sign_open)(unsigned char *m, unsigned long long *mlen,
                              const unsigned char *sm, unsigned long long smlen,
                              const unsigned char *pk);

#define GEMSS_crypto_sign_keypair GEMSS_PREFIX_NAME(GEMSS_crypto_sign_keypair)
#define GEMSS_crypto_sign GEMSS_PREFIX_NAME(GEMSS_crypto_sign)
#define GEMSS_crypto_sign_open GEMSS_PREFIX_NAME(GEMSS_crypto_sign_open)

#endif
 /*-----------------------------------------------------------------------------------*/
typedef struct gemss_st GEMSS;
typedef struct gemss_meth_st GEMSS_METHOD;


GEMSS *GEMSS_new();
GEMSS *GEMSS_new_method();
const GEMSS_METHOD *GEMSS_get_default_method(void);

void GEMSS_set_meth(GEMSS_METHOD *meth);

int GEMSS_generate_key(GEMSS *g);
int GEMSS_crypto_keygen(GEMSS *g);

int GEMSS_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, GEMSS *g);
int GEMSS_crypto_sign_message(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, GEMSS *g);

int GEMSS_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, GEMSS *g);
int GEMSS_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, GEMSS *g);


#endif

