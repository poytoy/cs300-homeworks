cmake_minimum_required(VERSION 3.24)
project(objection)

set(CMAKE_CXX_STANDARD 17)

add_executable(tree main.cpp AVLSearchTree.h WordItem.h WordItem.cpp DocumentItem.h DocumentItem.cpp FileReaderFunc.h)
