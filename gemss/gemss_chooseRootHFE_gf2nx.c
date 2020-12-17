#include "gemss_chooseRootHFE_gf2nx.h"

#ifndef GEMSS_UNIQUE_ROOT


#include <stdlib.h>
#include "gemss_tools_gf2n.h"
#include "gemss_add_gf2n.h"
#include "gemss_findRoots_gf2nx.h"

#if (!GEMSS_QUARTZ_ROOT)
#include "gemss_sort_gf2n.h"
#endif

#if (GEMSS_QUARTZ_ROOT||GEMSS_DETERMINIST_ROOT)
#include "gemss_hash.h"
#endif


/**
 * @brief   Find the roots of a monic GEMSS_HFE polynomial, then choose one.
 * @param[in]   F   A monic GEMSS_HFE polynomial in GF(2^n)[X] stored with a sparse
 * representation.
 * @param[in]   U   An element of GF(2^n).
 * @param[out]  root    An element of GF(2^n), one of the root of (F.poly-U).
 * @return  The number of roots of (F.poly-U), without the multiplicity.
 * @remark  Requirement: F.poly is monic.
 * @remark  Requirement: F.L must be initialized with GEMSS_initListDifferences_gf2nx.
 * @remark  A part of the implementation is not in constant-time.
 */
int GEMSS_PREFIX_NAME(GEMSS_chooseRootHFE_gf2nx)(gf2n root,
                                     const complete_sparse_monic_gf2nx F,
                                     cst_gf2n U)
{
    #if (GEMSS_HFEDeg==1)
        GEMSS_add_gf2n(root,F.poly,U);
        return 1;
    #else

        #if GEMSS_DETERMINIST_ROOT
            UINT hash[GEMSS_SIZE_DIGEST_UINT];
        #elif GEMSS_QUARTZ_ROOT
            UINT* hash;
            unsigned int j,i,ind=0;
        #endif

        vec_gf2n roots;
        int l;

        l=GEMSS_findRootsHFE_gf2nx(&roots,F,U);

        if(!l)
        {
            /* Zero root */
            return 0;
        } else
        {
            if(l==1)
            {
                /* One root */
                GEMSS_copy_gf2n(root,roots);
            } else
            {
                /* Several roots */
                #if GEMSS_QUARTZ_ROOT
                    hash=(UINT*)malloc(l*GEMSS_SIZE_DIGEST_UINT*sizeof(UINT));

                    /* We hash each root */
                    for(i=0;i<l;++i)
                    {
                        GEMSS_HASH((unsigned char*)(hash+i*GEMSS_SIZE_DIGEST_UINT),
                             (unsigned char*)(roots+i*GEMSS_NB_WORD_GFqn),
                             GEMSS_NB_BYTES_GFqn);
                    }

                    /* We search the smallest hash (seen as an integer) */
                    for(i=1;i<l;++i)
                    {
                        j=0;
                        while((j<GEMSS_SIZE_DIGEST_UINT)&&
                              (hash[ind*GEMSS_SIZE_DIGEST_UINT+j]==
                               hash[i*GEMSS_SIZE_DIGEST_UINT+j]))
                        {
                            ++j;
                        }
                        if((j<GEMSS_SIZE_DIGEST_UINT)&&
                           (hash[ind*GEMSS_SIZE_DIGEST_UINT+j]>
                            hash[i*GEMSS_SIZE_DIGEST_UINT+j]))
                        {
                            ind=i;
                        }
                    }

                    /* We choose the corresponding root */
                    GEMSS_copy_gf2n(root,roots+ind*GEMSS_NB_WORD_GFqn);

                    free(hash);
                #else

                    /* Sort the roots */
                    GEMSS_sort_gf2n(roots,l);

                    #if GEMSS_FIRST_ROOT
                        /* Choose the first root */
                        GEMSS_copy_gf2n(root,roots);
                    #elif GEMSS_DETERMINIST_ROOT
                        /* Choose a root with a determinist hash */
                        GEMSS_HASH((unsigned char*)hash,
                             (unsigned char*)U,GEMSS_NB_BYTES_GFqn);
                        GEMSS_copy_gf2n(root,roots+(hash[0]%l)*GEMSS_NB_WORD_GFqn);
                    #endif
                #endif
            }
            free(roots);
            return l;
        }
    #endif
}
#endif

