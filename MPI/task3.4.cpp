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
    }

    MPI_Scatter(matrix_a, part_size * size, MPI_INT, recieved_matrix_a, part_size * size, MPI_INT, 0, MPI_COMM_WORLD);

    int sum;
    int max = -1;

    for (int i = 0; i < part_size; i++) {
        sum = 0;
        for (int j = 0; j < size; j++) {
            sum += abs(matrix_a[i][j]);
        }

        if (sum > max) {
            max = sum;
        }
    }
    
    int res = 0;

    MPI_Reduce(&max, &res, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (current_process == 0) {
        std::cout << "res = " << res;
    }
    
    MPI_Finalize();
    
    return 0;
}