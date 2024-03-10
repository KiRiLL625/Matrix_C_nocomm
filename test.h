//
// Created by Admin on 09.03.2024.
//

#ifndef L1_TEST_H
#define L1_TEST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int tests_passed;
extern const int total_tests;

//todo: fix total_tests
#define TEST(test_name) void test_name()
#define RUN_TEST(test_name) printf("================[RUNNING TEST: %s]================\n", #test_name); test_name()
#define EXPECT_INT_EQ(expected, actual) if(expected != actual){ printf("[TEST FAILED]: %d != %d\n", expected, actual);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define ASSERT_INT_EQ(expected, actual) if(expected != actual){ printf("[TEST FAILED]: %d != %d\n===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n", expected, actual, tests_passed, total_tests, (tests_passed * 100) / total_tests); exit(0);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define EXPECT_DOUBLE_EQ(expected, actual) if(expected != actual){ printf("[TEST FAILED]: %f != %f\n", expected, actual);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define ASSERT_DOUBLE_EQ(expected, actual) if(expected != actual){ printf("[TEST FAILED]: %f != %f\n===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n", expected, actual, tests_passed, total_tests, (tests_passed * 100) / total_tests); exit(0);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define EXPECT_STRING_EQ(expected, actual) if(strcmp(expected, actual) != 0){ printf("[TEST FAILED]: %s != %s\n", expected, actual);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define ASSERT_STRING_EQ(expected, actual) if(strcmp(expected, actual) != 0){ printf("[TEST FAILED]: %s != %s\n===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n", expected, actual, tests_passed, total_tests, (tests_passed * 100) / total_tests); exit(0);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define EXPECT_NULL(actual) if(actual != NULL){ printf("[TEST FAILED]: %s != NULL\n", #actual);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define ASSERT_NULL(actual) if(actual != NULL){ printf("[TEST FAILED]: %s != NULL\n===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n", #actual, tests_passed, total_tests, (tests_passed * 100) / total_tests); exit(0);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define ASSERT_NOT_NULL(actual) if(actual == NULL){ printf("[TEST FAILED]: %s == NULL\n===================================[TESTS PASSED: %d/%d (%d%%)]===================================\n", #actual, tests_passed, total_tests, (tests_passed * 100) / total_tests); exit(0);} else {printf("[TEST PASSED]\n"); tests_passed++;}
#define EXPECT_NOT_NULL(actual) if(actual == NULL) printf("[TEST FAILED]: %s == NULL\n", #actual); else {printf("[TEST PASSED]\n"); tests_passed++;}
#endif //L1_TEST_H