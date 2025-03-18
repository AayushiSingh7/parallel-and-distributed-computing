#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100  // Number of elements per process

int main(int argc, char *argv[]) {
    int rank, size, i;
    int local_sum = 0, global_sum = 0;
    int data[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator
    srand(time(NULL) + rank);

    // Each process generates its own random data
    for (i = 0; i < N; i++) {
        data[i] = rand() % 10;  // Random numbers between 0 and 9
        local_sum += data[i];
    }

    printf("Process %d - Local Sum: %d\n", rank, local_sum);

    // Perform the reduction operation (sum) and store result in rank 0
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Rank 0 prints the final result
    if (rank == 0) {
        printf("Global Sum: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
