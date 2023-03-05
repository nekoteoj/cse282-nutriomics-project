cmake_minimum_required(VERSION 3.20)

project(nutriomics_project
        VERSION 1.0.0
        DESCRIPTION "CSE282 Final Project"
        LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-omit-frame-pointer")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set (LIB_FILES
     ${SRC_DIR}/sum.cpp)

add_executable(nutriomics_main ${SRC_DIR}/nutriomics_main.cpp ${LIB_FILES})
target_include_directories(nutriomics_main PRIVATE ${INCLUDE_DIR})
