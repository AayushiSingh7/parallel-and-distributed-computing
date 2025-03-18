#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  if (world_rank == 0) {
    int data[] = {10, 20, 30, 40, 50};
    int count = sizeof(data) / sizeof(data[0]);
    MPI_Send(&count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(data, count, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (world_rank == 1) {
    MPI_Status status;
    int count;
    MPI_Recv(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    int *data = (int*)malloc(count * sizeof(int));
    MPI_Recv(data, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    printf("Process 1 received array: ");
    for (int i = 0; i < count; i++) {
      printf("%d ", data[i]);
    }
    printf("\n");
    free(data);
  }
  
  MPI_Finalize();
}
