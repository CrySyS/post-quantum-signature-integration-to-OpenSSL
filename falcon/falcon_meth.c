#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "falcon_local.h"

static int ossl_falcon_keygen_make(FALCON *f);
static int ossl_falcon_expand_privkey(const FALCON *f);
static int ossl_falcon_sign_dyn(uint8_t *sig, size_t * siglen, const unsigned char *m, uint64_t m_len, FALCON *f);
static int ossl_falcon_sign_tree(uint8_t *sig, size_t * siglen, const unsigned char *m, uint64_t m_len, FALCON *f);
static int ossl_falcon_verify(uint8_t *sig, size_t siglen, const unsigned char* m, uint64_t m_len, const FALCON *f);
static FALCON_METHOD falcon_meth = {
    FALCON_CRYPTO_ALGNAME,
    ossl_falcon_keygen_make,
    ossl_falcon_expand_privkey,
    ossl_falcon_sign_dyn,
    ossl_falcon_sign_tree,
    ossl_falcon_verify,
    0,                          /* falcon_custom_keygen */
    0,                          /* falcon_custom_sign */
    0						/* falcon_custom_verify */
};


static const FALCON_METHOD *default_FALCON_meth = &falcon_meth;

const FALCON_METHOD *FALCON_get_default_method(void)
{
    return default_FALCON_meth;
}


void FALCON_set_meth(FALCON* f, FALCON_METHOD *meth)
{
    f->meth = meth;
}

static int ossl_falcon_keygen_make(FALCON *f){

    return falcon_keygen_make(&f->rng,f->logn,f->sk,FALCON_PRIVKEY_SIZE(f->logn),f->pk,FALCON_PUBKEY_SIZE(f->logn),f->tmp,f->tmp_len);
}

static int ossl_falcon_expand_privkey(const FALCON *f){
    return falcon_expand_privkey(f->esk,FALCON_EXPANDEDKEY_SIZE(f->logn),f->sk,FALCON_PRIVKEY_SIZE(f->logn),f->tmp,f->tmp_len);
}

static int ossl_falcon_sign_dyn(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f)
{
    return falcon_sign_dyn(&f->rng,sig, siglen, f->sk,FALCON_PRIVKEY_SIZE(f->logn),m,m_len,f->ct,f->tmp,f->tmp_len);
}

static int ossl_falcon_sign_tree(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f)
{
    return falcon_sign_tree(&f->rng, sig, siglen, f->esk, m, m_len, f->ct, f->tmp, f->tmp_len);
}

static int ossl_falcon_verify(uint8_t *sig, size_t siglen, const unsigned char* m, uint64_t m_len, const FALCON *f)
{
    return falcon_verify(sig, siglen, f->pk, FALCON_PUBKEY_SIZE(f->logn), m, m_len, f->tmp, f->tmp_len);
}
