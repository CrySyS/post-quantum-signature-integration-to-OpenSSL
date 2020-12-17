#include "luov_local.h"

static int luov_crypto_keygen(const LUOV *l);
static int luov_crypto_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, const LUOV *l);
static int luov_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, const LUOV *l);
static LUOV_METHOD luov_meth = {
    LUOV_CRYPTO_ALGNAME,
    luov_crypto_keygen,
    luov_crypto_sign,
    luov_crypto_verify,
    0,                          /* luov_custom_keygen */
    0,                          /* luov_custom_sign */
    0						/* luov_custom_verify */
};


static const LUOV_METHOD *default_LUOV_meth = &luov_meth;

const LUOV_METHOD *LUOV_get_default_method(void)
{
    return default_LUOV_meth;
}


void LUOV_set_meth(LUOV_METHOD *meth)
{
    default_LUOV_meth = meth;
}

static int luov_crypto_keygen(const LUOV *l){
    return LUOV_crypto_sign_keypair(l->pk, l->sk);
}

static int luov_crypto_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, const LUOV *l)
{
    return LUOV_crypto_sign(sig, smlen, m, m_len, l->sk);
}

static int luov_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, const LUOV *l)
{
    return LUOV_crypto_sign_open(m, mlen, sm, smlen, l->pk);
}
