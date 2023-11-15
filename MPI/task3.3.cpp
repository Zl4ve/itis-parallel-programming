#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int size = 100;
    int part_size = 20;
    int current_process;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    
    int matrix_a[size][size];
    int b[size];
    int recieved_matrix_a[part_size][size];

    if (current_process == 0) {

        std::cout << "matrix A: ";

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix_a[i][j] = std::rand() % 10 + 1;
                std::cout << matrix_a[i][j] << " ";
            }

            std::cout << std::endl;
        }

        std::cout << "vector b: ";

        for (int i = 0; i < size; i++) {
            b[i] = std::rand() % 10 + 1;
            std::cout << b[i] << " ";
        }

        std::cout << std::endl;
    }

    MPI_Bcast(b, size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrix_a, part_size * size, MPI_INT, recieved_matrix_a, part_size * size, MPI_INT, 0, MPI_COMM_WORLD);

    int part_c[part_size] = {0};

    for (int i = 0; i < part_size; ++i) {
        for (int j = 0; j < size; j++) {
            part_c[i] += recieved_matrix_a[i][j] * b[j];
        }
    }

    int c[size];

    MPI_Gather(part_c, part_size, MPI_INT, c, part_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (current_process == 0) {
        std::cout << "res = ";
        for (int i = 0; i < size; i++) {
            std::cout << c[i] << " ";
        }
    }
    
    MPI_Finalize();
    
    return 0;
}