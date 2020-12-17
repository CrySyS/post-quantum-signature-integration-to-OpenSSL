#include "gemss_inv_gf2n.h"
#include "gemss_tools_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_mul_gf2n.h"
#include "gemss_sqr_gf2n.h"
#include "gemss_rem_gf2x.h"
#include "gemss_rem_gf2n.h"
#include "gemss_ITMIA_addchains.h"



/**************************************************************************/
/**************************************************************************/
/********************************* Fermat *********************************/
/**************************************************************************/
/**************************************************************************/


/**
 * @brief   Inverse in GF(2^n)*.
 * @details A^(-1) = A^((2^n)-2) = (A^(2^(n-1)-1))^2.
 * @param[in]   A   An element of GF(2^n).
 * @param[out]  res res=A^(-1) in GF(2^n)*, and res=0 when A=0.
 * @remark  Constant-time implementation.
 * @remark  Complexity: (n-2) multiplications and (n-1) squarings in GF(2^n).
 */
void GEMSS_PREFIX_NAME(GEMSS_inv_Fermat_gf2n_ref)(uint64_t res[GEMSS_NB_WORD_GFqn],
                                      const uint64_t A[GEMSS_NB_WORD_GFqn])
{
    #if (GEMSS_HFEn==1)
        *res=*A;
    #else
        unsigned int i;

        /* A^2 */
        GEMSS_sqr_gf2n(res,A);
        for(i=2;i<GEMSS_HFEn;++i)
        {
            GEMSS_mul_gf2n(res,res,A);
            GEMSS_sqr_gf2n(res,res);
        }
    #endif
}


/*******************************************************************/
/*** Computation of the modular inverse with Itoh-Tsujii (ITMIA) ***/
/*******************************************************************/


/**
 * @brief   Inverse in GF(2^n)*.
 * @details A^(-1) = A^((2^n)-2) = (A^(2^(n-1)-1))^2.
 * The ITMIA algorithm is used. The power is computed with an addition chain.
 * Example for n=21:
 * n-1 = 20 = 10100.
 * So, we compute:
 * - A^((2^1)-1) (=A), the power of the power of two of A is 1,
 * - A^((2^2)-1), the power of the power of two of A is 10,
 * - A^((2^4)-1), the power of the power of two of A is 100,
 * - A^((2^5)-1), the power of the power of two of A is 101,
 * - A^((2^10)-1), the power of the power of two of A is 1010,
 * - A^((2^20)-1), the power of the power of two of A is 10100,
 * and finally, (A^((2^20)-1))^2 = A^((2^21)-2) = A^(-1).
 * @param[in]   A   An element of GF(2^n).
 * @param[out]  res res=A^(-1) in GF(2^n)*, and res=0 when A=0.
 * @remark  Constant-time implementation.
 * @remark  Complexity: (Floor(Log2(n-1)) + HW(n-1)-1) multiplications and
 * (n-1) squarings in GF(2^n), with HW the Hamming Weight.
 */
void GEMSS_PREFIX_NAME(GEMSS_inv_ITMIA_gf2n_ref)(static_gf2n res[GEMSS_NB_WORD_GFqn],
                                     cst_static_gf2n A[GEMSS_NB_WORD_GFqn])
{
    #if (GEMSS_HFEn==1)
        *res=*A;
    #else
        static_gf2n multi_sqr[GEMSS_NB_WORD_GFqn];
        unsigned int pos,nb_sqr,i,j;

        /* Search the position of the MSB of n-1 */
        pos=31;
        while(!((GEMSS_HFEn-1)>>pos))
        {
            --pos;
        }

        /* i=pos */
        GEMSS_copy_gf2n(res,A);
        for(i=pos-1;i!=(unsigned int)(-1);--i)
        {
            nb_sqr=(GEMSS_HFEn-1)>>(i+1);
            /* j=0 */
            GEMSS_sqr_gf2n(multi_sqr,res);
            for(j=1;j<nb_sqr;++j)
            {
                GEMSS_sqr_gf2n(multi_sqr,multi_sqr);
            }
            GEMSS_mul_gf2n(res,res,multi_sqr);

            if(((GEMSS_HFEn-1)>>i)&GEMSS_ONE32)
            {
                GEMSS_sqr_gf2n(multi_sqr,res);
                GEMSS_mul_gf2n(res,A,multi_sqr);
            }
        }
        GEMSS_sqr_gf2n(res,res);
    #endif
}


#ifdef GEMSS_ITOH


#if (defined(GEMSS_ENABLED_PCLMUL)&&(GEMSS_NB_WORD_GFqn<10))


#if (GEMSS_HFEn<33)
    #define GEMSS_rem_function GEMSS_REM_GF2N(*r,*r,Q,R)
#elif(GEMSS_NB_WORD_GFqn==1)
    #define GEMSS_rem_function GEMSS_REM_GF2N(*r,r,Q,R)
#else
    #define GEMSS_rem_function GEMSS_REM_GF2N(r,r,Q,R)
#endif


#if (GEMSS_HFEn<33)
    #if (GEMSS_HFEn<5)
        #define GEMSS_INIT_REGISTERS __m128i r_128,a_128;
    #else
        #define GEMSS_INIT_REGISTERS __m128i r_128,r_128_copy,a_128;
    #endif
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) GEMSS_PINIT_GF2N(r_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(*(r),r_128)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(*(r),r_128,a_128)

#elif (GEMSS_NB_WORD_GFqn==1)
    #define GEMSS_INIT_REGISTERS __m128i r_128,r_128_copy,a_128,ra;
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) GEMSS_PINIT_GF2N(r_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(r,r_128,ra,0)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(r,r_128,a_128,ra,0)

#elif (GEMSS_NB_WORD_GFqn==2)
    #define GEMSS_INIT_REGISTERS __m128i r_128,r_128_copy,a_128,ra,ra2,sum,res1,res2;
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) GEMSS_PINIT_GF2N(r_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(r,r_128,ra)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(r,r_128,a_128,ra,ra2,sum,res1,res2)

#elif ((GEMSS_NB_WORD_GFqn==3)||(GEMSS_NB_WORD_GFqn==4))
    #define GEMSS_INIT_REGISTERS __m128i r_128,r2_128,r_128_copy,r2_128_copy,\
a_128,a2_128,ra,ra2,sum,res1,res2;
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) \
            GEMSS_PINIT_GF2N(r_128,r2_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(r,r_128,r2_128,ra)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(r,r_128,r2_128,a_128,a2_128,ra,ra2,sum,res1,res2)

#elif ((GEMSS_NB_WORD_GFqn==5)||(GEMSS_NB_WORD_GFqn==6))
    #define GEMSS_INIT_REGISTERS __m128i r_128,r2_128,r3_128,r_128_copy,r2_128_copy,\
r3_128_copy,a_128,a2_128,a3_128,ra,ra2,sum,res1,res2;
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) \
            GEMSS_PINIT_GF2N(r_128,r2_128,r3_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(r,r_128,r2_128,r3_128,ra)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(r,r_128,r2_128,r3_128,a_128,a2_128,a3_128,ra,ra2,sum,res1,\
res2)

#elif ((GEMSS_NB_WORD_GFqn==7)||(GEMSS_NB_WORD_GFqn==8))
    #define GEMSS_INIT_REGISTERS __m128i r_128,r2_128,r3_128,r4_128,r_128_copy,\
r2_128_copy,r3_128_copy,r4_128_copy,a_128,a2_128,a3_128,a4_128,ra,ra2,\
sum,res1,res2;
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) \
            GEMSS_PINIT_GF2N(r_128,r2_128,r3_128,r4_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(r,r_128,r2_128,r3_128,r4_128,ra)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(r,r_128,r2_128,r3_128,r4_128,a_128,a2_128,a3_128,a4_128,\
ra,ra2,sum,res1,res2)

#elif (GEMSS_NB_WORD_GFqn==9)
    #define GEMSS_INIT_REGISTERS __m128i r_128,r2_128,r3_128,r4_128,r5_128,\
r_128_copy,r2_128_copy,r3_128_copy,r4_128_copy,r5_128_copy,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2;
    #define GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r) \
            GEMSS_PINIT_GF2N(r_128,r2_128,r3_128,r4_128,r5_128,r)
    #define GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra) \
            GEMSS_SQR_GF2X(r,r_128,r2_128,r3_128,r4_128,r5_128,ra)
    #define GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2) \
            GEMSS_MUL_GF2X(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2)
#endif


#define GEMSS_SQR_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra,GEMSS_rem_function) \
    GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r);\
    GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra);\
    GEMSS_rem_function;

#define GEMSS_MUL_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,\
a4_128,a5_128,ra,ra2,sum,res1,res2,GEMSS_rem_function) \
    GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,r);\
    GEMSS_MUL_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,a4_128,\
a5_128,ra,ra2,sum,res1,res2);\
    GEMSS_rem_function;

/* Take in input (GEMSS_HFEn-1)>>i (i the current bit of (GEMSS_HFEn-1)) */
#define GEMSS_EVEN_CASE(val) \
    /* res=res * res^(2^((GEMSS_HFEn-1)>>i)) */\
    /* res^(2^((GEMSS_HFEn-1)>>i)) */\
    GEMSS_PINIT_GF2N_(r_128_copy,r2_128_copy,r3_128_copy,r4_128_copy,r5_128_copy,r);\
    for(j=0;j<val;++j)\
    {\
        GEMSS_SQR_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra,GEMSS_rem_function);\
    }\
    /* multiply by the old res (res=res * res^(2^((GEMSS_HFEn-1)>>i))) */\
    GEMSS_MUL_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,r_128_copy,r2_128_copy,\
r3_128_copy,r4_128_copy,r5_128_copy,ra,ra2,sum,res1,res2,GEMSS_rem_function);

/* Take in input (GEMSS_HFEn-1)>>i (i the current bit of (GEMSS_HFEn-1)) */
#define GEMSS_ODD_CASE(val) \
    GEMSS_EVEN_CASE(val);\
    /* res = res^2 *A */\
    GEMSS_SQR_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra,GEMSS_rem_function);\
    GEMSS_MUL_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,a4_128,\
a5_128,ra,ra2,sum,res1,res2,GEMSS_rem_function);

/* Part of the odd case */
/* Compute A^((2^3)-1 from A^((2^2)-1) */
#define GEMSS_ODD_INIT \
    GEMSS_SQR_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra,GEMSS_rem_function);\
    GEMSS_MUL_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,a4_128,\
a5_128,ra,ra2,sum,res1,res2,GEMSS_rem_function);\


#endif



#if (defined(GEMSS_ENABLED_PCLMUL)&&(GEMSS_NB_WORD_GFqn<10))

#define GEMSS_ITOH_ GEMSS_ITOH

/**
 * @brief   Inverse in GF(2^n)*.
 * @details A^(-1) = A^((2^n)-2) = (A^(2^(n-1)-1))^2.
 * The ITMIA algorithm is used. The power is computed with an addition chain.
 * The latter is defined in ITMIA_addchains.h.
 * @param[in]   A   An element of GF(2^n).
 * @param[out]  res res=A^(-1) in GF(2^n)*, and res=0 when A=0.
 * @remark  Constant-time implementation.
 * @remark  Complexity: O(Floor(Log2(n-1))) multiplications and (n-1) squarings
 * in GF(2^n). However, the complexity of the squarings can be improved with
 * multi-squaring tables.
 */
void GEMSS_PREFIX_NAME(GEMSS_inv_ITMIA_gf2n)(static_gf2n res[GEMSS_NB_WORD_GFqn],
                             cst_static_gf2n A[GEMSS_NB_WORD_GFqn])
{
    GEMSS_INIT_REGISTERS;
    uint64_t r[GEMSS_NB_WORD_MUL];
    #if (((GEMSS_K3!=1)||(GEMSS_NB_WORD_GFqn!=1))&&(GEMSS_HFEn!=312)&&(GEMSS_HFEn!=402)&&(GEMSS_HFEn!=544))
        uint64_t R;
    #endif

    #if (GEMSS_NB_WORD_GFqn==1)
        uint64_t Q;
    #elif (GEMSS_HFEn&63)
        uint64_t Q[GEMSS_NB_WORD_GFqn];
    #endif

    #if (GEMSS_HFEn>4)
        unsigned int j;
    #endif

    GEMSS_PINIT_GF2N_(a_128,a2_128,a3_128,a4_128,a5_128,A);

    /* The MSB of (GEMSS_HFEn-1) is done here : A^(2^1 -1) = A */
    GEMSS_PINIT_GF2N_(r_128,r2_128,r3_128,r4_128,r5_128,A);

    /* The second MSB of (GEMSS_HFEn-1) is done here */
    /* Compute A^(2^2 -1) = A^3 */
    GEMSS_SQR_GF2X_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra);
    GEMSS_rem_function;
    GEMSS_MUL_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,a_128,a2_128,a3_128,a4_128,
              a5_128,ra,ra2,sum,res1,res2,GEMSS_rem_function);

    /* For the others bits of (GEMSS_HFEn-1): */
    /* bit Log_2(n-1)-2 to bit 0 of (n-1) */
    GEMSS_ITOH_;

    /* res=A^(2^(GEMSS_HFEn-1) -1) here */
    /* (2^(GEMSS_HFEn-1) -1)*2 = 2^k -2 */
    /* Square */
    GEMSS_SQR_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra,GEMSS_rem_function);
    GEMSS_copy_gf2n(res,r);
}
#endif



#endif


