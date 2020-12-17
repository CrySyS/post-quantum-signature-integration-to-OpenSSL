/*
//  rng.h
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
*/

#ifndef rng_h
#define rng_h

#include <stdio.h>

#define GEMSS_RNG_SUCCESS      0
#define GEMSS_RNG_BAD_MAXLEN  -1
#define GEMSS_RNG_BAD_OUTBUF  -2
#define GEMSS_RNG_BAD_REQ_LEN -3

typedef struct {
    unsigned char   buffer[16];
    int             buffer_pos;
    unsigned long   length_remaining;
    unsigned char   key[32];
    unsigned char   ctr[16];
} GEMSS_AES_XOF_struct;

typedef struct {
    unsigned char   Key[32];
    unsigned char   V[16];
    int             reseed_counter;
} GEMSS_AES256_CTR_DRBG_struct;


void
GEMSS_AES256_CTR_DRBG_Update(unsigned char *provided_data,
                       unsigned char *Key,
                       unsigned char *V);

int
GEMSS_seedexpander_init(GEMSS_AES_XOF_struct *ctx,
                  unsigned char *seed,
                  unsigned char *diversifier,
                  unsigned long maxlen);

int
GEMSS_seedexpander(GEMSS_AES_XOF_struct *ctx, unsigned char *x, unsigned long xlen);

void
GEMSS_randombytes_init(unsigned char *entropy_input,
                 unsigned char *personalization_string,
                 int security_strength);

int
GEMSS_randombytes_NIST(unsigned char *x, unsigned long long xlen);

#endif /* rng_h */

