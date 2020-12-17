#ifndef _CHOICE_CRYPTO_H
#define _CHOICE_CRYPTO_H

#include <stdint.h>

/* To test the library. */
/* Value 0: the user can modify parameters to test the library. */
/* The other values are the number of 32-bit words of an element of GF(2^n),
   i.e. ceil(n/32), between 1 and 18. */
/* #define GEMSS_TEST_LIBRARY (0) */

/** Level of security of the cryptosystem and the hash functions. */
#ifndef GEMSS_TEST_LIBRARY
    #define GEMSS_K 256U
#else
/*        #define GEMSS_K 256U */
#endif

/** Choice of the current cryptosystem. */
#ifndef GEMSS_TEST_LIBRARY
    /*#define GEMSS_BlueGeMSS*/
/* To choose parameters of GeMSS */
 /*#define GeMSS*/
/* To choose parameters of GEMSS_BlueGeMSS */
 /*#define GEMSS_BlueGeMSS*/
/* To choose parameters of GEMSS_RedGeMSS */
#define GEMSS_RedGeMSS
/* To choose parameters of GEMSS_FGeMSS */
/* #define GEMSS_FGeMSS*/
/* To choose parameters of GEMSS_DualModeMS */
/* #define GEMSS_DualModeMS */
/* To use GEMSS_QUARTZ (version 2, is broken) */
/* #define GEMSS_QUARTZ */
/* To use GEMSS_QUARTZ_V1 (is broken) */
/* #define GEMSS_QUARTZ_V1 */
#endif

#define GEMSS_INNER_DualModeMS 1

/** Choice of a GEMSS_HFE-based multivariate scheme. */
#if (defined(GeMSS)||defined(GEMSS_BlueGeMSS)||defined(GEMSS_RedGeMSS)||defined(GEMSS_FGeMSS)||\
     defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1)||\
     defined(GEMSS_DualModeMS)||defined(GEMSS_TEST_LIBRARY))
    #define GEMSS_HFE 1
#else
    #define GEMSS_HFE 0
#endif



#if (defined(GeMSS)||defined(GEMSS_BlueGeMSS)||defined(GEMSS_RedGeMSS)||defined(GEMSS_FGeMSS)||\
    defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1)||\
    GEMSS_INNER_DualModeMS||defined(GEMSS_TEST_LIBRARY))
    /** Boolean for the inner mode. */
    #define GEMSS_InnerMode 1
    /** Boolean for the dual mode. */
    #define GEMSS_DualMode 0
#else
    /** Boolean for the inner mode. */
    #define GEMSS_InnerMode 0
    /** Boolean for the dual mode. */
    #define GEMSS_DualMode 1
#endif

#if GEMSS_InnerMode
    /** Boolean enabling the code of the dual mode. */
    #define GEMSS_ENABLED_DUALMODE 0
#else
    /** Boolean enabling the code of the dual mode, necessarily True here. */
    #define GEMSS_ENABLED_DUALMODE 1
#endif

/** Set the EUF-CMA property of the cryptosystem. */
#define GEMSS_EUF_CMA_PROPERTY 0

/*----------------------Prefix-----------------------------------------------*/
/** Auxiliar macro. */
#define GEMSS_CONCAT_NAME2(a,b) a ## b
/** This macro permits to concat the names. */
#define GEMSS_CONCAT_NAME(a,b) GEMSS_CONCAT_NAME2(a,b)


/** This macro permits to prefix the name of all functions with the name of the
 *  current cryptosystem. */
/* For example, if you use GeMSS with a level of security 128 bits,
   GEMSS_PREFIX_NAME(function) will generate GeMSS_128U_function. */
#define GEMSS_PREFIX_NAME(name) GEMSS_CONCAT_NAME(GEMSS_CONCAT_NAME(GEMSS_CRYPTO_NAME,GEMSS_K),_##name)


/*------------------------------------Sizes--------------------------------------------------------*/
/** Theoretical in bits size of the public-key (inner mode). */
#define GEMSS_SIZE_PK_THEORETICAL_INNER GEMSS_SIZE_PK_THEORETICAL_HFE
/** Theoretical in bits size of the secret-key (inner mode). */
#define GEMSS_SIZE_SK_THEORETICAL_INNER GEMSS_SIZE_SK_THEORETICAL_HFE
/** Theoretical in bits size of the signature (inner mode). */
#define GEMSS_SIZE_SIGN_THEORETICAL_INNER GEMSS_SIZE_SIGN_THEORETICAL_HFE

/** Practical size in bytes of the public-key (inner mode). */
#define GEMSS_SIZE_PK_INNER GEMSS_SIZE_PK_HFE
/** Practical size in bytes of the secret-key (inner mode). */
#define GEMSS_SIZE_SK_INNER GEMSS_SIZE_SK_HFE
/** Practical size in bytes of the signature (inner mode). */
#define GEMSS_SIZE_SIGN_INNER GEMSS_SIZE_SIGN_HFE
#endif


#if GEMSS_InnerMode
/** Theoretical size in bits of the public-key. */
#define GEMSS_SIZE_PK_THEORETICAL GEMSS_SIZE_PK_THEORETICAL_INNER
/** Theoretical size in bits of the secret-key. */
#define GEMSS_SIZE_SK_THEORETICAL GEMSS_SIZE_SK_THEORETICAL_INNER
/** Theoretical size in bits of the signature. */
#define GEMSS_SIZE_SIGN_THEORETICAL GEMSS_SIZE_SIGN_THEORETICAL_INNER

/** Practical size in bytes of the public-key. */
#define GEMSS_SIZE_PK GEMSS_SIZE_PK_INNER
/** Practical size in bytes of the secret-key. */
#define GEMSS_SIZE_SK GEMSS_SIZE_SK_INNER
/** Practical size in bytes of the signature. */
#define GEMSS_SIZE_SIGN GEMSS_SIZE_SIGN_INNER
#endif

/*---------------------------------------Actual sizes------------------------------------------*/

#define GEMSS_ENABLED_SEED_SK 1

#if GEMSS_EUF_CMA_PROPERTY
    #define GEMSS_SIZE_SALT_BITS 128
    /* Size of the salt in bytes */
    #define GEMSS_SIZE_SALT 16
    #define GEMSS_SIZE_SALT_WORD 2
#else
    #define GEMSS_SIZE_SALT_BITS 0
    /* Size of the salt in bytes */
    #define GEMSS_SIZE_SALT 0
    #define GEMSS_SIZE_SALT_WORD 0
#endif


#if GEMSS_ENABLED_SEED_SK
    /* Size of the secret seed in bytes */
    #if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))
        #define GEMSS_SIZE_SEED_SK 16
    #else
        /* GEMSS_K bits */
        #define GEMSS_SIZE_SEED_SK (GEMSS_K>>3)
    #endif
#endif


/****************** THEORETICAL SIZES ******************/

/* Sizes in bits */
#define GEMSS_SIZE_PK_THEORETICAL_HFE (GEMSS_HFEm*(((GEMSS_HFEnv*(GEMSS_HFEnv+1))>>1)+1))

#if GEMSS_ENABLED_SEED_SK
    #define GEMSS_SIZE_SK_THEORETICAL_HFE (GEMSS_SIZE_SEED_SK<<3)
#else
    #define GEMSS_SIZE_SK_THEORETICAL_HFE \
                ((GEMSS_HFEnv*GEMSS_HFEnv)+(GEMSS_HFEn*GEMSS_HFEn)+GEMSS_NB_COEFS_HFEVPOLY*GEMSS_HFEn)
#endif

#define GEMSS_SIZE_SIGN_THEORETICAL_HFE (GEMSS_HFEnv+(GEMSS_NB_ITE-1)*(GEMSS_HFEnv-GEMSS_HFEm)+GEMSS_SIZE_SALT_BITS)




/* Secret-key: GEMSS_HFE polynomial + matrix S_inv + matrix T_inv (+ vector -t) */

#if GEMSS_AFFINE_TRANSFORMATION_BY_t
    #define GEMSS_SIZE_VECTOR_t GEMSS_NB_WORD_GF2m
#else
    #define GEMSS_SIZE_VECTOR_t 0
#endif

#define GEMSS_ACCESS_MATRIX_S GEMSS_NB_UINT_HFEVPOLY
#define GEMSS_ACCESS_MATRIX_T (GEMSS_ACCESS_MATRIX_S+GEMSS_MATRIXnv_SIZE)
#define GEMSS_ACCESS_VECTOR_t (GEMSS_ACCESS_MATRIX_T+GEMSS_MATRIXn_SIZE)

/* Secret-key (words) */
#define GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD (GEMSS_ACCESS_VECTOR_t+GEMSS_SIZE_VECTOR_t)
/* Secret-key (bytes) */
#define GEMSS_SIZE_SK_HFE_UNCOMPRESSED (GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD<<3)

#if GEMSS_ENABLED_SEED_SK
    /* Secret-key (bytes) */
    #define GEMSS_SIZE_SK_HFE GEMSS_SIZE_SEED_SK
    /* Secret-key (words) */
    #define GEMSS_SIZE_SK_HFE_WORD ((GEMSS_SIZE_SK_HFE+7)>>3)
#else
    /* Secret-key (words) */
    #define GEMSS_SIZE_SK_HFE_WORD GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD
    /* Secret-key (bytes) */
    #define GEMSS_SIZE_SK_HFE GEMSS_SIZE_SK_HFE_UNCOMPRESSED
#endif


/* Signature: GEMSS_NB_WORD_GF2nv for signature GEMSS_NB_ITE, GEMSS_NB_WORD_GF2nvm for others */

/* Size of signature (words): */
#define GEMSS_SIZE_SIGN_UNCOMPRESSED \
            (GEMSS_NB_WORD_GF2nv+(GEMSS_NB_ITE-1)*GEMSS_NB_WORD_GF2nvm+GEMSS_SIZE_SALT_WORD)
/* Size of signature (bytes): */
/* (x+7)/8 = Ceiling(x/8) */
#define GEMSS_SIZE_SIGN_HFE ((GEMSS_SIZE_SIGN_THEORETICAL_HFE+7)>>3)



/*-----------------------------------Parameters------------------------------------------------*/

/****************** PARAMETERS FOR GEMSS_HFE ******************/


/** GF(q) */
#if GEMSS_HFE
    #define GEMSS_GFq 2U
    #define GEMSS_Log2_q 1
    /* For GEMSS_HFE, the previous parameter is necessarily 2. */

    /** This type stores an element of GF(q). */
    typedef unsigned char gf2;
#endif



/* Number of variables of the public-key */
#define GEMSS_HFEnv (GEMSS_HFEn+GEMSS_HFEv)

/* Number of equations of the public-key */
#define GEMSS_HFEm (GEMSS_HFEn-GEMSS_HFEDELTA)



#if (defined(GEMSS_QUARTZ)||defined(GEMSS_QUARTZ_V1))

#if (GEMSS_K==80)

    #define GEMSS_HFEn 103U
    #define GEMSS_HFEv 4U
    #define GEMSS_HFEDELTA 3U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

#else
    #error "GEMSS_K is not 80"
#endif


#elif defined(GeMSS)

/* GeMSS128 */
#if (GEMSS_K==128)

    #define GEMSS_HFEn 174U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* GeMSS192 */
#elif (GEMSS_K==192)

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 20U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* GeMSS256 */
#elif (GEMSS_K==256)

    #define GEMSS_HFEn 354U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* GeMSS??? */
#else
    #error "GEMSS_K is not 128, 192 or 256"
#endif


#elif defined(GEMSS_BlueGeMSS)

/* BlueGeMSS128 */
#if (GEMSS_K==128)

    #define GEMSS_HFEn 175U
    #define GEMSS_HFEv 14U
    #define GEMSS_HFEDELTA 13U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* BlueGeMSS192 */
#elif (GEMSS_K==192)

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* BlueGeMSS256 */
#elif (GEMSS_K==256)

    #define GEMSS_HFEn 358U
    #define GEMSS_HFEv 32U
    #define GEMSS_HFEDELTA 34U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* GEMSS_BlueGeMSS??? */
#else
    #error "GEMSS_K is not 128, 192 or 256"
#endif


#elif defined(GEMSS_RedGeMSS)

/* RedGeMSS128 */
#if (GEMSS_K==128)

    #define GEMSS_HFEn 177U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* RedGeMSS192 */
#elif (GEMSS_K==192)

    #define GEMSS_HFEn 266U
    #define GEMSS_HFEv 25U
    #define GEMSS_HFEDELTA 23U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* RedGeMSS256 */
#elif (GEMSS_K==256)

    #define GEMSS_HFEn 358U
    #define GEMSS_HFEv 35U
    #define GEMSS_HFEDELTA 34U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* GEMSS_RedGeMSS??? */
#else
    #error "GEMSS_K is not 128, 192 or 256"
#endif


#elif defined(GEMSS_FGeMSS)

    #define GEMSS_NB_ITE 1U
    #define GEMSS_HFEs 0U

    /* GEMSS_FGeMSS(266) */
    #if (GEMSS_K==128)
        #define GEMSS_HFEn 266U

        #define GEMSS_HFEv 11U
        #define GEMSS_HFEDELTA 10U

        #define GEMSS_HFEDeg 129U
        #define GEMSS_HFEDegI 7U
        #define GEMSS_HFEDegJ 0U
    /* GEMSS_FGeMSS(402) */
    #elif (GEMSS_K==192)
        #define GEMSS_HFEn 402U

        #define GEMSS_HFEv 18U
        #define GEMSS_HFEDELTA 18U

        #define GEMSS_HFEDeg 640U
        #define GEMSS_HFEDegI 9U
        #define GEMSS_HFEDegJ 7U
    /* GEMSS_FGeMSS(537) */
    #elif (GEMSS_K==256)
        #define GEMSS_HFEn 537U

        #define GEMSS_HFEv 26U
        #define GEMSS_HFEDELTA 25U

        #define GEMSS_HFEDeg 1152U
        #define GEMSS_HFEDegI 10U
        #define GEMSS_HFEDegJ 7U
    /* GEMSS_FGeMSS(???) */
    #else
        #error "GEMSS_K is not 128, 192 or 256"
    #endif


#elif defined(GEMSS_DualModeMS)

/* DualModeMS128 */
#if (GEMSS_K==128)

    #define GEMSS_HFEn 266U
    #define GEMSS_HFEv 11U
    #define GEMSS_HFEDELTA 10U

    /* This parameter must not be changed */
    #define GEMSS_NB_ITE 1

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* DualModeMS192 */
#elif (GEMSS_K==192)

    #define GEMSS_HFEn 402U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 18U

    /* This parameter must not be changed */
    #define GEMSS_NB_ITE 1

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

/* DualModeMS256 */
#elif (GEMSS_K==256)

    #define GEMSS_HFEn 544U
    #define GEMSS_HFEv 32U
    #define GEMSS_HFEDELTA 32U

    /* This parameter must not be changed */
    #define GEMSS_NB_ITE 1

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U

#else
    /* GEMSS_DualModeMS??? */
    #error "GEMSS_K is not 128, 192 or 256"
#endif


#elif defined(GEMSS_TEST_LIBRARY)

#if (!GEMSS_TEST_LIBRARY)
    /* The user can modify these values to test the library */

    /* Level of security of the cryptosystems
       (2K is the level of security of the hash functions) */
    #define GEMSS_K 128U

    /* Degree of the extension GF(2^n) */
    #define GEMSS_HFEn 174U
    /* Number of vinegar variable */
    #define GEMSS_HFEv 12U
    /* Number of removed equations (the minus) */
    #define GEMSS_HFEDELTA 12U

    /* Number of iterations in the Feistel-Patarin scheme, different from 0 */
    #define GEMSS_NB_ITE 4

    /* Degree of the GEMSS_HFE polynomial: Deg = 2^DegI + 2^DegJ
     * or Deg = 2^0 (with DegI==DegJ==0) */
    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    /* Requirement : DegI>=DegJ */
    #define GEMSS_HFEDegJ 0U

    /* Number of removed odd degree terms in the GEMSS_HFEv polynomial */
    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==1)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 29U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==2)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 62U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==3)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 95U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==4)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 126U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==5)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 156U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==6)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 186U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==7)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 220U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==8)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 252U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==9)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 278U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==10)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 314U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==11)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 345U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==12)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 375U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==13)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 414U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==14)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 441U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==15)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 476U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==16)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 508U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==17)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 543U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 31U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==18)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 574U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 62U

    #define GEMSS_NB_ITE 4

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==100)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 268U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==101)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 204U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==102)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 186U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==103)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 177U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==104)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 268U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==105)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 204U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==106)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 186U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==107)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 177U
    #define GEMSS_HFEv 15U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==108)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 266U
    #define GEMSS_HFEv 11U
    #define GEMSS_HFEDELTA 10U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==109)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 266U
    #define GEMSS_HFEv 11U
    #define GEMSS_HFEDELTA 10U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==110)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 204U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==111)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 204U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==112)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 185U
    #define GEMSS_HFEv 13U
    #define GEMSS_HFEDELTA 14U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==113)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 185U
    #define GEMSS_HFEv 13U
    #define GEMSS_HFEDELTA 14U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==114)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 175U
    #define GEMSS_HFEv 14U
    #define GEMSS_HFEDELTA 13U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==115)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 175U
    #define GEMSS_HFEv 14U
    #define GEMSS_HFEDELTA 13U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==116)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 9U
    #define GEMSS_HFEDELTA 9U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==117)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 9U
    #define GEMSS_HFEDELTA 9U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==118)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 202U
    #define GEMSS_HFEv 11U
    #define GEMSS_HFEDELTA 10U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==119)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 202U
    #define GEMSS_HFEv 11U
    #define GEMSS_HFEDELTA 10U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==120)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 183U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==121)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 183U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==122)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 174U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==123)
    #define GEMSS_K 128U

    #define GEMSS_HFEn 174U
    #define GEMSS_HFEv 12U
    #define GEMSS_HFEDELTA 12U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==124)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 404U
    #define GEMSS_HFEv 19U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==125)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 310U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==126)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 279U
    #define GEMSS_HFEv 25U
    #define GEMSS_HFEDELTA 23U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==127)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 266U
    #define GEMSS_HFEv 25U
    #define GEMSS_HFEDELTA 23U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==128)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 404U
    #define GEMSS_HFEv 19U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==129)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 310U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==130)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 279U
    #define GEMSS_HFEv 25U
    #define GEMSS_HFEDELTA 23U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==131)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 266U
    #define GEMSS_HFEv 25U
    #define GEMSS_HFEDELTA 23U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==132)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 402U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 18U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==133)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 402U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 18U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==134)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 402U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 18U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 640U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 7U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==135)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 402U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 18U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 640U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 7U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==136)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 308U
    #define GEMSS_HFEv 22U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==137)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 308U
    #define GEMSS_HFEv 22U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==138)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 278U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==139)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 278U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==140)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==141)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 23U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==142)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 399U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==143)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 399U
    #define GEMSS_HFEv 18U
    #define GEMSS_HFEDELTA 15U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==144)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 308U
    #define GEMSS_HFEv 19U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==145)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 308U
    #define GEMSS_HFEv 19U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==146)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 276U
    #define GEMSS_HFEv 22U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==147)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 276U
    #define GEMSS_HFEv 22U
    #define GEMSS_HFEDELTA 20U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==148)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 20U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==149)
    #define GEMSS_K 192U

    #define GEMSS_HFEn 265U
    #define GEMSS_HFEv 20U
    #define GEMSS_HFEDELTA 22U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==150)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 540U
    #define GEMSS_HFEv 29U
    #define GEMSS_HFEDELTA 28U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==151)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 415U
    #define GEMSS_HFEv 32U
    #define GEMSS_HFEDELTA 31U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==152)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 375U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 33U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==153)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 358U
    #define GEMSS_HFEv 35U
    #define GEMSS_HFEDELTA 34U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 17U
    #define GEMSS_HFEDegI 4U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==154)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 540U
    #define GEMSS_HFEv 29U
    #define GEMSS_HFEDELTA 28U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==155)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 415U
    #define GEMSS_HFEv 32U
    #define GEMSS_HFEDELTA 31U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==156)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 375U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 33U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==157)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 358U
    #define GEMSS_HFEv 35U
    #define GEMSS_HFEDELTA 34U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 33U
    #define GEMSS_HFEDegI 5U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==158)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 540U
    #define GEMSS_HFEv 26U
    #define GEMSS_HFEDELTA 28U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==159)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 540U
    #define GEMSS_HFEv 26U
    #define GEMSS_HFEDELTA 28U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==160)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 414U
    #define GEMSS_HFEv 30U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==161)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 414U
    #define GEMSS_HFEv 30U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==162)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 372U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==163)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 372U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==164)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 358U
    #define GEMSS_HFEv 32U
    #define GEMSS_HFEDELTA 34U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 129U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==165)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 358U
    #define GEMSS_HFEv 32U
    #define GEMSS_HFEDELTA 34U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 130U
    #define GEMSS_HFEDegI 7U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==166)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 537U
    #define GEMSS_HFEv 26U
    #define GEMSS_HFEDELTA 25U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==167)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 537U
    #define GEMSS_HFEv 26U
    #define GEMSS_HFEDELTA 25U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==168)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 537U
    #define GEMSS_HFEv 26U
    #define GEMSS_HFEDELTA 25U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 1152U
    #define GEMSS_HFEDegI 10U
    #define GEMSS_HFEDegJ 7U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==169)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 537U
    #define GEMSS_HFEv 26U
    #define GEMSS_HFEDELTA 25U

    #define GEMSS_NB_ITE 1U

    #define GEMSS_HFEDeg 1152U
    #define GEMSS_HFEDegI 10U
    #define GEMSS_HFEDegJ 7U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==170)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 414U
    #define GEMSS_HFEv 27U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==171)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 414U
    #define GEMSS_HFEv 27U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 2U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==172)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 372U
    #define GEMSS_HFEv 30U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==173)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 372U
    #define GEMSS_HFEv 30U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 3U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#elif (GEMSS_TEST_LIBRARY==174)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 354U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 513U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 0U

    #define GEMSS_HFEs 0U
#elif (GEMSS_TEST_LIBRARY==175)
    #define GEMSS_K 256U

    #define GEMSS_HFEn 354U
    #define GEMSS_HFEv 33U
    #define GEMSS_HFEDELTA 30U

    #define GEMSS_NB_ITE 4U

    #define GEMSS_HFEDeg 514U
    #define GEMSS_HFEDegI 9U
    #define GEMSS_HFEDegJ 1U

    #define GEMSS_HFEs 3U
#else
    #error "The value of GEMSS_TEST_LIBRARY is not implemented."
#endif


#else
    #error "Parameters must be chosen."
#endif

/************************************************************************/
/* Number of monomial */
#if (GEMSS_GFq==2)
    #define GEMSS_NB_MONOMIAL (((GEMSS_HFEn*(GEMSS_HFEn+1))>>1)+1)
    #define GEMSS_NB_MONOMIAL_VINEGAR (((GEMSS_HFEv*(GEMSS_HFEv+1))>>1)+1)
    #define GEMSS_NB_MONOMIAL_PK (((GEMSS_HFEnv*(GEMSS_HFEnv+1))>>1)+1)
#else
    #define GEMSS_NB_MONOMIAL (((GEMSS_HFEn*(GEMSS_HFEn+3))>>1)+1)
    #define GEMSS_NB_MONOMIAL_VINEGAR (((GEMSS_HFEv*(GEMSS_HFEv+3))>>1)+1)
    #define GEMSS_NB_MONOMIAL_PK (((GEMSS_HFEnv*(GEMSS_HFEnv+3))>>1)+1)
#endif
/*************************************************************************/



/****************** VERIFICATION OF THE PARAMETERS ******************/

#if (!GEMSS_HFEn)
    #error "GEMSS_HFEn must be different from zero"
#endif

#if (!GEMSS_HFEm)
    #error "GEMSS_HFEm must be different from zero"
#endif

#if (GEMSS_HFEm>GEMSS_HFEn)
    #error "GEMSS_HFEm>GEMSS_HFEn is not possible for this implementation"
#endif

#if (GEMSS_HFEm>(GEMSS_K<<1))
    #error "GEMSS_HFEm>2K is not possible for this implementation"
#endif

#if (!GEMSS_NB_ITE)
    #error "GEMSS_NB_ITE must be different from zero"
#endif


#if (!GEMSS_HFEDeg)
    #error "GEMSS_HFEDeg must be different from zero"
#endif

#if (GEMSS_HFEDeg==1)
    #if(GEMSS_HFEDegI||GEMSS_HFEDegJ)
        #error "For GEMSS_HFEDeg==1, put GEMSS_HFEDegI==GEMSS_HFEDegJ==0"
    #endif
#else
    #if (GEMSS_HFEDeg!=((1U<<GEMSS_HFEDegI)+(1U<<GEMSS_HFEDegJ)))
        #error "GEMSS_HFEDeg!=2^(GEMSS_HFEDegI) + 2^(GEMSS_HFEDegJ)"
    #endif
#endif

#if (GEMSS_HFEDegI<GEMSS_HFEDegJ)
    #error "Requirement: GEMSS_HFEDegI>=GEMSS_HFEDegJ"
#endif

/* X^(2^i + 2^j) >= X^(2^n) */
#if ((GEMSS_HFEDegI>=GEMSS_HFEn)||((GEMSS_HFEDegI==(GEMSS_HFEn-1))&&(GEMSS_HFEDegI==GEMSS_HFEDegJ)))
    #error "X^(2^n)==X so the degree of GEMSS_HFE polynomial is biased"
#endif

/*--------------------------------------Public key---------------------------------------------*/
#define GEMSS_HFEmr8 (GEMSS_HFEm&7U)

#if (!GEMSS_HFEmr8)
    #define GEMSS_FORMAT_HYBRID_CPK8 0
    #define GEMSS_FORMAT_MONOMIAL_PK8 1
#else
    /* Compressed pk */
    #define GEMSS_FORMAT_HYBRID_CPK8 1
    #define GEMSS_FORMAT_MONOMIAL_PK8 1
#endif

#if GEMSS_FORMAT_HYBRID_CPK8
    #define GEMSS_EVAL_HYBRID_CPK8_UNCOMP 1
#endif

/* The verification does not need constant-time evaluation */
#if GEMSS_FORMAT_HYBRID_CPK8
    #define GEMSS_evalMQS_gf2_HFE GEMSS_evalMQShybrid8_nocst_gf2_m
#else
    #define GEMSS_evalMQS_gf2_HFE GEMSS_evalMQSnocst8_gf2
#endif

/****************** PRACTICAL SIZES ******************/

/* Public-key (words) */
#if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
    #define GEMSS_SIZE_PK_HFE_WORD ((((GEMSS_NB_MONOMIAL_PK*GEMSS_HFEm+7)>>3)+7)>>3)
#elif GEMSS_FORMAT_MONOMIAL_PK8
    #define GEMSS_SIZE_PK_HFE_WORD ((GEMSS_MQ_GFqm8_SIZE>>3)+((GEMSS_MQ_GFqm8_SIZE&7)?1:0))
#endif

/* Public-key (bytes) */
#if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
    /* Minimal size */
    #define GEMSS_SIZE_PK_HFE ((GEMSS_NB_MONOMIAL_PK*GEMSS_HFEm+7)>>3)
#elif GEMSS_FORMAT_MONOMIAL_PK8
    /* Minimal when m mod 8 == 0 */
    #define GEMSS_SIZE_PK_HFE GEMSS_MQ_GFqm8_SIZE
#endif
