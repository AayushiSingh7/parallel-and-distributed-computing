#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N (1 << 16)  // Vector size: 65536
#define a 2.5        // Scalar multiplier

void daxpy_serial(double *X, double *Y) {
    for (int i = 0; i < N; i++) {
        X[i] = a * X[i] + Y[i];
    }
}

void daxpy_parallel(int rank, int size, double *X, double *Y) {
    int chunk_size = N / size;  // Divide workload

    for (int i = 0; i < chunk_size; i++) {
        X[i] = a * X[i] + Y[i];
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    double *X, *Y, start, end, time_serial, time_parallel;
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;

    // Allocate memory
    X = (double *)malloc(N * sizeof(double));
    Y = (double *)malloc(N * sizeof(double));

    if (rank == 0) {
        // Initialize vectors
        for (int i = 0; i < N; i++) {
            X[i] = 1.0;
            Y[i] = 2.0;
        }

        // Measure Serial Execution Time
        start = MPI_Wtime();
        daxpy_serial(X, Y);
        end = MPI_Wtime();
        time_serial = end - start;
        printf("Serial Execution Time: %lf seconds\n", time_serial);
    }

    // Scatter data to all processes
    MPI_Scatter(X, chunk_size, MPI_DOUBLE, X, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(Y, chunk_size, MPI_DOUBLE, Y, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Measure Parallel Execution Time
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    daxpy_parallel(rank, size, X, Y);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    time_parallel = end - start;

    // Gather results back to rank 0
    MPI_Gather(X, chunk_size, MPI_DOUBLE, X, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Rank 0 prints the speedup
    if (rank == 0) {
        printf("Parallel Execution Time: %lf seconds\n", time_parallel);
        printf("Speedup: %lf\n", time_serial / time_parallel);
    }

    free(X);
    free(Y);
    MPI_Finalize();
    return 0;
}
