//
// Created by Admin on 26.02.2024.
//

#include "DynamicArray.h"

#include <stdlib.h>

DynamicArray *createDynamicArray(int capacity){
    DynamicArray *dynamicArray = (DynamicArray *) malloc(sizeof(DynamicArray));
    dynamicArray->array = (void **) malloc(capacity * sizeof(void *));
    dynamicArray->size = 0;
    dynamicArray->capacity = capacity;
    return dynamicArray;
}

void deleteDynamicArray(DynamicArray *dynamicArray) {
    free(dynamicArray->array);
    free(dynamicArray);
}

void insert(DynamicArray *dynamicArray, int index, void* value) {
    if (dynamicArray->size == dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        void** tmp = (void **) realloc(dynamicArray->array, dynamicArray->capacity * sizeof(void *));
        if (tmp != NULL) {
            dynamicArray->array = tmp;
        }
        else {
            return;
        }
    }
    for (int i = dynamicArray->size; i > index; i--) {
        dynamicArray->array[i] = dynamicArray->array[i - 1];
    }
    dynamicArray->array[index] = value;
    dynamicArray->size++;
}

void append(DynamicArray *dynamicArray, void* value) {
    insert(dynamicArray, dynamicArray->size, value);
}

void erase(DynamicArray *dynamicArray, int index) {
    for (int i = index; i < dynamicArray->size - 1; i++) {
        dynamicArray->array[i] = dynamicArray->array[i + 1];
    }
    dynamicArray->size--;
}

void* get(DynamicArray *dynamicArray, int index) {
    return dynamicArray->array[index];
}

void set(DynamicArray *dynamicArray, int index, void* value) {
    dynamicArray->array[index] = value;
}

int size(DynamicArray *dynamicArray) {
    return dynamicArray->size;
}

int capacity(DynamicArray *dynamicArray) {
    return dynamicArray->capacity;
}