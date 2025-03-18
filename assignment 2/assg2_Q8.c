#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  // Matrix size

void print_matrix(char *name, double matrix[N][N]) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    double A[N][N], B[N][N];
    double local_A[N][N], local_B[N][N];
    int rows_per_proc;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    rows_per_proc = N / size;  // Distribute rows evenly

    // Initialize matrix in rank 0
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i * N + j + 1;  // Example values
            }
        }
        print_matrix("Original Matrix A", A);
    }

    // Scatter rows of A to all processes
    MPI_Scatter(A, rows_per_proc * N, MPI_DOUBLE, local_A, rows_per_proc * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Compute local transposition
    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < N; j++) {
            local_B[j][i + rank * rows_per_proc] = local_A[i][j];  // Transpose block
        }
    }

    // Gather transposed blocks back to rank 0
    MPI_Gather(local_B, rows_per_proc * N, MPI_DOUBLE, B, rows_per_proc * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Print transposed matrix in rank 0
    if (rank == 0) {
        print_matrix("Transposed Matrix B", B);
    }

    MPI_Finalize();
    return 0;
}
