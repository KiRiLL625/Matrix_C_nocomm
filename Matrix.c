//
// Created by Admin on 26.02.2024.
//

#include <stdlib.h>
#include "Matrix.h"
#include "Complex.h"
#include <stdio.h>
#include <string.h>

Matrix *createMatrix(int rows, int columns) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->matrix_array = createDynamicArray(rows);
    for (int i = 0; i < rows; i++) {
        DynamicArray *row = createDynamicArray(columns);
        for (int j = 0; j < columns; j++) {
            append(row, NULL);
        }
        append(matrix->matrix_array, row);
    }
    matrix->rows = rows;
    matrix->columns = columns;
    return matrix;
}

void deleteMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        deleteDynamicArray(get(matrix->matrix_array, i));
    }
    deleteDynamicArray(matrix->matrix_array);
    free(matrix);
}

void setElement(Matrix *matrix, int row, int column, void *value) {
    set(get(matrix->matrix_array, row), column, value);
}

void *getElement(Matrix *matrix, int row, int column) {
    return get(get(matrix->matrix_array, row), column);
}

Matrix *add(Matrix *matrix1, Matrix *matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        return NULL;
    }
    Matrix *result = createMatrix(matrix1->rows, matrix1->columns);
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->columns; j++) {
            setElement(result, i, j,
                       addComplex(getElement(matrix1, i, j),
                                  getElement(matrix2, i, j)));
        }
    }
    return result;
}

Matrix *multiply(Matrix *matrix1, Matrix *matrix2) {
    if (matrix1->columns != matrix2->rows) {
        return NULL;
    }
    Matrix *result = createMatrix(matrix1->rows, matrix2->columns);
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->columns; j++) {
            setElement(result, i, j, createComplex(0, 0));
            for (int k = 0; k < matrix1->columns; k++) {
                setElement(result, i, j,
                           addComplex(getElement(result, i, j),
                                      multiplyComplex(getElement(matrix1, i, k),
                                                      getElement(matrix2, k, j))));
            }
        }
    }
    return result;
}

Matrix* scalarMultiply(Matrix *matrix, void *scalar) {
    Matrix *result = createMatrix(matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            setElement(result, i, j,
                       multiplyComplex(getElement(matrix, i, j), scalar));
        }
    }
    return result;
}

Matrix* addLinearCombination(Matrix* matrix, int row, void* alphas) {
    Matrix *result = createMatrix(matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if (i == row) {
                setElement(result, i, j, addComplex(getElement(matrix, i, j), get(alphas, j)));
            } else {
                setElement(result, i, j, getElement(matrix, i, j));
            }
        }
    }
    return result;
}

void printMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        printf("|| ");
        for (int j = 0; j < matrix->columns; j++) {
            char* res = complexToString(getElement(matrix, i, j));
            printf("%*s", max_elem_length(matrix->matrix_array), res);
            printf(" ");
        }
        printf("||");
        printf("\n");
    }
}

int max_elem_length(DynamicArray *matrix_array) {
    int max = 0;
    for (int i = 0; i < matrix_array->size; i++) {
        DynamicArray *row = get(matrix_array, i);
        for (int j = 0; j < row->size; j++) {
            char* res = complexToString(get(row, j));
            if (strlen(res) > max) {
                max = strlen(res);
            }
        }
    }
    return max;
}