#include "luov_local.h"

int LUOV_crypto_keygen(LUOV *l)
{
    return l->meth->luov_keygen(l);
}

int LUOV_crypto_sign_message(unsigned char *sig, unsigned long long *smlen, const unsigned char *m, uint64_t m_len, LUOV *l){
    return l->meth->luov_sign(sig, smlen, m, m_len, l);
}

int LUOV_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, LUOV *l){
    return l->meth->luov_verify(m, mlen, sm, smlen, l);
}
