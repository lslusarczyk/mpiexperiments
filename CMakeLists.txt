cmake_minimum_required(VERSION 3.25)
project(mpiexperiments)

set(CMAKE_CXX_STANDARD 17)
find_package(MPI REQUIRED)

add_executable(mpiexperiments main.cpp)
target_link_libraries(mpiexperiments PRIVATE MPI::MPI_CXX)

add_executable(windowcreate window_create.cpp)
target_link_libraries(mpiexperiments PRIVATE MPI::MPI_CXX)
