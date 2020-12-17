#ifndef GEMSS_LOCAL_H
#define GEMSS_LOCAL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <openssl/gemss.h>

#include <stdint.h>


struct gemss_st{
    unsigned char *pk;
    unsigned char *sk;
    const GEMSS_METHOD *meth;
};

struct gemss_meth_st{
    char *name;
    int (*gemss_keygen)(const GEMSS *g);
    int (*gemss_sign)(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, const GEMSS *g);
    int (*gemss_verify)(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen,
        const GEMSS *g);
    int (*gemss_custom_keygen)(const GEMSS *g);
    int (*gemss_custom_sign)(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len,
        const GEMSS *g);
    int (*gemss_custom_verify)(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen,
        const GEMSS *g);
};


int openssl_gemss_keygen(unsigned char *pk, unsigned char *sk);
int openssl_gemss_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char* document, uint64_t len, const unsigned char *sk);
int openssl_gemss_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, const unsigned char *pk);




#endif // GEMSS_LOCAL_H
