//
// Created by Admin on 07.03.2024.
//

#include "Complex.h"
#include <stdlib.h>
#include <stdio.h>

//функция создания комплексного числа
Complex *createComplex(double real, double imaginary) {
    //выделение памяти под структуру
    Complex *complex = (Complex *) malloc(sizeof(Complex));
    //инициализация полей структуры
    complex->real = real;
    complex->imaginary = imaginary;
    //возвращение указателя на структуру
    return complex;
}

//функция удаления комплексного числа (очистка памяти)
void deleteComplex(Complex *complex) {
    //очистка памяти структуры
    free(complex);
}

//функция сложения комплексных чисел
Complex *addComplex(Complex *complex1, Complex *complex2) {
    //складываем действительные и мнимые части отдельно
    return createComplex(complex1->real + complex2->real, complex1->imaginary + complex2->imaginary);
}

//функция умножения комплексных чисел
Complex *multiplyComplex(Complex *complex1, Complex *complex2) {
    //умножение комплексных чисел по формуле (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
    return createComplex(complex1->real * complex2->real - complex1->imaginary * complex2->imaginary,
                         complex1->real * complex2->imaginary + complex1->imaginary * complex2->real);
}

//функция умножения комплексного числа на скаляр
Complex *scalarMultiplyComplex(Complex *complex, double scalar) {
    //умножение действительной и мнимой части на скаляр
    return createComplex(complex->real * scalar, complex->imaginary * scalar);
}

//функция преобразования строки в комплексное число
Complex *stringToComplex(char *string) {
    //проверка: если строка пустая, то возвращаем NULL
    if (string == NULL)
        return NULL;
    //переменные для действительной и мнимой частей
    double real, imaginary;
    //переменная для символа 'i'
    char i;
    //проверка: если строка соответствует шаблону a+bi, то считываем действительную и мнимую части
    if (sscanf(string, "%lf+%lf%c", &real, &imaginary, &i) == 3 && i == 'i')
        return createComplex(real, imaginary);
    //проверка: если строка соответствует шаблону a-bi, то считываем действительную и мнимую части
    else if (sscanf(string, "%lf-%lf%c", &real, &imaginary, &i) == 3 && i == 'i')
        return createComplex(real, -imaginary);
    //проверка: если строка соответствует шаблону bi, то считываем только мнимую часть
    else if (sscanf(string, "%lf%c", &imaginary, &i) == 2 && i == 'i')
        return createComplex(0, imaginary);
    //проверка: если строка соответствует шаблону a, то считываем только действительную часть
    else if (sscanf(string, "%lf", &real) == 1)
        return createComplex(real, 0);
    //возвращаем NULL, если строка не соответствует шаблонам
    return NULL;
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
    //проверка: если действительная и мнимая части целые числа
    if((int) complex->imaginary == complex->imaginary && (int) complex->real == complex->real) {
        //выводим действительную и мнимую части без дробной части
        sprintf(string, "%.0lf%+.0lfi", complex->real, complex->imaginary);
    }
    //проверка: если действительная часть целое число, а мнимая - дробное
    else if((int) complex->real == complex->real && (int) complex->imaginary != complex->imaginary){
        //выводим действительную часть без дробной части, а мнимую - с двумя знаками после запятой
        sprintf(string, "%.0lf%+.2lfi", complex->real, complex->imaginary);
    }
    //проверка: если действительная часть дробное число, а мнимая - целое
    else if((int) complex->real != complex->real && (int) complex->imaginary == complex->imaginary){
        //выводим действительную часть с двумя знаками после запятой, а мнимую - без дробной части
        sprintf(string, "%.2lf%+.0lfi", complex->real, complex->imaginary);
    }
    //выводим действительную и мнимую части с двумя знаками после запятой
    else
        sprintf(string, "%.2lf%+.2lfi", complex->real, complex->imaginary);

    //+ после % нужен для вывода знака + перед мнимой частью, иначе число 5+3i будет выведено как 53i (без +)
    return string;
}