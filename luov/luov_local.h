#ifndef LUOV_LOCAL_H
#define LUOV_LOCAL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <openssl/luov.h>

#include <stdint.h>

/* Number of bytes it takes to encode a partial signature */
#define LUOV__PARTIAL_SIGNATURE_BYTES ( LUOV_VARS*(sizeof(LUOV_FELT)) + (LUOV_OIL_VARS*sizeof(LUOV_FELT)+7)/8*8*LUOV_OIL_VARS*(LUOV_FIELD_SIZE) + sizeof(LUOV_column)*(LUOV_VINEGAR_VARS+1) + LUOV_SALT_BYTES )
#define LUOV_PARTIAL_SIGNATURE_BYTES ((LUOV__PARTIAL_SIGNATURE_BYTES+7)/8*8)

#define LUOV_CRYPTO_ALGNAME "LUOV"

#define LUOV_crypto_sign_keypair luov_keygen
#define LUOV_crypto_sign luov_sign
#define LUOV_crypto_sign_open luov_verify


#define LUOV_PK_SEED(pk) pk
#define LUOV_PK_Q2(pk) (pk + 32)

#define LUOV_SIG_SOL(sig) sig
#define LUOV_SIG_SALT(sig) (sig+ (LUOV_VARS*LUOV_FIELD_SIZE + 7) /8 )

#define LUOV_PARTSIG_INVERSE(partial_signature) (partial_signature)
#define LUOV_PARTSIG_VINEGAR(partial_signature) (LUOV_PARTSIG_INVERSE(partial_signature) + (LUOV_OIL_VARS*sizeof(LUOV_FELT)+7)/8*8*LUOV_OIL_VARS*(LUOV_FIELD_SIZE))
#define LUOV_PARTSIG_TARGET(partial_signature) (LUOV_PARTSIG_VINEGAR(partial_signature) + (sizeof(LUOV_FELT))*LUOV_VINEGAR_VARS )
#define LUOV_PARTSIG_T(partial_signature) (LUOV_PARTSIG_TARGET(partial_signature) + (sizeof(LUOV_FELT))*LUOV_OIL_VARS  )
#define LUOV_PARTSIG_SALT(partial_signature) (LUOV_PARTSIG_T(partial_signature) + sizeof(LUOV_column)*(LUOV_VINEGAR_VARS+1) )


/* derived parameters */
#define LUOV_FIELD_MASK ((((uint64_t) 1) << LUOV_FIELD_SIZE) -1)

// Defines the appropriate Keccak_HashInitialize function based on the value of LUOV_SHAKENUM
#define LUOV__Keccak_HashInitialize_SHAKE(NUM) Keccak_HashInitialize_SHAKE##NUM
#define LUOV___Keccak_HashInitialize_SHAKE(NUM) LUOV__Keccak_HashInitialize_SHAKE(NUM)
#define LUOV_Keccak_HashInitialize_SHAKE LUOV___Keccak_HashInitialize_SHAKE(LUOV_SHAKENUM)

// Defines the field operations
#define LUOV___DEFINE_OPERATION(FS,OPERATION) LUOV_f##FS##OPERATION
#define LUOV__DEFINE_OPERATION(FS,OPERATION) LUOV___DEFINE_OPERATION(FS,OPERATION)
#define LUOV_DEFINE_OPERATION(OPERATION) LUOV__DEFINE_OPERATION(LUOV_FIELD_SIZE,OPERATION)

#define LUOV_FELT LUOV_DEFINE_OPERATION(FELT)
#define LUOV_serialize_FELT LUOV_DEFINE_OPERATION(serialize_FELT)
#define LUOV_deserialize_FELT LUOV_DEFINE_OPERATION(deserialize_FELT)
#define LUOV_printFELT LUOV_DEFINE_OPERATION(printFELT)
#define LUOV_isEqual LUOV_DEFINE_OPERATION(isEqual)
#define LUOV_multiply LUOV_DEFINE_OPERATION(multiply)
#define LUOV_minus(x) (x)
#define LUOV_add LUOV_DEFINE_OPERATION(add)
#define LUOV_subtract(x,y) LUOV_add(x,y)
#define LUOV_inverse LUOV_DEFINE_OPERATION(inverse)
#define LUOV_ZERO LUOV_DEFINE_OPERATION(ZERO)
#define LUOV_ONE LUOV_DEFINE_OPERATION(ONE)
#define LUOV_xpown LUOV_DEFINE_OPERATION(xpown)
#define LUOV_scalarMultiply LUOV_DEFINE_OPERATION(scalarMultiply)
#define LUOV_addInPlace LUOV_DEFINE_OPERATION(addInPlace)

struct luov_st{
    unsigned char *pk;
    unsigned char *sk;
    const LUOV_METHOD *meth;
    int security_level;
    int mode;
    int prng;
    int recovery_mode;
};

struct luov_meth_st{
    char *name;
    int (*luov_keygen)(const LUOV *l);
    int (*luov_sign)(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len, const LUOV *l);
    int (*luov_verify)(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen,
        const LUOV *l);
    int (*luov_custom_keygen)(const LUOV *l);
    int (*luov_custom_sign)(unsigned char *sig, unsigned long long * smlen, const unsigned char *m, uint64_t m_len,
        const LUOV *l);
    int (*luov_custom_verify)(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen,
        const LUOV *l);
};


int luov_keygen(unsigned char *pk, unsigned char *sk);
int luov_sign(unsigned char *sig, unsigned long long * smlen, const unsigned char* document, uint64_t len, const unsigned char *sk);
int luov_verify(unsigned char* m, unsigned long long *mlen, const unsigned char* sm, unsigned long long smlen, const unsigned char *pk);

int luov_sign_start(unsigned char *partial_signature, const unsigned char *sk);
int luov_sign_finish(unsigned char *sig, unsigned long long * smlen, const unsigned char* document, uint64_t len, unsigned char *partial_signature);

#endif // LUOV_LOCAL_H
