//
// Created by Admin on 26.02.2024.
//

#ifndef L1_MATRIX_H
#define L1_MATRIX_H

#include <stdbool.h>
#include "DynamicArray.h"

// Структура для матрицы
typedef struct{
    DynamicArray *matrix_array; // массив указателей на строки матрицы
    int rows; // количество строк
    int columns; // количество столбцов
} Matrix;

Matrix *createMatrix(int rows, int columns);

void deleteMatrix(Matrix *matrix);

void setElement(Matrix *matrix, int row, int column, void *value);

void *getElement(Matrix *matrix, int row, int column); //void** void* - указатели на элемент любого типа

Matrix* add(Matrix *matrix1, Matrix *matrix2);

Matrix* multiply(Matrix *matrix1, Matrix *matrix2);

Matrix* scalarMultiply(Matrix *matrix, void *scalar);

Matrix* addLinearCombination(Matrix* matrix, int row, void** alphas);

Matrix* transpose(Matrix* matrix);

void printMatrix(Matrix *matrix);

int max_elem_length(DynamicArray *matrix_array);

void example();

void example_row_column();

bool menu();

#endif //L1_MATRIX_H
