#ifndef _SIZES_CRYPTO_H
#define _SIZES_CRYPTO_H

#include <openssl/gemss_choice_crypto.h>
//#include "gemss.h"


/************************ SIZES ************************/

/* Theoretical sizes in bits */
/* Practical sizes in bytes */


/* Sizes with the inner mode */
#if GEMSS_HFE
#include "gemss_sizes_HFE.h"
    /** Theoretical in bits size of the public-key (inner mode). */
    #define GEMSS_SIZE_PK_THEORETICAL_INNER GEMSS_SIZE_PK_THEORETICAL_HFE
    /** Theoretical in bits size of the secret-key (inner mode). */
    #define GEMSS_SIZE_SK_THEORETICAL_INNER GEMSS_SIZE_SK_THEORETICAL_HFE
    /** Theoretical in bits size of the signature (inner mode). */
    #define GEMSS_SIZE_SIGN_THEORETICAL_INNER GEMSS_SIZE_SIGN_THEORETICAL_HFE

    /** Practical size in bytes of the public-key (inner mode). */
    #define GEMSS_SIZE_PK_INNER GEMSS_SIZE_PK_HFE
    /** Practical size in bytes of the secret-key (inner mode). */
    #define GEMSS_SIZE_SK_INNER GEMSS_SIZE_SK_HFE
    /** Practical size in bytes of the signature (inner mode). */
    #define GEMSS_SIZE_SIGN_INNER GEMSS_SIZE_SIGN_HFE
#endif


#if GEMSS_InnerMode
    /** Theoretical size in bits of the public-key. */
    #define GEMSS_SIZE_PK_THEORETICAL GEMSS_SIZE_PK_THEORETICAL_INNER
    /** Theoretical size in bits of the secret-key. */
    #define GEMSS_SIZE_SK_THEORETICAL GEMSS_SIZE_SK_THEORETICAL_INNER
    /** Theoretical size in bits of the signature. */
    #define GEMSS_SIZE_SIGN_THEORETICAL GEMSS_SIZE_SIGN_THEORETICAL_INNER

    /** Practical size in bytes of the public-key. */
    #define GEMSS_SIZE_PK GEMSS_SIZE_PK_INNER
    /** Practical size in bytes of the secret-key. */
    #define GEMSS_SIZE_SK GEMSS_SIZE_SK_INNER
    /** Practical size in bytes of the signature. */
    #define GEMSS_SIZE_SIGN GEMSS_SIZE_SIGN_INNER
#endif




#endif

