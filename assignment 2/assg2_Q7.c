#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 16  // Total number of elements

int main(int argc, char *argv[]) {
    int rank, size, i;
    int local_value, local_prefix_sum, global_prefix_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process gets one value (assuming N = size for simplicity)
    local_value = rank + 1;  // Example: process 0 has 1, process 1 has 2, etc.

    printf("Process %d - Initial Value: %d\n", rank, local_value);

    // Compute parallel prefix sum
    MPI_Scan(&local_value, &local_prefix_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d - Prefix Sum: %d\n", rank, local_prefix_sum);

    MPI_Finalize();
    return 0;
}
