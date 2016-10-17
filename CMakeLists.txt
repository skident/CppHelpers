cmake_minimum_required(VERSION 3.0)
project(eos)

# define the project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCES 	
		dummy.cpp  # just for cmake
)

set(HEADERS 	
		print.hpp
		range.hpp
)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
#add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})