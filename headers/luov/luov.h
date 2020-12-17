#ifndef LUOV_H
#define LUOV_H

#include <stdint.h>

/*
We define the size of the finite field to use (options are 8, 16, 32, 48, 64 and 80 ),
LUOV_OIL_VARS, the number oil variables and the number of equations in the UOV system,
LUOV_VINEGAR_VARS, the number of vinegar variables,
SHAKEVENUM, the version of the shake XOF that is used (either 128 or 256)
and Wherther or not we are using Message Recovery or not
*/

// Enable / Disable message recovery mode
// #define LUOV_MESSAGE_RECOVERY

// Choose a parameter set

/* SECURITY LEVEL 2 */
    /* SMALL PK
        #define LUOV_FIELD_SIZE 47
        #define LUOV_OIL_VARS 42
        #define LUOV_VINEGAR_VARS 182
        #define LUOV_SHAKENUM 128
        #define LUOV_FIRST_PART_TARGET 32 */

    /* SMALL SIG
        #define LUOV_FIELD_SIZE 7
        #define LUOV_OIL_VARS 57
        #define LUOV_VINEGAR_VARS 197
        #define LUOV_SHAKENUM 128
        #define LUOV_FIRST_PART_TARGET 32*/

/* SECURITY LEVEL 4 */
    /* SMALL PK*/
        #define LUOV_FIELD_SIZE 61
        #define LUOV_OIL_VARS 60
        #define LUOV_VINEGAR_VARS 261
        #define LUOV_SHAKENUM 256
        #define LUOV_FIRST_PART_TARGET 48

    /* SMALL SIG
        #define LUOV_FIELD_SIZE 7
        #define LUOV_OIL_VARS 83
        #define LUOV_VINEGAR_VARS 283
        #define LUOV_SHAKENUM 256
        #define LUOV_FIRST_PART_TARGET 48*/

/* SECURITY LEVEL 5 */
    /* SMALL PK
        #define LUOV_FIELD_SIZE 79
        #define LUOV_OIL_VARS 76
        #define LUOV_VINEGAR_VARS 341
        #define LUOV_SHAKENUM 256
        #define LUOV_FIRST_PART_TARGET 64 */

    /* SMALL SIG
        #define LUOV_FIELD_SIZE 7
        #define LUOV_OIL_VARS 110
        #define LUOV_VINEGAR_VARS 374
        #define LUOV_SHAKENUM 256
        #define LUOV_FIRST_PART_TARGET 64 */


#define LUOV_VARS (LUOV_OIL_VARS+LUOV_VINEGAR_VARS)
// The number of coefficients per polynomial of the Public map P
// that is not generated but stored in the public key
#define LUOV_STORED_COLS_OF_P (LUOV_OIL_VARS*(LUOV_OIL_VARS + 1) / 2)

#define LUOV_SALT_BYTES 16

/* Number of bytes it takes to encode the secret key */
#define LUOV_CRYPTO_SECRETKEYBYTES ( 32 )
/* Number of bytes it takes to encode the public key */
#define LUOV_CRYPTO_PUBLICKEYBYTES ( 32 + ((LUOV_STORED_COLS_OF_P*LUOV_OIL_VARS+7)/8) )
/* Number of bytes it takes to encode a signature */
#define LUOV_CRYPTO_BYTES ( (LUOV_VARS*LUOV_FIELD_SIZE + 7) /8  + LUOV_SALT_BYTES )

// Enable / Disable message recovery mode
//#define LUOV_MESSAGE_RECOVERY

#ifdef LUOV_MESSAGE_RECOVERY
    #define LUOV_FIRST_PART_TARGET (LUOV_SHAKENUM/4)
    #define LUOV_SECOND_PART_TARGET ((LUOV_OIL_VARS*sizeof(LUOV_FELT))-LUOV_FIRST_PART_TARGET)
    #define LUOV_RECOVERED_PART_MESSAGE (LUOV_SECOND_PART_TARGET-1)
#else
    #define LUOV_FIRST_PART_TARGET LUOV_OIL_VARS
    #define LUOV_SECOND_PART_TARGET 0
    #define LUOV_RECOVERED_PART_MESSAGE 0
#endif

//#define LUOV_PRNG_KECCAK
#define LUOV_PRNG_CHACHA


typedef struct luov_st LUOV;
typedef struct luov_meth_st LUOV_METHOD;


LUOV *LUOV_new(int sec_level, int mode, int prng, int recovery_mode);
LUOV *LUOV_new_method(int sec_level, int mode, int prng, int recovery_mode);
const LUOV_METHOD *LUOV_get_default_method(void);

void LUOV_set_meth(LUOV_METHOD *meth);

int LUOV_generate_key(LUOV *l);
int LUOV_crypto_keygen(LUOV *l);

int LUOV_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, LUOV *l);
int LUOV_crypto_sign_message(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, LUOV *l);

int LUOV_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, LUOV *l);
int LUOV_crypto_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, LUOV *l);


#endif // LUOV_H
