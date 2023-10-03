#include <iostream>
#include <omp.h>
#include <chrono>

int main() {
    
    int const rows = 4000;
    int const columns = 3000;

    int static matrix[rows][columns];
    int static vector[columns];

    std::srand(time(0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 1 + std::rand() % 100;
        }
    }

    for (int i = 0; i < columns; i++) {
        vector[i] = 1 + std::rand() % 100;
    }

    int result_serial[rows];

    auto start_serial = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < rows; i++) {
        result_serial[i] = 0;
        for (int j = 0; j < columns; j++) {
            result_serial[i] += matrix[i][j] * vector[j];
        }
    }
    auto end_serial = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> time_serial = end_serial - start_serial;

    int result_parallel[rows];

    auto start_parallel = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
        for (int i = 0; i < rows; i++) {
            result_parallel[i] = 0;
            for (int j = 0; j < columns; j++) {
                result_parallel[i] += matrix[i][j] * vector[j];
            }
        }

    auto end_parallel = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> time_parallel = end_parallel - start_parallel;

    printf("Serial: %.2f ms, parallel: %.2f ms", time_serial.count(), time_parallel.count());
    return 0;
}