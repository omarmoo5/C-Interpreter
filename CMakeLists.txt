cmake_minimum_required(VERSION 3.16)
project(Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Project main.c stack.h stack.c tree.c tree.h helpers.c helpers.h)

target_link_libraries(Project m)