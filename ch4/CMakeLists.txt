cmake_minimum_required(VERSION 3.16.4)
project(ch4 C)

set(CMAKE_C_STANDARD 11)

find_package (Threads)

add_executable(ch4 main.c)

target_link_libraries (ch4 ${CMAKE_THREAD_LIBS_INIT})