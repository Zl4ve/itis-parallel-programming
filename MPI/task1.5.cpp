#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    MPI_Status status;
    int current_process, proc_count;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

    if (current_process != 0) {

        int number = current_process * 10;

        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } else {

        int number;

        for (int i = 1; i < proc_count; i++) {
            MPI_Recv(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            std::cout << number << " ";
        }
    }
    
    MPI_Finalize();
    
    return 0;
}