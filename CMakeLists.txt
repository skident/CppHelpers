cmake_minimum_required(VERSION 2.6)
project(Cpp_helper)

# define the project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Target
set(SOURCES 
		main.cpp
)
set(HEADERS 	
		stl_helper.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})