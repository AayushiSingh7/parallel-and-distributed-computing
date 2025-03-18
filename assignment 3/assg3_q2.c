#include <mpi.h>
#include <stdio.h>

#define NUM_STEPS 100000  // Total number of steps

int main(int argc, char *argv[]) {
    int rank, size, i;
    double step, x, partial_sum = 0.0, global_sum = 0.0, pi;
    
    MPI_Init(&argc, &argv);                  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);     
    MPI_Comm_size(MPI_COMM_WORLD, &size);     

    // Step size
    step = 1.0 / (double)NUM_STEPS;

    // Broadcast step size to all processes
    MPI_Bcast(&step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Each process computes its portion of the sum
    for (i = rank; i < NUM_STEPS; i += size) {
        x = (i + 0.5) * step;
        partial_sum += 4.0 / (1.0 + x * x);
    }

    // Reduce all partial sums to get the final sum
    MPI_Reduce(&partial_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 calculates π and prints result
    if (rank == 0) {
        pi = step * global_sum;
        printf("Computed π value: %.12f\n", pi);
    }

    MPI_Finalize();
    return 0;
}
