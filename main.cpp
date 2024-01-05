#include <mpi.h>
#include <sycl/sycl.hpp>

int main() {

  MPI_Init(nullptr, nullptr);

#ifdef USE_SYCL
  sycl::usm::alloc kind = sycl::usm::alloc::host; // problem is with all shared/device/host
  sycl::queue sycl_queue_;
  std::byte* mem = sycl::malloc<std::byte>(40, sycl_queue_, kind);
#else
  std::byte* mem = new std::byte[40];
#endif

  MPI_Win win = MPI_WIN_NULL;
  MPI_Win_create(mem, 40, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  MPI_Win_free(&win);

#ifdef USE_SYCL
  sycl::free(mem, sycl_queue_);
#else
  delete[] mem;
#endif

  MPI_Finalize();
  return 0;
}
