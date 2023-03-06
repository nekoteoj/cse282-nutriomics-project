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
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set (LIB_FILES
     ${SRC_DIR}/sum.cpp
     ${SRC_DIR}/nim.cpp
     ${SRC_DIR}/util.cpp)

add_executable(nutriomics_main ${SRC_DIR}/nutriomics_main.cpp ${LIB_FILES})
target_include_directories(nutriomics_main PRIVATE ${INCLUDE_DIR})

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# Testing
add_executable(test_util ${TEST_DIR}/test_util.cpp ${LIB_FILES})
target_link_libraries(test_util PRIVATE Catch2::Catch2WithMain)
target_include_directories(test_util PRIVATE ${INCLUDE_DIR})

add_executable(test_nim ${TEST_DIR}/test_nim.cpp ${LIB_FILES})
target_link_libraries(test_nim PRIVATE Catch2::Catch2WithMain)
target_include_directories(test_nim PRIVATE ${INCLUDE_DIR})

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(test_util)
catch_discover_tests(test_nim)
