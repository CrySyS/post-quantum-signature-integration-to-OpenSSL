#include "luov_intermediateValues.h"

void printVinegarValues(LUOV_FELT *vinegar){
	#ifdef KAT
		int i,j;
		unsigned char buf[sizeof(LUOV_FELT)] = {0};
		writer W; 
		printf("vinegar values = ");
		for(i=0 ; i<LUOV_VINEGAR_VARS ; i++){
			W = newWriter(buf);
			LUOV_serialize_FELT(&W,vinegar[i]);
			for(j=0 ; j<sizeof(LUOV_FELT) ; j++){
				printf("%02X", buf[j]);
			}
		}
		printf("\n");
	#endif
}


void printAugmentedMatrix(Matrix A){
	#ifdef KAT
		int i,j,k;
		unsigned char buf[sizeof(LUOV_FELT)] = {0};
		writer W; 
		printf("Augmented matrix = ");
		for(i=0 ; i<LUOV_OIL_VARS ; i++){
			for(j=0 ; j<=LUOV_OIL_VARS ; j++){
				W = newWriter(buf);
				LUOV_serialize_FELT(&W,A.array[i][j]);
				for(k=0 ; k<sizeof(LUOV_FELT) ; k++){
					printf("%02X", buf[k]);
				}
			}
			printf("\n");
		}
	#endif
}

void reportSolutionFound(int solution_found){
	#ifdef KAT
		if(solution_found == 0){
			printf("solution not found, retry\n");
		}
		else{
			printf("solution found\n");
		}
	#endif
}

void printPrivateSolution(LUOV_FELT *sig){
	#ifdef KAT
		int i,j;
		unsigned char buf[sizeof(LUOV_FELT)] = {0};
		writer W; 
		printf("private solution = ");
		for(i=0 ; i<LUOV_VINEGAR_VARS + LUOV_OIL_VARS  ; i++){
			W = newWriter(buf);
			LUOV_serialize_FELT(&W,sig[i+1]);
			for(j=0 ; j<sizeof(LUOV_FELT) ; j++){
				printf("%02X", buf[j]);
			}
		}
		printf("\n");
	#endif
}

void printEvaluation(LUOV_FELT *eval){
	#ifdef KAT
		int i,j;
		unsigned char buf[sizeof(LUOV_FELT)] = {0};
		writer W; 
		printf("evaluation = ");
		for(i=0 ; i< LUOV_OIL_VARS  ; i++){
			W = newWriter(buf);
			LUOV_serialize_FELT(&W,eval[i]);
			for(j=0 ; j<sizeof(LUOV_FELT) ; j++){
				printf("%02X", buf[j]);
			}
		}
		printf("\n");
	#endif
}
