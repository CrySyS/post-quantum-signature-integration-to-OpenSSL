
/*
//  PQCgenKAT_sign.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gemss_rng.h"
#include "gemss_api.h"
/* XXX I add this file for GEMSS_randombytes XXX */
#include "gemss_randombytes.h"

#define GEMSS_NB_KATS 10
#define	GEMSS_MAX_MARKER_LEN		50

#define GEMSS_KAT_SUCCESS          0
#define GEMSS_KAT_FILE_OPEN_ERROR -1
#define GEMSS_KAT_DATA_ERROR      -3
#define GEMSS_KAT_CRYPTO_FAILURE  -4

int		FindMarker(FILE *infile, const char *marker);
int		ReadHex(FILE *infile, unsigned char *A, int Length, char *str);
void	fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

#ifdef GeMSS
    char    AlgName[] = "GeMSS";
#elif defined(GEMSS_BlueGeMSS)
    char    AlgName[] = "GEMSS_BlueGeMSS";
#elif defined(GEMSS_RedGeMSS)
    char    AlgName[] = "GEMSS_RedGeMSS";
#elif defined(GEMSS_FGeMSS)
    char    AlgName[] = "GEMSS_FGeMSS";
#elif defined(GEMSS_DualModeMS)
    char    AlgName[] = "GEMSS_DualModeMS";
#else
    char    AlgName[] = "MQsoft";
#endif

int
main()
{
    char                fn_req[32], fn_rsp[32], fn_int[32];
    FILE                *fp_req, *fp_rsp, *fp_int;
    unsigned char       seed[48];
    unsigned char       msg[3300];
    unsigned char       entropy_input[48];
    unsigned char       *m, *sm, *m1;
    unsigned long long  mlen, smlen, mlen1;
    int                 count;
    int                 done;
    /* XXX Modification to use malloc for large sizes of keys XXX */
/*  unsigned char       pk[GEMSS_CRYPTO_PUBLICKEYBYTES], sk[GEMSS_CRYPTO_SECRETKEYBYTES]; */
    unsigned char       *pk,*sk;
    int                 ret_val;
    int                 i;
    
    /* Create the REQUEST file */
    sprintf(fn_req, "PQCsignKAT_%d.req", GEMSS_CRYPTO_SECRETKEYBYTES);
    if ( (fp_req = fopen(fn_req, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_req);
        return GEMSS_KAT_FILE_OPEN_ERROR;
    }
    sprintf(fn_rsp, "PQCsignKAT_%d.rsp", GEMSS_CRYPTO_SECRETKEYBYTES);
    if ( (fp_rsp = fopen(fn_rsp, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return GEMSS_KAT_FILE_OPEN_ERROR;
    }
    sprintf(fn_int, "PQCsignKAT_%d.int", GEMSS_CRYPTO_SECRETKEYBYTES);
    if ( (fp_int = fopen(fn_int, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_int);
        return GEMSS_KAT_FILE_OPEN_ERROR;
    }
    fclose(fp_int);

    for (i=0; i<48; i++)
        entropy_input[i] = i;

    randombytes_init(entropy_input, NULL, 256);
    for (i=0; i<GEMSS_NB_KATS; i++) {
        fprintf(fp_req, "count = %d\n", i);
        GEMSS_randombytes(seed, 48);
        fprintBstr(fp_req, (char*)"seed = ", seed, 48);
        mlen = 33*(i+1);
        fprintf(fp_req, "mlen = %llu\n", mlen);
        GEMSS_randombytes(msg, mlen);
        fprintBstr(fp_req, (char*)"msg = ", msg, mlen);
        fprintf(fp_req, "pk =\n");
        fprintf(fp_req, "sk =\n");
        fprintf(fp_req, "smlen =\n");
        fprintf(fp_req, "sm =\n\n");
    }
    fclose(fp_req);
    
    /* Create the RESPONSE file based on what's in the REQUEST file */
    if ( (fp_req = fopen(fn_req, "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fn_req);
        return GEMSS_KAT_FILE_OPEN_ERROR;
    }
    
    pk=(unsigned char*)malloc(GEMSS_CRYPTO_PUBLICKEYBYTES*sizeof(unsigned char));
    sk=(unsigned char*)malloc(GEMSS_CRYPTO_SECRETKEYBYTES*sizeof(unsigned char));
    
    fprintf(fp_rsp, "# %s\n\n", GEMSS_CRYPTO_ALGNAME);
    done = 0;
    do {
        if ( FindMarker(fp_req, "count = ") )
            ret_val=fscanf(fp_req, "%d", &count);
        else {
            done = 1;
            break;
        }
        fprintf(fp_rsp, "count = %d\n", count);

        if ( (fp_int = fopen(fn_int, "a")) == NULL ) {
            printf("Couldn't open <%s> for write\n", fn_int);
            return GEMSS_KAT_FILE_OPEN_ERROR;
        }
        fprintf(fp_int, "\ncount = %d\n", count);
        fclose(fp_int);
        
        if ( !ReadHex(fp_req, seed, 48, (char*)"seed = ") ) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return GEMSS_KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, (char*)"seed = ", seed, 48);
        
        randombytes_init(seed, NULL, 256);
        
        if ( FindMarker(fp_req, "mlen = ") )
            ret_val=fscanf(fp_req, "%llu", &mlen);
        else {
            printf("ERROR: unable to read 'mlen' from <%s>\n", fn_req);
            return GEMSS_KAT_DATA_ERROR;
        }
        fprintf(fp_rsp, "mlen = %llu\n", mlen);
        
        m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        m1 = (unsigned char *)calloc(mlen+GEMSS_CRYPTO_BYTES, sizeof(unsigned char));
        sm = (unsigned char *)calloc(mlen+GEMSS_CRYPTO_BYTES, sizeof(unsigned char));
        
        if ( !ReadHex(fp_req, m, (int)mlen, (char*)"msg = ") ) {
            printf("ERROR: unable to read 'msg' from <%s>\n", fn_req);
            return GEMSS_KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, (char*)"msg = ", m, mlen);
        
        /* Generate the public/private keypair */
        if ( (ret_val = GEMSS_crypto_sign_keypair(pk, sk)) != 0) {
            printf("GEMSS_crypto_sign_keypair returned <%d>\n", ret_val);
            return GEMSS_KAT_CRYPTO_FAILURE;
        }
        fprintBstr(fp_rsp, (char*)"pk = ", pk, GEMSS_CRYPTO_PUBLICKEYBYTES);
        fprintBstr(fp_rsp, (char*)"sk = ", sk, GEMSS_CRYPTO_SECRETKEYBYTES);
        
        if ( (ret_val = GEMSS_crypto_sign(sm, &smlen, m, mlen, sk)) != 0) {
            printf("GEMSS_crypto_sign returned <%d>\n", ret_val);
            return GEMSS_KAT_CRYPTO_FAILURE;
        }
        fprintf(fp_rsp, "smlen = %llu\n", smlen);
        fprintBstr(fp_rsp, (char*)"sm = ", sm, smlen);
        fprintf(fp_rsp, "\n");
        
        if ( (ret_val = GEMSS_crypto_sign_open(m1, &mlen1, sm, smlen, pk)) != 0) {
            printf("GEMSS_crypto_sign_open returned <%d>\n", ret_val);
            return GEMSS_KAT_CRYPTO_FAILURE;
        }
        
        if ( mlen != mlen1 ) {
            printf("GEMSS_crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n", mlen1, mlen);
            return GEMSS_KAT_CRYPTO_FAILURE;
        }
        
        if ( memcmp(m, m1, mlen) ) {
            printf("GEMSS_crypto_sign_open returned bad 'm' value\n");
            return GEMSS_KAT_CRYPTO_FAILURE;
        }
        
        free(m);
        free(m1);
        free(sm);

    } while ( !done );
    
    fclose(fp_req);
    fclose(fp_rsp);
    free(pk);
    free(sk);

    return GEMSS_KAT_SUCCESS;
}

/*
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
*/
int
FindMarker(FILE *infile, const char *marker)
{
	char	line[GEMSS_MAX_MARKER_LEN];
	int		i, len;
	int curr_line;

	len = (int)strlen(marker);
	if ( len > GEMSS_MAX_MARKER_LEN-1 )
		len = GEMSS_MAX_MARKER_LEN-1;

	for ( i=0; i<len; i++ )
	  {
	    curr_line = fgetc(infile);
	    line[i] = curr_line;
	    if (curr_line == EOF )
	      return 0;
	  }
	line[len] = '\0';

	while ( 1 ) {
		if ( !strncmp(line, marker, len) )
			return 1;

		for ( i=0; i<len-1; i++ )
			line[i] = line[i+1];
		curr_line = fgetc(infile);
		line[len-1] = curr_line;
		if (curr_line == EOF )
		    return 0;
		line[len] = '\0';
	}

	/* shouldn't get here */
	return 0;
}

/*
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
*/
int
ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
	int			i, ch, started;
	unsigned char	ich;

	if ( Length == 0 ) {
		A[0] = 0x00;
		return 1;
	}
	memset(A, 0x00, Length);
	started = 0;
	if ( FindMarker(infile, str) )
		while ( (ch = fgetc(infile)) != EOF ) {
			if ( !isxdigit(ch) ) {
				if ( !started ) {
					if ( ch == '\n' )
						break;
					else
						continue;
				}
				else
					break;
			}
			started = 1;
			if ( (ch >= '0') && (ch <= '9') )
				ich = ch - '0';
			else if ( (ch >= 'A') && (ch <= 'F') )
				ich = ch - 'A' + 10;
			else if ( (ch >= 'a') && (ch <= 'f') )
				ich = ch - 'a' + 10;
            else /* shouldn't ever get here */
                ich = 0;
			
			for ( i=0; i<Length-1; i++ )
				A[i] = (A[i] << 4) | (A[i+1] >> 4);
			A[Length-1] = (A[Length-1] << 4) | ich;
		}
	else
		return 0;

	return 1;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
	unsigned long long  i;

	fprintf(fp, "%s", S);

	for ( i=0; i<L; i++ )
		fprintf(fp, "%02X", A[i]);

	if ( L == 0 )
		fprintf(fp, "00");

	fprintf(fp, "\n");
}

