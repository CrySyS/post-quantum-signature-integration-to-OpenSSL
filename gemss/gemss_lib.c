#include <openssl/crypto.h>
#include <memory.h>
#include "gemss_local.h"

GEMSS *GEMSS_new()
{
    return GEMSS_new_method();
}

GEMSS *GEMSS_new_method()
{
    GEMSS *ret = OPENSSL_zalloc(sizeof(*ret));

    /*if (ret == NULL) {
            RSAerr(RSA_F_RSA_NEW_METHOD, ERR_R_MALLOC_FAILURE);
            return NULL;
     }*/
    ret->meth = GEMSS_get_default_method();
    ret->sk = malloc(sizeof(unsigned char[GEMSS_CRYPTO_SECRETKEYBYTES]));
    ret->pk = malloc(sizeof (unsigned char[GEMSS_CRYPTO_PUBLICKEYBYTES]));

   return ret;
}

// Return 1 if generated successfully

int GEMSS_generate_key(GEMSS *g)
{
    if (g->meth->gemss_custom_keygen != NULL)
            return g->meth->gemss_custom_keygen(g);

    return GEMSS_crypto_keygen(g);
}

int GEMSS_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, GEMSS *g)
{
    if (g->meth->gemss_custom_keygen != NULL)
            return g->meth->gemss_custom_sign(sig, smlen, m, m_len, g);

    return GEMSS_crypto_sign_message(sig, smlen, m, m_len, g);

}

int GEMSS_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, GEMSS *g)
{
    if (g->meth->gemss_custom_keygen != NULL)
            return g->meth->gemss_custom_verify(m, mlen, sm, smlen, g);

    return GEMSS_crypto_verify(m, mlen, sm, smlen, g);
}

