#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include "luov_F7Field.h"
#include "luov_F47Field.h"
#include "luov_F61Field.h"
#include "luov_F79Field.h"

#define LUOV_PRINTMATRIX(M) printf(#M " = \n"); printMatrix(M);

/*Matrix over F_Q*/
typedef struct {
	int rows;
	int cols;
	LUOV_FELT** array;
} Matrix;

Matrix zeroMatrix(unsigned int rows, unsigned int cols);
void destroy_matrix(Matrix mat);
void printMatrix(Matrix Mat);
int getUniqueSolution(Matrix A, LUOV_FELT *solution);
int getInverse(Matrix *A, Matrix *A_inv);

#endif
