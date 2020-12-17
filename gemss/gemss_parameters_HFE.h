#ifndef _PARAMETERS_HFE_H
#define _PARAMETERS_HFE_H

#include <openssl/gemss_choice_crypto.h>

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




#endif

