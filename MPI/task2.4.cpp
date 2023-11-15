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

        int matrix_a[size][size];
        int matrix_b[size][size];
        int matrix_c[size][size];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix_a[i][j] = 1 + std::rand() % 10;
                matrix_b[i][j] = 1 + std::rand() % 10;
            }
        }

        std::cout << "matrix A:" << std::endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << matrix_a[i][j] << " ";
            }

            std::cout << std::endl;
        }

        std::cout << "matrix B:" << std::endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << matrix_b[i][j] << " ";
            }

            std::cout << std::endl;
        }

        int buffer_start_index = 0;

        for (int i = 0; i < size / part_size; i++, buffer_start_index += part_size) {
            MPI_Send(&matrix_a[buffer_start_index][0], size * part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix_b[0][0], size * size, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
        }

        buffer_start_index = 0;

        for (int i = 0; i < size / part_size; i++, buffer_start_index += part_size) {
            MPI_Recv(&matrix_c[buffer_start_index][0], size * part_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD, &status);
        }

        std::cout << "matrix C:" << std::endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << matrix_c[i][j] << " ";
            }

            std::cout << std::endl;
        }

    } else {

        int data_count;

        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &data_count);

        int recieved_matrix_a[part_size][size];
        int recieved_matrix_b[size][size];
        int part_matrix_c[part_size][size];

        for (int i = 0; i < part_size; i++) {
            for (int j = 0; j < size; j++) {
                part_matrix_c[i][j] = 0;
            }
        }

        MPI_Recv(&recieved_matrix_a[0][0], size * part_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&recieved_matrix_b[0][0], size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < part_size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    part_matrix_c[i][j] += recieved_matrix_a[i][k] * recieved_matrix_b[k][j];
                }
            }
        }

        MPI_Send(&part_matrix_c, size * part_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    
    return 0;
}