#include <iostream>
#include <mpi.h>

#define SIZE 3000

void get_and_check(MPI_Win win, int rank, int idx, int expected_value)
{
  MPI_Request request;
  int received_value = -1;
  MPI_Rget(
	  &received_value, sizeof(int), MPI_BYTE, rank, idx*sizeof(int), sizeof(int), MPI_BYTE, win, &request);

  MPI_Wait(&request, MPI_STATUS_IGNORE);

  if (received_value != expected_value)
	std::cout << "ERROR: expected:" << expected_value << " but value got:" << received_value << "\n";
}

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  int rank, comm_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  int* buffer = new int[SIZE];
  MPI_Win win = MPI_WIN_NULL;
  MPI_Win_create(buffer, SIZE*sizeof(int), 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  MPI_Win_fence(0, win);

  if (rank == 0) {
	int written_value=0;
	for (int rrank = 0; rrank < comm_size; ++rrank)
	  for (int i=0; i < SIZE; ++i) {
		// this version does not work
		//MPI_Put(&written_value, sizeof(int), MPI_BYTE, rrank, i*sizeof(int), sizeof(int), MPI_BYTE, win);
		// this one does
		MPI_Request request;
		MPI_Rput(&written_value, sizeof(int), MPI_BYTE, rrank, i*sizeof(int), sizeof(int), MPI_BYTE, win, &request);
		MPI_Wait(&request, MPI_STATUS_IGNORE);
		++written_value;
	  }

  }

  MPI_Win_fence(0, win);

  for (int dist=0; dist < SIZE-1; dist++)
  {
	get_and_check(win, comm_size-1, dist, SIZE*(comm_size-1) + dist);
  }

  MPI_Win_fence(0, win);
  MPI_Win_free(&win);
  delete[] buffer;

  return 0;
}
