cmake_minimum_required(VERSION 3.21)
project(ncu_lesson)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ncu_lesson
        ALG_HW3_Task1.cpp
        ALG_HW3_Task2.cpp
        ALG_HW3_Task3.cpp
        ALG_HW4_Task2.cpp
        DS_HW1_Task1.c
        DS_HW1_Task2.c
        DS_HW2_Task1.c
        DS_HW2_Task2.c
        DS_HW3_Task1.c
        DS_HW3_Task2.c
        DS_HW4_Task1.c
        DS_HW4_Task2.c
        DS_HW4_Task2_test.c
        DS_HW4_Task3.c
        DS_HW4_Task3_test.c
        PL_HW5.cpp)
