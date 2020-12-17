#include "gemss_local.h"

int GEMSS_crypto_keygen(GEMSS *g)
{
    return g->meth->gemss_keygen(g);
}

int GEMSS_crypto_sign_message(unsigned char *sig, unsigned long long *smlen, const unsigned char *m, uint64_t m_len, GEMSS *g){
    return g->meth->gemss_sign(sig, smlen, m, m_len, g);
}

int GEMSS_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, GEMSS *g){
    return g->meth->gemss_verify(m, mlen, sm, smlen, g);
}
