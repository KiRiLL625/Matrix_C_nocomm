//
// Created by Admin on 09.03.2024.
//

#include "test.h"
#include "Matrix.h"
#include "Complex.h"

int tests_passed = 0; //количество пройденных тестов
const int total_tests = 76; //общее количество тестов

//Описание функций (макросов) для тестирования

//Тест на создание динамического массива
TEST(CREATE_DYNAMIC_ARRAY) {
    DynamicArray *dynamicArray = createDynamicArray(10);
    //проверка, что вместимость массива равна 10
    ASSERT_INT_EQ(10, dynamicArray->capacity);
    //проверка, что размер массива равен 0
    ASSERT_INT_EQ(0, dynamicArray->size);
    //проверка, что массив не равен NULL
    ASSERT_NOT_NULL(dynamicArray->array);
    //удаление динамического массива
    deleteDynamicArray(dynamicArray);
}

//Тест на создание динамического массива с нулевой вместимостью
TEST(CREATE_DYNAMIC_ARRAY_HARD){
    //создание динамического массива с вместимостью 0
    DynamicArray *dynamicArray = createDynamicArray(0);
    //проверка, что вместимость массива равна 0
    ASSERT_INT_EQ(0, dynamicArray->capacity);
    //проверка, что размер массива равен 0
    ASSERT_INT_EQ(0, dynamicArray->size);
    //проверка, что массив не равен NULL
    ASSERT_NOT_NULL(dynamicArray->array);
    //удаление динамического массива
    deleteDynamicArray(dynamicArray);
}

//Тест на вставку элементов в динамический массив
TEST(INSERT_DYNAMIC_ARRAY){
    //создание динамического массива
    DynamicArray *dynamicArray = createDynamicArray(10);
    //вставка элемента в массив
    int value = 5;
    insert(dynamicArray, 0, &value);
    //проверка, что элемент вставился и равен 5
    ASSERT_INT_EQ(5, *(int *) get(dynamicArray, 0));
    //проверка, что размер массива увеличился
    ASSERT_INT_EQ(1, dynamicArray->size);
    //вставка элемента в массив (строка)
    char* string = "Hello";
    insert(dynamicArray, 1, string);
    //проверка, что элемент вставился и равен "Hello"
    ASSERT_STRING_EQ("Hello", (char *) get(dynamicArray, 1));
    //проверка, что размер массива увеличился
    ASSERT_INT_EQ(2, dynamicArray->size);
    //вставка элемента в массив (вещественное число)
    double d = 3.14;
    insert(dynamicArray, 1, &d);
    //проверка, что элемент вставился и равен 3.14
    ASSERT_DOUBLE_EQ(3.14, *(double *) get(dynamicArray, 1));
    //проверка, что размер массива увеличился
    ASSERT_INT_EQ(3, dynamicArray->size);
    //удаление динамического массива
    deleteDynamicArray(dynamicArray);
}

//Тест на создание комплексного числа
TEST(CREATE_COMPLEX){
    //создание комплексного числа
    Complex *complex = createComplex(5, 3);
    //проверка, что действительная часть равна 5
    ASSERT_INT_EQ(5, complex->real);
    //проверка, что мнимая часть равна 3
    ASSERT_INT_EQ(3, complex->imaginary);
    //проверка, что строковое представление комплексного числа равно "5+3i"
    ASSERT_STRING_EQ("5+3i", complexToString(complex));
    //удаление комплексного числа
    deleteComplex(complex);
}

//Тест на сложение комплексных чисел
TEST(ADD_COMPLEX){
    //создание двух комплексных чисел
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    //сложение комплексных чисел
    Complex *result = addComplex(complex1, complex2);
    //проверка, что действительная часть равна 7
    ASSERT_INT_EQ(7, result->real);
    //проверка, что мнимая часть равна 7
    ASSERT_INT_EQ(7, result->imaginary);
    //проверка, что строковое представление комплексного числа равно "7+7i"
    ASSERT_STRING_EQ("7+7i", complexToString(result));
    //удаление комплексных чисел
    deleteComplex(complex1);
    deleteComplex(complex2);
    deleteComplex(result);
}

//Тест на умножение комплексных чисел
TEST(MULTIPLY_COMPLEX){
    //создание двух комплексных чисел
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    Complex *result = multiplyComplex(complex1, complex2);
    //проверка, что действительная часть равна -2
    ASSERT_INT_EQ(-2, result->real);
    //проверка, что мнимая часть равна 26
    ASSERT_INT_EQ(26, result->imaginary);
    //проверка, что строковое представление комплексного числа равно "-2+26i"
    ASSERT_STRING_EQ("-2+26i", complexToString(result));
    //удаление комплексных чисел
    deleteComplex(complex1);
    deleteComplex(complex2);
    deleteComplex(result);
}

//Тест на преобразование строки в комплексное число
TEST(STRING_TO_COMPLEX){
    //преобразование строки в комплексное число
    char string[] = "5+3i";
    Complex *complex = stringToComplex(string);
    //проверка, что комплексное число не равно NULL
    EXPECT_NOT_NULL(complex);
    //проверка, что действительная часть равна 5
    ASSERT_INT_EQ(5, complex->real);
    //проверка, что мнимая часть равна 3
    ASSERT_INT_EQ(3, complex->imaginary);
    //удаление комплексного числа
    deleteComplex(complex);
}

//Тест на преобразование комплексного числа в строку
TEST(COMPLEX_TO_STRING){
    //создание комплексного числа
    Complex *complex = createComplex(5, 3);
    //преобразование комплексного числа в строку
    char *string = complexToString(complex);
    //проверка, что строка равна "5+3i" (снизу то же самое)
    ASSERT_STRING_EQ("5+3i", string);
    Complex* complex2 = createComplex(0, 3);
    string = complexToString(complex2);
    ASSERT_STRING_EQ("3i", string);
    Complex* complex3 = createComplex(5, 0);
    string = complexToString(complex3);
    ASSERT_STRING_EQ("5", string);
    Complex* complex4 = createComplex(0, 0);
    string = complexToString(complex4);
    ASSERT_STRING_EQ("0", string);
    Complex* complex5 = createComplex(0, 3.14);
    string = complexToString(complex5);
    ASSERT_STRING_EQ("3.14i", string);
    Complex* complex6 = createComplex(3.14, 0);
    string = complexToString(complex6);
    ASSERT_STRING_EQ("3.14", string);
    //удаление всех комплексных чисел
    deleteComplex(complex);
    deleteComplex(complex2);
    deleteComplex(complex3);
    deleteComplex(complex4);
    deleteComplex(complex5);
    deleteComplex(complex6);
    //освобождение памяти строки
    free(string);
}

//Тест на сложение матриц
TEST(SCALAR_MULTIPLY_COMPLEX){
    //создание комплексного числа
    Complex *complex = createComplex(5, 3);
    //умножение комплексного числа на скаляр
    Complex *result = scalarMultiplyComplex(complex, 2);
    //проверка, что действительная часть равна 10
    ASSERT_INT_EQ(10, result->real);
    //проверка, что мнимая часть равна 6
    ASSERT_INT_EQ(6, result->imaginary);
    //проверка, что строковое представление комплексного числа равно "10+6i"
    ASSERT_STRING_EQ("10+6i", complexToString(result));
    deleteComplex(complex);
    deleteComplex(result);
}

//Тест на создание матрицы
TEST(CREATE_MATRIX){
    //создание матрицы
    Matrix *matrix = createMatrix(3, 3);
    //проверка, что количество строк и столбцов равно 3
    ASSERT_INT_EQ(3, matrix->rows);
    ASSERT_INT_EQ(3, matrix->columns);
    //проверка, что все элементы матрицы равны NULL
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            ASSERT_NULL(getElement(matrix, i, j));
        }
    }
    //проверка: если количество строк или столбцов равно 0, то матрица не создается
    matrix = createMatrix(0, 3);
    ASSERT_NULL(matrix);
    if(matrix != NULL)
        deleteMatrix(matrix);
}

//Тест на установку элемента матрицы
TEST(MATRIX_SET_ELEM){
    //создание матрицы
    Matrix *matrix = createMatrix(3, 3);
    //создание комплексного числа
    Complex *complex = createComplex(5, 3);
    //установка элемента матрицы
    setElement(matrix, 1, 1, complex);
    //проверка, что элемент матрицы равен "5+3i"
    ASSERT_STRING_EQ("5+3i", complexToString(getElement(matrix, 1, 1)));
    matrix = createMatrix(3, 3);
    Complex* complex2 = NULL;
    setElement(matrix, 1, 1, complex2);
    //проверка, что элемент матрицы равен NULL
    ASSERT_NULL(getElement(matrix, 1, 1));
    //удаление матрицы и комплексного числа
    deleteMatrix(matrix);
    deleteComplex(complex);
}

//Тест на получение элемента матрицы
TEST(MATRIX_GET_ELEM){
    //создание матрицы
    Matrix *matrix = createMatrix(3, 3);
    //создание комплексного числа
    Complex *complex = createComplex(5, 3);
    //установка элемента матрицы
    setElement(matrix, 1, 1, complex);
    //получение элемента матрицы
    ASSERT_STRING_EQ("5+3i", complexToString(getElement(matrix, 1, 1)));
    //получение элемента матрицы, которого нет
    ASSERT_NULL(getElement(matrix, 0, 0));
    //удаление матрицы и комплексного числа
    deleteMatrix(matrix);
    deleteComplex(complex);
}

//Тест на сложение матриц
TEST(MATRIX_ADD){
    //создание двух матриц и установка элементов
    Matrix *matrix1 = createMatrix(2, 2);
    Matrix *matrix2 = createMatrix(2, 2);
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    setElement(matrix1, 0, 0, complex1);
    setElement(matrix1, 0, 1, complex2);
    setElement(matrix1, 1, 0, complex1);
    setElement(matrix1, 1, 1, complex2);
    setElement(matrix2, 0, 0, complex2);
    setElement(matrix2, 0, 1, complex1);
    setElement(matrix2, 1, 0, complex2);
    setElement(matrix2, 1, 1, complex1);
    //сложение матриц
    Matrix *result = add(matrix1, matrix2);
    //проверка на правильность сложения всех элементов
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 1, 1)));
    matrix1 = createMatrix(2, 3);
    matrix2 = createMatrix(2, 2);
    //сложение матриц разного размера
    result = add(matrix1, matrix2);
    //проверка, что результат равен NULL
    EXPECT_NULL(result);
    //удаление матриц
    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    if(result != NULL)
        deleteMatrix(result);
}

//Тест на сложение матриц с комплексными числами
TEST(MATRIX_ADD_HARD){
    Matrix *matrix1 = createMatrix(2, 2);
    Matrix *matrix2 = createMatrix(2, 2);
    Complex *complex1 = createComplex(0, 2);
    Complex *complex2 = createComplex(0, -2);
    setElement(matrix1, 0, 0, complex1);
    setElement(matrix1, 0, 1, complex1);
    setElement(matrix1, 1, 0, complex1);
    setElement(matrix1, 1, 1, complex2);
    setElement(matrix2, 0, 0, complex1);
    setElement(matrix2, 0, 1, complex1);
    setElement(matrix2, 1, 0, complex1);
    setElement(matrix2, 1, 1, complex2);
    Matrix *result = add(matrix1, matrix2);
    //проверка на сложение чисто комплексных чисел
    EXPECT_STRING_EQ("4i", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("4i", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("4i", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("-4i", complexToString(getElement(result, 1, 1)));
    complex1 = createComplex(2, 0);
    complex2 = createComplex(-2, 0);
    setElement(matrix1, 0, 0, complex1);
    setElement(matrix1, 0, 1, complex1);
    setElement(matrix1, 1, 0, complex1);
    setElement(matrix1, 1, 1, complex2);
    setElement(matrix2, 0, 0, complex1);
    setElement(matrix2, 0, 1, complex1);
    setElement(matrix2, 1, 0, complex1);
    setElement(matrix2, 1, 1, complex2);
    result = add(matrix1, matrix2);
    //проверка на сложение чисто действительных чисел
    EXPECT_STRING_EQ("4", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("4", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("4", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("-4", complexToString(getElement(result, 1, 1)));
    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    if(result != NULL)
        deleteMatrix(result);
}

//Тест на умножение матриц
TEST(MATRIX_MULTIPLY){
    //создание матриц и установка элементов
    Matrix *matrix1 = createMatrix(2, 2);
    Matrix *matrix2 = createMatrix(2, 2);
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    setElement(matrix1, 0, 0, complex1);
    setElement(matrix1, 0, 1, complex2);
    setElement(matrix1, 1, 0, complex1);
    setElement(matrix1, 1, 1, complex2);
    setElement(matrix2, 0, 0, complex2);
    setElement(matrix2, 0, 1, complex1);
    setElement(matrix2, 1, 0, complex2);
    setElement(matrix2, 1, 1, complex1);
    Matrix *result = multiply(matrix1, matrix2);
    //проверка на правильность умножения всех элементов
    EXPECT_STRING_EQ("-14+42i", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("14+56i", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("-14+42i", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("14+56i", complexToString(getElement(result, 1, 1)));
    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    Matrix* matrix3 = createMatrix(2, 3);
    Matrix* matrix4 = createMatrix(4, 5);
    result = multiply(matrix3, matrix4);
    //проверка, что результат равен NULL у матриц разного размера
    EXPECT_NULL(result);
    if(result != NULL)
        deleteMatrix(result);
    deleteMatrix(matrix3);
    deleteMatrix(matrix4);
}

//Тест на умножение матриц на скаляр
TEST(MATRIX_SCALAR_MULTIPLY){
    Matrix *matrix = createMatrix(2, 2);
    ASSERT_NOT_NULL(matrix)
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    setElement(matrix, 0, 0, complex1);
    setElement(matrix, 0, 1, complex2);
    setElement(matrix, 1, 0, complex1);
    setElement(matrix, 1, 1, complex2);
    Matrix *result = scalarMultiply(matrix, complex1);
    //проверка что функция complexToString работает
    ASSERT_NOT_NULL(complexToString(getElement(result, 0, 0)));
    //проверка на правильность умножения всех элементов на скаляр
    EXPECT_STRING_EQ("16+30i", complexToString(getElement(result, 0, 0)));
    ASSERT_NOT_NULL(complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("-2+26i", complexToString(getElement(result, 0, 1)));
    ASSERT_NOT_NULL(complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("16+30i", complexToString(getElement(result, 1, 0)));
    ASSERT_NOT_NULL(complexToString(getElement(result, 1, 1)));
    EXPECT_STRING_EQ("-2+26i", complexToString(getElement(result, 1, 1)));
    deleteMatrix(matrix);
    if(result != NULL)
        deleteMatrix(result);
}