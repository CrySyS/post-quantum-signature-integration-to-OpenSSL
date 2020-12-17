#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/luov.h>

#define LUOV_NUMBER_OF_KEYPAIRS 100      /* Number of keypairs that is generated during test */
#define LUOV_SIGNATURES_PER_KEYPAIR 10  /* Number of times each keypair is used to sign a random document, and verify the signature */

//used for timing stuff
static inline
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
#define LUOV_TIC printf("\n"); uint64_t cl = rdtsc();
#define LUOV_TOC(A) printf("%s cycles = %llu \n",#A ,rdtsc() - cl); cl = rdtsc();

int main(void)
{
    int i, j, k;
    int message_size = 10000;
    unsigned long long smlen;
    unsigned char m[message_size];
    unsigned char m2[message_size];
    unsigned char *pk = malloc(sizeof(unsigned char[LUOV_CRYPTO_PUBLICKEYBYTES]));
    unsigned char *sk = malloc(sizeof(unsigned char[LUOV_CRYPTO_SECRETKEYBYTES]));
    unsigned char *sm = malloc(sizeof(unsigned char[message_size + LUOV_CRYPTO_BYTES]));
    clock_t cl;

    // Print key and signature sizes
    printf("Public Key takes %d B\n", LUOV_CRYPTO_PUBLICKEYBYTES );
    printf("Secret Key takes %d B\n", LUOV_CRYPTO_SECRETKEYBYTES );
    printf("Signature takes %d B\n\n", LUOV_CRYPTO_BYTES );

    printf("Public Key takes %.2f kB\n", LUOV_CRYPTO_PUBLICKEYBYTES / 1024.0);
    printf("Secret Key takes %.2f kB\n", LUOV_CRYPTO_SECRETKEYBYTES / 1024.0);
    printf("Signature takes %.2f kB\n\n", LUOV_CRYPTO_BYTES / 1024.0);

    srand((unsigned int) time(NULL));

    float genTime = 0.0;
    float signTime = 0.0;
    float verifyTime = 0.0;
    uint64_t keygen_cyc = 0;
    uint64_t sign_cyc = 0;
    uint64_t verify_cyc = 0;
    uint64_t cycles = 0;

    LUOV *l = LUOV_new(1,1,1,1);
    for (i = 0; i < LUOV_NUMBER_OF_KEYPAIRS ; i++) {

        // time key pair generation
        cl = clock();
        cycles = rdtsc();

        int ret_num = LUOV_generate_key(l);

        keygen_cyc += rdtsc()-cycles;
        cl = clock() - cl;
        genTime += ((float) cl)/CLOCKS_PER_SEC;
        printf("\nret_num of keygen: %d\n",ret_num);

        for (j = 0; j < LUOV_SIGNATURES_PER_KEYPAIR ; j++) {

            // pick a random message to sign
            for (k = 0; k < message_size; k++) {
                m[k] = ((unsigned char) rand());
            }

            // time signing algorithm
            cl = clock();
            cycles = rdtsc();

            ret_num = LUOV_sign(sm, &smlen, m, (unsigned long long) sizeof(m), l);

            sign_cyc += rdtsc() - cycles;
            cl = clock() - cl;
            signTime += ((float)cl) / CLOCKS_PER_SEC;

            printf("\nret_num of sign: %d\n",ret_num);

            // time verification algorithm

            cl = clock();
            cycles = rdtsc();

            ret_num = LUOV_verify(m2, &smlen, sm, smlen, l);

            verify_cyc += rdtsc() - cycles;
            cl = clock() - cl;
            verifyTime += ((float)cl) / CLOCKS_PER_SEC;
            printf("\nret_num of verify: %d\n",ret_num);

            if (ret_num != 0) {
                printf("Verification of signature Failed!\n");
            }            
        }

    }

    printf("\n");
    printf("Key pair generation took %.4f seconds.\n", genTime / LUOV_NUMBER_OF_KEYPAIRS);
    printf("Signing took %.4f seconds.\n", (signTime/LUOV_NUMBER_OF_KEYPAIRS)/LUOV_SIGNATURES_PER_KEYPAIR );
    printf("Verifying took %.4f seconds.\n\n", (verifyTime / LUOV_NUMBER_OF_KEYPAIRS) / LUOV_SIGNATURES_PER_KEYPAIR );

    printf("Key pair generation took %ld cycles.\n", keygen_cyc / LUOV_NUMBER_OF_KEYPAIRS);
    printf("Signing took %ld cycles.\n", (sign_cyc/LUOV_NUMBER_OF_KEYPAIRS)/LUOV_SIGNATURES_PER_KEYPAIR );
    printf("Verifying took %ld cycles.\n\n", (verify_cyc / LUOV_NUMBER_OF_KEYPAIRS) / LUOV_SIGNATURES_PER_KEYPAIR );

    free(pk);
    free(sk);
    free(sm);

    return 0;
}
