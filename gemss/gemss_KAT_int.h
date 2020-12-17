#ifndef _KAT_INT_H
#define _KAT_INT_H


/** Define GEMSS_KAT_INT to enable the creation of intermediate KAT (Known Answer 
 *  Tests) files. */
#define GEMSS_KAT_INT

#ifdef GEMSS_KAT_INT
    #include <stdio.h>
#include <openssl/gemss_prefix_name.h>

    /** Error value from fopen. */
    #define GEMSS_KAT_INT_FILE_OPEN_ERROR -1
    /** Error value from fclose. */
    #define GEMSS_KAT_INT_FILE_CLOSE_ERROR -1

    int GEMSS_PREFIX_NAME(GEMSS_open_files_KAT_INT)(FILE** fp);
    void GEMSS_PREFIX_NAME(GEMSS_fprintBstr_KAT_INT)(FILE* fp, const char *S,
                                       unsigned char *A, unsigned long long L);
    #define GEMSS_open_files_KAT_INT GEMSS_PREFIX_NAME(GEMSS_open_files_KAT_INT)
    #define GEMSS_fprintBstr_KAT_INT GEMSS_PREFIX_NAME(GEMSS_fprintBstr_KAT_INT)

    /** Macro to open a intermediate KAT file. */
    #define GEMSS_OPEN_KAT_INT_FILE\
        FILE* fp;\
        if(GEMSS_open_files_KAT_INT(&fp))\
        {\
            return GEMSS_KAT_INT_FILE_OPEN_ERROR;\
        }

    /** Macro to close a intermediate KAT file. */
    #define GEMSS_CLOSE_KAT_INT_FILE\
        if(fclose(fp))\
        {\
            return GEMSS_KAT_INT_FILE_CLOSE_ERROR;\
        }
#endif


#endif

