//
// Created by Admin on 26.02.2024.
//

#include "DynamicArray.h"

#include <stdlib.h>

//функция создания динамического массива
DynamicArray *createDynamicArray(int capacity){
    //выделение памяти под структуру
    DynamicArray *dynamicArray = (DynamicArray *) malloc(sizeof(DynamicArray));
    //выделение памяти под массив указателей
    dynamicArray->array = (void **) malloc(capacity * sizeof(void *));
    //инициализация полей структуры (по умолчанию)
    dynamicArray->size = 0;
    dynamicArray->capacity = capacity;
    return dynamicArray;
}

//функция удаления динамического массива (очистка памяти)
void deleteDynamicArray(DynamicArray *dynamicArray) {
    free(dynamicArray->array); //очистка памяти массива указателей
    free(dynamicArray); //очистка памяти структуры
}

//функция вставки элемента в массив
void insert(DynamicArray *dynamicArray, int index, void* value) {
    //проверка: если массив заполнен, то увеличиваем его размер в 2 раза
    if (dynamicArray->size == dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        //выделение памяти под новый массив указателей (временная переменная для
        //избежания обнуления памяти в случае неудачного выделения памяти)
        void** tmp = (void **) realloc(dynamicArray->array, dynamicArray->capacity * sizeof(void *));
        if (tmp != NULL) {
            dynamicArray->array = tmp;
        }
        else {
            //return без ничего - выход из функции
            return;
        }
    }
    //сдвигаем элементы массива вправо
    for (int i = dynamicArray->size; i > index; i--) {
        dynamicArray->array[i] = dynamicArray->array[i - 1];
    }
    //вставляем элемент в освободившееся место
    dynamicArray->array[index] = value;
    //увеличиваем размер массива
    dynamicArray->size++;
}

//функция добавления элемента в конец массива
void append(DynamicArray *dynamicArray, void* value) {
    //вызов функции вставки элемента в массив (в качестве параметра index указывается
    //последний элемент)
    insert(dynamicArray, dynamicArray->size, value);
}

//функция удаления элемента из массива (в программе не используется)
void erase(DynamicArray *dynamicArray, int index) {
    //сдвигаем элементы массива влево
    for (int i = index; i < dynamicArray->size - 1; i++) {
        dynamicArray->array[i] = dynamicArray->array[i + 1];
    }
    //уменьшаем размер массива
    dynamicArray->size--;
}

//функция получения элемента массива по индексу
void* get(DynamicArray *dynamicArray, int index) {
    //возвращаем элемент массива по индексу
    return dynamicArray->array[index];
}

//функция установки значения элемента массива по индексу
void set(DynamicArray *dynamicArray, int index, void* value) {
    dynamicArray->array[index] = value;
}

//функция получения размера массива (не используется)
int size(DynamicArray *dynamicArray) {
    return dynamicArray->size;
}

//функция получения вместимости массива (не используется)
int capacity(DynamicArray *dynamicArray) {
    return dynamicArray->capacity;
}