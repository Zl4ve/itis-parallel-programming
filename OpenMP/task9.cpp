#include <iostream>
#include <omp.h>

int main() {
    
    int d[6][8];

    std::srand(time(0));

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = 1 + std::rand() % 100;
        }
    }

    int min = d[0][0];
    int max = d[0][0];

    #pragma omp parallel for num_threads(5)
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                if (d[i][j] > max) {
                    #pragma omp critical
                        max = d[i][j];
                }

                if (d[i][j] < min) {
                    #pragma omp critical
                        min = d[i][j];
                }
            }
        }

    printf("min: %d, max: %d", min, max);   
    return 0;
}