#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int size = 10;
    int part_size = 5;
    MPI_Status status;
    int current_process;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

    if (current_process == 0) {

        int matrix[size][size];
        int b[size];
        int c[size];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = 1 + std::rand() % 10;
            }
        }

        for (int i = 0; i < size; i++) {
            b[i] = 1 + std::rand() % 10;
        }

        std::cout << "matrix A:" << std::endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << matrix[i][j] << " ";
            }

            std::cout << std::endl;
        }

        std::cout << "vector b: ";

        for (int i = 0; i < size; i++) {
            std::cout << b[i] << " ";
        }

        std::cout << std::endl;

        int buffer_start_index = 0;

        for (int i = 0; i < size / part_size; i++, buffer_start_index += part_size) {
            MPI_Send(&matrix[buffer_start_index][0], size * part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
            MPI_Send(&b[0], size, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
        }

        buffer_start_index = 0;

        for (int i = 0; i < size / part_size; i++, buffer_start_index += part_size) {
            MPI_Recv(&c[buffer_start_index], part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD, &status);
        }

        std::cout << "vector C: ";
        for (int i = 0; i < size; i++) {
            std::cout << c[i] << " ";
        }

    } else {

        int data_count;

        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &data_count);

        int recieved_matrix[part_size][size];
        int recieved_b[size];
        int part_c[part_size] = {0};

        MPI_Recv(&recieved_matrix[0][0], size * part_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&recieved_b[0], size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < part_size; i++) {
            for (int j = 0; j < size; j++) {
                part_c[i] += recieved_matrix[i][j] * recieved_b[j];
            }
        }

        MPI_Send(&part_c, part_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    
    return 0;
}