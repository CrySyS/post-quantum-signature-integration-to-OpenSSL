#ifndef INTERMEDIATE_VALUES_H
#define INTERMEDIATE_VALUES_H

#include "luov_local.h"
#include "luov_LinearAlgebra.h"

void printVinegarValues(LUOV_FELT *vinegar);
void printAugmentedMatrix(Matrix A);
void reportSolutionFound(int solution_found);
void printPrivateSolution(LUOV_FELT *sig);
void printEvaluation(LUOV_FELT *eval);

#endif