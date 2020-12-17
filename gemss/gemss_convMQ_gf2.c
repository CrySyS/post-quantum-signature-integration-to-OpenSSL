#include "gemss_convMQ_gf2.h"
#include "gemss_parameters_HFE.h"
#include "gemss_MQ_gf2.h"



/**
 * @brief   Cast between two representations of a MQ equation in
 * GF(2)[x1,...,x_(n+v)] (upper to lower triangular matrix).
 * @details pk = (c,Q), with c the constant part in GF(2) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2). pk2 will have the same
 * format, but with a lower triangular matrix. These equations are compressed.
 * @param[in]   pk  A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @param[out]  pk2 A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @remark  Requires to allocate GEMSS_NB_BYTES_EQUATION bytes for pk2. This size is
 * the theoretical size.
 * @remark  Constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_convMQ_UL_gf2)(uint8_t* pk2, const uint8_t* pk)
{
    unsigned int i,k,nb_bits;
    int j;

    /* Constant + x_0*x_0 */
    *pk2=(*pk)&3;

    for(i=1;i<GEMSS_NB_BYTES_EQUATION;++i)
    {
        pk2[i]=0;
    }

    /* For each row of the output (the first is already done) */
    for(k=2,i=2;i<=GEMSS_HFEnv;++i)
    {
        nb_bits=i;
        /* For each column */
        for(j=GEMSS_HFEnv-1;j>=(int)(GEMSS_HFEnv-i);--j,++k)
        {
            pk2[k>>3]^=((pk[nb_bits>>3]>>(nb_bits&7))&GEMSS_ONE8)<<(k&7);
            nb_bits+=j;
        }
    }
}


/* Number of lost bits by the zero padding of each equation
   (without the last) */
#define GEMSS_LOST_BITS ((GEMSS_HFEmr8-1)*GEMSS_HFENr8c)
/* Size of the last equation after to have removed the GEMSS_LOST_BITS last bits. */
#define GEMSS_SIZE_LAST_EQUATION ((GEMSS_NB_MONOMIAL_PK-((GEMSS_HFEmr8-1)*GEMSS_HFENr8c)+7)>>3)



#if (GEMSS_HFENr8&&(GEMSS_HFEmr8>1))

/**
 * @brief   Cast between two representations of a MQ equation in
 * GF(2)[x1,...,x_(n+v)] (upper to lower triangular matrix). The end of the
 * matrix is not stored, but is returned.
 * @details pk = (c,Q), with c the constant part in GF(2) and Q is an upper
 * triangular matrix of size (n+v)*(n+v) in GF(2). pk2 will have the same
 * format, but with a lower triangular matrix. These equations are compressed.
 * @param[in]   pk  A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @param[out]  pk2 A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @return  The GEMSS_LOST_BITS last bits of pk2.
 * @remark  Requires to allocate GEMSS_SIZE_LAST_EQUATION bytes for pk2. This
 * size is the theoretical size.
 * @remark  This function does not support GEMSS_HFEnv<GEMSS_LOST_BITS.
 * @remark  This function is a modified copy of GEMSS_convMQ_UL_gf2.
 * @remark  Constant-time implementation.
 */
uint64_t GEMSS_PREFIX_NAME(GEMSS_convMQ_last_UL_gf2)(uint8_t* pk2, const uint8_t* pk)
{
    uint64_t val;
    unsigned int i,k,nb_bits;
    int j;

    /* Constant + x_0*x_0 */
    *pk2=(*pk)&3;

    for(i=1;i<GEMSS_SIZE_LAST_EQUATION;++i)
    {
        pk2[i]=0;
    }

    /* For each row of the output (the first is already done) */
    for(k=2,i=2;i<GEMSS_HFEnv;++i)
    {
        nb_bits=i;
        /* For each column */
        for(j=GEMSS_HFEnv-1;j>=(int)(GEMSS_HFEnv-i);--j,++k)
        {
            pk2[k>>3]^=((pk[nb_bits>>3]>>(nb_bits&7))&GEMSS_ONE8)<<(k&7);
            nb_bits+=j;
        }
    }

    /* i == GEMSS_HFEnv */
    nb_bits=GEMSS_HFEnv;
    /* For each column */
    for(j=GEMSS_HFEnv-1;j>=GEMSS_LOST_BITS;--j,++k)
    {
        pk2[k>>3]^=((pk[nb_bits>>3]>>(nb_bits&7))&GEMSS_ONE8)<<(k&7);
        nb_bits+=j;
    }
    val=0;
    for(;j>=(int)0;--j,++k)
    {
        val^=((uint64_t)((pk[nb_bits>>3]>>(nb_bits&7))&GEMSS_ONE8))<<(GEMSS_LOST_BITS-1-j);
        nb_bits+=j;
    }

    return val;
}
#endif


#define GEMSS_HFEnvqm1 ((GEMSS_HFEnv-1)>>6)
#define GEMSS_HFEnvrm1 ((GEMSS_HFEnv-1)&63)

/**
 * @brief   Decompression of a compressed MQ equation in GF(2)[x1,...,x_(n+v)].
 * Both use a lower triangular matrix.
 * @details pk = (c,Q), with c the constant part in GF(2) and Q is a lower
 * triangular matrix of size (n+v)*(n+v) in GF(2). pk2 will have the same
 * format, but the equation will be decompressed. Here, the last bits of pk
 * are missing (cf. the output of GEMSS_convMQ_last_UL_gf2). Moreover, the last byte
 * of pk is padded with null bits.
 * @param[in]   pk  A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @param[out]  pk2 A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @return  The constant c of pk2, in GF(2).
 * @remark  Requires to allocate GEMSS_NB_WORD_UNCOMP_EQ 64-bit words for pk2.
 * @remark  This function is a modified copy of GEMSS_convMQ_uncompressL_gf2.
 * @remark  Constant-time implementation.
 */
UINT GEMSS_PREFIX_NAME(GEMSS_convMQ_last_uncompressL_gf2)(uint64_t* pk2, const uint8_t* pk)
{
    const uint64_t *pk64;
    unsigned int iq,ir,k,nb_bits;

    pk64=(uint64_t*)pk;

    nb_bits=1;
    /* For each row */
    for(iq=0;iq<GEMSS_HFEnvqm1;++iq)
    {
        for(ir=1;ir<64;++ir)
        {
            if(nb_bits&63)
            {
                for(k=0;k<iq;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }

                pk2[k]=pk64[k]>>(nb_bits&63);
                if(((nb_bits&63)+ir)>64)
                {
                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
                }

                if(((nb_bits&63)+ir)>=64)
                {
                    ++pk64;
                }
            } else
            {
                for(k=0;k<=iq;++k)
                {
                    pk2[k]=pk64[k];
                }
            }

            pk64+=iq;
            /* 0 padding on the last word */
            pk2[iq]&=(GEMSS_ONE64<<ir)-GEMSS_ONE64;
            pk2+=iq+1;
            nb_bits+=(iq<<6)+ir;
        }

        /* ir=64 */
        if(nb_bits&63)
        {
            for(k=0;k<=iq;++k)
            {
                pk2[k]=(pk64[k]>>(nb_bits&63))^(pk64[k+1]<<(64-(nb_bits&63)));
            }
        } else
        {
            for(k=0;k<=iq;++k)
            {
                pk2[k]=pk64[k];
            }
        }
        pk64+=iq+1;
        pk2+=iq+1;
        nb_bits+=(iq+1)<<6;
    }

    #if GEMSS_HFEnvrm1
        for(ir=1;ir<=GEMSS_HFEnvrm1;++ir)
        {
            if(nb_bits&63)
            {
                for(k=0;k<iq;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }

                pk2[k]=pk64[k]>>(nb_bits&63);
                if(((nb_bits&63)+ir)>64)
                {
                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
                }

                if(((nb_bits&63)+ir)>=64)
                {
                    ++pk64;
                }
            } else
            {
                for(k=0;k<=iq;++k)
                {
                    pk2[k]=pk64[k];
                }
            }

            pk64+=iq;
            /* 0 padding on the last word */
            pk2[iq]&=(GEMSS_ONE64<<ir)-GEMSS_ONE64;
            pk2+=iq+1;
            nb_bits+=(iq<<6)+ir;
        }
    #endif

    /* Last row */
    /* The size of the last row is GEMSS_HFEnv-GEMSS_LOST_BITS bits */
    #define GEMSS_LAST_ROW_Q ((GEMSS_HFEnv-GEMSS_LOST_BITS)>>6)
    #define GEMSS_LAST_ROW_R ((GEMSS_HFEnv-GEMSS_LOST_BITS)&63)
    iq=GEMSS_LAST_ROW_Q;

    #if (((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7)
        uint8_t *pk_end;
        uint64_t end;
        unsigned int l;
    #endif

    #if GEMSS_LAST_ROW_R
        ir=GEMSS_LAST_ROW_R;
        if(nb_bits&63)
        {
            #if (((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7)
                #define GEMSS_NB_WHOLE_BLOCKS ((GEMSS_HFEnv-\
                        ((64-((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS-GEMSS_HFEnvr)&63))&63))>>6)

                for(k=0;k<GEMSS_NB_WHOLE_BLOCKS;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }

                #if (GEMSS_NB_WHOLE_BLOCKS<GEMSS_LAST_ROW_Q)
                    pk2[k]=pk64[k]>>(nb_bits&63);

                    end=0;
                    pk_end=(uint8_t*)(pk64+k+1);
                    for(l=0;l<(((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7);++l)
                    {
                        end^=((uint64_t)(pk_end[l]))<<(l<<3);
                    }

                    pk2[k]^=end<<(64-(nb_bits&63));
                    pk2[k+1]=end>>(nb_bits&63);
                #else
                    pk2[k]=pk64[k]>>(nb_bits&63);

                    if(((nb_bits&63)+ir)>64)
                    {
                        end=0;
                        pk_end=(uint8_t*)(pk64+k+1);
                        for(l=0;l<(((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7);++l)
                        {
                            end^=((uint64_t)(pk_end[l]))<<(l<<3);
                        }
                        pk2[k]^=end<<(64-(nb_bits&63));
                    }
                #endif
            #else
                for(k=0;k<iq;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }

                pk2[k]=pk64[k]>>(nb_bits&63);
                if(((nb_bits&63)+ir)>64)
                {
                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
                }
            #endif
        } else
        {
            #if (((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7)
                for(k=0;k<iq;++k)
                {
                    pk2[k]=pk64[k];
                }

                end=0;
                pk_end=(uint8_t*)(pk64+k);
                for(l=0;l<(((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7);++l)
                {
                    end^=((uint64_t)(pk_end[l]))<<(l<<3);
                }
                pk2[k]=end;
            #else
                for(k=0;k<=iq;++k)
                {
                    pk2[k]=pk64[k];
                }
            #endif
        }
    #elif GEMSS_LAST_ROW_Q
        if(nb_bits&63)
        {
            #if (((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7)
                for(k=0;k<(iq-1);++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }
                pk2[k]=pk64[k]>>(nb_bits&63);

                end=0;
                pk_end=(uint8_t*)(pk64+k+1);
                for(l=0;l<(((GEMSS_NB_MONOMIAL_PK-GEMSS_LOST_BITS+7)>>3)&7);++l)
                {
                    end^=((uint64_t)(pk_end[l]))<<(l<<3);
                }
                pk2[k]^=end<<(64-(nb_bits&63));
            #else
                for(k=0;k<iq;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }
            #endif
        } else
        {
            for(k=0;k<iq;++k)
            {
                pk2[k]=pk64[k];
            }
        }
    #endif

    /* Constant */
    return (*pk)&1;
}


/**
 * @brief   Decompression of a compressed MQ equation in GF(2)[x1,...,x_(n+v)].
 * Both use a lower triangular matrix.
 * @details pk = (c,Q), with c the constant part in GF(2) and Q is a lower
 * triangular matrix of size (n+v)*(n+v) in GF(2). pk2 will have the same
 * format, but the equation will be decompressed. Here, the last byte of pk is
 * padded with null bits.
 * @param[in]   pk  A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @param[out]  pk2 A MQ equation in GF(2)[x1,...,x_(n+v)].
 * @return  The constant c of pk2, in GF(2).
 * @remark  Requires to allocate GEMSS_NB_WORD_UNCOMP_EQ 64-bit words for pk2.
 * @remark  Requirement: at least GEMSS_NB_BYTES_EQUATION
 * + ((8-(GEMSS_NB_BYTES_EQUATION mod 8)) mod 8) bytes have to be allocated for pk
 * (because pk is casted in 64-bit, and the last memory access requires that
 * is allocated a multiple of 64 bits).
 * @remark  Constant-time implementation.
 */
UINT GEMSS_PREFIX_NAME(GEMSS_convMQ_uncompressL_gf2)(uint64_t* pk2, const uint8_t* pk)
{
    const uint64_t *pk64;
    unsigned int iq,ir,k,nb_bits;

    pk64=(uint64_t*)pk;

    nb_bits=1;
    /* For each row */
    for(iq=0;iq<GEMSS_HFEnvq;++iq)
    {
        for(ir=1;ir<64;++ir)
        {
            if(nb_bits&63)
            {
                for(k=0;k<iq;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }

                pk2[k]=pk64[k]>>(nb_bits&63);
                if(((nb_bits&63)+ir)>64)
                {
                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
                }

                if(((nb_bits&63)+ir)>=64)
                {
                    ++pk64;
                }
            } else
            {
                for(k=0;k<=iq;++k)
                {
                    pk2[k]=pk64[k];
                }
            }

            pk64+=iq;
            /* 0 padding on the last word */
            pk2[iq]&=(GEMSS_ONE64<<ir)-GEMSS_ONE64;
            pk2+=iq+1;
            nb_bits+=(iq<<6)+ir;
        }

        /* ir=64 */
        if(nb_bits&63)
        {
            for(k=0;k<=iq;++k)
            {
                pk2[k]=(pk64[k]>>(nb_bits&63))^(pk64[k+1]<<(64-(nb_bits&63)));
            }
        } else
        {
            for(k=0;k<=iq;++k)
            {
                pk2[k]=pk64[k];
            }
        }
        pk64+=iq+1;
        pk2+=iq+1;
        nb_bits+=(iq+1)<<6;
    }

    #if GEMSS_HFEnvr
        for(ir=1;ir<=GEMSS_HFEnvr;++ir)
        {
            if(nb_bits&63)
            {
                for(k=0;k<iq;++k)
                {
                    pk2[k]=(pk64[k]>>(nb_bits&63))
                          ^(pk64[k+1]<<(64-(nb_bits&63)));
                }

                pk2[k]=pk64[k]>>(nb_bits&63);
                if(((nb_bits&63)+ir)>64)
                {
                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
                }

                if(((nb_bits&63)+ir)>=64)
                {
                    ++pk64;
                }
            } else
            {
                for(k=0;k<=iq;++k)
                {
                    pk2[k]=pk64[k];
                }
            }

            pk64+=iq;
            /* 0 padding on the last word */
            pk2[iq]&=(GEMSS_ONE64<<ir)-GEMSS_ONE64;
            pk2+=iq+1;
            nb_bits+=(iq<<6)+ir;
        }
    #endif

    /* Constant */
    return (*pk)&1;
}


