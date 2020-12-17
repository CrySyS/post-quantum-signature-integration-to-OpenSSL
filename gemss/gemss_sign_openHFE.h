#ifndef _SIGN_OPENHFE_H
#define _SIGN_OPENHFE_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include <stdint.h>
#include <stddef.h>


int GEMSS_PREFIX_NAME(GEMSS_sign_openHFE_uncomp_pk)(const unsigned char* m, size_t len,
                                        const unsigned char* sm8,
                                        const uint8_t* pk,
                                        void (*eval_pk)());
#define GEMSS_sign_openHFE_uncomp_pk GEMSS_PREFIX_NAME(GEMSS_sign_openHFE_uncomp_pk)


int GEMSS_PREFIX_NAME(GEMSS_sign_openHFE_huncomp_pk)(const unsigned char* m, size_t len,
                                         const unsigned char* sm8,
                                         const uint8_t* pk, const uint8_t* hpk,
                                         void (*eval_pk)());
#define GEMSS_sign_openHFE_huncomp_pk GEMSS_PREFIX_NAME(GEMSS_sign_openHFE_huncomp_pk)


/* Verify a signature: m is the original message, sm8 is the signed message, 
 * pk is the public-key. */
int GEMSS_PREFIX_NAME(GEMSS_sign_openHFE)(const unsigned char* m, size_t len,
                              const unsigned char* sm8, const uint8_t* pk);
#define GEMSS_sign_openHFE GEMSS_PREFIX_NAME(GEMSS_sign_openHFE)


#endif

