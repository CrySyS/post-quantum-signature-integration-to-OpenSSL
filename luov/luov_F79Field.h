/*
	Finite field of order 2^47 implemented as polynomial ring F_2[x]/x^79 + x^5 + x^2 + x + 1
*/

#ifndef F79FIELD_H
#define F79FIELD_H

#include <stdint.h>
#include <stdio.h>
#include "luov_buffer.h"
#include "luov_local.h"
#include "luov_F61Field.h"

typedef struct {
	uint64_t coef[2];
} LUOV_f79FELT;

static const LUOV_f79FELT LUOV_f79ONE = {{ 1,0 }};
static const LUOV_f79FELT LUOV_f79ZERO = {{ 0,0}};

/* Field operations */

void LUOV_f79printFELT(LUOV_f79FELT a);
LUOV_f79FELT LUOV_f79add(LUOV_f79FELT a, LUOV_f79FELT b);
void LUOV_f79addInPlace(LUOV_f79FELT *a, LUOV_f79FELT *b);
int LUOV_f79isEqual(LUOV_f79FELT a, LUOV_f79FELT b);
LUOV_f79FELT LUOV_f79multiply(LUOV_f79FELT a, LUOV_f79FELT b);
LUOV_f79FELT LUOV_f79inverse(LUOV_f79FELT a); 
uint8_t LUOV_f79log(LUOV_f79FELT);
LUOV_f79FELT LUOV_f79antilog(uint8_t);
LUOV_f79FELT LUOV_f79xpown(int n);

/* serialization/deserialization */

void LUOV_f79serialize_FELT(writer *W, LUOV_f79FELT a);
LUOV_f79FELT LUOV_f79deserialize_FELT(reader *R);

#endif