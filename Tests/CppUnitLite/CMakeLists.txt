cmake_minimum_required(VERSION 3.0)
project(CppUnitLite)

# define the project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)

# which directories will be include to project. Used for includes in code
# like this #include <include/eos/io/print.hpp> or #include <eos/io/print.hpp>
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include/CppUnitLite)

# Find source files
file(GLOB_RECURSE INCLUDES include/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)


# Create static library
add_library(${PROJECT_NAME} STATIC ${INCLUDES} ${SOURCES})
