//
// Created by Admin on 07.03.2024.
//

#ifndef L1_COMPLEX_H
#define L1_COMPLEX_H

// Структура для комплексного числа (a + bi)
typedef struct{
    double real; // действительная часть
    double imaginary; // мнимая часть
} Complex;

Complex *createComplex(double real, double imaginary);

void deleteComplex(Complex *complex);

Complex *addComplex(Complex *complex1, Complex *complex2);

Complex *multiplyComplex(Complex *complex1, Complex *complex2);

Complex *scalarMultiplyComplex(Complex *complex, double scalar);

Complex *stringToComplex(char *string);

char *complexToString(Complex *complex);

#endif //L1_COMPLEX_H
