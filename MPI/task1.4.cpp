#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int a[10];
    MPI_Status status;
    int current_process, proc_count;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

    if (current_process == 1) {
        for (int i = 0; i < 10; i++) {
            a[i] = 1 + std::rand() % 100;
        }

        for (int i = 0; i < proc_count; i++) {
            if (i != 1) {
                MPI_Send(a, 10, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

    } else {
        
        int data_count;

        MPI_Probe(1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &data_count);

        int buf[data_count];

        MPI_Recv(buf, data_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < data_count; i++) {
            std::cout << buf[i] << " ";
        }

        std::cout << '\n';
    }
    
    MPI_Finalize();
    
    return 0;
}