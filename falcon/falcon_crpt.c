#include "falcon_local.h"

int FALCON_crypto_keygen(FALCON *f)
{
    if (f->exp_key == 0)
    {
        return f->meth->falcon_keygen(f);
    }
    if(f->exp_key == 1)
    {
        f->meth->falcon_keygen(f);
        return f->meth->falcon_keygen_exp(f);
    }
    else{
        return 2;
    }
}

int FALCON_crypto_sign_message(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f)
{
    if (f->exp_key == 0)
    {
        return f->meth->falcon_sign_dyn(sig, siglen, m, m_len, f);
    }
    if(f->exp_key == 1)
    {
        return f->meth->falcon_sign_tree(sig, siglen, m, m_len, f);
    }
    else{
        return 2;
    }
}

int FALCON_crypto_verify(uint8_t *sig, size_t siglen, const unsigned char *m, uint64_t m_len,const FALCON *f){
    return f->meth->falcon_verify(sig, siglen, m, m_len, f);
}
