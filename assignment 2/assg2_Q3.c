#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 12  // Size of array (should be divisible by the number of processes)

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Simple local bubble sort function
void local_bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int local_n;
    int *arr = NULL;
    int *local_arr = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_n = N / size;
    local_arr = (int *)malloc(local_n * sizeof(int));

    if (rank == 0) {
        // Generate random array in process 0
        arr = (int *)malloc(N * sizeof(int));
        srand(42);
        printf("Unsorted array: ");
        for (int i = 0; i < N; i++) {
            arr[i] = rand() % 100;
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    // Scatter the array among processes
    MPI_Scatter(arr, local_n, MPI_INT, local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Locally sort the received sub-array
    local_bubble_sort(local_arr, local_n);

    for (int phase = 0; phase < size; phase++) {
        int neighbor;
        if (phase % 2 == 0) {
            // Even phase: even-ranked processes swap with right neighbors
            if (rank % 2 == 0 && rank < size - 1) {
                neighbor = rank + 1;
            } else if (rank % 2 == 1) {
                neighbor = rank - 1;
            } else {
                neighbor = MPI_PROC_NULL;
            }
        } else {
            // Odd phase: odd-ranked processes swap with right neighbors
            if (rank % 2 == 1 && rank < size - 1) {
                neighbor = rank + 1;
            } else if (rank % 2 == 0 && rank > 0) {
                neighbor = rank - 1;
            } else {
                neighbor = MPI_PROC_NULL;
            }
        }

        if (neighbor != MPI_PROC_NULL) {
            int recv_arr[local_n];
            MPI_Sendrecv(local_arr, local_n, MPI_INT, neighbor, 0, 
                         recv_arr, local_n, MPI_INT, neighbor, 0, 
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Merge received and local arrays
            int merged[2 * local_n];
            int i = 0, j = 0, k = 0;
            while (i < local_n && j < local_n) {
                if (local_arr[i] < recv_arr[j]) {
                    merged[k++] = local_arr[i++];
                } else {
                    merged[k++] = recv_arr[j++];
                }
            }
            while (i < local_n) merged[k++] = local_arr[i++];
            while (j < local_n) merged[k++] = recv_arr[j++];

            // Keep appropriate half
            if (rank < neighbor) {
                for (i = 0; i < local_n; i++) {
                    local_arr[i] = merged[i];
                }
            } else {
                for (i = 0; i < local_n; i++) {
                    local_arr[i] = merged[i + local_n];
                }
            }
        }
    }

    // Gather sorted subarrays into process 0
    MPI_Gather(local_arr, local_n, MPI_INT, arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sorted array: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
    }

    free(local_arr);
    MPI_Finalize();
    return 0;
}
