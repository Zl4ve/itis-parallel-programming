#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int a[10];
    MPI_Status status;
    int currentProcess;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);
    if (currentProcess == 0) {
        for (int i = 0; i < 10; i++) {
            a[i] = 1 + std::rand() % 100;
        }
        
        MPI_Send(a, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (currentProcess == 1) {
        MPI_Recv(a, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < 10; i++) {
            std::cout << a[i] << " ";
        }
    }
    
    MPI_Finalize();
    
    return 0;
}