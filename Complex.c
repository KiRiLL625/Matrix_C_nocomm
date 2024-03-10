//
// Created by Admin on 07.03.2024.
//

#include "Complex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Complex *createComplex(double real, double imaginary) {
    Complex *complex = (Complex *) malloc(sizeof(Complex));
    complex->real = real;
    complex->imaginary = imaginary;
    return complex;
}

void deleteComplex(Complex *complex) {
    free(complex);
}

Complex *addComplex(Complex *complex1, Complex *complex2) {
    return createComplex(complex1->real + complex2->real, complex1->imaginary + complex2->imaginary);
}

Complex *multiplyComplex(Complex *complex1, Complex *complex2) {
    return createComplex(complex1->real * complex2->real - complex1->imaginary * complex2->imaginary,
                         complex1->real * complex2->imaginary + complex1->imaginary * complex2->real);
}

Complex *scalarMultiplyComplex(Complex *complex, double scalar) {
    return createComplex(complex->real * scalar, complex->imaginary * scalar);
}

Complex *stringToComplex(char *string) {
    if (string == NULL)
        return NULL;
    //todo: check if string is valid
    if (strstr(string, "+") == NULL) {
        return NULL;
    }
    char *token = strtok(string, "+");
    if (strstr(token, "i") != NULL) {
        double imaginary = atof(token);
        return createComplex(0, imaginary);
    }
    double real = atof(token);
    token = strtok(NULL, "i");
    double imaginary = atof(token);
    return createComplex(real, imaginary);
}

char *complexToString(Complex *complex) {
    if(complex == NULL)
        return NULL;
    char *string = (char *) malloc(100 * sizeof(char));
    if(complex->imaginary == 0){
        if((int) complex->real == complex->real)
            sprintf(string, "%.0lf", complex->real);
        else
            sprintf(string, "%.2lf", complex->real);
        return string;
    }
    else if(complex->real == 0){
        if((int) complex->imaginary == complex->imaginary)
            sprintf(string, "%.0lfi", complex->imaginary);
        else
            sprintf(string, "%.2lfi", complex->imaginary);
        return string;
    }
    if((int) complex->imaginary == complex->imaginary && (int) complex->real == complex->real)
        sprintf(string, "%.0lf+%.0lfi", complex->real, complex->imaginary);
    else if((int) complex->real == complex->real && (int) complex->imaginary != complex->imaginary)
        sprintf(string, "%.0lf+%.2lfi", complex->real, complex->imaginary);
    else if((int) complex->real != complex->real && (int) complex->imaginary == complex->imaginary)
        sprintf(string, "%.2lf+%.0lfi", complex->real, complex->imaginary);
    else
        sprintf(string, "%.2lf+%.2lfi", complex->real, complex->imaginary);
    return string;
}