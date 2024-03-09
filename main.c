#include <stdio.h>
#include <malloc.h>
#include "DynamicArray.h"
#include "Complex.h"
#include "Matrix.h"
#include "stdbool.h"

bool menu(){
    printf("Choose an option:\n");
    printf("1. Add matrices\n");
    printf("2. Multiply matrices\n");
    printf("3. Multiply matrix by scalar\n");
    printf("4. Add linear combination of rows\n");
    printf("5. Exit\n");
    int option;
    scanf("%d", &option);
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
            if (rows1 != rows2 || columns1 != columns2) {
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
            Matrix *result = add(matrix1, matrix2);
            if (result == NULL) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            printMatrix(matrix1);
            printf("+\n");
            printMatrix(matrix2);
            printf("=\n");
            printMatrix(result);
            deleteMatrix(matrix1);
            deleteMatrix(matrix2);
            deleteMatrix(result);
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
            printMatrix(matrix1);
            printf("*\n");
            printMatrix(matrix2);
            printf("=\n");
            printMatrix(result);
            deleteMatrix(matrix1);
            deleteMatrix(matrix2);
            deleteMatrix(result);
            return true;
        }
        case 3: {
            printf("Enter the number of rows and columns of the matrix\n");
            int rows, columns;
            scanf("%d %d", &rows, &columns);
            Matrix *matrix = createMatrix(rows, columns);
            printf("Enter the elements of the matrix\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix, i, j, stringToComplex(string));
                }
            }
            printf("Enter the scalar\n");
            double scalar;
            scanf("%lf", &scalar);
            Matrix *result = scalarMultiply(matrix, createComplex(scalar, 0));
            printMatrix(matrix);
            printf("*%lf=\n", scalar);
            printMatrix(result);
            deleteMatrix(matrix);
            deleteMatrix(result);
            return true;
        }
        case 4: {
            printf("Enter the number of rows and columns of the matrix\n");
            int rows, columns;
            scanf("%d %d", &rows, &columns);
            Matrix *matrix = createMatrix(rows, columns);
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
            printf("Enter the coefficients\n");
            DynamicArray *alphas = createDynamicArray(sizeof(Complex));
            for (int i = 0; i < columns; i++) {
                char string[100];
                scanf("%s", string);
                append(alphas, stringToComplex(string));
            }
            Matrix *result = addLinearCombination(matrix, row, alphas);
            printMatrix(matrix);
            printf("+\n");
            printf("alpha1*");
            printMatrix(matrix);
            printf("+...+\n");
            printf("alpha%d*", columns);
            printMatrix(matrix);
            printf("=\n");
            printMatrix(result);
            deleteMatrix(matrix);
            deleteMatrix(result);
            deleteDynamicArray(alphas);
            return true;
        }
        case 5:
            return false;
        default:
            printf("Wrong option! Choose another.\n");
            return true;
    }
}

int main() {
    while(menu());
    return 0;
}
