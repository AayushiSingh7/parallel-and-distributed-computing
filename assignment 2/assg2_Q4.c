#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define GRID_SIZE 10    // Grid size (NxN)
#define MAX_ITER 500    // Maximum iterations
#define TOLERANCE 0.001 // Convergence threshold

// Function to initialize the grid
void initialize_grid(double grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0.0;  // Initialize all cells to 0.0
        }
    }
    // Set a heat source in the middle
    grid[GRID_SIZE / 2][GRID_SIZE / 2] = 100.0;
}

// Function to print the grid (for debugging)
void print_grid(double grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%6.2f ", grid[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size, i, j, iter;
    double grid[GRID_SIZE][GRID_SIZE], new_grid[GRID_SIZE][GRID_SIZE];
    double diff, max_diff;
    double *recv_grid = NULL;  // Separate buffer for MPI_Gather
    int rows_per_process, start_row, end_row;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    rows_per_process = GRID_SIZE / size;
    start_row = rank * rows_per_process;
    end_row = (rank == size - 1) ? GRID_SIZE - 1 : start_row + rows_per_process;

    if (rank == 0) {
        initialize_grid(grid);
        printf("Initial Heat Distribution:\n");
        print_grid(grid);
    }

    // Broadcast the initial grid to all processes
    MPI_Bcast(grid, GRID_SIZE * GRID_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        recv_grid = (double *)malloc(GRID_SIZE * GRID_SIZE * sizeof(double));
    }

    for (iter = 0; iter < MAX_ITER; iter++) {
        diff = 0.0;

        // Compute new temperature values
        for (i = start_row; i < end_row; i++) {
            for (j = 1; j < GRID_SIZE - 1; j++) {  // Excluding boundary cells
                new_grid[i][j] = 0.25 * (grid[i - 1][j] + grid[i + 1][j] +
                                         grid[i][j - 1] + grid[i][j + 1]);
                diff = fmax(diff, fabs(new_grid[i][j] - grid[i][j]));
            }
        }

        // Synchronize updated values across processes
        MPI_Allgather(&new_grid[start_row], rows_per_process * GRID_SIZE, MPI_DOUBLE,
                      new_grid, rows_per_process * GRID_SIZE, MPI_DOUBLE, MPI_COMM_WORLD);

        // Copy new values into grid
        for (i = start_row; i < end_row; i++) {
            for (j = 1; j < GRID_SIZE - 1; j++) {
                grid[i][j] = new_grid[i][j];
            }
        }

        // Check for convergence
        MPI_Allreduce(&diff, &max_diff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
        if (max_diff < TOLERANCE) {
            if (rank == 0) {
                printf("Converged after %d iterations\n", iter);
            }
            break;
        }
    }

    // Gather final results in process 0 using a separate buffer
    MPI_Gather(&grid[start_row], rows_per_process * GRID_SIZE, MPI_DOUBLE,
               recv_grid, rows_per_process * GRID_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Copy gathered data back to the original grid
        memcpy(grid, recv_grid, GRID_SIZE * GRID_SIZE * sizeof(double));
        printf("Final Heat Distribution:\n");
        print_grid(grid);
        free(recv_grid);
    }

    MPI_Finalize();
    return 0;
}
