#include <iostream>
#include <mpi.h>
#include <sycl/sycl.hpp>

//inline auto partitionable(sycl::device device) {
//  // Earlier commits used the query API, but they return true even
//  // though a partition will fail:  Intel MPI mpirun with multiple
//  // processes.
//  try {
//    device.create_sub_devices<
//        sycl::info::partition_property::partition_by_affinity_domain>(
//        sycl::info::partition_affinity_domain::numa);
//  } catch (sycl::exception const &e) {
//    if (e.code() == sycl::errc::invalid ||
//        e.code() == sycl::errc::feature_not_supported) {
//      return false;
//    } else {
//      throw;
//    }
//  }
//
//  return true;
//}

int my_rank, comm_size;

//inline sycl::queue select_queue(bool check_different_devices = false) {
//  std::vector<sycl::device> devices;
//
//  auto root_devices = sycl::platform().get_devices();
//
//  for (auto &&root_device : root_devices) {
//	std::cout << "Root device: " << root_device.get_info<sycl::info::device::name>() << "\n";
//    if (partitionable(root_device)) {
//      auto subdevices = root_device.create_sub_devices<
//          sycl::info::partition_property::partition_by_affinity_domain>(
//          sycl::info::partition_affinity_domain::numa);
//      assert(std::size(subdevices) > 0);
//
//      for (auto &&subdevice : subdevices) {
//        std::cout << "  add subdevice: {}" << subdevice.get_info<sycl::info::device::name>() << "\n";
//        devices.push_back(subdevice);
//      }
//    } else {
//      std::cout << "  add root device: " << root_device.get_info<sycl::info::device::name>() << "\n";
//	  devices.push_back(root_device);
//    }
//  }
//
//  assert(std::size(devices) > 0);
//  assert(!check_different_devices || my_rank < std::size(devices));
//
//  // Round robin assignment of devices to ranks
//  return sycl::queue(devices[my_rank % std::size(devices)]);
//}

int main() {

  MPI_Init(nullptr, nullptr);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

//  static constexpr std::size_t scratchpad_size_ = 1000000;
//
//  std::vector<char> root_scratchpad_;
//  root_scratchpad_.resize(scratchpad_size_);
//  void *data = root_scratchpad_.data();
//  std::size_t size = std::size(root_scratchpad_) * sizeof(root_scratchpad_[0]);
//
//  MPI_Win win_ = MPI_WIN_NULL;
//  MPI_Win_create(data, size, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win_);
//  MPI_Win_fence(0, win_);

  sycl::usm::alloc kind = sycl::usm::alloc::host;
  sycl::queue sycl_queue_; // = select_queue();

  //std::byte* mem = sycl::malloc<std::byte>(40, sycl_queue_, kind);
  std::byte* mem = new std::byte[40];

  MPI_Win win_2 = MPI_WIN_NULL;
  MPI_Win_create(mem, 40, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win_2);

  //MPI_Win_free(&win_);
  MPI_Win_free(&win_2);
  //sycl::free(mem, sycl_queue_);
  delete[] mem;

  MPI_Finalize();
  return 0;
}
