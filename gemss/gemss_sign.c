#include <openssl/gemss.h>
#if GEMSS_SUPERCOP
#include "gemss_crypto_sign.h"
#endif
#include <string.h>

#include "gemss_sign_keypairHFE.h"
#include "gemss_signHFE.h"
#include "gemss_sign_openHFE.h"


/**
 * @brief   Generation of a keypair for the digital signature.
 * @param[out]   pk  The public-key.
 * @param[out]   sk  The secret-key.
 * @return  Zero if the function runs correctly, non-zero else.
 */
#if GEMSS_SUPERCOP
int GEMSS_crypto_sign_keypair(unsigned char *pk, unsigned char *sk)
#else
int GEMSS_PREFIX_NAME(GEMSS_crypto_sign_keypair)(unsigned char *pk, unsigned char *sk)
#endif
{
    return GEMSS_sign_keypairHFE(pk,(UINT*)sk);
}


/**
 * @brief   Generation of the signature of a document.
 * @param[out]  sm  The signature, the document will be stored at the end.
 * @param[out]  smlen   The length of the signature (including the document).
 * @param[in]   m   The document.
 * @param[in]   mlen    The length of the document.
 * @param[in]   sk  The secret-key.
 * @return  Zero if the function runs correctly, non-zero else.
 */
#if GEMSS_SUPERCOP
int GEMSS_crypto_sign(
#else
int GEMSS_PREFIX_NAME(GEMSS_crypto_sign)(
#endif
  unsigned char *sm, unsigned long long *smlen,
  const unsigned char *m, unsigned long long mlen,
  const unsigned char *sk)
{
    *smlen=mlen+GEMSS_CRYPTO_BYTES;
    memcpy(sm+GEMSS_CRYPTO_BYTES,m,(size_t)mlen);
    return GEMSS_signHFE(sm,m,(size_t)mlen,(UINT*)sk);
}


/**
 * @brief   Verification of the signature of a document.
 * @param[out]   m   The original document.
 * @param[out]   mlen    The length of the document.
 * @param[in]  sm  The signature, the document is stored at the end.
 * @param[in]  smlen   The length of the signature (including the document).
 * @param[in]   pk  The public-key.
 * @return  Zero if the function runs correctly, non-zero else.
 */
#if GEMSS_SUPERCOP
int GEMSS_crypto_sign_open(
#else
int GEMSS_PREFIX_NAME(GEMSS_crypto_sign_open)(
#endif
  unsigned char *m, unsigned long long *mlen,
  const unsigned char *sm, unsigned long long smlen,
  const unsigned char *pk)
{
    int result;
    *mlen=smlen-GEMSS_CRYPTO_BYTES;
    result=GEMSS_sign_openHFE(sm+GEMSS_CRYPTO_BYTES,(size_t)(*mlen),sm,pk);
    /* For compatibily with GEMSS_SUPERCOP, the memcpy is done only after sign_open */
    memcpy(m,sm+GEMSS_CRYPTO_BYTES,(size_t)(*mlen));
    return result;
}


