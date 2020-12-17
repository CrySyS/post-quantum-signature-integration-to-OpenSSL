#include "gemss_local.h"


static int gemss_crypto_keygen(const GEMSS *g);
static int gemss_crypto_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, const GEMSS *g);
static int gemss_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, const GEMSS *g);
static GEMSS_METHOD gemss_meth = {
    GEMSS_CRYPTO_ALGNAME,
    gemss_crypto_keygen,
    gemss_crypto_sign,
    gemss_crypto_verify,
    0,                          /* luov_custom_keygen */
    0,                          /* luov_custom_sign */
    0						/* luov_custom_verify */
};


static const GEMSS_METHOD *default_GEMSS_meth = &gemss_meth;

const GEMSS_METHOD *GEMSS_get_default_method(void)
{
    return default_GEMSS_meth;
}


void GEMSS_set_meth(GEMSS_METHOD *meth)
{
    default_GEMSS_meth = meth;
}

static int gemss_crypto_keygen(const GEMSS *g){
    return GEMSS_crypto_sign_keypair(g->pk, g->sk);
}

static int gemss_crypto_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, const GEMSS *g)
{
    return GEMSS_crypto_sign(sig, smlen, m, m_len, g->sk);
}

static int gemss_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, const GEMSS *g)
{
    return GEMSS_crypto_sign_open(m, mlen, sm, smlen, g->pk);
}
