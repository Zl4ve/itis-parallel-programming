#include <iostream>
#include <omp.h>

int main() {
    
    int a[10] = {2, 5, 8, 1, 15, 3, 5, 0, -4, -14};
    int b[10] = {1, 8, -1, -3, 10, -9, 23, 15, 0, -1};

    int min_a;
    int max_b;

    #pragma omp parallel num_threads(2) 
    {
        int thread_num = omp_get_thread_num();
        if (thread_num == 0) {
            min_a = a[0];
            for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
                if (min_a < a[i]) {
                    min_a = a[i];
                }
            }
        } else {
            max_b = b[0];
            for (int i = 0; i < sizeof(b) / sizeof(b[0]); i++) {
                if (max_b > a[i]) {
                    max_b = a[i];
                }
            }
        }
    }

    printf("Min value of a: %d, max value of b: %d", min_a, max_b);


    
    return 0;
}