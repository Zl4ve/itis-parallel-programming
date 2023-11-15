#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    std::srand(time(0));

    int size = 100;
    int part_size = 20;
    int process_count;
    int current_process;

    
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    
    int x[size];
    int recieved_x[part_size];

    if (current_process == 0) {

        std::cout << "vector x: ";

        for (int i = 0; i < size; i++) {
            x[i] = std::rand() % 100 - 50;
            std::cout << x[i] << " ";
        }

        std::cout << std::endl;
    }

    MPI_Scatter(x, part_size, MPI_INT, recieved_x, part_size, MPI_INT, 0, MPI_COMM_WORLD);

    int max = -1;

    for (int i = 0; i < part_size; i++) {
        if (recieved_x[i] > max) {
            max = recieved_x[i];
        }
    }

    int local_res[2] = {current_process, max};
    int global_res;

    int results[process_count][2];

    MPI_Gather(local_res, 2, MPI_INT, results, 2, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_res[1], &global_res, 1, MPI_2INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);

    if (current_process == 0) {
        for (int i = 0; i < process_count; i++) {
            printf("proc: %d, local max: %d\n", results[i][0], results[i][1]);
        }

        printf("global max: %d", global_res);
    }
    
    MPI_Finalize();
    
    return 0;
}