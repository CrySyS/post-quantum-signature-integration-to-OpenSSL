#include "gemss_sqr_gf2x.h"
#include "gemss_simd.h"

/* C=A*A in GF(2)[x] for each function */

/***********************************************************************/
/***********************************************************************/
/********************** version without vectorization ******************/
/***********************************************************************/
/***********************************************************************/


uint64_t GEMSS_PREFIX_NAME(GEMSS_sqr32_no_simd_gf2x)(uint64_t A)
{
    uint64_t C;
    GEMSS_SQR32_NO_SIMD_GF2X(C,A);
    return C;
}

uint64_t GEMSS_PREFIX_NAME(GEMSS_sqr64low_no_simd_gf2x)(uint64_t A)
{
    uint64_t C;
    GEMSS_SQR64LOW_NO_SIMD_GF2X(C,A);
    return C;
}


/***********************************************************************/
/***********************************************************************/
/*************************** sse2 version ******************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_SSE2
uint64_t GEMSS_PREFIX_NAME(GEMSS_psqr64low_gf2x)(uint64_t A)
{
    __m128i A1,C1,RA,R1;
    uint64_t C;
    A1=GEMSS_PSETL_64(A);

    GEMSS_PSQR64_GF2X(C1,A1,RA,R1);

    GEMSS_PCVT_64(C,C1);
    return C;
}

void GEMSS_PREFIX_NAME(GEMSS_psqr64_gf2x)(uint64_t C[2], const uint64_t A[1])
{
    __m128i A1,C1,RA,R1;
    GEMSS_PINIT64(A1,A);

    GEMSS_PSQR64_GF2X(C1,A1,RA,R1);

    GEMSS_PSTORE128(C,C1);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr96_gf2x)(uint64_t C[3], const uint64_t A[2])
{
    __m128i A1,C1,C2,RA,R1;
    GEMSS_PINIT128(A1,A);

    GEMSS_PSQR128_GF2X(C1,C2,A1,RA,R1);

    GEMSS_PSTORE192(C,C1,C2);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr128_gf2x)(uint64_t C[4], const uint64_t A[2])
{
    __m128i A1,C1,C2,RA,R1;
    GEMSS_PINIT128(A1,A);

    GEMSS_PSQR128_GF2X(C1,C2,A1,RA,R1);

    GEMSS_PSTORE256(C,C1,C2);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr160_gf2x)(uint64_t C[5], const uint64_t A[3])
{
    __m128i A1,A2,C1,C2,C3,RA,R1;
    GEMSS_PINIT192(A1,A2,A);

    GEMSS_PSQR192_GF2X(C1,C2,C3,A1,A2,RA,R1);

    GEMSS_PSTORE320(C,C1,C2,C3);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr192_gf2x)(uint64_t C[6], const uint64_t A[3])
{
    __m128i A1,A2,C1,C2,C3,RA,R1;
    GEMSS_PINIT192(A1,A2,A);

    GEMSS_PSQR192_GF2X(C1,C2,C3,A1,A2,RA,R1);

    GEMSS_PSTORE384(C,C1,C2,C3);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr224_gf2x)(uint64_t C[7], const uint64_t A[4])
{
    __m128i A1,A2,C1,C2,C3,C4,RA,R1;
    GEMSS_PINIT256(A1,A2,A);

    GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1);

    GEMSS_PSTORE448(C,C1,C2,C3,C4);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr256_gf2x)(uint64_t C[8], const uint64_t A[4])
{
    __m128i A1,A2,C1,C2,C3,C4,RA,R1;
    GEMSS_PINIT256(A1,A2,A);

    GEMSS_PSQR256_GF2X(C1,C2,C3,C4,A1,A2,RA,R1);

    GEMSS_PSTORE512(C,C1,C2,C3,C4);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr288_gf2x)(uint64_t C[9], const uint64_t A[5])
{
    __m128i A1,A2,A3,C1,C2,C3,C4,C5,RA,R1;
    GEMSS_PINIT320(A1,A2,A3,A);

    GEMSS_PSQR320_GF2X(C1,C2,C3,C4,C5,A1,A2,A3,RA,R1);

    GEMSS_PSTORE576(C,C1,C2,C3,C4,C5);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr320_gf2x)(uint64_t C[10], const uint64_t A[5])
{
    __m128i A1,A2,A3,C1,C2,C3,C4,C5,RA,R1;
    GEMSS_PINIT320(A1,A2,A3,A);

    GEMSS_PSQR320_GF2X(C1,C2,C3,C4,C5,A1,A2,A3,RA,R1);

    GEMSS_PSTORE640(C,C1,C2,C3,C4,C5);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr352_gf2x)(uint64_t C[11], const uint64_t A[6])
{
    __m128i A1,A2,A3,C1,C2,C3,C4,C5,C6,RA,R1;
    GEMSS_PINIT384(A1,A2,A3,A);

    GEMSS_PSQR384_GF2X(C1,C2,C3,C4,C5,C6,A1,A2,A3,RA,R1);

    GEMSS_PSTORE704(C,C1,C2,C3,C4,C5,C6);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr384_gf2x)(uint64_t C[12], const uint64_t A[6])
{
    __m128i A1,A2,A3,C1,C2,C3,C4,C5,C6,RA,R1;
    GEMSS_PINIT384(A1,A2,A3,A);

    GEMSS_PSQR384_GF2X(C1,C2,C3,C4,C5,C6,A1,A2,A3,RA,R1);

    GEMSS_PSTORE768(C,C1,C2,C3,C4,C5,C6);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr416_gf2x)(uint64_t C[13], const uint64_t A[7])
{
    __m128i A1,A2,A3,A4,C1,C2,C3,C4,C5,C6,C7,RA,R1;
    GEMSS_PINIT448(A1,A2,A3,A4,A);

    GEMSS_PSQR448_GF2X(C1,C2,C3,C4,C5,C6,C7,A1,A2,A3,A4,RA,R1);

    GEMSS_PSTORE832(C,C1,C2,C3,C4,C5,C6,C7);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr448_gf2x)(uint64_t C[14], const uint64_t A[7])
{
    __m128i A1,A2,A3,A4,C1,C2,C3,C4,C5,C6,C7,RA,R1;
    GEMSS_PINIT448(A1,A2,A3,A4,A);

    GEMSS_PSQR448_GF2X(C1,C2,C3,C4,C5,C6,C7,A1,A2,A3,A4,RA,R1);

    GEMSS_PSTORE896(C,C1,C2,C3,C4,C5,C6,C7);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr480_gf2x)(uint64_t C[15], const uint64_t A[8])
{
    __m128i A1,A2,A3,A4,C1,C2,C3,C4,C5,C6,C7,C8,RA,R1;
    GEMSS_PINIT512(A1,A2,A3,A4,A);

    GEMSS_PSQR512_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A1,A2,A3,A4,RA,R1);

    GEMSS_PSTORE960(C,C1,C2,C3,C4,C5,C6,C7,C8);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr512_gf2x)(uint64_t C[16], const uint64_t A[8])
{
    __m128i A1,A2,A3,A4,C1,C2,C3,C4,C5,C6,C7,C8,RA,R1;
    GEMSS_PINIT512(A1,A2,A3,A4,A);

    GEMSS_PSQR512_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,A1,A2,A3,A4,RA,R1);

    GEMSS_PSTORE1024(C,C1,C2,C3,C4,C5,C6,C7,C8);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr544_gf2x)(uint64_t C[17], const uint64_t A[9])
{
    __m128i A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6,C7,C8,C9,RA,R1;
    GEMSS_PINIT576(A1,A2,A3,A4,A5,A);

    GEMSS_PSQR576_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A1,A2,A3,A4,A5,RA,R1);

    GEMSS_PSTORE1088(C,C1,C2,C3,C4,C5,C6,C7,C8,C9);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr576_gf2x)(uint64_t C[18], const uint64_t A[9])
{
    __m128i A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6,C7,C8,C9,RA,R1;
    GEMSS_PINIT576(A1,A2,A3,A4,A5,A);

    GEMSS_PSQR576_GF2X(C1,C2,C3,C4,C5,C6,C7,C8,C9,A1,A2,A3,A4,A5,RA,R1);

    GEMSS_PSTORE1152(C,C1,C2,C3,C4,C5,C6,C7,C8,C9);
}
#endif


/***********************************************************************/
/***********************************************************************/
/*************************** shuffle version ***************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_SSSE3
uint64_t GEMSS_PREFIX_NAME(GEMSS_psqr64low_shuffle_gf2x)(uint64_t A)
{
    __m128i M,T,A1,E1;
    uint64_t C;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    A1=GEMSS_PSETL_64(A);

    GEMSS_PSQR64_SHUFFLE_GF2X(E1,A1,M,T);

    GEMSS_PCVT_64(C,E1);
    return C;
}

void GEMSS_PREFIX_NAME(GEMSS_psqr64_shuffle_gf2x)(uint64_t C[2], const uint64_t A[1])
{
    __m128i M,T,A1,E1;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT64(A1,A);

    GEMSS_PSQR64_SHUFFLE_GF2X(E1,A1,M,T);

    GEMSS_PSTORE128(C,E1);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr96_shuffle_gf2x)(uint64_t C[3], const uint64_t A[2])
{
    __m128i M,T,A1,E1,E2;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT128(A1,A);

    GEMSS_PSQR128_SHUFFLE_GF2X(E1,E2,A1,M,T);

    GEMSS_PSTORE192(C,E1,E2);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr128_shuffle_gf2x)(uint64_t C[4], const uint64_t A[2])
{
    __m128i M,T,A1,E1,E2;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT128(A1,A);

    GEMSS_PSQR128_SHUFFLE_GF2X(E1,E2,A1,M,T);

    GEMSS_PSTORE256(C,E1,E2);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr160_shuffle_gf2x)(uint64_t C[5], const uint64_t A[3])
{
    __m128i M,T,A1,A2,E1,E2,E3;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT192(A1,A2,A);

    GEMSS_PSQR192_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T);

    GEMSS_PSTORE320(C,E1,E2,E3);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr192_shuffle_gf2x)(uint64_t C[6], const uint64_t A[3])
{
    __m128i M,T,A1,A2,E1,E2,E3;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT192(A1,A2,A);

    GEMSS_PSQR192_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T);

    GEMSS_PSTORE384(C,E1,E2,E3);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr224_shuffle_gf2x)(uint64_t C[7], const uint64_t A[4])
{
    __m128i M,T,A1,A2,E1,E2,E3,E4;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT256(A1,A2,A);

    GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);

    GEMSS_PSTORE448(C,E1,E2,E3,E4);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr256_shuffle_gf2x)(uint64_t C[8], const uint64_t A[4])
{
    __m128i M,T,A1,A2,E1,E2,E3,E4;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT256(A1,A2,A);

    GEMSS_PSQR256_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);

    GEMSS_PSTORE512(C,E1,E2,E3,E4);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr288_shuffle_gf2x)(uint64_t C[9], const uint64_t A[5])
{
    __m128i M,T,A1,A2,A3,E1,E2,E3,E4,E5;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT320(A1,A2,A3,A);

    GEMSS_PSQR320_SHUFFLE_GF2X(E1,E2,E3,E4,E5,A1,A2,A3,M,T);

    GEMSS_PSTORE576(C,E1,E2,E3,E4,E5);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr320_shuffle_gf2x)(uint64_t C[10], const uint64_t A[5])
{
    __m128i M,T,A1,A2,A3,E1,E2,E3,E4,E5;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT320(A1,A2,A3,A);

    GEMSS_PSQR320_SHUFFLE_GF2X(E1,E2,E3,E4,E5,A1,A2,A3,M,T);

    GEMSS_PSTORE640(C,E1,E2,E3,E4,E5);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr352_shuffle_gf2x)(uint64_t C[11], const uint64_t A[6])
{
    __m128i M,T,A1,A2,A3,E1,E2,E3,E4,E5,E6;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT384(A1,A2,A3,A);

    GEMSS_PSQR384_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,A1,A2,A3,M,T);

    GEMSS_PSTORE704(C,E1,E2,E3,E4,E5,E6);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr384_shuffle_gf2x)(uint64_t C[12], const uint64_t A[6])
{
    __m128i M,T,A1,A2,A3,E1,E2,E3,E4,E5,E6;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT384(A1,A2,A3,A);

    GEMSS_PSQR384_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,A1,A2,A3,M,T);

    GEMSS_PSTORE768(C,E1,E2,E3,E4,E5,E6);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr416_shuffle_gf2x)(uint64_t C[13], const uint64_t A[7])
{
    __m128i M,T,A1,A2,A3,A4,E1,E2,E3,E4,E5,E6,E7;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT448(A1,A2,A3,A4,A);

    GEMSS_PSQR448_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,A1,A2,A3,A4,M,T);

    GEMSS_PSTORE832(C,E1,E2,E3,E4,E5,E6,E7);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr448_shuffle_gf2x)(uint64_t C[14], const uint64_t A[7])
{
    __m128i M,T,A1,A2,A3,A4,E1,E2,E3,E4,E5,E6,E7;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT448(A1,A2,A3,A4,A);

    GEMSS_PSQR448_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,A1,A2,A3,A4,M,T);

    GEMSS_PSTORE896(C,E1,E2,E3,E4,E5,E6,E7);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr480_shuffle_gf2x)(uint64_t C[15], const uint64_t A[8])
{
    __m128i M,T,A1,A2,A3,A4,E1,E2,E3,E4,E5,E6,E7,E8;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT512(A1,A2,A3,A4,A);

    GEMSS_PSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,A1,A2,A3,A4,M,T);

    GEMSS_PSTORE960(C,E1,E2,E3,E4,E5,E6,E7,E8);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr512_shuffle_gf2x)(uint64_t C[16], const uint64_t A[8])
{
    __m128i M,T,A1,A2,A3,A4,E1,E2,E3,E4,E5,E6,E7,E8;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT512(A1,A2,A3,A4,A);

    GEMSS_PSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,A1,A2,A3,A4,M,T);

    GEMSS_PSTORE1024(C,E1,E2,E3,E4,E5,E6,E7,E8);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr544_shuffle_gf2x)(uint64_t C[17], const uint64_t A[9])
{
    __m128i M,T,A1,A2,A3,A4,A5,E1,E2,E3,E4,E5,E6,E7,E8,E9;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT576(A1,A2,A3,A4,A5,A);

    GEMSS_PSQR576_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,E9,A1,A2,A3,A4,A5,M,T);

    GEMSS_PSTORE1088(C,E1,E2,E3,E4,E5,E6,E7,E8,E9);
}

void GEMSS_PREFIX_NAME(GEMSS_psqr576_shuffle_gf2x)(uint64_t C[18], const uint64_t A[9])
{
    __m128i M,T,A1,A2,A3,A4,A5,E1,E2,E3,E4,E5,E6,E7,E8,E9;
    GEMSS_PSQR_INIT_SHUFFLE_GF2X(M,T);
    GEMSS_PINIT576(A1,A2,A3,A4,A5,A);

    GEMSS_PSQR576_SHUFFLE_GF2X(E1,E2,E3,E4,E5,E6,E7,E8,E9,A1,A2,A3,A4,A5,M,T);

    GEMSS_PSTORE1152(C,E1,E2,E3,E4,E5,E6,E7,E8,E9);
}
#endif


#ifdef GEMSS_ENABLED_AVX2
uint64_t GEMSS_PREFIX_NAME(GEMSS_vpsqr64low_shuffle_gf2x)(uint64_t A)
{
    __m256i M,T,A1,E1;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    A1=GEMSS_VPSETL_64(A);
    GEMSS_VPSQR64_SHUFFLE_GF2X(E1,A1,M,T);

    return GEMSS_VPEXTRACT64(E1,0);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr64_shuffle_gf2x)(uint64_t C[2], const uint64_t A[1])
{
    __m256i M,T,A1,E1;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT64(A1,A);
    GEMSS_VPSQR64_SHUFFLE_GF2X(E1,A1,M,T);

    GEMSS_VPSTORE128(C,E1);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr96_shuffle_gf2x)(uint64_t C[3], const uint64_t A[2])
{
    __m256i M,T,A1,E1;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT128(A1,A);
    GEMSS_VPSQR128_SHUFFLE_GF2X(E1,A1,M,T);

    GEMSS_VPSTORE192(C,E1);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr128_shuffle_gf2x)(uint64_t C[4], const uint64_t A[2])
{
    __m256i M,T,A1,E1;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT128(A1,A);
    GEMSS_VPSQR128_SHUFFLE_GF2X(E1,A1,M,T);

    GEMSS_VPSTORE256(C,E1);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr160_shuffle_gf2x)(uint64_t C[5], const uint64_t A[3])
{
    __m256i M,T,A1,E1,E2;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT192(A1,A);
    GEMSS_VPSQR192_SHUFFLE_GF2X(E1,E2,A1,M,T);

    GEMSS_VPSTORE320(C,E1,E2);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr192_shuffle_gf2x)(uint64_t C[6], const uint64_t A[3])
{
    __m256i M,T,A1,E1,E2;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT192(A1,A);
    GEMSS_VPSQR192_SHUFFLE_GF2X(E1,E2,A1,M,T);

    GEMSS_VPSTORE384(C,E1,E2);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr224_shuffle_gf2x)(uint64_t C[7], const uint64_t A[4])
{
    __m256i M,T,A1,E1,E2;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT256(A1,A);
    GEMSS_VPSQR256_SHUFFLE_GF2X(E1,E2,A1,M,T);

    GEMSS_VPSTORE448(C,E1,E2);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr256_shuffle_gf2x)(uint64_t C[8], const uint64_t A[4])
{
    __m256i M,T,A1,E1,E2;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT256(A1,A);
    GEMSS_VPSQR256_SHUFFLE_GF2X(E1,E2,A1,M,T);

    GEMSS_VPSTORE512(C,E1,E2);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr288_shuffle_gf2x)(uint64_t C[9], const uint64_t A[5])
{
    __m256i M,T,A1,A2,E1,E2,E3;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT320(A1,A2,A);
    GEMSS_VPSQR320_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T);

    GEMSS_VPSTORE576(C,E1,E2,E3);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr320_shuffle_gf2x)(uint64_t C[10], const uint64_t A[5])
{
    __m256i M,T,A1,A2,E1,E2,E3;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT320(A1,A2,A);
    GEMSS_VPSQR320_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T);

    GEMSS_VPSTORE640(C,E1,E2,E3);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr352_shuffle_gf2x)(uint64_t C[11], const uint64_t A[6])
{
    __m256i M,T,A1,A2,E1,E2,E3;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT384(A1,A2,A);
    GEMSS_VPSQR384_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T);

    GEMSS_VPSTORE704(C,E1,E2,E3);
}


void GEMSS_PREFIX_NAME(GEMSS_vpsqr384_shuffle_gf2x)(uint64_t C[12], const uint64_t A[6])
{
    __m256i M,T,A1,A2,E1,E2,E3;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT384(A1,A2,A);
    GEMSS_VPSQR384_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T);

    GEMSS_VPSTORE768(C,E1,E2,E3);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr416_shuffle_gf2x)(uint64_t C[13], const uint64_t A[7])
{
    __m256i M,T,A1,A2,E1,E2,E3,E4;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT448(A1,A2,A);
    GEMSS_VPSQR448_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);

    GEMSS_VPSTORE832(C,E1,E2,E3,E4);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr448_shuffle_gf2x)(uint64_t C[14], const uint64_t A[7])
{
    __m256i M,T,A1,A2,E1,E2,E3,E4;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT448(A1,A2,A);
    GEMSS_VPSQR448_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);

    GEMSS_VPSTORE896(C,E1,E2,E3,E4);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr480_shuffle_gf2x)(uint64_t C[15], const uint64_t A[8])
{
    __m256i M,T,A1,A2,E1,E2,E3,E4;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT512(A1,A2,A);
    GEMSS_VPSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);

    GEMSS_VPSTORE960(C,E1,E2,E3,E4);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr512_shuffle_gf2x)(uint64_t C[16], const uint64_t A[8])
{
    __m256i M,T,A1,A2,E1,E2,E3,E4;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT512(A1,A2,A);
    GEMSS_VPSQR512_SHUFFLE_GF2X(E1,E2,E3,E4,A1,A2,M,T);

    GEMSS_VPSTORE1024(C,E1,E2,E3,E4);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr544_shuffle_gf2x)(uint64_t C[17], const uint64_t A[9])
{
    __m256i M,T,A1,A2,A3,E1,E2,E3,E4,E5;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT576(A1,A2,A3,A);
    GEMSS_VPSQR576_SHUFFLE_GF2X(E1,E2,E3,E4,E5,A1,A2,A3,M,T);

    GEMSS_VPSTORE1088(C,E1,E2,E3,E4,E5);
}

void GEMSS_PREFIX_NAME(GEMSS_vpsqr576_shuffle_gf2x)(uint64_t C[18], const uint64_t A[9])
{
    __m256i M,T,A1,A2,A3,E1,E2,E3,E4,E5;
    GEMSS_VPSQR_INIT_SHUFFLE_GF2X(M,T);

    GEMSS_VPINIT576(A1,A2,A3,A);
    GEMSS_VPSQR576_SHUFFLE_GF2X(E1,E2,E3,E4,E5,A1,A2,A3,M,T);

    GEMSS_VPSTORE1152(C,E1,E2,E3,E4,E5);
}
#endif


/***********************************************************************/
/***********************************************************************/
/**************************** pclmul version ***************************/
/***********************************************************************/
/***********************************************************************/


#ifdef GEMSS_ENABLED_PCLMUL


/***********************************************************************/
/***********************************************************************/
/********************** store at the end version ***********************/
/***********************************************************************/
/***********************************************************************/


uint64_t GEMSS_PREFIX_NAME(GEMSS_sqr64low_pclmul_gf2x)(uint64_t A) 
{
    __m128i x;
    uint64_t C;
    GEMSS_PINIT64(x,&A);

    GEMSS_PCVT_64(C,GEMSS_PCLMUL(x,x,0));
    return C;
}

void GEMSS_PREFIX_NAME(GEMSS_sqr64_pclmul_gf2x)(uint64_t C[2], const uint64_t A[1])
{
    __m128i x,z;
    GEMSS_PINIT64(x,A);

    GEMSS_SQR64_WS_PCLMUL_GF2X(z,x,0);

    GEMSS_PSTORE128(C,z);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr96_pclmul_gf2x)(uint64_t C[3], const uint64_t A[2])
{
    __m128i x,z1,z2;
    GEMSS_PINIT128(x,A);

    GEMSS_SQR128_WS_PCLMUL_GF2X(z1,z2,x);

    GEMSS_PSTORE192(C,z1,z2);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr128_pclmul_gf2x)(uint64_t C[4], const uint64_t A[2])
{
    __m128i x,z1,z2;
    GEMSS_PINIT128(x,A);

    GEMSS_SQR128_WS_PCLMUL_GF2X(z1,z2,x);

    GEMSS_PSTORE256(C,z1,z2);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr160_pclmul_gf2x)(uint64_t C[5], const uint64_t A[3])
{
    __m128i x1,x2,z1,z2,z3;
    GEMSS_PINIT192(x1,x2,A);

    GEMSS_SQR192_WS_PCLMUL_GF2X(z1,z2,z3,x1,x2);

    GEMSS_PSTORE320(C,z1,z2,z3);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr192_pclmul_gf2x)(uint64_t C[6], const uint64_t A[3])
{
    __m128i x1,x2,z1,z2,z3;
    GEMSS_PINIT192(x1,x2,A);

    GEMSS_SQR192_WS_PCLMUL_GF2X(z1,z2,z3,x1,x2);

    GEMSS_PSTORE384(C,z1,z2,z3);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr224_pclmul_gf2x)(uint64_t C[7], const uint64_t A[4])
{
    __m128i x1,x2,z1,z2,z3,z4;
    GEMSS_PINIT256(x1,x2,A);

    GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2);

    GEMSS_PSTORE448(C,z1,z2,z3,z4);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr256_pclmul_gf2x)(uint64_t C[8], const uint64_t A[4])
{
    __m128i x1,x2,z1,z2,z3,z4;
    GEMSS_PINIT256(x1,x2,A);

    GEMSS_SQR256_WS_PCLMUL_GF2X(z1,z2,z3,z4,x1,x2);

    GEMSS_PSTORE512(C,z1,z2,z3,z4);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr288_pclmul_gf2x)(uint64_t C[9], const uint64_t A[5])
{
    __m128i x1,x2,x3,z1,z2,z3,z4,z5;
    GEMSS_PINIT320(x1,x2,x3,A);

    GEMSS_SQR320_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,x1,x2,x3);

    GEMSS_PSTORE576(C,z1,z2,z3,z4,z5);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr320_pclmul_gf2x)(uint64_t C[10], const uint64_t A[5])
{
    __m128i x1,x2,x3,z1,z2,z3,z4,z5;
    GEMSS_PINIT320(x1,x2,x3,A);

    GEMSS_SQR320_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,x1,x2,x3);

    GEMSS_PSTORE640(C,z1,z2,z3,z4,z5);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr352_pclmul_gf2x)(uint64_t C[11], const uint64_t A[6])
{
    __m128i x1,x2,x3,z1,z2,z3,z4,z5,z6;
    GEMSS_PINIT384(x1,x2,x3,A);

    GEMSS_SQR384_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,x1,x2,x3);

    GEMSS_PSTORE704(C,z1,z2,z3,z4,z5,z6);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr384_pclmul_gf2x)(uint64_t C[12], const uint64_t A[6])
{
    __m128i x1,x2,x3,z1,z2,z3,z4,z5,z6;
    GEMSS_PINIT384(x1,x2,x3,A);

    GEMSS_SQR384_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,x1,x2,x3);

    GEMSS_PSTORE768(C,z1,z2,z3,z4,z5,z6);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr416_pclmul_gf2x)(uint64_t C[13], const uint64_t A[7])
{
    __m128i x1,x2,x3,x4,z1,z2,z3,z4,z5,z6,z7;
    GEMSS_PINIT448(x1,x2,x3,x4,A);

    GEMSS_SQR448_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,x1,x2,x3,x4);

    GEMSS_PSTORE832(C,z1,z2,z3,z4,z5,z6,z7);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr448_pclmul_gf2x)(uint64_t C[14], const uint64_t A[7])
{
    __m128i x1,x2,x3,x4,z1,z2,z3,z4,z5,z6,z7;
    GEMSS_PINIT448(x1,x2,x3,x4,A);

    GEMSS_SQR448_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,x1,x2,x3,x4);

    GEMSS_PSTORE896(C,z1,z2,z3,z4,z5,z6,z7);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr480_pclmul_gf2x)(uint64_t C[15], const uint64_t A[8])
{
    __m128i x1,x2,x3,x4,z1,z2,z3,z4,z5,z6,z7,z8;
    GEMSS_PINIT512(x1,x2,x3,x4,A);

    GEMSS_SQR512_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,x1,x2,x3,x4);

    GEMSS_PSTORE960(C,z1,z2,z3,z4,z5,z6,z7,z8);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr512_pclmul_gf2x)(uint64_t C[16], const uint64_t A[8])
{
    __m128i x1,x2,x3,x4,z1,z2,z3,z4,z5,z6,z7,z8;
    GEMSS_PINIT512(x1,x2,x3,x4,A);

    GEMSS_SQR512_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,x1,x2,x3,x4);

    GEMSS_PSTORE1024(C,z1,z2,z3,z4,z5,z6,z7,z8);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr544_pclmul_gf2x)(uint64_t C[17], const uint64_t A[9])
{
    __m128i x1,x2,x3,x4,x5,z1,z2,z3,z4,z5,z6,z7,z8,z9;
    GEMSS_PINIT576(x1,x2,x3,x4,x5,A);

    GEMSS_SQR576_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,z9,x1,x2,x3,x4,x5);

    GEMSS_PSTORE1088(C,z1,z2,z3,z4,z5,z6,z7,z8,z9);
}

void GEMSS_PREFIX_NAME(GEMSS_sqr576_pclmul_gf2x)(uint64_t C[18], const uint64_t A[9])
{
    __m128i x1,x2,x3,x4,x5,z1,z2,z3,z4,z5,z6,z7,z8,z9;
    GEMSS_PINIT576(x1,x2,x3,x4,x5,A);

    GEMSS_SQR576_WS_PCLMUL_GF2X(z1,z2,z3,z4,z5,z6,z7,z8,z9,x1,x2,x3,x4,x5);

    GEMSS_PSTORE1152(C,z1,z2,z3,z4,z5,z6,z7,z8,z9);
}
#endif

