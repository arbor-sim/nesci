project(nesci-test-package)
cmake_minimum_required(VERSION 2.8)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP(TARGETS)

add_executable(nesci-test-package main.cpp)
target_link_libraries(nesci-test-package CONAN_PKG::nesci)
