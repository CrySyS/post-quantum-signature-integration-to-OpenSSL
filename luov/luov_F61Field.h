/*
	Finite field of order 2^47 implemented as polynomial ring F_2[x]/x^61 + x^5 + x^2 + x + 1
*/

#ifndef F61FIELD_H
#define F61FIELD_H

#include <stdint.h>
#include <stdio.h>
#include "luov_buffer.h"
#include "luov_local.h"

typedef uint64_t LUOV_f61FELT;

/* Field operations */

void LUOV_f61printFELT(LUOV_f61FELT a);
LUOV_f61FELT LUOV_f61multiply(LUOV_f61FELT a, LUOV_f61FELT b);
LUOV_f61FELT LUOV_f61inverse(LUOV_f61FELT a); 
uint8_t LUOV_f61log(LUOV_f61FELT);
LUOV_f61FELT LUOV_f61antilog(uint8_t);

uint64_t clmul(uint64_t a, uint64_t b);

/* serialization/deserialization */

void LUOV_f61serialize_FELT(writer *W, LUOV_f61FELT a);
LUOV_f61FELT LUOV_f61deserialize_FELT(reader *R);

#define LUOV_f61ZERO ((uint64_t) 0 )
#define LUOV_f61ONE ((uint64_t) 1)
#define LUOV_f61add(A,B) (A^B)
#define LUOV_f61addInPlace(A,B) (*A ^= *B)
#define LUOV_f61isEqual(A,B) ((A & 0x1fffffffffffffff) == (B & 0x1fffffffffffffff) )
#define LUOV_f61xpown(n) (((LUOV_f61FELT) 1) << n)

#endif