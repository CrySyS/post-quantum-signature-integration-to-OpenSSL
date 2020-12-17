#include "gemss_hash.h"


/* A simple way to use GEMSS_SHA3 from OpenSSL */
#define GEMSS_MACRO_SHA3(SHA3_NAME,EVP_SHA3) \
int SHA3_NAME(unsigned char *output, const unsigned char *m, size_t len)\
{\
    unsigned int s;\
    return EVP_Digest((const unsigned char*)m,len,output,&s,EVP_SHA3(),NULL);\
}


/* Here, the code of EVP_Digest is inlined from digest.c */
#define GEMSS_MACRO_SHA3_INLINED(SHA3_NAME,EVP_SHA3) \
int SHA3_NAME(unsigned char *output, const unsigned char *m, size_t len)\
{\
    EVP_MD_CTX *ctx;\
    unsigned int s;\
    int ret;\
\
    ctx=EVP_MD_CTX_new();\
    if (ctx==NULL)\
        return 0;\
    EVP_MD_CTX_set_flags(ctx,EVP_MD_CTX_FLAG_ONESHOT);\
    ret=EVP_DigestInit_ex(ctx,EVP_SHA3(),NULL)\
     && EVP_DigestUpdate(ctx,m,len)\
     && EVP_DigestFinal_ex(ctx,output,&s);\
    EVP_MD_CTX_free(ctx);\
\
    return ret;\
}


#ifdef GEMSS_ENABLED_SHA3_OPENSSL
    #include <openssl/evp.h>
    GEMSS_MACRO_SHA3_INLINED(GEMSS_PREFIX_NAME(GEMSS_sha3_256),EVP_sha3_256);
    GEMSS_MACRO_SHA3_INLINED(GEMSS_PREFIX_NAME(GEMSS_sha3_384),EVP_sha3_384);
    GEMSS_MACRO_SHA3_INLINED(GEMSS_PREFIX_NAME(GEMSS_sha3_512),EVP_sha3_512);
#endif


