#include <iostream>
#include <mpi.h>
// #include <sycl/sycl.hpp>

int my_rank, comm_size;

int main() {

  MPI_Init(nullptr, nullptr);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  MPI_Finalize();
  return 0;
}
