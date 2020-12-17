#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <openssl/falcon.h>
#include <oqs/sig_falcon.h>


#define NUMBER_OF_KEYPAIRS 1      /* Number of keypairs that is generated during test */
#define SIGNATURES_PER_KEYPAIR 1  /* Number of times each keypair is used to sign a random document, and verify the signature */

//used for timing stuff
static inline
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
#define TIC printf("\n"); uint64_t cl = rdtsc();
#define TOC(A) printf("%s cycles = %llu \n",#A ,rdtsc() - cl); cl = rdtsc();

static void *xmalloc(size_t len)
{
    void *buf;

    if (len == 0) {
        return NULL;
    }
    buf = malloc(len);
    if (buf == NULL) {
        fprintf(stderr, "memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return buf;
}

int main()
{
    int logn = 9;
    int i,j;
    FALCON *f=FALCON_new(logn,0,0);
    clock_t cl;

    srand((unsigned int) time(NULL));

    float genTime = 0.0;
    float signTime = 0.0;
    float verifyTime = 0.0;

    uint64_t keygen_cyc = 0;    
    uint64_t sign_cyc = 0;
    uint64_t verify_cyc = 0;
    uint64_t cycles = 0;

    int ret;

    for (i = 0; i < NUMBER_OF_KEYPAIRS ; i++) {

        // time key pair generation
        cl = clock();
        cycles = rdtsc();

        ret = FALCON_generate_key(f);
        keygen_cyc += rdtsc()-cycles;
        cl = clock() - cl;
        genTime += ((float) cl)/CLOCKS_PER_SEC;
        printf("\nret of keygen: %d\n",ret);

        for (j = 0; j < SIGNATURES_PER_KEYPAIR ; j++) {

            // pick a random message to sign
            int message_len = 10000;
            unsigned char message[message_len];

            for (int k = 0; k < message_len; k++) {
                message[k] = ((unsigned char) rand());
            }

            uint8_t* sig = xmalloc(FALCON_SIG_VARTIME_MAXSIZE(logn));
            size_t siglen =FALCON_SIG_VARTIME_MAXSIZE(logn);          

            cl = clock();
            cycles = rdtsc();

            ret = FALCON_sign(sig, &siglen,message, message_len,f);

            sign_cyc += rdtsc() - cycles;
            cl = clock() - cl;
            signTime += ((float)cl) / CLOCKS_PER_SEC;
            printf("\nret of sign: %d\n",ret);

            // time verification algorithm

            cl = clock();
            cycles = rdtsc();

            ret = FALCON_verify(sig, siglen, message, message_len, f);

            verify_cyc += rdtsc() - cycles;
            cl = clock() - cl;
            verifyTime += ((float)cl) / CLOCKS_PER_SEC;
            printf("\nret of verify: %d\n",ret);

        }
    }

    printf("\n");
    printf("Key pair generation took %.4f seconds.\n", genTime / NUMBER_OF_KEYPAIRS);
    printf("Signing took %.4f seconds.\n", (signTime/NUMBER_OF_KEYPAIRS)/SIGNATURES_PER_KEYPAIR );
    printf("Verifying took %.4f seconds.\n\n", (verifyTime / NUMBER_OF_KEYPAIRS) / SIGNATURES_PER_KEYPAIR );

    printf("Key pair generation took %ld cycles.\n", keygen_cyc / NUMBER_OF_KEYPAIRS);
    printf("Signing took %ld cycles.\n", (sign_cyc/NUMBER_OF_KEYPAIRS)/SIGNATURES_PER_KEYPAIR );
    printf("Verifying took %ld cycles.\n\n", (verify_cyc / NUMBER_OF_KEYPAIRS) / SIGNATURES_PER_KEYPAIR );

    return 0;
}
