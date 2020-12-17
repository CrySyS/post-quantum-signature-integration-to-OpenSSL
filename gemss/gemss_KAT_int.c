#include "gemss_KAT_int.h"


#ifdef GEMSS_KAT_INT
#include <openssl/gemss.h>

/**
 * @brief   Open a intermediate KAT (Known Answer Tests) file.
 * @param[out]   fp  A file descriptor which will the intermediate KAT file.
 * @return  Zero if the function runs correctly, non-zero else.
 */
int GEMSS_PREFIX_NAME(GEMSS_open_files_KAT_INT)(FILE** fp)
{
    char fn_int[32];

    sprintf(fn_int, "PQCsignKAT_%d.int", GEMSS_CRYPTO_SECRETKEYBYTES);
    if ( (*fp = fopen(fn_int, "a")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_int);
        return GEMSS_KAT_INT_FILE_OPEN_ERROR;
    }

    return 0;
}

/**
 * @brief   Open a intermediate KAT (Known Answer Tests) file.
 * @param[in]   fp  A file descriptor.
 * @param[in]   S   A string which will be written in first in fp.
 * @param[in]   A   A buffer of bytes, which will be written in hexadecimal in
 * A.
 * @param[in]   L   The length in bytes of A.
 */
/* This function is a modified version of fprintBstr from PQCgenKAT_sign.c */
void GEMSS_PREFIX_NAME(GEMSS_fprintBstr_KAT_INT)(FILE* fp, const char *S, unsigned char *A,
                                     unsigned long long L)
{
    unsigned long long  i;

    fprintf(fp, "%s", S);

    for ( i=0; i<L; i++ )
        fprintf(fp, "%02X", A[i]);

    if ( L == 0 )
        fprintf(fp, "00");

    fprintf(fp, "\n");
}
#endif

