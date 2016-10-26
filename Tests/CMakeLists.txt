cmake_minimum_required(VERSION 3.0)
project(eos_tests)

# define the project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_BUILD_TYPE Release)

# Find source files
file(GLOB_RECURSE INCLUDES *.h*)
file(GLOB_RECURSE INCLUDES *.hpp)
file(GLOB_RECURSE SOURCES *.cpp)

#add_subdirectory(gtest)

# which directories will be include to project. Used for includes in code
# like this #include <include/eos/io/print.hpp> or #include <eos/io/print.hpp>
include_directories(../include gtest/include)
link_directories(../lib gtest/lib)

# Create application
add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})


target_link_libraries(${PROJECT_NAME} eos gtest)

