#include "luov_F47Field.h"

/*
	Write a field element to a char array

	W : writer object
	a : field element to write
*/
void LUOV_f47serialize_FELT(writer *W, LUOV_f47FELT a) {
	serialize_uint64_t(W, a , 47);
}

/*
	Read a field element from a char array

	R : reader object

	returns : a field element
*/
LUOV_f47FELT LUOV_f47deserialize_FELT(reader *R) {
	return ((LUOV_f47FELT) deserialize_uint64_t(R,47));
}

/*
	prints a field element, mainly used for debugging
*/
void LUOV_f47printFELT(LUOV_f47FELT a) {
	if LUOV_f47isEqual(a,0){
		printf(".");
	} else {
		printf("x");
	}
}

//used for timing stuff
static inline
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
#define LUOV_TIC printf("\n"); uint64_t cl = rdtsc();
#define LUOV_TOC(A) printf("%s cycles = %llu \n",#A ,rdtsc() - cl); cl = rdtsc();

void f47reduce(LUOV_f47FELT *a){
	LUOV_f47FELT overflow = *a >> 47;
	*a ^= overflow ^ (overflow << 5);
	*a &= 0x7fffffffffff;
}

/*
	Multiplies two field elements

	a,b : reduced field element to LUOV_multiply

	return : the reduced product of a and b
*/
LUOV_f47FELT LUOV_f47multiply(LUOV_f47FELT a, LUOV_f47FELT b) {
	a = a & 0x7fffffffffff;
	b = b & 0x7fffffffffff; 

	LUOV_f47FELT table[16] ;

	table[ 0] = 0;
	table[ 1] = a;
	table[ 2] = (a << 1);
	table[ 3] = (a << 1) ^ a;
	
	table[ 4] = (a << 2);
	table[ 5] = (a << 2) ^  a;
	table[ 6] = (a << 2) ^ (a << 1);
	table[ 7] = (a << 2) ^ (a << 1) ^ a;

	table[ 8] = (a << 3);
	table[ 9] = (a << 3) ^  a;
	table[10] = (a << 3) ^ (a << 1);
	table[11] = (a << 3) ^ (a << 1) ^ a;

	table[12] = (a << 3) ^ (a << 2);
	table[13] = (a << 3) ^ (a << 2) ^  a;
	table[14] = (a << 3) ^ (a << 2) ^ (a << 1);
	table[15] = (a << 3) ^ (a << 2) ^ (a << 1) ^ a; 

	LUOV_f47FELT out = 0;
	LUOV_f47FELT out_lower = 0;
	LUOV_f47FELT out_upper = 0;
	LUOV_f47FELT b_lower =        b & 0x0f0f0f0f0f0f;
	LUOV_f47FELT b_upper = (b >> 4) & 0x0f0f0f0f0f0f;
	
	unsigned char *b_lower_nibbles = (unsigned char *) &b_lower;
	unsigned char *b_upper_nibbles = (unsigned char *) &b_upper;

	out_upper = table[b_upper_nibbles[5]];
	out_lower = table[b_lower_nibbles[5]];
	out_upper <<= 8;
	out_lower <<= 8;
	out_upper ^= table[b_upper_nibbles[4]];
	out_lower ^= table[b_lower_nibbles[4]];

	out = (out_upper << 4) ^ out_lower;
	f47reduce(&out);
	
	out_upper = table[b_upper_nibbles[3]];
	out_lower = table[b_lower_nibbles[3]];
	out_upper <<= 8;
	out_lower <<= 8;
	out_upper ^= table[b_upper_nibbles[2]];
	out_lower ^= table[b_lower_nibbles[2]];

	out = (out <<16) ^ (out_upper << 4) ^ out_lower;
	f47reduce(&out);

	out_upper = table[b_upper_nibbles[1]];
	out_lower = table[b_lower_nibbles[1]];
	out_upper <<= 8;
	out_lower <<= 8;
	out_upper ^= table[b_upper_nibbles[0]];
	out_lower ^= table[b_lower_nibbles[0]];

	out = (out <<16) ^ (out_upper << 4) ^ out_lower;
	f47reduce(&out);

	return out;
}

/*
	Inverts a field element

	a : field element to invert

	return : the LUOV_inverse of a, if a is nonzero
*/
LUOV_f47FELT LUOV_f47inverse(LUOV_f47FELT a) {
	uint64_t pow = 0x7ffffffffffe;
	//uint64_t pow = 0x1;
	uint64_t e = a;
	uint64_t ans = 1;
	while(pow != 0){
		if(pow & 1 == 1){
			ans = LUOV_f47multiply(ans,e);
		}
		e = LUOV_f47multiply(e,e);
		pow >>= 1;
	}
	return ans;
}

