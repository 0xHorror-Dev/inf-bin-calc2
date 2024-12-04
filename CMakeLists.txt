cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("inf-bin-calc2")

add_subdirectory("bop")
add_executable("calc" "source/main.c")

target_link_libraries("calc" PUBLIC bops)