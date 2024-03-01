cmake_minimum_required(VERSION 3.25)
project(l1 C)

set(CMAKE_C_STANDARD 11)

add_executable(l1 main.c DynamicArray.h DynamicArray.c Matrix.h Matrix.c)
