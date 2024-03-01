#include <stdio.h>
#include "DynamicArray.h"

int main() {
    DynamicArray *dynamicArray = createDynamicArray(2);
    int a = 1;
    int b = 2;
    int c = 3;
    //char* d = "Hello";
    append(dynamicArray, &a);
    append(dynamicArray, &b);
    append(dynamicArray, &c);

    for(int i = 0; i < size(dynamicArray); i++){
        printf("%d\n", *(int *) get(dynamicArray, i));
    }
    printf("%d\n", *(int *) get(dynamicArray, 2)); //Нумерация с нуля
    deleteDynamicArray(dynamicArray);
    return 0;
}
