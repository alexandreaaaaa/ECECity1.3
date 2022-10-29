cmake_minimum_required(VERSION 3.23)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled2 main.c )

target_link_libraries(untitled2 -lmingw32 -lalleg44)