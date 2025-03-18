#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VALUE 100  // Define the upper limit for prime search

// Function to check if a number is prime
int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size, num, result;
    MPI_Init(&argc, &argv);                  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);     
    MPI_Comm_size(MPI_COMM_WORLD, &size);     

    if (rank == 0) {
        // Master process
        int current = 2, active_workers = size - 1;
        
        while (active_workers > 0) {
            int worker_rank, received;
            MPI_Status status;

            // Receive a request from any worker
            MPI_Recv(&received, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            worker_rank = status.MPI_SOURCE;

            if (received > 0) {
                printf("%d is prime\n", received);
            }

            // Send a new number to test or stop signal (-1)
            if (current <= MAX_VALUE) {
                MPI_Send(&current, 1, MPI_INT, worker_rank, 0, MPI_COMM_WORLD);
                current++;
            } else {
                int stop_signal = -1;
                MPI_Send(&stop_signal, 1, MPI_INT, worker_rank, 0, MPI_COMM_WORLD);
                active_workers--;
            }
        }
    } else {
        // Worker processes
        int test_num;
        
        // Send initial request
        int request = 0;
        MPI_Send(&request, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        while (1) {
            MPI_Recv(&test_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (test_num == -1) break;

            // Check if the number is prime
            result = is_prime(test_num) ? test_num : -test_num;
            
            // Send result back to master
            MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
