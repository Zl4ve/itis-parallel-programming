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

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int sum = 0;

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    sum += d[i][j];
                }
            }

            float avg = (float) sum / (6 * 8);

            int current_thread = omp_get_thread_num();
            printf("Current thread: %d, average = %f\n", current_thread, avg);
        }

        #pragma omp section
        {
            int min = d[0][0];
            int max = d[0][0];

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] > max) {
                        max = d[i][j];
                    } 
                    
                    if (d[i][j] < min) {
                        min = d[i][j];
                    }
                }
            }

            int current_thread = omp_get_thread_num();

            printf("Current thread: %d, min: %d, max: %d\n", current_thread, min, max);
        }

        #pragma omp section
        {
            int count = 0;

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] % 3 == 0) {
                        count++;
                    }
                }
            }

            int current_thread = omp_get_thread_num();

            printf("Current thread: %d, count % 3: %d\n", current_thread, count);
        }
    }

    

    return 0;
}