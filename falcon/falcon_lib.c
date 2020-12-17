#include <openssl/crypto.h>
#include <memory.h>
#include "falcon_local.h"
#include <openssl/rsa.h>
#include <openssl/rsaerr.h>
#include <openssl/err.h>

static inline size_t maxsz(size_t a, size_t b)
{
    return a > b ? a : b;
}

FALCON *FALCON_new(unsigned logn, int exp_key, int ct)
{
    return FALCON_new_method(logn, exp_key, ct);
}

FALCON *FALCON_new_method(unsigned logn, int exp_key, int ct)
{

    FALCON *ret = OPENSSL_zalloc(sizeof(*ret));
    if(ret == NULL){
        return NULL;
    }
    size_t len;

    shake256_context rng;
    ret->logn = logn;
    ret->exp_key = exp_key;
    ret->ct = ct;
    ret->meth = FALCON_get_default_method();
    ret->sk = FALCON_xmalloc(FALCON_PRIVKEY_SIZE(logn));
    if(ret->sk == NULL){
        FALCON_free(ret);
        return NULL;
    }

    if(exp_key == 1){
        ret->esk = FALCON_xmalloc(FALCON_EXPANDEDKEY_SIZE(logn));
        if(ret->esk == NULL){
            FALCON_free(ret);
            return NULL;
        }
    }

    ret->pk = FALCON_xmalloc(FALCON_PUBKEY_SIZE(logn));
    if(ret->pk == NULL){
        FALCON_free(ret);
        return NULL;
    }

    if (shake256_init_prng_from_system(&rng) != 0) {
        FALCON_free(ret);
        return NULL;
     }
    ret->rng = rng;

    len = FALCON_TMPSIZE_KEYGEN(logn);
    len = maxsz(len, FALCON_TMPSIZE_SIGNDYN(logn));
    len = maxsz(len, FALCON_TMPSIZE_SIGNTREE(logn));
    len = maxsz(len, FALCON_TMPSIZE_EXPANDPRIV(logn));
    len = maxsz(len, FALCON_TMPSIZE_VERIFY(logn));
    len = maxsz(len, FALCON_TMPSIZE_MAKEPUB(logn));

    ret->tmp = FALCON_xmalloc(len);
    if(ret->tmp == NULL){
        FALCON_free(ret);
        return NULL;
    }

    ret->tmp_len = len;

   return ret;
}

int FALCON_generate_key(FALCON *f)
{
    if (f->meth->falcon_custom_keygen != NULL)
            return f->meth->falcon_custom_keygen(f);
    return FALCON_crypto_keygen(f);


}

int FALCON_sign(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f)
{
    if (f->meth->falcon_custom_keygen != NULL)
            return f->meth->falcon_custom_sign(sig, siglen, m, m_len, f);

    return FALCON_crypto_sign_message(sig, siglen, m, m_len, f);

}

int FALCON_verify(uint8_t *sig, size_t siglen, const unsigned char *m, uint64_t m_len,const FALCON *f)
{
    if (f->meth->falcon_custom_keygen != NULL)
            return f->meth->falcon_custom_verify(sig, siglen, m, m_len, f);

    return FALCON_crypto_verify(sig, siglen, m, m_len, f);
}

uint8_t* FALCON_get_publickey(FALCON* f){
    return f->pk;
}

uint8_t* FALCON_get_secretkey(FALCON* f){
    if(f->exp_key == 1)
        return f->esk;
    else
        return f->sk;
}

uint8_t *FALCON_get_tmp(FALCON* f){
    return f->tmp;
}

size_t FALCON_get_tmp_len(FALCON* f){
    return f->tmp_len;
}

void FALCON_read_publickey(FALCON* f, uint8_t* pk){
    free(f->pk);
    f->pk = pk;
}

void FALCON_read_privatekey(FALCON* f, uint8_t* sk){
    free(f->sk);
    f->sk = sk;
}

int FALCON_write_to_file(const char *fname, const void *data, size_t len){
    const unsigned char *buf;
        FILE *f;

        f = fopen(fname, "wb");
        if (f == NULL) {
            return FALCON_ERR_FILE_OPEN;
        }
        buf = data;
        while (len > 0) {
            size_t wlen;

            wlen = fwrite(buf, 1, len, f);
            if (wlen == 0) {
            	fclose(f);
                return FALCON_ERR_WRITE;
            }
            buf += wlen;
            len -= wlen;
        }
        fclose(f);
        return 0;
}

unsigned char *FALCON_read_from_file(const char *fname, size_t *data_len){
    FILE *f;
    size_t ptr, len;

    unsigned char* buf;

    f = fopen(fname, "rb");
    if (f == NULL) {
        return NULL;
    }
    buf = NULL;
    ptr = 0;
    len = 0;
    for (;;) {
        unsigned char tmp[4096];
        size_t rlen;

        rlen = fread(tmp, 1, sizeof tmp, f);
        if (rlen == 0) {
            break;
        }
        if (buf == NULL) {
            buf = malloc(rlen);
            if(buf == NULL){
            	fclose(f);
                return NULL;
            }
            memcpy(buf, tmp, rlen);
            ptr = rlen;
            len = rlen;
        } else {
            if ((len - ptr) < rlen) {
                unsigned char *nbuf;

                len <<= 1;
                if ((len - ptr) < rlen) {
                    len = ptr + rlen;
                }
                nbuf = malloc(len);
                if(nbuf == NULL){
                    fclose(f);
                    return NULL;
            	}
                memcpy(nbuf, buf, ptr);
                free(buf);
                buf = nbuf;
                free(nbuf);
            }
            memcpy(buf + ptr, tmp, rlen);
            ptr += rlen;
        }
    }
    fclose(f);

    *data_len = ptr;
    return buf;
}

void *FALCON_xmalloc(size_t len)
{
    void *buf;

    if (len == 0) {
        return NULL;
    }
    buf = malloc(len);
    if (buf == NULL) {
        return NULL;
    }
    return buf;
}

void FALCON_free(FALCON* f){
    if(f->tmp)
        free(f->tmp);
    if(f->exp_key == 1)
        free(f->esk);
    if(f->pk)
        free(f->pk);
    if(f->sk)
        free(f->sk);
    free(f);
}
