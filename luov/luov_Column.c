#include "luov_Column.h"

#if LUOV_OIL_VARS>64 

/*
	Write a LUOV_column to a char array
*/
void LUOV_serialize_column(writer * W, LUOV_column b) {
	int a = 0;
	int bits = LUOV_OIL_VARS;
	while (bits >64 ){
		serialize_uint64_t(W, b.components[a++]  , 64);
		bits -= 64;
	}
	serialize_uint64_t(W, b.components[a], bits);
}

/*
	Read a LUOV_column from a char array
*/
LUOV_column LUOV_deserialize_column(reader * R) {
	LUOV_column out;
	int a = 0;
	int bits = LUOV_OIL_VARS;
	while (bits >64 ){
		out.components[a++] = deserialize_uint64_t(R, 64);
		bits -= 64;
	}
	out.components[a] = deserialize_uint64_t(R, bits);
	return out;
}

/*
	LUOV_xor two columns
*/
void LUOV_xor(LUOV_column *a, LUOV_column *b) {
	a->components[0] ^= b->components[0];
	a->components[1] ^= b->components[1];
}

/*
	Randomize LUOV_column with Keccak LUOV_Sponge
*/
void LUOV_random_column(LUOV_Sponge *sponge , LUOV_column *BC) {
	int i;
	for(i=0 ; i<LUOV_COLUMN_COMPONENTS-1 ; i++){
		squeezeuint64_t(sponge,8,&BC->components[i]);
	}
	squeezeuint64_t(sponge,((LUOV_OIL_VARS%64)+7)/8,&BC->components[LUOV_COLUMN_COMPONENTS-1] ); 
}

/*
	Get a bit from the LUOV_column
*/
uint64_t LUOV_getBit(LUOV_column container, uint64_t bit) {
	return (container.components[bit/64] & ((uint64_t)1) << (bit%64) );
}

/*
	Flip a bit from the LUOV_column
*/
void LUOV_flipBit(LUOV_column *container, uint64_t bit) {
	container->components[bit/64] ^= ((uint64_t)1) << (bit%64);
}

#endif

/*
	Generates an array of columns

	sponge : pointer to a LUOV_Sponge object
	arr    : the array that will receive the generated columns
	size   : the number of columns that is generated
*/
void squeeze_column_array(LUOV_Sponge *sponge, LUOV_column *arr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		LUOV_random_column(sponge,&arr[i]);
	}
}

void ColumnGenerator_init(ColumnGenerator * col_gen, const unsigned char* key){
	int i;
	unsigned char stream[16] = {0};

	for(i=0; i<LUOV_STATES; i++){
		stream[0] = i;
		LUOV_PRNG_INIT(&col_gen->states[i], key, stream);
	}
	col_gen->cols_used = LUOV_BLOCK_SIZE/2;
}


LUOV_column Next_Column(ColumnGenerator *col_gen){
	unsigned char i,j;
	if(col_gen->cols_used == LUOV_BLOCK_SIZE/2){
		for(i=0; i<LUOV_STATES; i++){
			LUOV_PRNG_GET_BLOCK(&col_gen->states[i],col_gen->blocks[i]);
		}
		col_gen->cols_used = 0;
	}

	#if (LUOV_OIL_VARS <= 64) 
		LUOV_column Out = 0;
		for(i=0; i<LUOV_STATES; i++){
			Out |= ((LUOV_column)col_gen->blocks[i][col_gen->cols_used*2    ]) << 16*i;
			Out |= ((LUOV_column)col_gen->blocks[i][col_gen->cols_used*2 + 1]) << 16*i+8;
		}
	#else
		LUOV_column Out = {0};
		for(i=0; i<4; i++){
			Out.components[0] |= ((uint64_t)col_gen->blocks[i][col_gen->cols_used*2    ]) << 16*i;
			Out.components[0] |= ((uint64_t)col_gen->blocks[i][col_gen->cols_used*2 + 1]) << 16*i+8;
		}

		for(; i<LUOV_STATES; i++){
			Out.components[1] |= ((uint64_t)col_gen->blocks[i][col_gen->cols_used*2 + 0]) << 16*(i-4);
			Out.components[1] |= ((uint64_t)col_gen->blocks[i][col_gen->cols_used*2 + 1]) << 16*(i-4)+8;
		}
	#endif

	col_gen->cols_used ++;
	return Out;
}