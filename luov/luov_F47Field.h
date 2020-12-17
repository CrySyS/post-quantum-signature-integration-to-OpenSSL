/*
	Finite field of order 2^47 implemented as polynomial ring F_2[x]/x^47 + x^5 + 1
*/

#ifndef F47FIELD_H
#define F47FIELD_H

#include <stdint.h>
#include <stdio.h>
#include "luov_buffer.h"
#include "luov_local.h"

typedef uint64_t LUOV_f47FELT;

/* Field operations */

void LUOV_f47printFELT(LUOV_f47FELT a);
LUOV_f47FELT LUOV_f47multiply(LUOV_f47FELT a, LUOV_f47FELT b);
LUOV_f47FELT LUOV_f47inverse(LUOV_f47FELT a); 
uint8_t LUOV_f47log(LUOV_f47FELT);
LUOV_f47FELT LUOV_f47antilog(uint8_t);

/* serialization/deserialization */

void LUOV_f47serialize_FELT(writer *W, LUOV_f47FELT a);
LUOV_f47FELT LUOV_f47deserialize_FELT(reader *R);

#define LUOV_f47ZERO ((uint64_t) 0 )
#define LUOV_f47ONE ((uint64_t) 1)
#define LUOV_f47add(A,B) (A^B)
#define LUOV_f47addInPlace(A,B) (*A ^= *B)
#define LUOV_f47isEqual(A,B) ((A & 0x7fffffffffff) == (B & 0x7fffffffffff) )
#define LUOV_f47xpown(n) (((LUOV_f47FELT) 1) << n)

#endif