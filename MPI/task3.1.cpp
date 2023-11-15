#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int vector_size = 100;
    int part_size = 10;
    int current_process;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    
    int x[vector_size];
    int recieved_buf[part_size];

    if (current_process == 0) {

        std::cout << "vector x: ";

        for (int i = 0; i < vector_size; i++) {
            x[i] = std::rand() % 10 - 4;
            std :: cout << x[i] << " ";
        }

        std::cout << std::endl;
    }

    MPI_Scatter(&x[0], part_size, MPI_INT, &recieved_buf[0], part_size, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;

    for (int i = 0; i < part_size; i++) {
        sum += abs(recieved_buf[i]);
    }

    int res;

    MPI_Reduce(&sum, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (current_process == 0) {
        std::cout << "||x|| = " << res;
    }
    
    MPI_Finalize();
    
    return 0;
}