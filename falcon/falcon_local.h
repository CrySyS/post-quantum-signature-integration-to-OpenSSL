/*
 * External Falcon API.
 *
 * ==========================(LICENSE BEGIN)============================
 *
 * Copyright (c) 2017-2019  Falcon Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * ===========================(LICENSE END)=============================
 *
 * @author   Thomas Pornin <thomas.pornin@nccgroup.com>
 */

#ifndef FALCON_LOCAL_H__
#define FALCON_LOCAL_H__

#include <stddef.h>
#include <stdint.h>

#include <openssl/falcon.h>

#ifdef __cplusplus
extern "C" {
#endif


#define FALCON_CRYPTO_ALGNAME "Falcon"

struct falcon_st{
    uint8_t *pk;
    uint8_t *sk;
    uint8_t *esk;
    const FALCON_METHOD *meth;
    unsigned logn;
    int exp_key;
    int ct;
    shake256_context rng;
    uint8_t *tmp;
    size_t tmp_len;

};

struct falcon_meth_st{
    char *name;
    int (*falcon_keygen)(FALCON *f);
    int (*falcon_keygen_exp)(const FALCON *f);
    int (*falcon_sign_dyn)(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f);
    int (*falcon_sign_tree)(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f);
    int (*falcon_verify)(uint8_t *sig, size_t siglen, const unsigned char *m, uint64_t m_len,const FALCON *f);
    int (*falcon_custom_keygen)(const FALCON *f);
    int (*falcon_custom_sign)(uint8_t *sig, size_t *siglen, const unsigned char *m, uint64_t m_len, FALCON *f);
    int (*falcon_custom_verify)(uint8_t *sig, size_t siglen, const unsigned char *m, uint64_t m_len,const FALCON *f);
};


#ifdef __cplusplus
}
#endif

#endif
