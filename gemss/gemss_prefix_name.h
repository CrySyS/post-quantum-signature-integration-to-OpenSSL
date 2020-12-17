#ifndef _PREFIX_NAME_H
#define _PREFIX_NAME_H

//#include "gemss.h"
#include "gemss_parameters_HFE.h"


/** Auxiliar macro. */
#define GEMSS_CONCAT_NAME2(a,b) a ## b
/** This macro permits to concat the names. */
#define GEMSS_CONCAT_NAME(a,b) GEMSS_CONCAT_NAME2(a,b)


/** This macro permits to prefix the name of all functions with the name of the
 *  current cryptosystem. */
/* For example, if you use GeMSS with a level of security 128 bits,
   GEMSS_PREFIX_NAME(function) will generate GeMSS_128U_function. */
#define GEMSS_PREFIX_NAME(name) GEMSS_CONCAT_NAME(GEMSS_CONCAT_NAME(GEMSS_CRYPTO_NAME,GEMSS_K),_##name)


#endif

