cmake_minimum_required(VERSION 3.24)
project(mpiexperiments)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
    message(FATAL_ERROR "use intel compiler")
endif()

add_compile_options(-fsycl)
add_link_options(-fsycl)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")

set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

set(CMAKE_CXX_STANDARD 17)
find_package(MPI REQUIRED)

add_executable(mpiexperiments main.cpp)
target_link_libraries(mpiexperiments PRIVATE MPI::MPI_CXX)

