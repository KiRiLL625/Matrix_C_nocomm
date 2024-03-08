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
    printf("5. Print matrix\n");
    printf("6. Exit\n");
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
        case 2:
            printf("Enter the number of rows and columns of the first matrix\n");
            int rows1, columns1;
            scanf("%d %d", &rows1, &columns1);
            Matrix *matrix1 = createMatrix(rows1, columns1);
            printf("Enter the number of rows and columns of the second matrix\n");
            int rows2, columns2;
            scanf("%d %d", &rows2, &columns2);
            Matrix *matrix2 = createMatrix(rows2, columns2);
            if(columns1 != rows2){
                printf("Matrices have different dimensions\n");
                return true;
            }
            printf("Enter the elements of the first matrix\n");
            for(int i = 0; i < rows1; i++){
                for(int j = 0; j < columns1; j++){
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix1, i, j, stringToComplex(string));
                }
            }
            printf("Enter the elements of the second matrix\n");
            for(int i = 0; i < rows2; i++){
                for(int j = 0; j < columns2; j++){
                    char string[100];
                    scanf("%s", string);
                    setElement(matrix2, i, j, stringToComplex(string));
                }
            }
            Matrix* result = multiply(matrix1, matrix2);
            if(result == NULL){
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
        case 3:
        case 4:
        case 5:
            printf("Not implemented\n");
            return true;
        case 6:
            return false;
    }
    return false;
}

int main() {
    while(menu());
    return 0;
}
