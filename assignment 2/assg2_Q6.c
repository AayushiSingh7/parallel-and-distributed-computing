#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000  // Vector size

int main(int argc, char *argv[]) {
    int rank, size, i;
    double local_dot = 0.0, global_dot = 0.0;
    double *A, *B;
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;  // Divide work equally

    // Allocate memory for local parts of vectors
    A = (double *)malloc(chunk_size * sizeof(double));
    B = (double *)malloc(chunk_size * sizeof(double));

    // Seed random generator differently for each process
    srand(time(NULL) + rank);

    // Initialize A and B with random values
    for (i = 0; i < chunk_size; i++) {
        A[i] = rand() % 10;  // Values between 0-9
        B[i] = rand() % 10;
        local_dot += A[i] * B[i];  // Compute local dot product
    }

    printf("Process %d - Local Dot Product: %f\n", rank, local_dot);

    // Reduce all local dot products to compute the final dot product
    MPI_Reduce(&local_dot, &global_dot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Final Dot Product: %f\n", global_dot);
    }

    // Free memory
    free(A);
    free(B);

    MPI_Finalize();
    return 0;
}
