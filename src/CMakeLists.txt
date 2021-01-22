cmake_minimum_required(VERSION 3.17)
project(dcfsm C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(dcfsm STATIC fsm.c)
target_compile_options(dcfsm PRIVATE -Wpedantic -Wall -Wextra)

install(TARGETS dcfsm DESTINATION lib)
install(FILES fsm.h DESTINATION include/dcfsm)
