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
    if(rows == 0 || columns == 0)
        return NULL;
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
    if(row < 0 || column < 0 || value == NULL || matrix == NULL){
        return;
    }
    if(row >= matrix->rows || column >= matrix->columns)
        return;
    set(get(matrix->matrix_array, row), column, value);
}

void *getElement(Matrix *matrix, int row, int column) {
    if(row < 0 || column < 0 || matrix == NULL){
        return NULL;
    }
    if(row >= matrix->rows || column >= matrix->columns)
        return NULL;
    return get(get(matrix->matrix_array, row), column);
}

Matrix *add(Matrix *matrix1, Matrix *matrix2) {
    if(matrix1 == NULL || matrix2 == NULL)
        return NULL;
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns || matrix1->rows == 0 || matrix1->columns == 0) {
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
    if(matrix1 == NULL || matrix2 == NULL)
        return NULL;
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

//todo: check if scalar is valid
Matrix* scalarMultiply(Matrix *matrix, void *scalar) {
    if(matrix == NULL || scalar == NULL)
        return NULL;
    if(*(double *)scalar == 0)
        return NULL;
    Matrix *result = createMatrix(matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            setElement(result, i, j,
                       multiplyComplex(getElement(matrix, i, j), scalar));
        }
    }
    return result;
}

Matrix* addLinearCombination(Matrix* matrix, int row, void** alphas) {
    Matrix *result = createMatrix(matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if (i == row) {
                setElement(result, i, j, addComplex(getElement(matrix, i, j), alphas[j]));
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

Matrix* transpose(Matrix* matrix) {
    Matrix *result = createMatrix(matrix->columns, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            setElement(result, j, i, getElement(matrix, i, j));
        }
    }
    return result;
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

bool menu(){
    printf("Choose an option:\n");
    printf("1. Add matrices\n");
    printf("2. Multiply matrices\n");
    printf("3. Multiply matrix by scalar\n");
    printf("4. Add linear combination of rows\n");
    printf("5. Transpose matrix\n");
    printf("6. Exit\n");
    char choice[1];
    scanf("%s", choice);
    int option = atoi(choice);
    switch (option) {
        case 1: {
            printf("Enter the number of rows and columns of the first matrix\n");
            int rows1, columns1;
            scanf("%d %d", &rows1, &columns1);
            Matrix *matrix1 = createMatrix(rows1, columns1);
            printf("Enter the number of rows and columns of the second matrix\n");
            int rows2, columns2;
            scanf("%d %d", &rows2, &columns2);
            Matrix *matrix2 = createMatrix(rows2, columns2);
            if(matrix1 == NULL || matrix2 == NULL) {
                printf("Size of matrix can't be 0\n");
                return true;
            }
            if (rows1 != rows2 || columns1 != columns2) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            printf("Enter the elements of the first matrix\n");
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < columns1; j++) {
                    char string[100];
                    scanf("%s", string);
                    void* value = stringToComplex(string);
                    if(value == NULL) {
                        printf("Incorrect input\n");
                        return true;
                    }
                    setElement(matrix1, i, j, value);
                }
            }
            printf("Enter the elements of the second matrix\n");
            for (int i = 0; i < rows2; i++) {
                for (int j = 0; j < columns2; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix2, i, j, stringToComplex(string));
                }
            }
            Matrix *result = add(matrix1, matrix2);
            if (result == NULL) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            printf("___________________________________\n");
            printMatrix(matrix1);
            printf("+\n");
            printMatrix(matrix2);
            printf("=\n");
            printMatrix(result);
            deleteMatrix(matrix1);
            deleteMatrix(matrix2);
            deleteMatrix(result);
            printf("___________________________________\n");
            return true;
        }
        case 2: {
            printf("Enter the number of rows and columns of the first matrix\n");
            int rows1, columns1;
            scanf("%d %d", &rows1, &columns1);
            Matrix *matrix1 = createMatrix(rows1, columns1);
            printf("Enter the number of rows and columns of the second matrix\n");
            int rows2, columns2;
            scanf("%d %d", &rows2, &columns2);
            Matrix *matrix2 = createMatrix(rows2, columns2);
            if(matrix1 == NULL || matrix2 == NULL) {
                printf("Size of matrix can't be 0\n");
                return true;
            }
            if (columns1 != rows2) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            printf("Enter the elements of the first matrix\n");
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < columns1; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix1, i, j, stringToComplex(string));
                }
            }
            printf("Enter the elements of the second matrix\n");
            for (int i = 0; i < rows2; i++) {
                for (int j = 0; j < columns2; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix2, i, j, stringToComplex(string));
                }
            }
            Matrix *result = multiply(matrix1, matrix2);
            if (result == NULL) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            printf("___________________________________\n");
            printMatrix(matrix1);
            printf("*\n");
            printMatrix(matrix2);
            printf("=\n");
            printMatrix(result);
            deleteMatrix(matrix1);
            deleteMatrix(matrix2);
            deleteMatrix(result);
            printf("___________________________________\n");
            return true;
        }
        case 3: {
            printf("Enter the number of rows and columns of the matrix\n");
            int rows, columns;
            scanf("%d %d", &rows, &columns);
            Matrix *matrix = createMatrix(rows, columns);
            if(matrix == NULL) {
                printf("Size of matrix can't be 0\n");
                return true;
            }
            printf("Enter the elements of the matrix\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix, i, j, stringToComplex(string));
                }
            }
            printf("Enter the scalar\n");
            double scalar = 0;
            scanf("%lf", &scalar);
            if(scalar == 0) {
                printf("Scalar can't be 0 or incorrect input\n");
                return true;
            }
            Matrix *result = scalarMultiply(matrix, createComplex(scalar, 0));
            printf("___________________________________\n");
            printMatrix(matrix);
            printf("*%lf=\n", scalar);
            printMatrix(result);
            printf("___________________________________\n");
            deleteMatrix(matrix);
            deleteMatrix(result);
            return true;
        }
        case 4: {
            printf("Enter the number of rows and columns of the matrix\n");
            int rows, columns;
            scanf("%d %d", &rows, &columns);
            Matrix *matrix = createMatrix(rows, columns);
            if(matrix == NULL) {
                printf("Size of matrix can't be 0\n");
                return true;
            }
            printf("Enter the elements of the matrix\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix, i, j, stringToComplex(string));
                }
            }
            printf("Enter the row number\n");
            int row;
            scanf("%d", &row);
            row--;
            printf("Enter the coefficients\n");
            DynamicArray *alphas = createDynamicArray(sizeof(Complex));
            for (int i = 0; i < columns; i++) {
                char string[100];
                scanf("%s", string);
                Complex* complex = stringToComplex(string);
                if(complex == NULL) {
                    printf("Incorrect input\n");
                    return true;
                }
                append(alphas, complex);
            }
            Matrix *result = addLinearCombination(matrix, row, alphas->array);
            printf("___________________________________\n");
            printMatrix(matrix);
            printf("+\n");
            printf("alpha1*\n");
            printMatrix(matrix);
            printf("+...+\n");
            printf("alpha%d*\n", columns);
            printMatrix(matrix);
            printf("=\n");
            printMatrix(result);
            printf("___________________________________\n");
            deleteMatrix(matrix);
            deleteMatrix(result);
            deleteDynamicArray(alphas);
            return true;
        }
        case 5:
            printf("Enter the number of rows and columns of the matrix\n");
            int rows, columns;
            scanf("%d %d", &rows, &columns);
            Matrix *matrix = createMatrix(rows, columns);
            if(matrix == NULL) {
                printf("Size of matrix can't be 0\n");
                return true;
            }
            printf("Enter the elements of the matrix\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix, i, j, stringToComplex(string));
                }
            }
            Matrix *result = transpose(matrix);
            printf("___________________________________\n");
            printMatrix(matrix);
            printf("=\n");
            printMatrix(result);
            printf("___________________________________\n");
            deleteMatrix(matrix);
            deleteMatrix(result);
            return true;
        case 6:
            return false;
        default:
            printf("Wrong option! Choose another.\n");
            return true;
    }
}