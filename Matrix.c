//
// Created by Admin on 26.02.2024.
//

#include <stdlib.h>
#include "Matrix.h"
#include "Complex.h"
#include <stdio.h>
#include <string.h>

//функция создания матрицы
Matrix *createMatrix(int rows, int columns) {
    //выделение памяти под структуру
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    //если количество строк или столбцов равно 0, то возвращаем NULL
    if(rows == 0 || columns == 0)
        return NULL;
    //выделение памяти под массив указателей на строки матрицы
    matrix->matrix_array = createDynamicArray(rows);
    //инициализация полей структуры
    for (int i = 0; i < rows; i++) {
        //выделение памяти под массив указателей на элементы строки матрицы
        DynamicArray *row = createDynamicArray(columns);
        //инициализация полей структуры
        for (int j = 0; j < columns; j++) {
            append(row, NULL);
        }
        append(matrix->matrix_array, row);
    }
    //инициализация полей структуры
    matrix->rows = rows;
    matrix->columns = columns;
    /*
     После создания матрицы у нас получается двумерный массив, где строки - маленькие массивы
     внутри большого массива, содержащего всю матрицу. Пример:

     [[1, 2, 3],
       [4, 5, 6],
       [7, 8, 9]] - тут 3 маленьких массива внутри большого массива
     */
    return matrix;
}

//функция удаления матрицы (очистка памяти)
void deleteMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        //очистка памяти маленьких массивов
        deleteDynamicArray(get(matrix->matrix_array, i));
    }
    //очистка памяти большого массива
    deleteDynamicArray(matrix->matrix_array);
    //очистка памяти структуры
    free(matrix);
}

//функция установки элемента матрицы
void setElement(Matrix *matrix, int row, int column, void *value) {
    //проверка: если строка или столбец отрицательные, или значение равно NULL, или матрица равна NULL, то выходим из функции
    if(row < 0 || column < 0 || value == NULL || matrix == NULL){
        return;
    }
    //проверка: если строка или столбец больше, чем количество строк или столбцов матрицы, то выходим из функции
    if(row >= matrix->rows || column >= matrix->columns)
        return;
    //устанавливаем значение в массиве (получаем маленький массив, внутри большого массива, и устанавливаем значение)
    set(get(matrix->matrix_array, row), column, value);
}

//функция получения элемента матрицы
void *getElement(Matrix *matrix, int row, int column) {
    //проверка: если строка или столбец отрицательные, или матрица равна NULL, то возвращаем NULL
    if(row < 0 || column < 0 || matrix == NULL){
        return NULL;
    }
    //проверка: если строка или столбец больше, чем количество строк или столбцов матрицы, то возвращаем NULL
    if(row >= matrix->rows || column >= matrix->columns)
        return NULL;
    //возвращаем значение из массива (получаем маленький массив, внутри большого массива, и возвращаем значение)
    return get(get(matrix->matrix_array, row), column);
}

//функция сложения матриц
Matrix *add(Matrix *matrix1, Matrix *matrix2) {
    //проверка: если матрицы равны NULL, то возвращаем NULL
    if(matrix1 == NULL || matrix2 == NULL)
        return NULL;
    //проверка: если количество строк или столбцов матриц не равны, или равны 0, то возвращаем NULL
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns || matrix1->rows == 0 || matrix1->columns == 0) {
        return NULL;
    }
    //создание новой (результирующей) матрицы
    Matrix *result = createMatrix(matrix1->rows, matrix1->columns);
    //цикл по строкам
    for (int i = 0; i < matrix1->rows; i++) {
        //цикл по столбцам
        for (int j = 0; j < matrix1->columns; j++) {
            //установка значения в результирующей матрице (сложение значений из двух матриц с помощью функции addComplex)
            setElement(result, i, j,
                       addComplex(getElement(matrix1, i, j),
                                  getElement(matrix2, i, j)));
        }
    }
    //возвращаем результирующую матрицу
    return result;
}

//функция умножения матриц
Matrix *multiply(Matrix *matrix1, Matrix *matrix2) {
    //проверка: если матрицы равны NULL, или количество столбцов первой матрицы не равно
    // количеству строк второй матрицы, то возвращаем NULL
    if(matrix1 == NULL || matrix2 == NULL)
        return NULL;
    if (matrix1->columns != matrix2->rows) {
        return NULL;
    }
    //создание новой (результирующей) матрицы
    Matrix *result = createMatrix(matrix1->rows, matrix2->columns);
    //цикл по строкам
    for (int i = 0; i < matrix1->rows; i++) {
        //цикл по столбцам
        for (int j = 0; j < matrix2->columns; j++) {
            //установка значения в результирующей матрице (умножение значений из двух матриц с помощью функции multiplyComplex)
            setElement(result, i, j, createComplex(0, 0));
            //цикл по столбцам
            for (int k = 0; k < matrix1->columns; k++) {
                setElement(result, i, j,
                           addComplex(getElement(result, i, j),
                                      multiplyComplex(getElement(matrix1, i, k),
                                                      getElement(matrix2, k, j))));
            }
        }
    }
    //возвращаем результирующую матрицу
    return result;
}

//функция умножения матрицы на скаляр
Matrix* scalarMultiply(Matrix *matrix, void *scalar) {
    //проверка: если матрица или скаляр равны NULL, или скаляр равен 0, то возвращаем NULL
    if(matrix == NULL || scalar == NULL)
        return NULL;
    if(*(double *)scalar == 0)
        return NULL;
    //создание новой (результирующей) матрицы
    Matrix *result = createMatrix(matrix->rows, matrix->columns);
    //цикл по строкам
    for (int i = 0; i < matrix->rows; i++) {
        //цикл по столбцам
        for (int j = 0; j < matrix->columns; j++) {
            //установка значения в результирующей матрице (умножение значения из матрицы на скаляр с помощью функции scalarMultiplyComplex)
            setElement(result, i, j,
                       multiplyComplex(getElement(matrix, i, j), scalar));
        }
    }
    return result;
}

//функция сложения линейной комбинации строк
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

//функция печати матрицы
void printMatrix(Matrix *matrix) {
    //цикл по строкам
    for (int i = 0; i < matrix->rows; i++) {
        //печать левой границы матрицы
        printf("|| ");
        //цикл по столбцам
        for (int j = 0; j < matrix->columns; j++) {
            //печать элемента матрицы с помощью функции complexToString и max_elem_length
            char* res = complexToString(getElement(matrix, i, j));
            printf("%*s", max_elem_length(matrix->matrix_array), res);
            printf(" ");
        }
        //печать правой границы матрицы
        printf("||");
        printf("\n");
    }
}

//функция нахождения максимальной длины элемента матрицы (нужна для правильного вывода матрицы)
int max_elem_length(DynamicArray *matrix_array) {
    //переменная для максимальной длины
    int max = 0;
    //цикл по строкам
    for (int i = 0; i < matrix_array->size; i++) {
        //получаем маленький массив (строку матрицы)
        DynamicArray *row = get(matrix_array, i);
        //цикл по столбцам
        for (int j = 0; j < row->size; j++) {
            //получаем элемент матрицы и преобразуем его в строку
            char* res = complexToString(get(row, j));
            //если длина строки больше максимальной, то обновляем максимальную длину
            if (strlen(res) > max) {
                max = strlen(res);
            }
        }
    }
    //возвращаем максимальную длину
    return max;
}

//функция меню (интерфейс программы)
bool menu(){
    //вывод меню
    printf("Choose an option:\n");
    printf("1. Add matrices\n");
    printf("2. Multiply matrices\n");
    printf("3. Multiply matrix by scalar\n");
    printf("4. Add linear combination of rows\n");
    printf("5. Exit\n");
    //переменная, отвечающая за выбор пользователя (сделана в виде char, чтобы можно было ввести 1 символ)
    //и для обработки неправильного ввода пункта (если пользователь ввёл не число)
    char choice[1];
    scanf("%s", choice);
    //преобразование char в int (это делает функция atoi)
    int option = atoi(choice);
    switch (option) {
        //если пользователь выбрал 1 пункт
        case 1: {
            //ввод количества строк и столбцов первой матрицы
            printf("Enter the number of rows and columns of the first matrix\n");
            int rows1, columns1;
            scanf("%d %d", &rows1, &columns1);
            Matrix *matrix1 = createMatrix(rows1, columns1);
            printf("Enter the number of rows and columns of the second matrix\n");
            int rows2, columns2;
            scanf("%d %d", &rows2, &columns2);
            Matrix *matrix2 = createMatrix(rows2, columns2);
            //проверка: если матрицы равны NULL, то выводим сообщение об ошибке
            if(matrix1 == NULL || matrix2 == NULL) {
                printf("Size of matrix can't be 0\n");
                return true;
            }
            //проверка: если количество строк или столбцов матриц не равны, то выводим сообщение об ошибке
            if (rows1 != rows2 || columns1 != columns2) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            //ввод элементов первой матрицы
            printf("Enter the elements of the first matrix\n");
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < columns1; j++) {
                    char string[100];
                    scanf("%s", string);
                    void* value = stringToComplex(string);
                    //проверка: если значение равно NULL (не удалось перевести
                    // строку в комплексное число), то выводим сообщение об ошибке
                    if(value == NULL) {
                        printf("Incorrect input\n");
                        return true;
                    }
                    //установка значения в матрицу
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
            //проверка: если результат равен NULL, то выводим сообщение об ошибке (дополнительная
            // проверка, так как в функции add уже есть проверка на равенство размеров матриц)
            if (result == NULL) {
                printf("Matrices have different dimensions\n");
                return true;
            }
            //красивый вывод результата
            printf("___________________________________\n");
            printMatrix(matrix1);
            printf("+\n");
            printMatrix(matrix2);
            printf("=\n");
            printMatrix(result);
            //очистка памяти
            deleteMatrix(matrix1);
            deleteMatrix(matrix2);
            deleteMatrix(result);
            printf("___________________________________\n");
            //возвращаем true, чтобы программа продолжила работу (снова вывела меню)
            return true;
        }
        //если мы хотим умножить 2 матрицы
        case 2: {
            //тут всё по тому же шаблону, что и в case 1
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
        //если мы хотим умножить матрицу на скаляр
        case 3: {
            //ввод элементов матрицы
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
            //ввод скаляра
            printf("Enter the scalar\n");
            double scalar = 0;
            scanf("%lf", &scalar);
            //проверка: если скаляр равен 0 или строке, то выводим сообщение об ошибке
            if(scalar == 0) {
                printf("Scalar can't be 0 or incorrect input\n");
                return true;
            }
            //умножение матрицы на скаляр
            Matrix *result = scalarMultiply(matrix, createComplex(scalar, 0));
            //красивый вывод результата
            printf("___________________________________\n");
            printMatrix(matrix);
            printf("*%lf=\n", scalar);
            printMatrix(result);
            printf("___________________________________\n");
            //очистка памяти
            deleteMatrix(matrix);
            deleteMatrix(result);
            return true;
        }
        //если мы хотим сложить линейную комбинацию строк
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
            printf("Enter the coefficients\n");
            DynamicArray *alphas = createDynamicArray(sizeof(Complex));
            for (int i = 0; i < columns; i++) {
                char string[100];
                scanf("%s", string);
                append(alphas, stringToComplex(string));
            }
            Matrix *result = addLinearCombination(matrix, row, alphas);
            printf("___________________________________\n");
            printMatrix(matrix);
            printf("+\n");
            printf("alpha1*");
            printMatrix(matrix);
            printf("+...+\n");
            printf("alpha%d*", columns);
            printMatrix(matrix);
            printf("=\n");
            printMatrix(result);
            printf("___________________________________\n");
            deleteMatrix(matrix);
            deleteMatrix(result);
            deleteDynamicArray(alphas);
            return true;
        }
        //если мы хотим выйти из программы, то возвращаем false, чтобы прервать цикл while в main
        case 5:
            return false;
        //если пользователь ввёл неправильный пункт, то выводим сообщение об ошибке
        default:
            printf("Wrong option! Choose another.\n");
            return true;
    }
}