//
// Created by Admin on 09.03.2024.
//

#include "test.h"

int main(){
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
    RUN_TEST(MATRIX_MULTIPLY);
    RUN_TEST(MATRIX_SCALAR_MULTIPLY);

    if(tests_passed == total_tests)
        printf("===================================[ALL TESTS PASSED]===================================\n");
    else
        printf("===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n",
               tests_passed, total_tests, (tests_passed * 100) / total_tests);
    return 0;
}