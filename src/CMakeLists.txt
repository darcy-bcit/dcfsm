cmake_minimum_required(VERSION 3.17)
project(dc_fsm C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(dc_fsm SHARED fsm.c)
target_compile_options(dc_fsm PRIVATE -Wpedantic -Wall -Wextra)

install(TARGETS dc_fsm DESTINATION lib)
install(FILES fsm.h DESTINATION include/dc_fsm)
