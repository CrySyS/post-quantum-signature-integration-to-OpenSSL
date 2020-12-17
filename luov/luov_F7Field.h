/*
	Finite field of order 2^16 implemented as polynomial ring F_2[x] mod x^16+x^12 + x^3 + 1
*/

#ifndef F7FIELD_H
#define F7FIELD_H

#include <stdint.h>
#include <stdio.h>
#include "luov_buffer.h"
#include "luov_local.h"

enum { twoPow7 = 128, f7units = twoPow7 - 1 };
typedef uint8_t LUOV_f7FELT;

/* Field operations */

void LUOV_f7printFELT(LUOV_f7FELT a);
LUOV_f7FELT LUOV_f7multiply(LUOV_f7FELT a, LUOV_f7FELT b);
LUOV_f7FELT LUOV_f7inverse(LUOV_f7FELT a); 
uint8_t LUOV_f7log(LUOV_f7FELT);
LUOV_f7FELT LUOV_f7antilog(uint8_t);

/* serialization/deserialization */

void LUOV_f7serialize_FELT(writer *W, LUOV_f7FELT a);
LUOV_f7FELT LUOV_f7deserialize_FELT(reader *R);

#define LUOV_f7ZERO 0
#define LUOV_f7ONE 1
#define LUOV_f7add(A,B) (A^B)
#define LUOV_f7addInPlace(A,B) (*A ^= *B)
#define LUOV_f7isEqual(A,B) ((A & 127) == (B & 127) )
#define LUOV_f7xpown(n) (((LUOV_f7FELT) 1) << n)

#endif