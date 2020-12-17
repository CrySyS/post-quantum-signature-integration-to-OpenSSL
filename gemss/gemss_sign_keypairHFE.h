#ifndef _SIGN_KEYPAIRHFE_H
#define _SIGN_KEYPAIRHFE_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"
#include <stdint.h>


/* Generates a keypair - pk is the public-key and sk is the secret-key. */
int GEMSS_PREFIX_NAME(GEMSS_sign_keypairHFE)(uint8_t* pk, UINT* sk);
#define GEMSS_sign_keypairHFE GEMSS_PREFIX_NAME(GEMSS_sign_keypairHFE)


#endif

