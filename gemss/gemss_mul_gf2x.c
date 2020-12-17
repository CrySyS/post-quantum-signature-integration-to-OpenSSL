#include "gemss_mul_gf2x.h"
#include "gemss_simd.h"

/* C=A*B in GF(2)[x] for each function */

/***********************************************************************/
/***********************************************************************/
/********************** version without vectorization ******************/
/***********************************************************************/
/***********************************************************************/


uint64_t GEMSS_PREFIX_NAME(GEMSS_mul32_no_simd_gf2x)(uint64_t A, uint64_t B)
{
    uint64_t C;
    GEMSS_MUL32_NO_SIMD_GF2X(C,A,B);
    return C;
}

uint64_t GEMSS_PREFIX_NAME(GEMSS_mul64low_no_simd_gf2x)(uint64_t A, uint64_t B)
{
    uint64_t C;
    GEMSS_MUL64LOW_NO_SIMD_GF2X(C,A,B);
    return C;
}

void GEMSS_PREFIX_NAME(GEMSS_mul64_no_simd_gf2x)(uint64_t C[2], const uint64_t A[1],
                                                    const uint64_t B[1])
{
    uint64_t tmp;
    GEMSS_MUL64_NO_SIMD_GF2X(C,*A,*B,tmp);
}

void GEMSS_PREFIX_NAME(GEMSS_mul96_no_simd_gf2x)(uint64_t C[3], const uint64_t A[2],
                                                    const uint64_t B[2])
{
    uint64_t tmp,AA,BB;
    GEMSS_MUL96_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
}

void GEMSS_PREFIX_NAME(GEMSS_mul128_no_simd_gf2x)(uint64_t C[4], const uint64_t A[2],
                                                     const uint64_t B[2])
{
    uint64_t tmp,AA,BB;
    GEMSS_MUL128_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
}

void GEMSS_PREFIX_NAME(GEMSS_mul160_no_simd_gf2x)(uint64_t C[5], const uint64_t A[3],
                                                     const uint64_t B[3])
{
    uint64_t tmp,AA,BB;
    GEMSS_MUL160_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
}

void GEMSS_PREFIX_NAME(GEMSS_mul192_no_simd_gf2x)(uint64_t C[6], const uint64_t A[3],
                                                     const uint64_t B[3])
{
    uint64_t tmp,AA,BB;
    GEMSS_MUL192_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
}

void GEMSS_PREFIX_NAME(GEMSS_mul224_no_simd_gf2x)(uint64_t C[7], const uint64_t A[4],
                                                     const uint64_t B[4])
{
    uint64_t tmp,AA[2],BB[2],tmp1,tmp2;
    GEMSS_MUL224_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul256_no_simd_gf2x)(uint64_t C[8], const uint64_t A[4],
                                                     const uint64_t B[4])
{
    uint64_t tmp,AA[2],BB[2],tmp1,tmp2;
    GEMSS_MUL256_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul288_no_simd_gf2x)(uint64_t C[9], const uint64_t A[5],
                                                     const uint64_t B[5])
{
    uint64_t tmp,AA[3],BB[3],tmp1,tmp2;
    GEMSS_MUL288_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
}


void GEMSS_PREFIX_NAME(GEMSS_mul320_no_simd_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                      const uint64_t B[5])
{
    uint64_t tmp,AA[3],BB[3],tmp1,tmp2;
    GEMSS_MUL320_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul352_no_simd_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                      const uint64_t B[6])
{
    uint64_t tmp,AA[3],BB[3],tmp1,tmp2;
    GEMSS_MUL352_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul384_no_simd_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                      const uint64_t B[6])
{
    uint64_t tmp,AA[3],BB[3],tmp1,tmp2;
    GEMSS_MUL384_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul416_no_simd_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                      const uint64_t B[7])
{
    uint64_t tmp,AA[4],BB[4],tmp3[2],tmp4[2],tmp1,tmp2;
    GEMSS_MUL416_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul448_no_simd_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                      const uint64_t B[7])
{
    uint64_t tmp,AA[4],BB[4],tmp3[2],tmp4[2],tmp1,tmp2;
    GEMSS_MUL448_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul480_no_simd_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                      const uint64_t B[8])
{
    uint64_t tmp,AA[4],BB[4],tmp3[2],tmp4[2],tmp1,tmp2;
    GEMSS_MUL480_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul512_no_simd_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                      const uint64_t B[8])
{
    uint64_t tmp,AA[4],BB[4],tmp3[2],tmp4[2],tmp1,tmp2;
    GEMSS_MUL512_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul544_no_simd_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                      const uint64_t B[9])
{
    uint64_t tmp,AA[5],BB[5],tmp3[3],tmp4[3],tmp1,tmp2;
    GEMSS_MUL544_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
}

void GEMSS_PREFIX_NAME(GEMSS_mul576_no_simd_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                      const uint64_t B[9])
{
    uint64_t tmp,AA[5],BB[5],tmp3[3],tmp4[3],tmp1,tmp2;
    GEMSS_MUL576_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
}


/***********************************************************************/
/***********************************************************************/
/*************************** sse2 version ******************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_SSE2
uint64_t GEMSS_PREFIX_NAME(GEMSS_pmul32_gf2x)(uint64_t A, uint64_t B)
{
    __m128i C1,RA,RB,CL,CH,M,one32;
    uint64_t C;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL32_WS_CLAS_GF2X(C1,A,B,RA,RB,CL,CH,M,one32);

    GEMSS_PCVT_64(C,C1);
    return C;
}

void GEMSS_PREFIX_NAME(GEMSS_pmul64_gf2x)(uint64_t C[2], const uint64_t A[1],
                                             const uint64_t B[1])
{
    __m128i C1,RA,RAM,RB,CL,CH,M,CLM,CHM,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL64_WS_CLAS2_GF2X(C1,*A,*B,RA,RAM,RB,CL,CH,M,CLM,CHM,one32);

    GEMSS_PSTORE128(C,C1);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul96_gf2x)(uint64_t C[3], const uint64_t A[2],
                                             const uint64_t B[2])
{
    __m128i C1,C2,RA,RB,CL,CH,M,M2,CM,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL96_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,M2,CM,one32);

    GEMSS_PSTORE192(C,C1,C2);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul128_gf2x)(uint64_t C[4], const uint64_t A[2],
                                              const uint64_t B[2])
{
    __m128i C1,C2,RA,RB,CL,CH,M,M2,CM,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL128_WS_KAR_GF2X(C1,C2,A,B,RA,RB,CL,CH,M,M2,CM,one32);

    GEMSS_PSTORE256(C,C1,C2);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul160_gf2x)(uint64_t C[5], const uint64_t A[3],
                                              const uint64_t B[3])
{
    __m128i C1,C2,C3,RA,RB,CL,CH,M,M2,CM,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL160_WS_KAR6_GF2X(C1,C2,C3,A,B,RA,RB,CL,CH,M,M2,CM,res1,res2,one32);

    GEMSS_PSTORE320(C,C1,C2,C3);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul192_gf2x)(uint64_t C[6], const uint64_t A[3],
                                              const uint64_t B[3])
{
    __m128i C1,C2,C3,RA,RB,CL,CH,M,M2,CM,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL192_WS_KAR6_GF2X(C1,C2,C3,A,B,RA,RB,CL,CH,M,M2,CM,res1,res2,one32);

    GEMSS_PSTORE384(C,C1,C2,C3);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul224_gf2x)(uint64_t C[7], const uint64_t A[4],
                                              const uint64_t B[4])
{
    __m128i C1,C2,C3,C4,RA,RB,CL,CH,M,MM,CM,M1,M2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL224_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32);

    GEMSS_PSTORE448(C,C1,C2,C3,C4);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul256_gf2x)(uint64_t C[8], const uint64_t A[4],
                                              const uint64_t B[4])
{
    __m128i C1,C2,C3,C4,RA,RB,CL,CH,M,MM,CM,M1,M2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32);

    GEMSS_PSTORE512(C,C1,C2,C3,C4);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul288_gf2x)(uint64_t C[9], const uint64_t A[5],
                                              const uint64_t B[5])
{
    __m128i C1,C2,C3,C4,C5,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL288_WS_KAR_GF2X(C1,C2,C3,C4,C5,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,
                        res1,res2,one32);

    GEMSS_PSTORE576(C,C1,C2,C3,C4,C5);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul320_gf2x)(uint64_t C[10], const uint64_t A[5],
                                               const uint64_t B[5])
{
    __m128i C1,C2,C3,C4,C5,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL320_WS_KAR_GF2X(C1,C2,C3,C4,C5,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,
                        res1,res2,one32);

    GEMSS_PSTORE640(C,C1,C2,C3,C4,C5);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul352_gf2x)(uint64_t C[11], const uint64_t A[6],
                                               const uint64_t B[6])
{
    __m128i C1,C2,C3,C4,C5,C6,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL384_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,
                        res1,res2,one32)

    GEMSS_PSTORE704(C,C1,C2,C3,C4,C5,C6);
}


void GEMSS_PREFIX_NAME(GEMSS_pmul384_gf2x)(uint64_t C[12], const uint64_t A[6],
                                               const uint64_t B[6])
{
    __m128i C1,C2,C3,C4,C5,C6,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL384_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,M3,
                        res1,res2,one32)

    GEMSS_PSTORE768(C,C1,C2,C3,C4,C5,C6);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul416_gf2x)(uint64_t C[13], const uint64_t A[7],
                                               const uint64_t B[7])
{
    __m128i C1,C2,C3,C4,C5,C6,C7,RA,RB,CL,CH,M,MM,CM,CM1,CM2,
            M1,M2,M3,M4,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL416_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,A,B,RA,RB,CL,CH,M,MM,CM,CM1,
                        CM2,M1,M2,M3,M4,one32)

    GEMSS_PSTORE832(C,C1,C2,C3,C4,C5,C6,C7);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul448_gf2x)(uint64_t C[14], const uint64_t A[7],
                                               const uint64_t B[7])
{
    __m128i C1,C2,C3,C4,C5,C6,C7,RA,RB,CL,CH,M,MM,CM,CM1,CM2,
            M1,M2,M3,M4,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL448_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,A,B,RA,RB,CL,CH,M,MM,CM,CM1,
                        CM2,M1,M2,M3,M4,one32)

    GEMSS_PSTORE896(C,C1,C2,C3,C4,C5,C6,C7);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul480_gf2x)(uint64_t C[15], const uint64_t A[8],
                                               const uint64_t B[8])
{
    __m128i C1,C2,C3,C4,C5,C6,C7,C8,RA,RB,CL,CH,M,MM,CM,CM1,CM2,
            M1,M2,M3,M4,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL480_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A,B,RA,RB,CL,CH,M,MM,CM,CM1,
                        CM2,M1,M2,M3,M4,one32)

    GEMSS_PSTORE960(C,C1,C2,C3,C4,C5,C6,C7,C8);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul512_gf2x)(uint64_t C[16], const uint64_t A[8],
                                               const uint64_t B[8])
{
    __m128i C1,C2,C3,C4,C5,C6,C7,C8,RA,RB,CL,CH,M,MM,CM,CM1,CM2,
            M1,M2,M3,M4,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL512_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A,B,RA,RB,CL,CH,M,MM,CM,CM1,
                        CM2,M1,M2,M3,M4,one32)

    GEMSS_PSTORE1024(C,C1,C2,C3,C4,C5,C6,C7,C8);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul544_gf2x)(uint64_t C[17], const uint64_t A[9],
                                               const uint64_t B[9])
{
    __m128i C1,C2,C3,C4,C5,C6,C7,C8,C9,RA,RB,CL,CH,M,MM,CM,CM1,CM2,CM3,
            M1,M2,M3,M4,M5,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL544_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A,B,RA,RB,CL,CH,M,MM,CM,CM1,
                        CM2,CM3,M1,M2,M3,M4,M5,res1,res2,one32);

    GEMSS_PSTORE1088(C,C1,C2,C3,C4,C5,C6,C7,C8,C9);
}

void GEMSS_PREFIX_NAME(GEMSS_pmul576_gf2x)(uint64_t C[18], const uint64_t A[9],
                                               const uint64_t B[9])
{
    __m128i C1,C2,C3,C4,C5,C6,C7,C8,C9,RA,RB,CL,CH,M,MM,CM,CM1,CM2,CM3,
            M1,M2,M3,M4,M5,res1,res2,one32;
    one32=GEMSS_PSET1_32(1);

    GEMSS_PMUL576_WS_KAR_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A,B,RA,RB,CL,CH,M,MM,CM,CM1,
                        CM2,CM3,M1,M2,M3,M4,M5,res1,res2,one32);

    GEMSS_PSTORE1152(C,C1,C2,C3,C4,C5,C6,C7,C8,C9);
}
#endif


/***********************************************************************/
/***********************************************************************/
/**************************** pclmul version ***************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_PCLMUL
uint64_t GEMSS_PREFIX_NAME(GEMSS_pclmul64low_gf2x)(uint64_t A, uint64_t B)
{
    __m128i x,y;
    uint64_t C;
    GEMSS_PINIT64(x,&A);
    GEMSS_PINIT64(y,&B);
    GEMSS_PCLMUL64LOW_GF2X(C,x,y,0);
    return C;
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul64_gf2x)(uint64_t C[2], const uint64_t A[1],
                                               const uint64_t B[1])
{
    __m128i x,y,z;
    GEMSS_PINIT64(x,A);
    GEMSS_PINIT64(y,B);
    GEMSS_PCLMUL64_GF2X(C,x,y,z,0);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul96_gf2x)(uint64_t C[3], const uint64_t A[2],
                                               const uint64_t B[2])
{
    __m128i x,y,z1,z2,sum,res_low,res_high;
    GEMSS_PINIT128(x,A);
    GEMSS_PINIT128(y,B);
    GEMSS_PCLMUL96_GF2X(C,x,y,z1,z2,sum,res_low,res_high);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul128_gf2x)(uint64_t C[4], const uint64_t A[2],
                                                const uint64_t B[2])
{
    __m128i x,y,z1,z2,sum,res_low,res_high;
    GEMSS_PINIT128(x,A);
    GEMSS_PINIT128(y,B);
    GEMSS_PCLMUL128_GF2X(C,x,y,z1,z2,sum,res_low,res_high);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul160_gf2x)(uint64_t C[5], const uint64_t A[3],
                                                const uint64_t B[3])
{
    __m128i x1,x2,y1,y2,z1,z2,sum,res1,res2;
    GEMSS_PINIT192(x1,x2,A);
    GEMSS_PINIT192(y1,y2,B);
    GEMSS_PCLMUL160_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul192_gf2x)(uint64_t C[6], const uint64_t A[3],
                                                const uint64_t B[3])
{
    __m128i x1,x2,y1,y2,z1,z2,sum,res1,res2;
    GEMSS_PINIT192(x1,x2,A);
    GEMSS_PINIT192(y1,y2,B);
    GEMSS_PCLMUL192_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul224_gf2x)(uint64_t C[7], const uint64_t A[4],
                                                const uint64_t B[4])
{
    __m128i x1,x2,y1,y2,z1,z2,sum,res1,res2;
    GEMSS_PINIT256(x1,x2,A);
    GEMSS_PINIT256(y1,y2,B);
    GEMSS_PCLMUL224_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul256_gf2x)(uint64_t C[8], const uint64_t A[4],
                                                const uint64_t B[4])
{
    __m128i x1,x2,y1,y2,z1,z2,sum,res1,res2;
    GEMSS_PINIT256(x1,x2,A);
    GEMSS_PINIT256(y1,y2,B);
    GEMSS_PCLMUL256_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul288_gf2x)(uint64_t C[9], const uint64_t A[5],
                                                const uint64_t B[5])
{
    __m128i x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2;
    GEMSS_PINIT320(x1,x2,x3,A);
    GEMSS_PINIT320(y1,y2,y3,B);
    GEMSS_PCLMUL288_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul320_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                 const uint64_t B[5])
{
    __m128i x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2;
    GEMSS_PINIT320(x1,x2,x3,A);
    GEMSS_PINIT320(y1,y2,y3,B);
    GEMSS_PCLMUL320_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul352_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                 const uint64_t B[6])
{
    __m128i x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2;
    GEMSS_PINIT384(x1,x2,x3,A);
    GEMSS_PINIT384(y1,y2,y3,B);
    GEMSS_PCLMUL352_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul384_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                 const uint64_t B[6])
{
    __m128i x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2;
    GEMSS_PINIT384(x1,x2,x3,A);
    GEMSS_PINIT384(y1,y2,y3,B);
    GEMSS_PCLMUL384_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul416_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                 const uint64_t B[7])
{
    __m128i x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2;
    GEMSS_PINIT448(x1,x2,x3,x4,A);
    GEMSS_PINIT448(y1,y2,y3,y4,B);
    GEMSS_PCLMUL416_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul448_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                 const uint64_t B[7])
{
    __m128i x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2;
    GEMSS_PINIT448(x1,x2,x3,x4,A);
    GEMSS_PINIT448(y1,y2,y3,y4,B);
    GEMSS_PCLMUL448_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul480_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                 const uint64_t B[8])
{
    __m128i x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2;
    GEMSS_PINIT512(x1,x2,x3,x4,A);
    GEMSS_PINIT512(y1,y2,y3,y4,B);
    GEMSS_PCLMUL480_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul512_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                 const uint64_t B[8])
{
    __m128i x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2;
    GEMSS_PINIT512(x1,x2,x3,x4,A);
    GEMSS_PINIT512(y1,y2,y3,y4,B);
    GEMSS_PCLMUL512_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul544_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                 const uint64_t B[9])
{
    __m128i x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2;
    GEMSS_PINIT576(x1,x2,x3,x4,x5,A);
    GEMSS_PINIT576(y1,y2,y3,y4,y5,B);
    GEMSS_PCLMUL544_GF2X(C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2);
}

void GEMSS_PREFIX_NAME(GEMSS_pclmul576_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                 const uint64_t B[9])
{
    __m128i x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2;
    GEMSS_PINIT576(x1,x2,x3,x4,x5,A);
    GEMSS_PINIT576(y1,y2,y3,y4,y5,B);
    GEMSS_PCLMUL576_GF2X(C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2);
}
#endif

