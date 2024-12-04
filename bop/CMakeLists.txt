cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

add_library(bops STATIC 
"source/add.c"
"source/basecon.c"
"source/binl.c"
"source/div.c"
"source/mul.c"
"source/sub.c"
)
target_include_directories(bops PUBLIC "inc/")