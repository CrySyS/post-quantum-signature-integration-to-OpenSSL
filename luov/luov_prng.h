#ifndef RNG_H
#define RNG_H

#include "luov_local.h"
#include <stdlib.h>
#include <libkeccak.a.headers/KeccakHash.h>
#include "luov_buffer.h"
#include "luov_LinearAlgebra.h"

#define LUOV_Sponge Keccak_HashInstance 

#define LUOV_squeezeBytes(S,D,L) Keccak_HashSqueeze (S,D,L * 8)

void initializeAndAbsorb(LUOV_Sponge *sponge, const unsigned char * seed, int len);
void squeezeuint64_t(LUOV_Sponge *sponge, int bytes , uint64_t * a);

#ifdef LUOV_PRNG_KECCAK

#define LUOV_BLOCK_SIZE 64
#define LUOV_PRNG_STATE LUOV_Sponge
#define LUOV_PRNG_INIT(S,K,I) Keccak_HashInitialize_SHAKE128(S); Keccak_HashUpdate(S, K, 32*8 ); Keccak_HashUpdate(S, I, 8); Keccak_HashFinal(S,0); 
#define LUOV_PRNG_GET_BLOCK(S,O) Keccak_HashSqueeze(S, O, LUOV_BLOCK_SIZE*8);

#endif

#ifdef LUOV_PRNG_CHACHA
#include "luov_chacha.h"

#define LUOV_BLOCK_SIZE 64
#define LUOV_PRNG_STATE chacha_ctx
#define LUOV_PRNG_INIT(S,K,I) chacha_keysetup(S, K, 256); chacha_ivsetup(S, I, 0);      
#define LUOV_PRNG_GET_BLOCK(S,O) { unsigned char In[LUOV_BLOCK_SIZE] = {0}; \
							  chacha_encrypt_bytes(S, In, O, LUOV_BLOCK_SIZE); }; 
#endif

#endif

