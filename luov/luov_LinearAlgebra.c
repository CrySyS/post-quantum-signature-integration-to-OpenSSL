#include <stdio.h>
#include <stdlib.h>

#include "luov_LinearAlgebra.h"
#include "luov_buffer.h"

/*
	Creates a new matrix

	rows : the number of rows of the new matrix
	cols : the number of columns of the new matrix

	returns : The new matrix
*/
Matrix newMatrix(unsigned int rows, unsigned int cols) {
	unsigned int i;
	Matrix new;
	new.rows = rows;
	new.cols = cols;
	new.array = malloc(rows * sizeof(LUOV_FELT*));
	for (i = 0; i < rows; i++) {
		new.array[i] = malloc(cols * sizeof(LUOV_FELT));
	}
	return new;
}

/*
	Creates a new matrix whose entries are zero

	rows : the number of rows of the new matrix
	cols : the number of columns of the new matrix

	returns : The new matrix
*/
Matrix zeroMatrix(unsigned int rows, unsigned int cols) {
	unsigned int i, j;
	Matrix newMat = newMatrix(rows, cols);
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			newMat.array[i][j] = LUOV_ZERO;
		}
	}
	return newMat;
}

/*
	Free the memory of a matrix

	mat : the matrix to destroy
*/
void destroy_matrix(Matrix mat) {
	int i;
	for (i = 0; i < mat.rows; i++) {
		free(mat.array[i]);
	}
	free(mat.array);
}

/*
	Prints a matrix
*/
void printMatrix(Matrix Mat) {
	int i, j;
	for (i = 0; i < Mat.rows; i++) {
		for (j = 0; j < Mat.cols; j++) {
			LUOV_printFELT(Mat.array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
	Swaps two rows of a matrix

	A : A matrix
	row1 , row2 : The rows of A that have to be swapped
*/
void swapRows(Matrix A, int row1, int row2) {
	LUOV_FELT *temp = A.array[row1];
	A.array[row1] = A.array[row2];
	A.array[row2] = temp;
}

/*
	Multiplies all the entries of a row of a matrix by a scalar

	A : A matrix
	row : the index of the row that has to be rescaled
	a : A field element
*/
void scaleRow(Matrix A, int row, LUOV_FELT a) {
	int i;
	for (i = 0; i < A.cols; i++) {
		A.array[row][i] = LUOV_multiply(a,A.array[row][i]);
	}
}

/*
	Add a part of the scalar multiple of one row of a matrix to another row of that matrix

	A : A matrix
	destrow : The row to LUOV_add to
	sourcerow  : The row that is multiplied by a scalar and added to destrow
	constant : The contant that sourcerow is multiplied with
	offset : Only the entries in columns with index larger than or equal to offset are affected
*/
void rowOp(Matrix A, int destrow, int sourcerow, LUOV_FELT constant, int offset)
{
	int j;
	LUOV_FELT T;
	if (LUOV_isEqual(constant, LUOV_ZERO))
		return;

	for (j = offset; j < A.cols; ++j)
	{
		T = LUOV_multiply(constant,A.array[sourcerow][j]);
		LUOV_addInPlace(&A.array[destrow][j],&T);
	}
}

/* 
	Puts the first part of an augmented matrix in row echelon form.
	
	A : A matrix

	returns : The rank ok the first part of the row echelon form of A
*/
int rowEchelonAugmented(Matrix A)
{
	int i,col;
	int row = 0;
	for (col = 0; col < A.cols - 1; ++col)
	{
		for (i = row; i < A.rows; ++i)
		{
			if (!LUOV_isEqual(A.array[i][col], LUOV_ZERO))
			{
				if (i != row)
				{
					swapRows(A, i, row);
				}
				break;
			}
		}

		if (i == A.rows)
		{
			continue;
		}

		scaleRow(A, row, LUOV_inverse(A.array[row][col]));

		for (i++; i < A.rows; ++i)
		{
			rowOp(A, i, row, LUOV_minus(A.array[i][col]), col);
		}

		row++;

		if (row == A.rows)
		{
			break;
		}
	}
	return row;
}

/* 
	Calculates the unique solution to a linear system described by an augmented matrix

	A : The augmented matrix of some linear system of equations
	solution : Receives the unique solution if it exists 

	returns : 1 if a unique solution exists, 0 otherwise 
*/
int getUniqueSolution(Matrix A, LUOV_FELT *solution) {
	int i,j,col,row;
	LUOV_FELT T;
	int rank = rowEchelonAugmented(A);

	if (rank != A.rows) {
		return 0;
	}

	/* clear memory for solution */
    for (i = 0 ; i< A.cols-1 ; i++){
    	solution[i] = LUOV_ZERO;
    }

	for (row = A.rows - 1; row >= 0; row--) {
		col = row;
		while (LUOV_isEqual(A.array[row][col], LUOV_ZERO))
		{
			col++;
		}

		solution[col] = A.array[row][A.cols - 1];
		for (j = col + 1; j < A.cols - 1; j++) {
			T = LUOV_multiply(solution[j], A.array[row][j]);
			solution[col] = LUOV_subtract(solution[col],T);
		}
	}
	return 1;
}

int getInverse(Matrix *A, Matrix *A_inv){
	int i,j;
	*A_inv = zeroMatrix(A->rows,A->rows);
	for(i=0; i<A->rows; i++){
		A_inv->array[i][i] = LUOV_ONE;
	}

	int col;
	int row = 0;
	for (col = 0; col < A->cols - 1; ++col)
	{
		for (i = row; i < A->rows; ++i)
		{
			if (!LUOV_isEqual(A->array[i][col], LUOV_ZERO))
			{
				if (i != row)
				{
					swapRows(*A, i, row);
					swapRows(*A_inv,i,row);
				}
				break;
			}
		}

		if (i == A->rows)
		{
			continue;
		}

		LUOV_FELT inv = LUOV_inverse(A->array[row][col]);
		scaleRow(*A, row, inv);
		scaleRow(*A_inv, row, inv);

		for (j = 0; j < row; j++)
		{
			LUOV_FELT s = LUOV_minus(A->array[j][col]);
			rowOp(*A, j, row, s, col);
			rowOp(*A_inv, j, row, s, 0);
		}

		for (i++; i < A->rows; ++i)
		{
			LUOV_FELT s = LUOV_minus(A->array[i][col]);
			rowOp(*A, i, row, s, col);
			rowOp(*A_inv, i, row, s, 0);
		}

		row++;

		if (row == A->rows)
		{
			break;
		}
	}
	int rank = row;

	if(rank != A->rows)
	{
		destroy_matrix(*A_inv);
		return 0;
	}

	return 1;
}