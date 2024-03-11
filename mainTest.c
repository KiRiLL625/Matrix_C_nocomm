//
// Created by Admin on 09.03.2024.
//

#include "test.h"

int main(){
    //Запуск каждого теста по имени с помощью макроса RUN_TEST
    //В редакторе название тестов может подсвечиваться красным, но это не ошибка
    RUN_TEST(CREATE_DYNAMIC_ARRAY);
    RUN_TEST(CREATE_DYNAMIC_ARRAY_HARD);
    RUN_TEST(INSERT_DYNAMIC_ARRAY);
    RUN_TEST(CREATE_COMPLEX);
    RUN_TEST(ADD_COMPLEX);
    RUN_TEST(MULTIPLY_COMPLEX);
    RUN_TEST(STRING_TO_COMPLEX);
    RUN_TEST(COMPLEX_TO_STRING);
    RUN_TEST(SCALAR_MULTIPLY_COMPLEX);
    RUN_TEST(CREATE_MATRIX);
    RUN_TEST(MATRIX_SET_ELEM);
    RUN_TEST(MATRIX_GET_ELEM);
    RUN_TEST(MATRIX_ADD);
    RUN_TEST(MATRIX_ADD_HARD);
    RUN_TEST(MATRIX_MULTIPLY);
    RUN_TEST(MATRIX_SCALAR_MULTIPLY);

    //если все тесты пройдены, то выводится сообщение "ALL TESTS PASSED"
    if(tests_passed == total_tests)
        printf("===================================[ALL TESTS PASSED]===================================\n");
    else //иначе выводится количество пройденных тестов и процент пройденных тестов
        printf("===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n",
               tests_passed, total_tests, (tests_passed * 100) / total_tests);
    return 0;
}