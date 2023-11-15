#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int vector_size = 10;
    int part_size = 5;
    int a = 3;
    int b = 2;
    MPI_Status status;
    int current_process;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

    if (current_process == 0) {

        int x[vector_size];
        int y[vector_size];
        int z[vector_size];

        for (int i = 0; i < vector_size; i++) {
            x[i] = 1 + std::rand() % 100;
            y[i] = 1 + std::rand() % 100;
        }

        std::cout << "vector x: ";

        for (int i = 0; i < vector_size; i++) {
            std::cout << x[i] << " ";
        }
        
        std::cout << std::endl;

        std::cout << "vector y: ";

        for (int i = 0; i < vector_size; i++) {
            std::cout << y[i] << " ";
        }
        
        std::cout << std::endl;
        
        int buffer_start_index = 0;

        for (int i = 0; i < vector_size / part_size; i++, buffer_start_index += part_size) {
            MPI_Send(&x[buffer_start_index], part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
            MPI_Send(&y[buffer_start_index], part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
        }

        buffer_start_index = 0;

        for (int i = 0; i < vector_size / part_size; i++, buffer_start_index += part_size) {
            MPI_Recv(&z[buffer_start_index], part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD, &status);
        }

        std::cout << "vector z: ";

        for (int i = 0; i < vector_size; i++) {
            std::cout << z[i] << " ";
        }


    } else {

        int data_count;

        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &data_count);

        int recieved_x[data_count];
        int recieved_y[data_count];
        int part_z[data_count];

        MPI_Recv(&recieved_x[0], data_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&recieved_y[0], data_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < data_count; i++) {
            part_z[i] = a * recieved_x[i] + b * recieved_y[i];
        }

        MPI_Send(&part_z, data_count, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }
    
    MPI_Finalize();
    
    return 0;
}