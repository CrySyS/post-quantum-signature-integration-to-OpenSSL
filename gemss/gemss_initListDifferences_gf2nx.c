#include "gemss_initListDifferences_gf2nx.h"
#include "gemss_parameters_HFE.h"
#include "gemss_tools_gf2n.h"
#include "gemss_gf2nx.h"


/**
 * @brief   Initialize L to the list of the successive differences of the 
 * exponents of the monomials of a GEMSS_HFE polynomial, multiplied by GEMSS_NB_WORD_GFqn.
 * @details A GEMSS_HFE polynomial has the exponents 0,1,2,3,4,5,6,8,9,10,12,16,...
 * So, L = GEMSS_NB_WORD_GFqn*{0,1-0,2-1,3-2,4-3,5-4,6-5,8-6,9-8,10-9,12-10,16-12,...}
 *       = GEMSS_NB_WORD_GFqn*{0,1,
 *                         1,
 *                         1,1,
 *                         1,1,2,
 *                         1,1,2,4,
 *                         1,1,2,4,8,
 *                         1,1,2,4,8,16,
 *                         ...}
 * @param[out]    L   A list of GEMSS_NB_COEFS_HFEPOLY unsigned integers.
 * @remark  Requires to allocate GEMSS_NB_COEFS_HFEPOLY unsigned int for L.
 * @remark  This function does not require a constant-time implementation.
 */
void GEMSS_PREFIX_NAME(GEMSS_initListDifferences_gf2nx)(unsigned int* L)
{
    #if(GEMSS_HFEDeg!=1)
        unsigned int i,j,k=2U;
    #endif

    L[0]=0U;
    #if(GEMSS_HFEDeg!=1)
        L[1]=GEMSS_NB_WORD_GFqn;
        for(i=0;i<GEMSS_HFEDegI;++i)
        {
            #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
            if(((1U<<i)+1U)<=GEMSS_HFE_odd_degree)
            {
                /* j=0 */
                L[k]=GEMSS_NB_WORD_GFqn;
                ++k;

                /* j=1 to j=i */
                for(j=0;j<i;++j)
                {
                    L[k]=GEMSS_NB_WORD_GFqn<<j;
                    ++k;
                }
            } else
            {
                /* j=0 */
                if(i)
                {
                    L[k]=GEMSS_NB_WORD_GFqn<<1;
                    ++k;
                }

                /* j=1 to j=i */
                for(j=1;j<i;++j)
                {
                    L[k]=GEMSS_NB_WORD_GFqn<<j;
                    ++k;
                }
            }
            #else
            /* j=0 */
            L[k]=GEMSS_NB_WORD_GFqn;
            ++k;

            /* j=1 to j=i */
            for(j=0;j<i;++j)
            {
                L[k]=GEMSS_NB_WORD_GFqn<<j;
                ++k;
            }
            #endif
        }
        #if GEMSS_HFEDegJ
            #if GEMSS_ENABLED_REMOVE_ODD_DEGREE
            if(((1U<<i)+1U)<=GEMSS_HFE_odd_degree)
            {
                /* j=0 */
                L[k]=GEMSS_NB_WORD_GFqn;
                ++k;

                /* j=1 to j=i */
                for(j=0;j<(GEMSS_HFEDegJ-1);++j)
                {
                    L[k]=GEMSS_NB_WORD_GFqn<<j;
                    ++k;
                }
            } else
            {
                /* j=0 */
                #if (GEMSS_HFEDegJ!=1)
                    L[k]=GEMSS_NB_WORD_GFqn<<1;
                    ++k;
                #endif

                /* j=1 to j=i */
                for(j=1;j<(GEMSS_HFEDegJ-1);++j)
                {
                    L[k]=GEMSS_NB_WORD_GFqn<<j;
                    ++k;
                }
            }
            #else
            /* j=0*/
            L[k]=GEMSS_NB_WORD_GFqn;
            ++k;

            /* j=1 to j=GEMSS_HFEDegJ-1 */
            for(j=0;j<(GEMSS_HFEDegJ-1);++j)
            {
                L[k]=GEMSS_NB_WORD_GFqn<<j;
                ++k;
            }
            #endif
        #endif
    #endif
}


