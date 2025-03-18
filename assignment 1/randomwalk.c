#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    srand(time(NULL) + world_rank);
    int token;
    if (world_rank == 0) {
        token = 0;
        int next = rand() % world_size;
        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf("Process 0 sent token %d to process %d\n", token, next);
    }
    
    while (1) {
        MPI_Status status;
        MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
        
        token++;
        int next = rand() % world_size;
        if (token >= 10) break;
        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf("Process %d sent token %d to process %d\n", world_rank, token, next);
    }
    
    MPI_Finalize();
}
