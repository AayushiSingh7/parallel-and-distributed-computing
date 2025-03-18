#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 70

void matrix_multiply(int rank, int size, double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]) {
    int i, j, k;
    for (i = rank; i < SIZE; i += size) {
        for (j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    double start_time, run_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Initialize matrices A and B
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }
    }

    start_time = omp_get_wtime();

    // Broadcast matrices A and B to all processes
    MPI_Bcast(A, SIZE * SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, SIZE * SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Perform matrix multiplication
    matrix_multiply(rank, size, A, B, C);

    // Gather the result matrix C from all processes
    MPI_Gather(C, SIZE * SIZE / size, MPI_DOUBLE, C, SIZE * SIZE / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    run_time = omp_get_wtime() - start_time;

    if (rank == 0) {
        printf("Matrix multiplication completed in %lf seconds.\n", run_time);
    }

    MPI_Finalize();
    return 0;
}