cmake_minimum_required(VERSION 3.24)

project(Hydra2D VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_definitions(-Wall -O3 -fopenmp)
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")


include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB CPP_SOURCES "source/*.cpp")

add_executable(Hydra2D ${CPP_SOURCES} main.cpp)