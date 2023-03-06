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
     ${SRC_DIR}/util.cpp
     ${SRC_DIR}/patient.cpp)

set (TEST_FILES
     test_util
     test_nim
     test_patient)

# Setup Armadillo
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Setup main executable
add_executable(nutriomics_main ${SRC_DIR}/nutriomics_main.cpp ${LIB_FILES})
target_link_libraries(nutriomics_main PRIVATE ${ARMADILLO_LIBRARIES})
target_include_directories(nutriomics_main PRIVATE ${INCLUDE_DIR})

# Setup test
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

foreach(TEST_FILE ${TEST_FILES})
        add_executable(${TEST_FILE} ${TEST_DIR}/${TEST_FILE}.cpp ${LIB_FILES})
        target_link_libraries(${TEST_FILE} PRIVATE Catch2::Catch2WithMain)
        target_link_libraries(${TEST_FILE} PRIVATE ${ARMADILLO_LIBRARIES})
        target_include_directories(${TEST_FILE} PRIVATE ${INCLUDE_DIR})
        catch_discover_tests(${TEST_FILE})
endforeach()
