#include "gemss_sign_openHFE.h"
#include <openssl/gemss_choice_crypto.h>
#include "gemss_sizes_HFE.h"
#include "gemss_hash.h"
#include "gemss_add_gf2x.h"
#include "gemss_arch.h"

#if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP&&GEMSS_HFEmr8)
    #include <stdlib.h>
#endif
#if (GEMSS_FORMAT_HYBRID_CPK8)
#include "gemss_evalMQShybrid_gf2.h"
#else
#include "gemss_evalMQSnocst8_gf2.h"
#endif
#if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
#include "gemss_convMQ_gf2.h"
#endif
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2nv.h"


#if (GEMSS_NB_ITE!=1)

/* Number of bits to complete the byte of sm64, in [0,7] */
#define GEMSS_VAL_BITS_M (((GEMSS_HFEDELTA+GEMSS_HFEv)<(8-GEMSS_HFEmr8))?(GEMSS_HFEDELTA+GEMSS_HFEv):(8-GEMSS_HFEmr8))

/* Uncompress the signature */
static void uncompress_signHFE(UINT* sm, const unsigned char* sm8)
{
    unsigned char *sm64;
    unsigned int k2;

    sm64=(unsigned char*)sm;
    /* Take the (n+v) first bits */
    for(k2=0;k2<GEMSS_NB_BYTES_GFqnv;++k2)
    {
        sm64[k2]=sm8[k2];
    }

    /* Clean the last byte */
    #if ((GEMSS_NB_ITE>1)&&GEMSS_HFEnvr8)
        sm64[k2-1]&=GEMSS_MASK8_GF2nv;
    #endif

    /* Take the (Delta+v)*(nb_ite-1) bits */
    #if ((GEMSS_NB_ITE>1) || !(GEMSS_HFEDELTA+GEMSS_HFEv))
        unsigned int k1,nb_bits,nb_rem2,nb_rem_m,val_n;
        #if (GEMSS_HFEmr8)
            int nb_rem;
        #endif

        /* GEMSS_HFEnv bits are already extracted from sm8 */
        nb_bits=GEMSS_HFEnv;
        sm64+=(GEMSS_NB_WORD_GF2nv<<3)+(GEMSS_HFEmq8&7U);

        for(k1=1;k1<GEMSS_NB_ITE;++k1)
        {
            /* Number of bits to complete the byte of sm8, in [0,7] */
            val_n=((GEMSS_HFEDELTA+GEMSS_HFEv)<((8-(nb_bits&7U))&7U))?(GEMSS_HFEDELTA+GEMSS_HFEv)
                  :((8-(nb_bits&7U))&7U);

            /* First byte of sm8 */
            if(nb_bits&7U)
            {
                #if (GEMSS_HFEmr8)
                    *sm64^=(sm8[nb_bits>>3]>>(nb_bits&7U))<<GEMSS_HFEmr8;

                    /* Number of bits to complete the first byte of sm8 */
                    nb_rem=(int)((val_n-GEMSS_VAL_BITS_M));
                    if(nb_rem>=0)
                    {
                        /* We take the next byte since we used 
                           GEMSS_VAL_BITS_M bits */
                        ++sm64;
                    }
                    if(nb_rem > 0)
                    {
                        nb_bits+=GEMSS_VAL_BITS_M;
                        *sm64^=sm8[nb_bits>>3]>>(nb_bits&7U);
                        nb_bits+=nb_rem;
                    } else
                    {
                        nb_bits+=val_n;
                    }
                #else
                    /* We can take 8 bits, and we want at most 7 bits. */
                    (*sm64)=sm8[nb_bits>>3]>>(nb_bits&7U);
                    nb_bits+=val_n;
                #endif
            }

            /* Other bytes of sm8 */
            nb_rem2=(GEMSS_HFEDELTA+GEMSS_HFEv)-val_n;
            /*nb_rem2 can be zero only in this case */
            #if ((GEMSS_HFEDELTA+GEMSS_HFEv)<8)
            if(nb_rem2)
            {
            #endif
                /* Number of bits used of sm64, mod 8 */
                nb_rem_m=(GEMSS_HFEm+val_n)&7U;

                /* Other bytes */
                if(nb_rem_m)
                {
                    /* -1 to take the ceil of /8, -1 */
                    for(k2=0;k2<((nb_rem2-1)>>3);++k2)
                    {
                        *sm64^=sm8[nb_bits>>3]<<nb_rem_m;
                        ++sm64;
                        *sm64=sm8[nb_bits>>3]>>(8-nb_rem_m);

                        nb_bits+=8;
                    }
                    /* The last byte of sm8, between 1 and 8 bits to put */
                    *sm64^=sm8[nb_bits>>3]<<nb_rem_m;
                    ++sm64;

                    /* nb_rem2 between 1 and 8 bits */
                    nb_rem2=((nb_rem2+7U)&7U)+1U;
                    if(nb_rem2>(8-nb_rem_m))
                    {
                        *sm64=sm8[nb_bits>>3]>>(8-nb_rem_m);
                        ++sm64;
                    }

                    nb_bits+=nb_rem2;
                } else
                {
                    /* We are at the beginning of the bytes of sm8 and sm64 */

                    /* +7 to take the ceil of /8 */
                    for(k2=0;k2<((nb_rem2+7)>>3);++k2)
                    {
                        *sm64=sm8[nb_bits>>3];
                        nb_bits+=8;
                        ++sm64;
                    }
                    /* The last byte has AT MOST 8 bits. */
                    nb_bits-=(8-(nb_rem2&7U))&7U;
                }
            #if ((GEMSS_HFEDELTA+GEMSS_HFEv)<8)
            } else
            {
                ++sm64;
            }
            #endif

            /* Clean the last byte */
            #if GEMSS_HFEnvr8
                sm64[-1]&=GEMSS_MASK8_GF2nv;
            #endif

            /* We complete the word. Then we search the first byte. */
            sm64+=((8-(GEMSS_NB_BYTES_GFqnv&7U))&7U)+(GEMSS_HFEmq8&7U);
        }
    #endif
}
#endif


/**
 * @brief   Verify the signature of the document m of length len bytes, using a
 * (GEMSS_HFEv-)-based signature scheme. pk can be evaluated with the eval_pk function
 * @details eval_pk takes 3 arguments here.
 * @param[in]   m   A pointer on a document.
 * @param[in]   len The length in bytes of the document m.
 * @param[in]   sm8 A signature generated by a (GEMSS_HFEv-)-based signature scheme.
 * @param[in]   pk  The public-key, a MQ system with m equations in
 * GF(2)[x1,...,x_(n+v)].
 * @param[in]   eval_pk The function allowing to evaluate pk. This choice
 * depends on the chosen representation of pk.
 * @return  0 for a valid signature, !=0 else.
 * @remark  Requirement: when SSE or AVX is enabled, the public-key must be
 * aligned respectively on 16 or 32 bytes. However, this requirement and the
 * alignment are disabled for the public/stable version of MQsoft (to be simple
 * to use, generic for the allocation of pk and to avoid segmentation faults).
 * @remark  This function does not require a constant-time implementation.
 * @todo    To simply the use of the memory alignment for the public-key.
 */
int GEMSS_PREFIX_NAME(GEMSS_sign_openHFE_uncomp_pk)(const unsigned char* m, size_t len,
                                        const unsigned char* sm8,
                                        const uint8_t* pk,
                                        void (*eval_pk)())
{
    UINT sm[GEMSS_SIZE_SIGN_UNCOMPRESSED-GEMSS_SIZE_SALT_WORD]={0};

    static_vecnv_gf2 Si_tab[GEMSS_NB_WORD_GF2nv] GEMSS_ALIGNED_GFqm,
                     Si1_tab[GEMSS_NB_WORD_GF2nv] GEMSS_ALIGNED_GFqm;
    /* Copy of pointer */
    vecnv_gf2 tmp,Si=Si_tab,Si1=Si1_tab;
    /* Vector of D_1, ..., D_(GEMSS_NB_ITE) */
    UINT D[GEMSS_NB_ITE*GEMSS_SIZE_DIGEST_UINT];
    unsigned int i;
    #if (GEMSS_HFEnv!=GEMSS_HFEm)
        unsigned int index;
    #endif

    #ifdef GEMSS_KAT_INT
        GEMSS_OPEN_KAT_INT_FILE;
        fputs("Sign_open:\n",fp);
    #endif

    #if GEMSS_EUF_CMA_PROPERTY
        sm8+=GEMSS_SIZE_SALT;
    #endif

    #if (GEMSS_NB_ITE==1)
        /* Take the (n+v) first bits */
        for(i=0;i<GEMSS_NB_BYTES_GFqnv;++i)
        {
            ((unsigned char*)sm)[i]=sm8[i];
        }
    #else
        uncompress_signHFE(sm,sm8);
    #endif


    #if GEMSS_EUF_CMA_PROPERTY
        UINT Hd[GEMSS_SIZE_DIGEST_UINT+GEMSS_SIZE_SALT_WORD];

        /* Compute H(m) */
        GEMSS_HASH((unsigned char*)Hd,m,len);

        /* H(m)||r */
        sm8-=GEMSS_SIZE_SALT;
        for(i=0;i<GEMSS_SIZE_SALT_WORD;++i)
        {
            Hd[GEMSS_SIZE_DIGEST_UINT+i]=((UINT*)sm8)[i];
        }

        /* Compute H1 = H(H(m)||r) */
        GEMSS_HASH((unsigned char*)D,(unsigned char*)Hd,GEMSS_SIZE_DIGEST+GEMSS_SIZE_SALT);
    #else
        /* Compute H1 = H(m), the m first bits are D1 */
        GEMSS_HASH((unsigned char*)D,m,len);
    #endif

    for(i=1;i<GEMSS_NB_ITE;++i)
    {
        /* Compute Hi = H(H_(i-1)), the m first bits are Di */
        GEMSS_HASH((unsigned char*)(D+i*GEMSS_SIZE_DIGEST_UINT),
             (unsigned char*)(D+(i-1)*GEMSS_SIZE_DIGEST_UINT),GEMSS_SIZE_DIGEST);
        /* Clean the previous hash (= extract D_(i-1) from H_(i-1)) */
        #if GEMSS_HFEmr
            D[GEMSS_SIZE_DIGEST_UINT*(i-1)+GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
        #endif
    }
    /* Clean the previous hash (= extract D_(i-1) from H_(i-1)) */
    #if GEMSS_HFEmr
        D[GEMSS_SIZE_DIGEST_UINT*(i-1)+GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
    #endif

    /* Compute p(S_(NB_IT),X_(NB_IT)) */
    eval_pk(Si,sm,pk);
    #ifdef GEMSS_KAT_INT
        fprintf(fp,"i=%u\n",GEMSS_NB_ITE);
        GEMSS_fprintBstr_KAT_INT(fp,"xor(Di,S_(i-1)): ",(unsigned char*)Si,
                           GEMSS_NB_BYTES_GFqm);
    #endif

    for(i=GEMSS_NB_ITE-1;i>0;--i)
    {
        #ifdef GEMSS_KAT_INT
            fprintf(fp,"i=%u\n",i);
        #endif
        /* Compute Si = xor(p(S_i+1,X_i+1),D_i+1) */
        GEMSS_add2_gf2m(Si,D+i*GEMSS_SIZE_DIGEST_UINT);

        #if (GEMSS_HFEnv!=GEMSS_HFEm)
            /* Compute Si||Xi */
            index=GEMSS_NB_WORD_GF2nv+(GEMSS_NB_ITE-1-i)*GEMSS_NB_WORD_GF2nvm;
            #if GEMSS_HFEmr
                Si[GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;

                /* Concatenation(Si,Xi): the intersection between S1 and X1 is 
                 * not null */
                Si[GEMSS_NB_WORD_GF2m-1]^=sm[index];
                #if (GEMSS_NB_WORD_GF2nvm != 1)
                    ++index;
                    GEMSS_copy_gf2nvm1(Si+GEMSS_NB_WORD_GF2m,sm+index);
                #endif
            #else
                /* Concatenation(Si,Xi) */
                GEMSS_copy_gf2nvm(Si+GEMSS_NB_WORD_GF2m,sm+index);
            #endif
        #endif

        #ifdef GEMSS_KAT_INT
            GEMSS_fprintBstr_KAT_INT(fp,"Si||Xi: ",(unsigned char*)Si,GEMSS_NB_BYTES_GFqnv);
        #endif

        /* Compute p(Si,Xi) */
        eval_pk(Si1,Si,pk);

        /* Permutation of pointers */
        tmp=Si1;
        Si1=Si;
        Si=tmp;

        #ifdef GEMSS_KAT_INT
            GEMSS_fprintBstr_KAT_INT(fp,"xor(Di,S_(i-1)): ",(unsigned char*)Si,
                               GEMSS_NB_BYTES_GFqm);
        #endif
    }

    #ifdef GEMSS_KAT_INT
        GEMSS_fprintBstr_KAT_INT(fp,"true D1: ",(unsigned char*)D,GEMSS_NB_BYTES_GFqm);
        GEMSS_CLOSE_KAT_INT_FILE;
    #endif

    /* D1'' == D1 */
    return !GEMSS_isEqual_nocst_gf2m(Si,D);
}


/**
 * @brief   Verify the signature of the document m of length len bytes, using a
 * (GEMSS_HFEv-)-based signature scheme. pk can be evaluated with the eval_pk
 * function, and hpk is used during this evaluation.
 * @details eval_pk takes 4 arguments here.
 * @param[in]   m   A pointer on a document.
 * @param[in]   len The length in bytes of the document m.
 * @param[in]   sm8 A signature generated by a (GEMSS_HFEv-)-based signature scheme.
 * @param[in]   pk  The original public-key, a MQ system with m equations in
 * GF(2)[x1,...,x_(n+v)].
 * @param[in]   hpk The hybrid representation of one part of the public-key pk.
 * @param[in]   eval_pk The function allowing to evaluate pk. This choice
 * depends on the chosen representation of pk.
 * @return  0 for a valid signature, !=0 else.
 * @remark  Requirement: when SSE or AVX is enabled, the public-key must be
 * aligned respectively on 16 or 32 bytes. However, this requirement and the
 * alignment are disabled for the public/stable version of MQsoft (to be simple
 * to use, generic for the allocation of pk and to avoid segmentation faults).
 * @remark  This function does not require a constant-time implementation.
 * @todo    To simply the use of the memory alignment for the public-key.
 */
int GEMSS_PREFIX_NAME(GEMSS_sign_openHFE_huncomp_pk)(const unsigned char* m, size_t len,
                                         const unsigned char* sm8,
                                         const uint8_t* pk, const uint8_t* hpk,
                                         void (*eval_pk)())
{
    UINT sm[GEMSS_SIZE_SIGN_UNCOMPRESSED-GEMSS_SIZE_SALT_WORD]={0};

    static_vecnv_gf2 Si_tab[GEMSS_NB_WORD_GF2nv] GEMSS_ALIGNED_GFqm,
                     Si1_tab[GEMSS_NB_WORD_GF2nv] GEMSS_ALIGNED_GFqm;
    #if GEMSS_HFEmr8
        UINT cst;
    #endif
    /* Copy of pointer */
    vecnv_gf2 tmp,Si=Si_tab,Si1=Si1_tab;
    /* Vector of D_1, ..., D_(GEMSS_NB_ITE) */
    UINT D[GEMSS_NB_ITE*GEMSS_SIZE_DIGEST_UINT];
    unsigned int i;
    #if (GEMSS_HFEnv!=GEMSS_HFEm)
        unsigned int index;
    #endif

    #ifdef GEMSS_KAT_INT
        GEMSS_OPEN_KAT_INT_FILE;
        fputs("Sign_open:\n",fp);
    #endif

    #if GEMSS_HFEmr8
        cst=*((UINT*)hpk);
        /* We jump the constant (stored on 8 bytes) */
        hpk+=8;
    #endif

    #if GEMSS_EUF_CMA_PROPERTY
        sm8+=GEMSS_SIZE_SALT;
    #endif

    #if (GEMSS_NB_ITE==1)
        /* Take the (n+v) first bits */
        for(i=0;i<GEMSS_NB_BYTES_GFqnv;++i)
        {
            ((unsigned char*)sm)[i]=sm8[i];
        }
    #else
        uncompress_signHFE(sm,sm8);
    #endif


    #if GEMSS_EUF_CMA_PROPERTY
        UINT Hd[GEMSS_SIZE_DIGEST_UINT+GEMSS_SIZE_SALT_WORD];

        /* Compute H(m) */
        GEMSS_HASH((unsigned char*)Hd,m,len);

        /* H(m)||r */
        sm8-=GEMSS_SIZE_SALT;
        for(i=0;i<GEMSS_SIZE_SALT_WORD;++i)
        {
            Hd[GEMSS_SIZE_DIGEST_UINT+i]=((UINT*)sm8)[i];
        }

        /* Compute H1 = H(H(m)||r) */
        GEMSS_HASH((unsigned char*)D,(unsigned char*)Hd,GEMSS_SIZE_DIGEST+GEMSS_SIZE_SALT);
    #else
        /* Compute H1 = H(m), the m first bits are D1 */
        GEMSS_HASH((unsigned char*)D,m,len);
    #endif

    for(i=1;i<GEMSS_NB_ITE;++i)
    {
        /* Compute Hi = H(H_(i-1)), the m first bits are Di */
        GEMSS_HASH((unsigned char*)(D+i*GEMSS_SIZE_DIGEST_UINT),
             (unsigned char*)(D+(i-1)*GEMSS_SIZE_DIGEST_UINT),GEMSS_SIZE_DIGEST);
        /* Clean the previous hash (= extract D_(i-1) from H_(i-1)) */
        #if GEMSS_HFEmr
            D[GEMSS_SIZE_DIGEST_UINT*(i-1)+GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
        #endif
    }
    /* Clean the previous hash (= extract D_(i-1) from H_(i-1)) */
    #if GEMSS_HFEmr
        D[GEMSS_SIZE_DIGEST_UINT*(i-1)+GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
    #endif

    /* Compute p(S_(NB_IT),X_(NB_IT)) */
    eval_pk(Si,sm,pk,hpk);
    #if GEMSS_HFEmr8
        Si[GEMSS_HFEmq]^=cst;
    #endif
    #ifdef GEMSS_KAT_INT
        fprintf(fp,"i=%u\n",GEMSS_NB_ITE);
        GEMSS_fprintBstr_KAT_INT(fp,"xor(Di,S_(i-1)): ",(unsigned char*)Si,
                           GEMSS_NB_BYTES_GFqm);
    #endif

    for(i=GEMSS_NB_ITE-1;i>0;--i)
    {
        #ifdef GEMSS_KAT_INT
            fprintf(fp,"i=%u\n",i);
        #endif
        /* Compute Si = xor(p(S_i+1,X_i+1),D_i+1) */
        GEMSS_add2_gf2m(Si,D+i*GEMSS_SIZE_DIGEST_UINT);

        #if (GEMSS_HFEnv!=GEMSS_HFEm)
            /* Compute Si||Xi */
            index=GEMSS_NB_WORD_GF2nv+(GEMSS_NB_ITE-1-i)*GEMSS_NB_WORD_GF2nvm;
            #if GEMSS_HFEmr
                Si[GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;

                /* Concatenation(Si,Xi): the intersection between S1 and X1 is 
                 * not null */
                Si[GEMSS_NB_WORD_GF2m-1]^=sm[index];
                #if (GEMSS_NB_WORD_GF2nvm != 1)
                    ++index;
                    GEMSS_copy_gf2nvm1(Si+GEMSS_NB_WORD_GF2m,sm+index);
                #endif
            #else
                /* Concatenation(Si,Xi) */
                GEMSS_copy_gf2nvm(Si+GEMSS_NB_WORD_GF2m,sm+index);
            #endif
        #endif

        #ifdef GEMSS_KAT_INT
            GEMSS_fprintBstr_KAT_INT(fp,"Si||Xi: ",(unsigned char*)Si,GEMSS_NB_BYTES_GFqnv);
        #endif

        /* Compute p(Si,Xi) */
        eval_pk(Si1,Si,pk,hpk);
        #if GEMSS_HFEmr8
            Si1[GEMSS_HFEmq]^=cst;
        #endif

        /* Permutation of pointers */
        tmp=Si1;
        Si1=Si;
        Si=tmp;

        #ifdef GEMSS_KAT_INT
            GEMSS_fprintBstr_KAT_INT(fp,"xor(Di,S_(i-1)): ",(unsigned char*)Si,
                               GEMSS_NB_BYTES_GFqm);
        #endif
    }

    #ifdef GEMSS_KAT_INT
        GEMSS_fprintBstr_KAT_INT(fp,"true D1: ",(unsigned char*)D,GEMSS_NB_BYTES_GFqm);
        GEMSS_CLOSE_KAT_INT_FILE;
    #endif

    /* D1'' == D1 */
    return !GEMSS_isEqual_nocst_gf2m(Si,D);
}


/**
 * @brief   Verify the signature of the document m of length len bytes, using a
 * (GEMSS_HFEv-)-based signature scheme.
 * @param[in]   m   A pointer on a document.
 * @param[in]   len The length in bytes of the document m.
 * @param[in]   sm8 A signature generated by a (GEMSS_HFEv-)-based signature scheme.
 * @param[in]   pk  The public-key, a MQ system with m equations in
 * GF(2)[x1,...,x_(n+v)].
 * @return  0 for a valid signature, !=0 else.
 * @remark  Requirement: when SSE or AVX is enabled, the public-key must be
 * aligned respectively on 16 or 32 bytes. However, this requirement and the
 * alignment are disabled for the public/stable version of MQsoft (to be simple
 * to use, generic for the allocation of pk and to avoid segmentation faults).
 * @remark  This function does not require a constant-time implementation.
 * @todo    To simply the use of the memory alignment for the public-key.
 */
int GEMSS_PREFIX_NAME(GEMSS_sign_openHFE)(const unsigned char* m, size_t len,
                              const unsigned char* sm8, const uint8_t* pk)
{
    int ret;

    /* Compute p(S_(NB_IT),X_(NB_IT)) */
    #if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
        UINT* pk_tmp;
        unsigned int i;
        #if GEMSS_HFEmr8
            /* 1 to store the constant */
            pk_tmp=(UINT*)malloc((1+GEMSS_NB_WORD_UNCOMP_EQ*GEMSS_HFEmr8)*sizeof(UINT));
        #endif

        #if (GEMSS_HFENr8&&(GEMSS_HFEmr8>1))
            uint64_t val;
            const uint8_t* pk_cp;

            pk_cp=pk+GEMSS_ACCESS_last_equations8-1;
            val=0;

            for(i=0;i<(GEMSS_HFEmr8-1);++i)
            {
                /* Last byte of the equation */
                pk_cp+=GEMSS_NB_BYTES_EQUATION;
                val^=((uint64_t)((*pk_cp)>>GEMSS_HFENr8))<<(i*GEMSS_HFENr8c);
            }
        #endif

        #if GEMSS_HFEmr8
            UINT cst;
            cst=0;

            for(i=0;i<(GEMSS_HFEmr8-1);i++)
            {
                cst^=GEMSS_convMQ_uncompressL_gf2(pk_tmp+1+i*GEMSS_NB_WORD_UNCOMP_EQ,
                     pk+GEMSS_ACCESS_last_equations8+i*GEMSS_NB_BYTES_EQUATION)<<i;
            }

            /* The last equation in input is smaller because compressed */
            cst^=GEMSS_convMQ_last_uncompressL_gf2(pk_tmp+1+i*GEMSS_NB_WORD_UNCOMP_EQ,
                 pk+GEMSS_ACCESS_last_equations8+i*GEMSS_NB_BYTES_EQUATION)<<i;

            #if (GEMSS_HFENr8&&(GEMSS_HFEmr8>1))

            /* Number of lost bits by the zero padding of each equation
               (without the last) */
            #define GEMSS_LOST_BITS ((GEMSS_HFEmr8-1)*GEMSS_HFENr8c)

            #if (!GEMSS_HFEnvr)
                pk_tmp[1+(i+1)*GEMSS_NB_WORD_UNCOMP_EQ-1]^=val<<(64-GEMSS_LOST_BITS);
            #elif(GEMSS_HFEnvr>GEMSS_LOST_BITS)
                pk_tmp[1+(i+1)*GEMSS_NB_WORD_UNCOMP_EQ-1]^=val<<(GEMSS_HFEnvr-GEMSS_LOST_BITS);
            #elif (GEMSS_HFEnvr==GEMSS_LOST_BITS)
                pk_tmp[1+(i+1)*GEMSS_NB_WORD_UNCOMP_EQ-1]=val;
            #elif (GEMSS_HFEnvr<GEMSS_LOST_BITS)
                pk_tmp[1+(i+1)*GEMSS_NB_WORD_UNCOMP_EQ-2]^=val<<(64-
                                                          (GEMSS_LOST_BITS-GEMSS_HFEnvr));
                pk_tmp[1+(i+1)*GEMSS_NB_WORD_UNCOMP_EQ-1]=val>>(GEMSS_LOST_BITS-GEMSS_HFEnvr);
            #endif

            #endif
            cst<<=GEMSS_HFEmr-GEMSS_HFEmr8;
            *pk_tmp=cst;
        #endif
    #endif


    #if(GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP)
        ret=GEMSS_sign_openHFE_huncomp_pk(m,len,sm8,pk,(uint8_t*)pk_tmp,
                                    GEMSS_evalMQShybrid8_nocst_gf2_m);
    #else
        ret=GEMSS_sign_openHFE_uncomp_pk(m,len,sm8,pk,GEMSS_evalMQS_gf2_HFE);
    #endif


    #if (GEMSS_FORMAT_HYBRID_CPK8&&GEMSS_EVAL_HYBRID_CPK8_UNCOMP&&GEMSS_HFEmr8)
        free(pk_tmp);
    #endif

    return ret;
}


