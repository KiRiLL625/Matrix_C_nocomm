//
// Created by Admin on 26.02.2024.
//

#ifndef L1_DYNAMICARRAY_H
#define L1_DYNAMICARRAY_H


/*
 Структура для динамического массива
 */
typedef struct {
    void **array; // массив указателей на элементы (void* - указатель на произвольный тип)
    int size; // количество элементов в массиве
    int capacity; // вместимость массива
} DynamicArray;

DynamicArray *createDynamicArray(int capacity);

void deleteDynamicArray(DynamicArray *dynamicArray);

void insert(DynamicArray *dynamicArray, int index, void* value);

void append(DynamicArray *dynamicArray, void* value);

void erase(DynamicArray *dynamicArray, int index);

void* get(DynamicArray *dynamicArray, int index);

void set(DynamicArray *dynamicArray, int index, void* value);

int size(DynamicArray *dynamicArray);

int capacity(DynamicArray *dynamicArray);

#endif //L1_DYNAMICARRAY_H
