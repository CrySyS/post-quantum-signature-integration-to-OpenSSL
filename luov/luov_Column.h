/*
	Nothing fancy here, just an implementation of a container that stores LUOV_OIL_VARS bits and supports basic functionalities such as xoring, reading bits and flipping a bit
*/

#ifndef COLUMN_H
#define COLUMN_H

#include <stdint.h>
#include <libkeccak.a.headers/KeccakSpongeWidth1600.h>
#include "luov_buffer.h"
#include "luov_prng.h"
#include "luov_local.h"

#if LUOV_OIL_VARS > 64

#define LUOV_COLUMN_COMPONENTS ((LUOV_OIL_VARS+63)/64)

typedef struct {
	uint64_t components[LUOV_COLUMN_COMPONENTS];
} LUOV_column;

static const LUOV_column LUOV_empty = {0};

void LUOV_serialize_column(writer * Buff, LUOV_column b);
LUOV_column LUOV_deserialize_column(reader *Buff);
void LUOV_xor(LUOV_column *a, LUOV_column *yb);
void LUOV_random_column(LUOV_Sponge *sponge,LUOV_column * BC);
uint64_t LUOV_getBit(LUOV_column container, uint64_t bit);
void LUOV_flipBit(LUOV_column *container, uint64_t bit);

#else 

#define LUOV_column uint64_t
#define LUOV_empty ((uint64_t) 0)
#define LUOV_xor(a,b) *a ^= *b
#define LUOV_getBit(container,bit) (container & ((uint64_t)1) << bit)
#define LUOV_flipBit(container,bit) (*container ^= ((uint64_t)1) << bit)
#define LUOV_random_column(sponge,a) squeezeuint64_t(sponge,((LUOV_OIL_VARS+7)/8),a)
#define LUOV_serialize_column(W,container) serialize_uint64_t(W, container , LUOV_OIL_VARS)
#define LUOV_deserialize_column(R) deserialize_uint64_t(R,LUOV_OIL_VARS)

#endif

void squeeze_column_array(LUOV_Sponge *sponge, LUOV_column *arr, int size);


#define LUOV_STATES (((LUOV_OIL_VARS-1)/16)+1)

typedef struct {
	LUOV_PRNG_STATE states[LUOV_STATES];
	unsigned char blocks[LUOV_STATES][LUOV_BLOCK_SIZE];
	int cols_used;
} ColumnGenerator;

void ColumnGenerator_init(ColumnGenerator * col_gen, const unsigned char* key);
LUOV_column Next_Column(ColumnGenerator *col_gen);


#endif
