//
// Created by Admin on 09.03.2024.
//

#include "test.h"
#include "Matrix.h"
#include "Complex.h"

int tests_passed = 0;
const int total_tests = 76;

TEST(CREATE_DYNAMIC_ARRAY) {
    DynamicArray *dynamicArray = createDynamicArray(10);
    ASSERT_INT_EQ(10, dynamicArray->capacity);
    ASSERT_INT_EQ(0, dynamicArray->size);
    EXPECT_NOT_NULL(dynamicArray->array);
    deleteDynamicArray(dynamicArray);
}

TEST(CREATE_DYNAMIC_ARRAY_HARD){
    DynamicArray *dynamicArray = createDynamicArray(0);
    ASSERT_INT_EQ(0, dynamicArray->capacity);
    ASSERT_INT_EQ(0, dynamicArray->size);
    EXPECT_NOT_NULL(dynamicArray->array);
    deleteDynamicArray(dynamicArray);
}

TEST(INSERT_DYNAMIC_ARRAY){
    DynamicArray *dynamicArray = createDynamicArray(10);
    int value = 5;
    insert(dynamicArray, 0, &value);
    ASSERT_INT_EQ(5, *(int *) get(dynamicArray, 0));
    ASSERT_INT_EQ(1, dynamicArray->size);
    char* string = "Hello";
    insert(dynamicArray, 1, string);
    ASSERT_STRING_EQ("Hello", (char *) get(dynamicArray, 1));
    ASSERT_INT_EQ(2, dynamicArray->size);
    double d = 3.14;
    insert(dynamicArray, 1, &d);
    ASSERT_DOUBLE_EQ(3.14, *(double *) get(dynamicArray, 1));
    ASSERT_INT_EQ(3, dynamicArray->size);
    deleteDynamicArray(dynamicArray);
}

TEST(CREATE_COMPLEX){
    Complex *complex = createComplex(5, 3);
    ASSERT_INT_EQ(5, complex->real);
    ASSERT_INT_EQ(3, complex->imaginary);
    ASSERT_STRING_EQ("5+3i", complexToString(complex));
    deleteComplex(complex);
}

TEST(ADD_COMPLEX){
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    Complex *result = addComplex(complex1, complex2);
    ASSERT_INT_EQ(7, result->real);
    ASSERT_INT_EQ(7, result->imaginary);
    ASSERT_STRING_EQ("7+7i", complexToString(result));
    deleteComplex(complex1);
    deleteComplex(complex2);
    deleteComplex(result);
}

TEST(MULTIPLY_COMPLEX){
    Complex *complex1 = createComplex(5, 3);
    Complex *complex2 = createComplex(2, 4);
    Complex *result = multiplyComplex(complex1, complex2);
    ASSERT_INT_EQ(-2, result->real);
    ASSERT_INT_EQ(26, result->imaginary);
    ASSERT_STRING_EQ("-2+26i", complexToString(result));
    deleteComplex(complex1);
    deleteComplex(complex2);
    deleteComplex(result);
}

TEST(STRING_TO_COMPLEX){
    char string[] = "5+3i";
    Complex *complex = stringToComplex(string);
    EXPECT_NOT_NULL(complex);
    ASSERT_INT_EQ(5, complex->real);
    ASSERT_INT_EQ(3, complex->imaginary);
    deleteComplex(complex);
}

TEST(COMPLEX_TO_STRING){
    Complex *complex = createComplex(5, 3);
    char *string = complexToString(complex);
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
    deleteComplex(complex);
    deleteComplex(complex2);
    deleteComplex(complex3);
    deleteComplex(complex4);
    deleteComplex(complex5);
    deleteComplex(complex6);
    free(string);
}

TEST(SCALAR_MULTIPLY_COMPLEX){
    Complex *complex = createComplex(5, 3);
    Complex *result = scalarMultiplyComplex(complex, 2);
    ASSERT_INT_EQ(10, result->real);
    ASSERT_INT_EQ(6, result->imaginary);
    ASSERT_STRING_EQ("10+6i", complexToString(result));
    deleteComplex(complex);
    deleteComplex(result);
}

TEST(CREATE_MATRIX){
    Matrix *matrix = createMatrix(3, 3);
    ASSERT_INT_EQ(3, matrix->rows);
    ASSERT_INT_EQ(3, matrix->columns);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            ASSERT_NULL(getElement(matrix, i, j));
        }
    }
    matrix = createMatrix(0, 3);
    ASSERT_NULL(matrix);
    if(matrix != NULL)
        deleteMatrix(matrix);
}

TEST(MATRIX_SET_ELEM){
    Matrix *matrix = createMatrix(3, 3);
    Complex *complex = createComplex(5, 3);
    setElement(matrix, 1, 1, complex);
    ASSERT_STRING_EQ("5+3i", complexToString(getElement(matrix, 1, 1)));
    matrix = createMatrix(3, 3);
    Complex* complex2 = NULL;
    setElement(matrix, 1, 1, complex2);
    ASSERT_NULL(getElement(matrix, 1, 1));
    deleteMatrix(matrix);
    deleteComplex(complex);
}

TEST(MATRIX_GET_ELEM){
    Matrix *matrix = createMatrix(3, 3);
    Complex *complex = createComplex(5, 3);
    setElement(matrix, 1, 1, complex);
    ASSERT_STRING_EQ("5+3i", complexToString(getElement(matrix, 1, 1)));
    ASSERT_NULL(getElement(matrix, 0, 0));
    deleteMatrix(matrix);
    deleteComplex(complex);
}

TEST(MATRIX_ADD){
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
    Matrix *result = add(matrix1, matrix2);
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("7+7i", complexToString(getElement(result, 1, 1)));
    matrix1 = createMatrix(2, 3);
    matrix2 = createMatrix(2, 2);
    result = add(matrix1, matrix2);
    EXPECT_NULL(result);
    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    if(result != NULL)
        deleteMatrix(result);
}

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
    EXPECT_STRING_EQ("4", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("4", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("4", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("-4", complexToString(getElement(result, 1, 1)));
    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    if(result != NULL)
        deleteMatrix(result);
}

TEST(MATRIX_MULTIPLY){
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
    EXPECT_STRING_EQ("-14+42i", complexToString(getElement(result, 0, 0)));
    EXPECT_STRING_EQ("14+56i", complexToString(getElement(result, 0, 1)));
    EXPECT_STRING_EQ("-14+42i", complexToString(getElement(result, 1, 0)));
    EXPECT_STRING_EQ("14+56i", complexToString(getElement(result, 1, 1)));
    deleteMatrix(matrix1);
    deleteMatrix(matrix2);
    Matrix* matrix3 = createMatrix(2, 3);
    Matrix* matrix4 = createMatrix(4, 5);
    result = multiply(matrix3, matrix4);
    EXPECT_NULL(result);
    if(result != NULL)
        deleteMatrix(result);
    deleteMatrix(matrix3);
    deleteMatrix(matrix4);
}

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
    ASSERT_NOT_NULL(complexToString(getElement(result, 0, 0)));
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