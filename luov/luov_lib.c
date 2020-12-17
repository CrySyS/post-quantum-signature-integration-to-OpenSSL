#include <openssl/crypto.h>
#include <memory.h>
#include "luov_local.h"

LUOV *LUOV_new(int sec_level, int mode, int prng,int recovery_mode)
{
    return LUOV_new_method(sec_level, mode, prng, recovery_mode);
}

LUOV *LUOV_new_method(int sec_level, int mode, int prng, int recovery_mode)
{
    LUOV *ret = OPENSSL_zalloc(sizeof(*ret));

    /*if (ret == NULL) {
            RSAerr(RSA_F_RSA_NEW_METHOD, ERR_R_MALLOC_FAILURE);
            return NULL;
     }*/
    ret->mode = mode;
    ret->prng = prng;
    ret->recovery_mode = recovery_mode;
    ret->security_level = sec_level;
    ret->meth = LUOV_get_default_method();
    ret->sk = malloc(sizeof(unsigned char[LUOV_CRYPTO_SECRETKEYBYTES]));
    ret->pk = malloc(sizeof (unsigned char[LUOV_CRYPTO_PUBLICKEYBYTES]));

   return ret;
}

// Return 1 if generated successfully

int LUOV_generate_key(LUOV *l)
{
    if (l->meth->luov_custom_keygen != NULL)
            return l->meth->luov_custom_keygen(l);

    return LUOV_crypto_keygen(l);
}

int LUOV_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, LUOV *l)
{
    if (l->meth->luov_custom_keygen != NULL)
            return l->meth->luov_custom_sign(sig, smlen, m, m_len, l);

    return LUOV_crypto_sign_message(sig, smlen, m, m_len, l);

}

int LUOV_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, LUOV *l)
{
    if (l->meth->luov_custom_keygen != NULL)
            return l->meth->luov_custom_verify(m, mlen, sm, smlen, l);

    return LUOV_crypto_verify(m, mlen, sm, smlen, l);
}

