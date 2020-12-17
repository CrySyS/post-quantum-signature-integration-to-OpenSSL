#include "gemss_signHFE.h"
#include "gemss_arch.h"
#include <openssl/gemss_choice_crypto.h>
#include "gemss_gf2nx.h"
#include "gemss_config_HFE.h"
#include "gemss_sizes_HFE.h"
#include "gemss_hash.h"
#include "gemss_add_gf2n.h"
#include "gemss_tools_gf2m.h"
#include "gemss_tools_gf2n.h"
#include "gemss_tools_gf2v.h"
#include "gemss_randombytes.h"
#include "gemss_vecMatProduct_gf2.h"
#if(GEMSS_HFEv)
#include "gemss_evalMQSv_gf2.h"
#endif

#include "gemss_chooseRootHFE_gf2nx.h"
#if(GEMSS_HFEDeg!=1)
#include "gemss_initListDifferences_gf2nx.h"
#endif

#if (GEMSS_ENABLED_SEED_SK||GEMSS_HFEv)
    #include <stdlib.h>
#endif

#if GEMSS_ENABLED_SEED_SK
#include "gemss_rand_gf2nx.h"
#include "gemss_randMatrix_gf2.h"

    #if GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        /* To generate S and T from a seed */
#include "gemss_determinantn_gf2.h"
#include "gemss_determinantnv_gf2.h"
    #endif
    #if (!GEMSS_GEN_INVERSE_IN_FIRST)
        /* To compute the inverse of S and T */
#include "gemss_invMatrixn_gf2.h"
#include "gemss_invMatrixnv_gf2.h"
    #endif
#endif


#if 0
    /* When the root finding fails, only the vinegars are regenerated */
    #define GEMSS_GEN_MINUS_VINEGARS 0
#else
    /* When the root finding fails, the minus and vinegars are regenerated */
    #define GEMSS_GEN_MINUS_VINEGARS 1
#endif



#if (GEMSS_NB_ITE!=1)

/* Number of bits to complete the byte of sm64, in [0,7] */
#define GEMSS_VAL_BITS_M (((GEMSS_HFEDELTA+GEMSS_HFEv)<(8-GEMSS_HFEmr8))?(GEMSS_HFEDELTA+GEMSS_HFEv):(8-GEMSS_HFEmr8))

static void compress_signHFE(unsigned char* sm8, const UINT* sm)
{
    unsigned char *sm64;
    unsigned int k2;

    sm64=(unsigned char*)sm;

    /* Take the (n+v) first bits */
    for(k2=0;k2<GEMSS_NB_BYTES_GFqnv;++k2)
    {
        sm8[k2]=sm64[k2];
    }

    /* Take the (Delta+v)*(nb_ite-1) bits */
    #if ((GEMSS_NB_ITE>1) || !(GEMSS_HFEDELTA+GEMSS_HFEv))
        unsigned int k1,nb_bits,nb_rem2,nb_rem_m,val_n;
        #if (GEMSS_HFEmr8)
            int nb_rem;
        #endif

        /* GEMSS_HFEnv bits are already stored in sm8 */
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
                    sm8[nb_bits>>3]^=((*sm64)>>GEMSS_HFEmr8)<<(nb_bits&7U);

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
                        sm8[nb_bits>>3]^=(*sm64)<<(nb_bits&7U);
                        nb_bits+=nb_rem;
                    } else
                    {
                        nb_bits+=val_n;
                    }
                #else
                    /* We can take 8 bits, and we want at most 7 bits. */
                    sm8[nb_bits>>3]^=(*sm64)<<(nb_bits&7U);
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
                        sm8[nb_bits>>3]=((*sm64)>>nb_rem_m)
                                        ^((*(sm64+1))<<(8-nb_rem_m));
                        nb_bits+=8;
                        ++sm64;
                    }
                    /* The last byte of sm8, between 1 and 8 bits to put */
                    sm8[nb_bits>>3]=(*sm64)>>nb_rem_m;
                    ++sm64;

                    /* nb_rem2 between 1 and 8 bits */
                    nb_rem2=((nb_rem2+7U)&7U)+1U;
                    if(nb_rem2>(8-nb_rem_m))
                    {
                        sm8[nb_bits>>3]^=(*sm64)<<(8-nb_rem_m);
                        ++sm64;
                    }

                    nb_bits+=nb_rem2;
                } else
                {
                    /* We are at the beginning of the bytes of sm8 and sm64 */

                    /* +7 to take the ceil of /8 */
                    for(k2=0;k2<((nb_rem2+7)>>3);++k2)
                    {
                        sm8[nb_bits>>3]=*sm64;
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
            /* We complete the word. Then we search the first byte. */
            sm64+=((8-(GEMSS_NB_BYTES_GFqnv&7U))&7U)+(GEMSS_HFEmq8&7U);
        }
    #endif
}
#endif


/* Precomputation for one secret-key */
#if GEMSS_ENABLED_SEED_SK
void GEMSS_PREFIX_NAME(GEMSS_precSignHFESeed)(secret_key_HFE *sk_HFE, const UINT *sk)
{
    #if GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        GEMSS_expandSeedCxtDeclaration;
        Mnv_gf2 S_buf;
        GLnv_gf2 S;
        GLn_gf2 T;
    #elif GEMSS_GEN_INVERTIBLE_MATRIX_LU
        Tnv_gf2 L,U;
    #endif


    #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
        GEMSS_ALIGNED_GFqn_MALLOC(sk_HFE->sk_uncomp,UINT*,GEMSS_NB_UINT_HFEVPOLY
                                  +(GEMSS_LTRIANGULAR_NV_SIZE<<1)
                                  +(GEMSS_LTRIANGULAR_N_SIZE<<1)+GEMSS_SIZE_VECTOR_t
                                  +GEMSS_MATRIXnv_SIZE+GEMSS_MATRIXn_SIZE,sizeof(UINT));
        GEMSS_expandSeed((uint8_t*)(sk_HFE->sk_uncomp),(GEMSS_NB_UINT_HFEVPOLY
                                     +(GEMSS_LTRIANGULAR_NV_SIZE<<1)
                                     +(GEMSS_LTRIANGULAR_N_SIZE<<1)+GEMSS_SIZE_VECTOR_t)<<3,
             (uint8_t*)sk,GEMSS_SIZE_SEED_SK);

        sk_HFE->S=sk_HFE->sk_uncomp+GEMSS_NB_UINT_HFEVPOLY+(GEMSS_LTRIANGULAR_NV_SIZE<<1)
                                   +(GEMSS_LTRIANGULAR_N_SIZE<<1)+GEMSS_SIZE_VECTOR_t;
        #if GEMSS_AFFINE_TRANSFORMATION_BY_t
            sk_HFE->t=sk_HFE->sk_uncomp+GEMSS_NB_UINT_HFEVPOLY
                                       +(GEMSS_LTRIANGULAR_NV_SIZE<<1)
                                       +(GEMSS_LTRIANGULAR_N_SIZE<<1);
        #endif
    #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        S_buf=GEMSS_MALLOC_MATRIXnv;
        #if GEMSS_GEN_INVERSE_IN_FIRST
            GEMSS_ALIGNED_GFqn_MALLOC(sk_HFE->sk_uncomp,UINT*,
                                GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD,sizeof(UINT));
        #else
            GEMSS_ALIGNED_GFqn_MALLOC(sk_HFE->sk_uncomp,UINT*,
                                GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD+GEMSS_MATRIXnv_SIZE
                                +GEMSS_MATRIXn_SIZE,sizeof(UINT));
        #endif
        GEMSS_expandSeedIUF(&hashInstance,(uint8_t*)sk,GEMSS_SIZE_SEED_SK<<3);
        GEMSS_expandSeedSqueeze(&hashInstance,(uint8_t*)(sk_HFE->sk_uncomp),
                           GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD<<6);

        S=sk_HFE->sk_uncomp+GEMSS_ACCESS_MATRIX_S;
        T=S+GEMSS_MATRIXnv_SIZE;

        #if GEMSS_GEN_INVERSE_IN_FIRST
            sk_HFE->S=S;
        #else
            sk_HFE->S=sk_HFE->sk_uncomp+GEMSS_SIZE_SK_HFE_UNCOMPRESSED_WORD;
        #endif
        #if GEMSS_AFFINE_TRANSFORMATION_BY_t
            sk_HFE->t=sk_HFE->sk_uncomp+GEMSS_ACCESS_VECTOR_t;
        #endif
    #endif
    sk_HFE->T=sk_HFE->S+GEMSS_MATRIXnv_SIZE;


    /* zero padding for the GEMSS_HFEv polynomial F */
    sk_HFE->F_HFEv=sk_HFE->sk_uncomp;
    GEMSS_cleanMonicHFEv_gf2nx(sk_HFE->F_HFEv);


    #if GEMSS_GEN_INVERTIBLE_MATRIX_LU
        /* The random bytes are already generated from a seed */
        L=sk_HFE->sk_uncomp+GEMSS_NB_UINT_HFEVPOLY;
        U=L+GEMSS_LTRIANGULAR_NV_SIZE;

        GEMSS_cleanLowerMatrixnv(L);
        GEMSS_cleanLowerMatrixnv(U);

        #if GEMSS_GEN_INVERSE_IN_FIRST
            /* Generate S^(-1) = L*U */
            GEMSS_mulMatricesLU_gf2_nv(sk_HFE->S,L,U);
        #else
            /* Generate S the inverse of S^(-1) */
            GEMSS_invMatrixLUnv_gf2(sk_HFE->S,L,U);
        #endif


        /* The random bytes are already generated from a seed */
        L+=(GEMSS_LTRIANGULAR_NV_SIZE<<1);
        U=L+GEMSS_LTRIANGULAR_N_SIZE;

        GEMSS_cleanLowerMatrixn(L);
        GEMSS_cleanLowerMatrixn(U);

        #if GEMSS_GEN_INVERSE_IN_FIRST
            /* Generate T^(-1) = L*U */
            GEMSS_mulMatricesLU_gf2_n(sk_HFE->T,L,U);
        #else
            /* Generate T the inverse of T^(-1) */
            GEMSS_invMatrixLUn_gf2(sk_HFE->T,L,U);
        #endif

    #elif GEMSS_GEN_INV_MATRIX_TRIAL_ERROR
        /* The random bytes are already generated from a seed */
        GEMSS_cleanMatrix_gf2_nv(S);
        while(!GEMSS_determinantnv_gf2(S,S_buf))
        {
            GEMSS_expandSeedSqueeze(&hashInstance,(uint8_t*)S,GEMSS_MATRIXnv_SIZE<<6);
            GEMSS_cleanMatrix_gf2_nv(S);
        }

        #if (!GEMSS_GEN_INVERSE_IN_FIRST)
            GEMSS_invMatrixnv_gf2(sk_HFE->S,S);
        #endif


        /* The random bytes are already generated from a seed */
        GEMSS_cleanMatrix_gf2_n(T);
        while(!GEMSS_determinantn_gf2(T,S_buf))
        {
            GEMSS_expandSeedSqueeze(&hashInstance,(uint8_t*)T,GEMSS_MATRIXn_SIZE<<6);
            GEMSS_cleanMatrix_gf2_n(T);
        }

        #if (!GEMSS_GEN_INVERSE_IN_FIRST)
            GEMSS_invMatrixn_gf2(sk_HFE->T,T);
        #endif

        free(S_buf);
    #endif
}
#endif


/* Precomputation for one secret-key */
int GEMSS_PREFIX_NAME(GEMSS_precSignHFE)(secret_key_HFE* sk_HFE, const UINT** linear_coefs,
                                                     const UINT *sk)
{
    #if GEMSS_HFEv
        cst_sparse_monic_gf2nx F_HFEv;
        UINT* F;
        unsigned int i;
    #endif

    #if GEMSS_ENABLED_SEED_SK
        GEMSS_precSignHFESeed(sk_HFE,sk);
    #else
        sk_HFE->F_HFEv=sk;
        sk_HFE->S=sk+GEMSS_ACCESS_MATRIX_S;
        sk_HFE->T=sk+GEMSS_ACCESS_MATRIX_T;
        #if GEMSS_AFFINE_TRANSFORMATION_BY_t
            sk_HFE->t=sk+GEMSS_ACCESS_VECTOR_t;
        #endif
    #endif

    #if(GEMSS_HFEDeg!=1)
        GEMSS_initListDifferences_gf2nx(sk_HFE->F_struct.L);
    #endif

    #if GEMSS_HFEv
        F_HFEv=sk_HFE->F_HFEv;

        GEMSS_ALIGNED_GFqn_MALLOC(F,UINT*,GEMSS_NB_UINT_HFEPOLY,sizeof(UINT));
        GEMSS_VERIFY_ALLOC_RET(F);

        #if (GEMSS_HFEDeg>1)
        UINT *F_cp;
        unsigned int j;

        /* X^(2^0) */
        linear_coefs[0]=F_HFEv+GEMSS_MQv_GFqn_SIZE;
        /* X^(2^1) */
        F_HFEv=linear_coefs[0]+GEMSS_MLv_GFqn_SIZE;
        F_cp=F+2*GEMSS_NB_WORD_GFqn;
        for(i=0;i<GEMSS_HFEDegI;++i)
        {
            /* Copy i quadratic terms */

            #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
            for(j=(((1U<<i)+1U)<=GEMSS_HFE_odd_degree)?0:1;j<i;++j)
            #else
            for(j=0;j<i;++j)
            #endif
            {
                /* X^(2^i + 2^j) */
                GEMSS_copy_gf2n(F_cp,F_HFEv);
                F_HFEv+=GEMSS_NB_WORD_GFqn;
                F_cp+=GEMSS_NB_WORD_GFqn;
            }
            /* Store the address of X^(2^(i+1)) */
            linear_coefs[i+1]=F_HFEv;
            /* Linear term is not copied */
            F_HFEv+=GEMSS_MLv_GFqn_SIZE;
            F_cp+=GEMSS_NB_WORD_GFqn;
        }
        #if GEMSS_HFEDegJ
            /* X^(2^GEMSS_HFEDegI + 2^j) */
            #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
            for(j=(((1U<<i)+1U)<=GEMSS_HFE_odd_degree)?0:1;j<GEMSS_HFEDegJ;++j)
            #else
            for(j=0;j<GEMSS_HFEDegJ;++j)
            #endif
            {
                GEMSS_copy_gf2n(F_cp,F_HFEv);
                F_HFEv+=GEMSS_NB_WORD_GFqn;
                F_cp+=GEMSS_NB_WORD_GFqn;
            }
        #endif
        #endif
        sk_HFE->F_struct.poly=F;
    #else
        sk_HFE->F_struct.poly=sk_HFE->F_HFEv;
    #endif

    return 0;
}


/* Format of the signature: S_NB_ITE||X_NB_ITE||...||X1
    _ S_NB_ITE||X_NB_ITE: n+v bits
    _ X_(GEMSS_NB_ITE-1): (n+v-m) bits. When the signature is uncompressed, the first
      word is padding with m%64 zero bits. It is to simply the concatenation of
      S_(GEMSS_NB_ITE-1) and X_(GEMSS_NB_ITE-1) during the verifying process.
    _ It is the same format for X_(GEMSS_NB_ITE-2),...,X1
*/


/**
 * @brief   Generate the signature of the document m of length len bytes, using
 * a (GEMSS_HFEv-)-based signature scheme.
 * @details The Feistel-Patarin scheme is used with GEMSS_NB_ITE rounds.
 * @param[in]   m   A pointer on a document.
 * @param[in]   len The length in bytes of the document m.
 * @param[in]   sk  The secret-key, which is the concatenation of a GEMSS_HFEv
 * polynomial in GF(2^n)[X], the S^(-1) matrix (n+v,n+v) in GL_{n+v}(GF(2))
 * and the T^(-1) matrix (n,n) in GLn(GF(2)).
 * @param[out]  sm8 The signature of m generated by a (GEMSS_HFEv-)-based signature
 * scheme. Its length is GEMSS_SIZE_SIGN_HFE bytes, and more precisely
 * GEMSS_SIZE_SIGN_THEORETICAL_HFE bits. The last byte is padded with zero bits when
 * necessary.
 * @return   0 if the result is correct, GEMSS_ERROR_ALLOC for error from
 * malloc/calloc functions.
 * @remark  Requirement: when SSE or AVX is enabled, the secret-key must be
 * aligned respectively on 16 or 32 bytes. However, this requirement and the
 * alignment are disabled for the public/stable version of MQsoft (to be simple
 * to use, generic for the allocation of sk and to avoid segmentation faults).
 * @remark  A part of the implementation is not in constant-time.
 * @todo    To simply the use of the memory alignment for the secret-key.
 */
#if GEMSS_EUF_CMA_PROPERTY
int GEMSS_PREFIX_NAME(GEMSS_signHFE_FeistelPatarin)(unsigned char* sm8,
                                        const unsigned char* m, size_t len,
                                        const UINT* sk)
{
    UINT sm[GEMSS_SIZE_SIGN_UNCOMPRESSED-GEMSS_SIZE_SALT_WORD]={0};

    static_vecnv_gf2 DR[GEMSS_NB_WORD_GF2nv];
    static_gf2n U[GEMSS_NB_WORD_GFqn];
    UINT Hd[GEMSS_SIZE_DIGEST_UINT+GEMSS_SIZE_SALT_WORD],Hi_tab[GEMSS_SIZE_DIGEST_UINT],
                                             Hi1_tab[GEMSS_SIZE_DIGEST_UINT];
    UINT *tmp,*Hi=Hi_tab,*Hi1=Hi1_tab;
    unsigned int k;
    unsigned char b;
    #if (GEMSS_HFEnv!=GEMSS_HFEm)
        unsigned int index;
    #endif
    #if(GEMSS_HFEn>GEMSS_HFEm)
        unsigned char* DR_cp=(unsigned char*)DR;
        #if(GEMSS_HFEm&7)
            unsigned char rem_char;
        #endif
    #endif

    int nb_root;
    secret_key_HFE sk_HFE;

    #if(GEMSS_HFEv)
        UINT* F;
        unsigned int i;
        static_vecv_gf2 V_tab[GEMSS_NB_ITE*GEMSS_NB_WORD_GFqv];
        vecv_gf2 V;
        #if (GEMSS_HFEDeg>1)
            static_gf2n tmp_n[GEMSS_NB_WORD_GFqn];
        #endif
    #endif


    #if (GEMSS_HFEDeg>1)
        const UINT* linear_coefs[GEMSS_HFEDegI+1];
        nb_root=GEMSS_precSignHFE(&sk_HFE,linear_coefs,sk);
    #else
        nb_root=GEMSS_precSignHFE(&sk_HFE,NULL,sk);
    #endif
    if(nb_root)
    {
        /* Error from malloc */
        return nb_root;
    }
    #if(GEMSS_HFEv)
        F=(UINT*)sk_HFE.F_struct.poly;
    #endif


    #ifdef GEMSS_KAT_INT
        GEMSS_OPEN_KAT_INT_FILE;
        fputs("Sign:\n",fp);
        unsigned int nb_try_to_sign;
    #endif


    /* Compute H(m) */
    GEMSS_HASH((unsigned char*)Hd,m,len);


    /* Generation of vinegar variables: v bits by iteration */
    #if GEMSS_HFEv
        GEMSS_randombytes((unsigned char*)V_tab,
                    (unsigned long long)((GEMSS_NB_ITE*GEMSS_NB_WORD_GFqv)<<3));
        V=V_tab+GEMSS_NB_WORD_GFqv-1;
        #if GEMSS_HFEvr
            for(k=0;k<GEMSS_NB_ITE;++k)
            {
                /* Clean the last word */
                (*V)&=GEMSS_HFE_MASKv;
                V+=GEMSS_NB_WORD_GFqv;
            }
        #endif
    #endif


    #if(GEMSS_HFEn>GEMSS_HFEm)
        unsigned int j;
        #if(GEMSS_HFEm&7)
            unsigned char minus_vec[GEMSS_NB_ITE*(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm+1)];
            GEMSS_randombytes(minus_vec, (unsigned long long)
                                   (GEMSS_NB_ITE*(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm+1)));
        #else
            unsigned char minus_vec[GEMSS_NB_ITE*(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm)];
            GEMSS_randombytes(minus_vec, (unsigned long long)
                                   (GEMSS_NB_ITE*(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm)));
        #endif
    #endif


    do
    {
        b=0;
        /* V is the current vinegar variables */
        V=V_tab;

        /* It is to initialize S0 to 0, because Sk||Xk is stored in sm */
        for(k=0;k<GEMSS_NB_WORD_GF2nv;++k)
        {
            sm[k]=0;
            DR[k]=0;
        }

        /* Random salt r, Hd is H(m)||r */
        GEMSS_randombytes((unsigned char*)(Hd+GEMSS_SIZE_DIGEST_UINT),
                    (unsigned long long)(GEMSS_SIZE_SALT));

        /* Compute H1 = H(H(m)||r) */
        GEMSS_HASH((unsigned char*)Hi,(unsigned char*)Hd,GEMSS_SIZE_DIGEST+GEMSS_SIZE_SALT);


        for(k=1;k<=GEMSS_NB_ITE;++k)
        {
            #ifdef GEMSS_KAT_INT
                nb_try_to_sign=0U;
                fprintf(fp,"k=%u\n",k);
            #endif

            /* Compute xor(D_k,S_(k-1)) */
            GEMSS_add_gf2m(DR,sm,Hi);

            #if GEMSS_AFFINE_TRANSFORMATION_BY_t
                /* DR - t */
                GEMSS_add2_gf2m(DR,sk_HFE.t);
            #endif

            #if(GEMSS_HFEm&7)
                /* Clean the last char to compute rem_char (the last word is 
                   cleaned) */
                DR[GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
                /* Save the last byte because we need to erase this value by 
                 * GEMSS_randombytes */
                #if(GEMSS_HFEn>GEMSS_HFEm)
                    rem_char=DR_cp[GEMSS_NB_BYTES_GFqm-1];
                #endif
            #endif

            #ifdef GEMSS_KAT_INT
                GEMSS_fprintBstr_KAT_INT(fp,"xor(Dk,S_(k-1)): ",
                                   (unsigned char*)DR,GEMSS_NB_BYTES_GFqm);
            #endif



            #if(GEMSS_HFEn>GEMSS_HFEm)
            /* Compute Dk||Rk: add random to have n bits, without erased the m 
             * bits */
                #if(GEMSS_HFEm&7)
                /* Generation of Rk */
                for(j=0;j<(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm+1);++j)
                {
                    DR_cp[GEMSS_NB_BYTES_GFqm-1+j]=minus_vec[(k-1)*(GEMSS_NB_BYTES_GFqn
                                                       -GEMSS_NB_BYTES_GFqm+1)+j];
                }
                /* Put GEMSS_HFEm&7 first bits to 0 */
                DR_cp[GEMSS_NB_BYTES_GFqm-1]&=~((1U<<(GEMSS_HFEm&7))-1);
                /* Store rem_char */
                DR_cp[GEMSS_NB_BYTES_GFqm-1]^=rem_char;
                #else
                /* Generation of Rk */
                for(j=0;j<(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm);++j)
                {
                    DR_cp[GEMSS_NB_BYTES_GFqm+j]=minus_vec[(k-1)*(GEMSS_NB_BYTES_GFqn
                                                     -GEMSS_NB_BYTES_GFqm)+j];
                }
                #endif

                /* To clean the last char (because of GEMSS_randombytes), the last 
                   word is cleaned */
                #if (GEMSS_HFEn&7)
                    DR[GEMSS_NB_WORD_GFqn-1]&=GEMSS_MASK_GF2n;
                #endif
            #endif

            #ifdef GEMSS_KAT_INT
                ++nb_try_to_sign;
                fprintf(fp,"Try %u, ",nb_try_to_sign);
                GEMSS_fprintBstr_KAT_INT(fp,"Dk||Rk: ",(unsigned char*)DR,
                                                 GEMSS_NB_BYTES_GFqn);
            #endif

            /* Compute Sk||Xk = Inv_p(Dk,Rk) */
            /* Firstly: compute c * T^(-1) */
            GEMSS_vecMatProductn_gf2(U,DR,sk_HFE.T);



            /* Secondly: find v with F_HFE(v) = U */

           #if(GEMSS_HFEv)
                /* Evaluation of the constant, quadratic map with v vinegars */
                GEMSS_evalMQSv_gf2(F,V,sk_HFE.F_HFEv);

                #if (GEMSS_HFEDeg>1)
                    /* Evaluation of the linear terms, linear maps with v
                       vinegars */
                    #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
                    #if(GEMSS_HFEDegI==GEMSS_HFEDegJ)
                    for(i=0;i<=GEMSS_LOG_odd_degree;++i)
                    #elif(GEMSS_HFEDegI<=GEMSS_LOG_odd_degree)
                    for(i=0;i<=GEMSS_HFEDegI;++i)
                    #else
                    for(i=0;i<=(GEMSS_LOG_odd_degree+1);++i)
                    #endif
                    {
                        GEMSS_vecMatProductv_gf2(tmp_n,V,linear_coefs[i]
                                           +GEMSS_NB_WORD_GFqn);
                        GEMSS_add_gf2n(F+GEMSS_NB_WORD_GFqn*(((i*(i+1))>>1)+1),
                                 linear_coefs[i],tmp_n);
                    }
                    for(;i<=GEMSS_HFEDegI;++i)
                    {
                        GEMSS_vecMatProductv_gf2(tmp_n,V,linear_coefs[i]
                                           +GEMSS_NB_WORD_GFqn);
                        GEMSS_add_gf2n(F+GEMSS_NB_WORD_GFqn*(((i*(i-1))>>1)+2+
                                 GEMSS_LOG_odd_degree),linear_coefs[i],tmp_n);
                    }
                    #else
                    for(i=0;i<=GEMSS_HFEDegI;++i)
                    {
                        GEMSS_vecMatProductv_gf2(tmp_n,V,linear_coefs[i]
                                           +GEMSS_NB_WORD_GFqn);
                        GEMSS_add_gf2n(F+GEMSS_NB_WORD_GFqn*(((i*(i+1))>>1)+1),
                                 linear_coefs[i],tmp_n);
                    }
                    #endif
                #endif
            #endif

            nb_root=GEMSS_chooseRootHFE_gf2nx(DR,sk_HFE.F_struct,U);
            if(!nb_root)
            {
                /* fail: retry */
                b=1;
                break;
            }
            if(nb_root<0)
            {
                /* Error from chooseRootHFE */
                #if GEMSS_HFEv
                    GEMSS_ALIGNED_GFqn_FREE(F);
                #endif
                return nb_root;
            }


            #if GEMSS_HFEv
                /* Add the v bits to DR */
                #if GEMSS_HFEnr
                    DR[GEMSS_NB_WORD_GFqn-1]^=V[0]<<GEMSS_HFEnr;
                    for(i=0;i<(GEMSS_NB_WORD_GFqv-1);++i)
                    {
                        DR[GEMSS_NB_WORD_GFqn+i]=(V[i]>>(64-GEMSS_HFEnr))^(V[i+1]<<GEMSS_HFEnr);
                    }
                    #if ((GEMSS_NB_WORD_GFqn+GEMSS_NB_WORD_GFqv) == GEMSS_NB_WORD_GF2nv)
                        DR[GEMSS_NB_WORD_GFqn+i]=V[i]>>(64-GEMSS_HFEnr);
                    #endif
                #else
                    for(i=0;i<GEMSS_NB_WORD_GFqv;++i)
                    {
                        DR[GEMSS_NB_WORD_GFqn+i]=V[i];
                    }
                #endif
            #endif

            /* Finally: compute Sk||Xk = v * S^(-1) */
            GEMSS_vecMatProductnv_gf2(sm,DR,sk_HFE.S);

            if(k!=GEMSS_NB_ITE)
            {
                #ifdef GEMSS_KAT_INT
                    GEMSS_fprintBstr_KAT_INT(fp,"Sk||Xk: ",(unsigned char*)sm,
                                                     GEMSS_NB_BYTES_GFqnv);
                #endif

                #if GEMSS_HFEv
                    /* Update of the vinegar variables */
                    V+=GEMSS_NB_WORD_GFqv;
                #endif

                #if (GEMSS_HFEnv!=GEMSS_HFEm)
                    /* Store X1 in the signature */
                    index=GEMSS_NB_WORD_GF2nv+(GEMSS_NB_ITE-1-k)*GEMSS_NB_WORD_GF2nvm;
                    GEMSS_copy_gf2nvm(sm+index,sm+GEMSS_NB_WORD_GF2nv-GEMSS_NB_WORD_GF2nvm);
                    /* To put zeros at the beginning of the first word of X1 */
                    #if GEMSS_HFEmr
                        sm[index]&=GEMSS_MASK_GF2nvm;
                    #endif
                #endif

                /* Compute H2 = H(H1) */
                GEMSS_HASH((unsigned char*)Hi1,(unsigned char*)Hi,GEMSS_SIZE_DIGEST);

                /* Permutation of pointers */
                tmp=Hi1;
                Hi1=Hi;
                Hi=tmp;
            }
        }
    } while(b);

    #if GEMSS_ENABLED_SEED_SK
        free(sk_HFE.sk_uncomp);
    #endif
    #if GEMSS_HFEv
        GEMSS_ALIGNED_GFqn_FREE(F);
    #endif


    /* Copy the salt in the signature */
    for(k=0;k<GEMSS_SIZE_SALT_WORD;++k)
    {
        ((UINT*)sm8)[k]=Hd[GEMSS_SIZE_DIGEST_UINT+k];
    }
    sm8+=GEMSS_SIZE_SALT;


    #ifdef GEMSS_KAT_INT
        GEMSS_CLOSE_KAT_INT_FILE;
    #endif

    #if (GEMSS_NB_ITE==1)
        /* Take the (n+v) first bits */
        for(k=0;k<GEMSS_NB_BYTES_GFqnv;++k)
        {
            sm8[k]=((unsigned char*)sm)[k];
        }
    #else
        compress_signHFE(sm8,sm);
    #endif

    return 0;
}


#else

int GEMSS_PREFIX_NAME(GEMSS_signHFE_FeistelPatarin)(unsigned char* sm8,
                                        const unsigned char* m, size_t len,
                                        const UINT* sk)
{
    UINT sm[GEMSS_SIZE_SIGN_UNCOMPRESSED-GEMSS_SIZE_SALT_WORD]={0};

    static_vecnv_gf2 DR[GEMSS_NB_WORD_GF2nv];
    static_gf2n U[GEMSS_NB_WORD_GFqn];
    UINT Hi_tab[GEMSS_SIZE_DIGEST_UINT],Hi1_tab[GEMSS_SIZE_DIGEST_UINT];
    UINT *tmp, *Hi=Hi_tab,*Hi1=Hi1_tab;
    unsigned int k;
    #if (GEMSS_HFEnv!=GEMSS_HFEm)
        unsigned int index;
    #endif
    #if(GEMSS_HFEn>GEMSS_HFEm)
        unsigned char* DR_cp=(unsigned char*)DR;
        #if(GEMSS_HFEm&7)
            unsigned char rem_char;
        #endif
    #endif

    int nb_root;
    secret_key_HFE sk_HFE;

    #if(GEMSS_HFEv)
        UINT* F;
        unsigned int i;
        static_vecv_gf2 V[GEMSS_NB_WORD_GFqv];
        #if (GEMSS_HFEDeg>1)
            static_gf2n tmp_n[GEMSS_NB_WORD_GFqn];
        #endif
    #endif


    #if (GEMSS_HFEDeg>1)
        const UINT* linear_coefs[GEMSS_HFEDegI+1];
        nb_root=GEMSS_precSignHFE(&sk_HFE,linear_coefs,sk);
    #else
        nb_root=GEMSS_precSignHFE(&sk_HFE,NULL,sk);
    #endif
    if(nb_root)
    {
        /* Error from malloc */
        return nb_root;
    }
    #if(GEMSS_HFEv)
        F=(UINT*)sk_HFE.F_struct.poly;
    #endif


    #ifdef GEMSS_KAT_INT
        GEMSS_OPEN_KAT_INT_FILE;
        fputs("Sign:\n",fp);
        unsigned int nb_try_to_sign;
    #endif


    /* Compute H1 = H(m) */
    GEMSS_HASH((unsigned char*)Hi,m,len);

    /* It is to initialize S0 to 0, because Sk||Xk is stored in sm */
    for(k=0;k<GEMSS_NB_WORD_GF2nv;++k)
    {
        sm[k]=0;
        DR[k]=0;
    }

    for(k=1;k<=GEMSS_NB_ITE;++k)
    {
        #ifdef GEMSS_KAT_INT
            nb_try_to_sign=0U;
            fprintf(fp,"k=%u\n",k);
        #endif

        /* Compute xor(D_k,S_(k-1)) */
        GEMSS_add_gf2m(DR,sm,Hi);

        #if GEMSS_AFFINE_TRANSFORMATION_BY_t
            /* DR - t */
            GEMSS_add2_gf2m(DR,sk_HFE.t);
        #endif

        #if(GEMSS_HFEm&7)
            /* Clean the last char to compute rem_char (the last word is 
               cleaned) */
            DR[GEMSS_NB_WORD_GF2m-1]&=GEMSS_MASK_GF2m;
            /* Save the last byte because we need to erase this value by 
             * GEMSS_randombytes */
            #if(GEMSS_HFEn>GEMSS_HFEm)
                rem_char=DR_cp[GEMSS_NB_BYTES_GFqm-1];
            #endif
        #endif

        #ifdef GEMSS_KAT_INT
            GEMSS_fprintBstr_KAT_INT(fp,"xor(Dk,S_(k-1)): ",
                               (unsigned char*)DR,GEMSS_NB_BYTES_GFqm);
        #endif

        #if GEMSS_GEN_MINUS_VINEGARS
        /* When the root finding fails, the minus and vinegars are 
           regenerated */
        do
        {
        #endif
            #if(GEMSS_HFEn>GEMSS_HFEm)
            /* Compute Dk||Rk: add random to have n bits, without erased the m 
             * bits */
            #if(GEMSS_HFEm&7)
                /* Generation of Rk */
                GEMSS_randombytes(DR_cp+GEMSS_NB_BYTES_GFqm-1,
                           (unsigned long long)(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm+1));
                /* Put GEMSS_HFEm&7 first bits to 0 */
                DR_cp[GEMSS_NB_BYTES_GFqm-1]&=~((1U<<(GEMSS_HFEm&7))-1);
                /* Store rem_char */
                DR_cp[GEMSS_NB_BYTES_GFqm-1]^=rem_char;
            #else
                /* Generation of Rk */
                GEMSS_randombytes(DR_cp+GEMSS_NB_BYTES_GFqm,
                        (unsigned long long)(GEMSS_NB_BYTES_GFqn-GEMSS_NB_BYTES_GFqm));
            #endif

            /* To clean the last char (because of GEMSS_randombytes), the last word is 
             * cleaned */
            #if (GEMSS_HFEn&7)
                DR[GEMSS_NB_WORD_GFqn-1]&=GEMSS_MASK_GF2n;
            #endif
            #endif

            #ifdef GEMSS_KAT_INT
                ++nb_try_to_sign;
                fprintf(fp,"Try %u, ",nb_try_to_sign);
                GEMSS_fprintBstr_KAT_INT(fp,"Dk||Rk: ",(unsigned char*)DR,
                                                 GEMSS_NB_BYTES_GFqn);
            #endif

            /* Compute Sk||Xk = Inv_p(Dk,Rk) */
            /* Firstly: compute c * T^(-1) */
            GEMSS_vecMatProductn_gf2(U,DR,sk_HFE.T);

        #if (!GEMSS_GEN_MINUS_VINEGARS)
        /* When the root finding fails, only the vinegars are regenerated */
        do
        {
        #endif
            /* Secondly: find v with F_HFE(v) = U */

            /* Generation of vinegar variables: v bits */
           #if(GEMSS_HFEv)
                GEMSS_randombytes((unsigned char*)V,
                            (unsigned long long)(GEMSS_NB_BYTES_GFqv));
                #if GEMSS_HFEvr8
                    /* Clean the last word */
                    V[GEMSS_NB_WORD_GFqv-1]&=GEMSS_HFE_MASKv;
                #endif

                /* Evaluation of the constant, quadratic map with v vinegars */
                GEMSS_evalMQSv_gf2(F,V,sk_HFE.F_HFEv);

                #if (GEMSS_HFEDeg>1)
                    /* Evaluation of the linear terms, linear maps with v
                       vinegars */
                    #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
                    #if(GEMSS_HFEDegI==GEMSS_HFEDegJ)
                    for(i=0;i<=GEMSS_LOG_odd_degree;++i)
                    #elif(GEMSS_HFEDegI<=GEMSS_LOG_odd_degree)
                    for(i=0;i<=GEMSS_HFEDegI;++i)
                    #else
                    for(i=0;i<=(GEMSS_LOG_odd_degree+1);++i)
                    #endif
                    {
                        GEMSS_vecMatProductv_gf2(tmp_n,V,linear_coefs[i]
                                           +GEMSS_NB_WORD_GFqn);
                        GEMSS_add_gf2n(F+GEMSS_NB_WORD_GFqn*(((i*(i+1))>>1)+1),
                                 linear_coefs[i],tmp_n);
                    }
                    for(;i<=GEMSS_HFEDegI;++i)
                    {
                        GEMSS_vecMatProductv_gf2(tmp_n,V,linear_coefs[i]
                                           +GEMSS_NB_WORD_GFqn);
                        GEMSS_add_gf2n(F+GEMSS_NB_WORD_GFqn*(((i*(i-1))>>1)+2+
                                 GEMSS_LOG_odd_degree),linear_coefs[i],tmp_n);
                    }
                    #else
                    for(i=0;i<=GEMSS_HFEDegI;++i)
                    {
                        GEMSS_vecMatProductv_gf2(tmp_n,V,linear_coefs[i]
                                           +GEMSS_NB_WORD_GFqn);
                        GEMSS_add_gf2n(F+GEMSS_NB_WORD_GFqn*(((i*(i+1))>>1)+1),
                                 linear_coefs[i],tmp_n);
                    }
                    #endif
                #endif
            #endif

            nb_root=GEMSS_chooseRootHFE_gf2nx(DR,sk_HFE.F_struct,U);
            if(!nb_root)
            {
                /* fail: retry with an other Rk */
                continue;
            }
            if(nb_root<0)
            {
                /* Error from chooseRootHFE */
                #if GEMSS_HFEv
                    GEMSS_ALIGNED_GFqn_FREE(F);
                #endif
                return nb_root;
            }

            break;
        } while(1);


        #if GEMSS_HFEv
            /* Add the v bits to DR */
            #if GEMSS_HFEnr
                DR[GEMSS_NB_WORD_GFqn-1]^=V[0]<<GEMSS_HFEnr;
                for(i=0;i<(GEMSS_NB_WORD_GFqv-1);++i)
                {
                    DR[GEMSS_NB_WORD_GFqn+i]=(V[i]>>(64-GEMSS_HFEnr))^(V[i+1]<<GEMSS_HFEnr);
                }
                #if ((GEMSS_NB_WORD_GFqn+GEMSS_NB_WORD_GFqv) == GEMSS_NB_WORD_GF2nv)
                    DR[GEMSS_NB_WORD_GFqn+i]=V[i]>>(64-GEMSS_HFEnr);
                #endif
            #else
                for(i=0;i<GEMSS_NB_WORD_GFqv;++i)
                {
                    DR[GEMSS_NB_WORD_GFqn+i]=V[i];
                }
            #endif
        #endif

        /* Finally: compute Sk||Xk = v * S^(-1) */
        GEMSS_vecMatProductnv_gf2(sm,DR,sk_HFE.S);

        if(k!=GEMSS_NB_ITE)
        {
            #ifdef GEMSS_KAT_INT
                GEMSS_fprintBstr_KAT_INT(fp,"Sk||Xk: ",(unsigned char*)sm,
                                                 GEMSS_NB_BYTES_GFqnv);
            #endif

            #if (GEMSS_HFEnv!=GEMSS_HFEm)
                /* Store X1 in the signature */
                index=GEMSS_NB_WORD_GF2nv+(GEMSS_NB_ITE-1-k)*GEMSS_NB_WORD_GF2nvm;
                GEMSS_copy_gf2nvm(sm+index,sm+GEMSS_NB_WORD_GF2nv-GEMSS_NB_WORD_GF2nvm);
                /* To put zeros at the beginning of the first word of X1 */
                #if GEMSS_HFEmr
                    sm[index]&=GEMSS_MASK_GF2nvm;
                #endif
            #endif

            /* Compute H2 = H(H1) */
            GEMSS_HASH((unsigned char*)Hi1,(unsigned char*)Hi,GEMSS_SIZE_DIGEST);

            /* Permutation of pointers */
            tmp=Hi1;
            Hi1=Hi;
            Hi=tmp;
        }
    }

    #if GEMSS_ENABLED_SEED_SK
        free(sk_HFE.sk_uncomp);
    #endif
    #if GEMSS_HFEv
        GEMSS_ALIGNED_GFqn_FREE(F);
    #endif
    #ifdef GEMSS_KAT_INT
        GEMSS_CLOSE_KAT_INT_FILE;
    #endif

    #if (GEMSS_NB_ITE==1)
        /* Take the (n+v) first bits */
        for(k=0;k<GEMSS_NB_BYTES_GFqnv;++k)
        {
            sm8[k]=((unsigned char*)sm)[k];
        }
    #else
        compress_signHFE(sm8,sm);
    #endif

    return 0;
}

#endif




