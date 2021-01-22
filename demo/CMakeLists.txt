cmake_minimum_required(VERSION 3.17)
project(dcfsm C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(dcecho demo.c)
target_link_libraries(dcecho dcfsm)
target_compile_options(dcecho PRIVATE -Wpedantic -Wall -Wextra)

