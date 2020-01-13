cmake_minimum_required(VERSION 3.10)
project(affine_ciphers)

set(CMAKE_CXX_STANDARD 14)
add_executable(affine_ciphers main.cpp io_helper.h program.cpp program.h ui.h)
target_compile_options(affine_ciphers PRIVATE -MT)