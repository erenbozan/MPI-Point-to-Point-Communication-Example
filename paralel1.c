#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank of the current process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Set the size of the message
    const int N = 10;
    int message[N];

    printf("giriyoz %d----\n",rank);
    if(rank==1){
        for (int i = 0; i < N; i++) {
        message[i] = rank + i;
        printf("%d-",rank+i);
        }
    }
    
    printf("\n");

    // Send the message from process 1 to process 0
    if (rank == 1) {
        MPI_Send(message, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Receive the message on process 0
    if (rank == 0) {
        MPI_Recv(message, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Print the message
        printf("Process %d received:", rank);
        for (int i = 0; i < N; i++) {
            printf(" %d", message[i]);
        }
        printf("\n");
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
