//
// Created by Admin on 26.02.2024.
//

#ifndef L1_DYNAMICARRAY_H
#define L1_DYNAMICARRAY_H


typedef struct {
    void **array;
    int size;
    int capacity;
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
