//
// Created by Admin on 26.02.2024.
//

#ifndef L1_MATRIX_H
#define L1_MATRIX_H

#include "DynamicArray.h"

typedef struct{
    DynamicArray *matrix_array;
    int rows;
    int columns;
} Matrix;

Matrix *createMatrix(int rows, int columns);

void deleteMatrix(Matrix *matrix);

void setElement(Matrix *matrix, int row, int column, void *value);

void *getElement(Matrix *matrix, int row, int column);

Matrix* add(Matrix *matrix1, Matrix *matrix2);

Matrix* multiply(Matrix *matrix1, Matrix *matrix2);

Matrix* scalarMultiply(Matrix *matrix, void *scalar);

Matrix* addLinearCombination(Matrix* matrix, int row, void* alphas);

void printMatrix(Matrix *matrix);

#endif //L1_MATRIX_H
