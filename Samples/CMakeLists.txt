cmake_minimum_required(VERSION 3.1)
project(eos_samples)


set (CMAKE_CXX_STANDARD 11)

# define the project
set(CMAKE_BUILD_TYPE Release)


# which directories will be include to project. Used for includes in code
# like this #include <include/eos/io/print.hpp> or #include <eos/io/print.hpp>
include_directories(./ ../include)
link_directories(../lib)

# Find source files
file(GLOB_RECURSE INCLUDES *.h)
file(GLOB_RECURSE INCLUDES *.hpp)
file(GLOB_RECURSE SOURCES *.cpp)

find_package (Threads)

# Create application
add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})
target_link_libraries(${PROJECT_NAME} eos)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
