#include "luov_prng.h"

/* 
	Initializes a LUOV_Sponge object, absorbs a seed and finalizes the absorbing phase

	 sponge  : The sponge object
	 seed    : The seed to absorb
	 len     : The length of the seed
*/
void initializeAndAbsorb(LUOV_Sponge *sponge ,const unsigned char * seed , int len ) {
	LUOV_Keccak_HashInitialize_SHAKE(sponge);
	Keccak_HashUpdate(sponge, seed, len*8 );
	Keccak_HashFinal(sponge, 0 );
}

/* 
	Squeezes a uint64_t from the sponge object

	sponge : The sponge object
	bytes  : The number of bytes to squeeze from the sponge (should be between 1 and 8)
*/
void squeezeuint64_t(LUOV_Sponge *sponge, int bytes, uint64_t *a){
	Keccak_HashSqueeze(sponge,(unsigned char *) a, bytes*8);
}