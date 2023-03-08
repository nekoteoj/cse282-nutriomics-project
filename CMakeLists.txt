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

set(LIB_FILES
        ${SRC_DIR}/ds/nim.cpp
        ${SRC_DIR}/ds/patient.cpp
        ${SRC_DIR}/ds/treatment.cpp
        ${SRC_DIR}/cli/argument.cpp
        ${SRC_DIR}/util/util.cpp
        ${SRC_DIR}/util/sum.cpp
        ${SRC_DIR}/core/scoring.cpp
        ${SRC_DIR}/core/solver.cpp
        ${SRC_DIR}/core/report.cpp)

set(TEST_FILES
        ds/test_nim
        ds/test_patient
        ds/test_treatment
        util/test_util
        core/test_scoring
        core/test_solver)

# Setup Armadillo
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Setup argparse
include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/argparse-src/include)

# Setup main executable
add_executable(nutriomics_main ${SRC_DIR}/cli/nutriomics_main.cpp ${LIB_FILES})
target_link_libraries(nutriomics_main PRIVATE ${ARMADILLO_LIBRARIES})
target_link_libraries(nutriomics_main PRIVATE argparse)
target_include_directories(nutriomics_main PRIVATE ${INCLUDE_DIR})

# Setup test
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

foreach(TEST_FILE ${TEST_FILES})
        STRING(REGEX REPLACE "^ds/|^util/|^core/" "" TEST_NAME ${TEST_FILE})
        add_executable(${TEST_NAME} ${TEST_DIR}/${TEST_FILE}.cpp ${LIB_FILES})
        target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
        target_link_libraries(${TEST_NAME} PRIVATE ${ARMADILLO_LIBRARIES})
        target_link_libraries(${TEST_NAME} PRIVATE argparse)
        target_include_directories(${TEST_NAME} PRIVATE ${INCLUDE_DIR})
        catch_discover_tests(${TEST_NAME})
endforeach()
