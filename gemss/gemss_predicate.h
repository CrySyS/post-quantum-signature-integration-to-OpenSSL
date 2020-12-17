#ifndef _PREDICATE_H
#define _PREDICATE_H

#include "gemss_prefix_name.h"
#include "gemss_arch.h"


/* Compare two 64-bit words in constant-time */
#define GEMSS_CMP_LT_U64(a,b) \
            (((((a)>>63U)^((b)>>63U))    &((((a)>>63U)-((b)>>63U))>>63U))\
        ^    ((((a)>>63U)^((b)>>63U)^GEMSS_ONE64)\
              &((((a)&((uint64_t)0x7FFFFFFFFFFFFFFF))\
                -((b)&((uint64_t)0x7FFFFFFFFFFFFFFF)))>>63U)))

/* Compare two 32-bit words in constant-time */
#define GEMSS_CMP_LT_U32(a,b) \
            (((((a)>>31U)^((b)>>31U))    &((((a)>>31U)-((b)>>31U))>>31U))\
        ^    ((((a)>>31U)^((b)>>31U)^GEMSS_ONE32)\
              &((((a)&((uint32_t)0x7FFFFFFF))\
                -((b)&((uint32_t)0x7FFFFFFF)))>>31U)))

/* Compare two UINT in constant-time */
#define GEMSS_CMP_LT_UINT GEMSS_CONCAT(GEMSS_CMP_LT_U,GEMSS_NB_BITS_UINT)


/* Constant-time version */
int GEMSS_PREFIX_NAME(ISZERO)(const UINT* a, unsigned int size);
int GEMSS_PREFIX_NAME(ISNOTZERO)(const UINT* a, unsigned int size);
int GEMSS_PREFIX_NAME(ISONE)(const UINT* a, unsigned int size);
int GEMSS_PREFIX_NAME(GEMSS_ISEQUAL)(const UINT* a, const UINT* b, unsigned int size);
int GEMSS_PREFIX_NAME(GEMSS_CMP_LT)(const UINT* a, const UINT* b, unsigned int size);


#define GEMSS_f_ISZERO GEMSS_PREFIX_NAME(ISZERO)
#define GEMSS_f_ISNOTZERO GEMSS_PREFIX_NAME(ISNOTZERO)
#define GEMSS_f_ISONE GEMSS_PREFIX_NAME(ISONE)
#define GEMSS_f_ISEQUAL GEMSS_PREFIX_NAME(GEMSS_ISEQUAL)
#define GEMSS_f_CMP_LT GEMSS_PREFIX_NAME(GEMSS_CMP_LT)
#define GEMSS_f_CMP_GT(a,b,size) GEMSS_f_CMP_LT(b,a,size)


/* Variable-time version */
int GEMSS_PREFIX_NAME(ISZERO_NOCST)(const UINT* a, unsigned int size);
int GEMSS_PREFIX_NAME(ISONE_NOCST)(const UINT* a, unsigned int size);
int GEMSS_PREFIX_NAME(ISEQUAL_NOCST)(const UINT* a, const UINT* b, unsigned int size);
int GEMSS_PREFIX_NAME(CMP_LT_NOCST)(const UINT* a, const UINT* b, unsigned int size);


#define GEMSS_f_ISZERO_NOCST GEMSS_PREFIX_NAME(ISZERO_NOCST)
#define GEMSS_f_ISONE_NOCST GEMSS_PREFIX_NAME(ISONE_NOCST)
#define GEMSS_f_ISEQUAL_NOCST GEMSS_PREFIX_NAME(ISEQUAL_NOCST)
#define GEMSS_f_CMP_LT_NOCST GEMSS_PREFIX_NAME(CMP_LT_NOCST)
#define GEMSS_f_CMP_GT_NOCST(a,b,size) GEMSS_f_CMP_LT_NOCST(b,a,size)


/* Inlined version */
/* Equal to 0 */
#define GEMSS_ISZERO1_NOCST(a) ((a)[0]==0)
#define GEMSS_ISZERO2_NOCST(a) (GEMSS_ISZERO1_NOCST(a)&&((a)[1]==0))
#define GEMSS_ISZERO3_NOCST(a) (GEMSS_ISZERO2_NOCST(a)&&((a)[2]==0))
#define GEMSS_ISZERO4_NOCST(a) (GEMSS_ISZERO3_NOCST(a)&&((a)[3]==0))
#define GEMSS_ISZERO5_NOCST(a) (GEMSS_ISZERO4_NOCST(a)&&((a)[4]==0))
#define GEMSS_ISZERO6_NOCST(a) (GEMSS_ISZERO5_NOCST(a)&&((a)[5]==0))
#define GEMSS_ISZERO7_NOCST(a) (GEMSS_ISZERO6_NOCST(a)&&((a)[6]==0))
#define GEMSS_ISZERO8_NOCST(a) (GEMSS_ISZERO7_NOCST(a)&&((a)[7]==0))
#define GEMSS_ISZERO9_NOCST(a) (GEMSS_ISZERO8_NOCST(a)&&((a)[8]==0))


/* Equal to 1 */
#define GEMSS_ISONE1_NOCST(a) ((a)[0]==1)
#define GEMSS_ISONE2_NOCST(a) (GEMSS_ISONE1_NOCST(a)&&((a)[1]==0))
#define GEMSS_ISONE3_NOCST(a) (GEMSS_ISONE2_NOCST(a)&&((a)[2]==0))
#define GEMSS_ISONE4_NOCST(a) (GEMSS_ISONE3_NOCST(a)&&((a)[3]==0))
#define GEMSS_ISONE5_NOCST(a) (GEMSS_ISONE4_NOCST(a)&&((a)[4]==0))
#define GEMSS_ISONE6_NOCST(a) (GEMSS_ISONE5_NOCST(a)&&((a)[5]==0))
#define GEMSS_ISONE7_NOCST(a) (GEMSS_ISONE6_NOCST(a)&&((a)[6]==0))
#define GEMSS_ISONE8_NOCST(a) (GEMSS_ISONE7_NOCST(a)&&((a)[7]==0))
#define GEMSS_ISONE9_NOCST(a) (GEMSS_ISONE8_NOCST(a)&&((a)[8]==0))


/* Equality */
#define GEMSS_ISEQUAL1_NOCST(a,b) ((a)[0]==(b)[0])
#define GEMSS_ISEQUAL2_NOCST(a,b) (GEMSS_ISEQUAL1_NOCST(a,b)&&((a)[1]==(b)[1]))
#define GEMSS_ISEQUAL3_NOCST(a,b) (GEMSS_ISEQUAL2_NOCST(a,b)&&((a)[2]==(b)[2]))
#define GEMSS_ISEQUAL4_NOCST(a,b) (GEMSS_ISEQUAL3_NOCST(a,b)&&((a)[3]==(b)[3]))
#define GEMSS_ISEQUAL5_NOCST(a,b) (GEMSS_ISEQUAL4_NOCST(a,b)&&((a)[4]==(b)[4]))
#define GEMSS_ISEQUAL6_NOCST(a,b) (GEMSS_ISEQUAL5_NOCST(a,b)&&((a)[5]==(b)[5]))
#define GEMSS_ISEQUAL7_NOCST(a,b) (GEMSS_ISEQUAL6_NOCST(a,b)&&((a)[6]==(b)[6]))
#define GEMSS_ISEQUAL8_NOCST(a,b) (GEMSS_ISEQUAL7_NOCST(a,b)&&((a)[7]==(b)[7]))
#define GEMSS_ISEQUAL9_NOCST(a,b) (GEMSS_ISEQUAL8_NOCST(a,b)&&((a)[8]==(b)[8]))


/* Comparison, less than */
#define GEMSS_CMP_LT1_NOCST(a,b) ((a)[0]<(b)[0])
#define GEMSS_CMP_LT2_NOCST(a,b) (((a)[1]==(b)[1])?GEMSS_CMP_LT1_NOCST(a,b)\
                                              :((a)[1]<(b)[1]))
#define GEMSS_CMP_LT3_NOCST(a,b) (((a)[2]==(b)[2])?GEMSS_CMP_LT2_NOCST(a,b)\
                                              :((a)[2]<(b)[2]))
#define GEMSS_CMP_LT4_NOCST(a,b) (((a)[3]==(b)[3])?GEMSS_CMP_LT3_NOCST(a,b)\
                                              :((a)[3]<(b)[3]))
#define GEMSS_CMP_LT5_NOCST(a,b) (((a)[4]==(b)[4])?GEMSS_CMP_LT4_NOCST(a,b)\
                                              :((a)[4]<(b)[4]))
#define GEMSS_CMP_LT6_NOCST(a,b) (((a)[5]==(b)[5])?GEMSS_CMP_LT5_NOCST(a,b)\
                                              :((a)[5]<(b)[5]))
#define GEMSS_CMP_LT7_NOCST(a,b) (((a)[6]==(b)[6])?GEMSS_CMP_LT6_NOCST(a,b)\
                                              :((a)[6]<(b)[6]))
#define GEMSS_CMP_LT8_NOCST(a,b) (((a)[7]==(b)[7])?GEMSS_CMP_LT7_NOCST(a,b)\
                                              :((a)[7]<(b)[7]))
#define GEMSS_CMP_LT9_NOCST(a,b) (((a)[8]==(b)[8])?GEMSS_CMP_LT8_NOCST(a,b)\
                                              :((a)[8]<(b)[8]))


#endif

