cmake_minimum_required(VERSION 3.8)
project(expression_parser)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Parser.cpp Parser.h)

add_executable(expression_parser ${SOURCE_FILES})