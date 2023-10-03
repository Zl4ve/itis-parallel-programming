#include <iostream>
#include <omp.h>

int main() {
    
    int a[10] = {2, 5, 8, 1, 15, 3, 5, 0, 4, 14};
    int b[10] = {1, 8, 1, 3, 10, 9, 23, 15, 0, 1};

    float avg_a = 0;
    float avg_b = 0;

    #pragma omp parallel reduction(+:avg_a) reduction(+:avg_b)
        for (int i = 0; i < 10; i++) {
            avg_a += a[i];
            avg_b += b[i];
        }

    avg_a = avg_a / 10;
    avg_b = avg_b / 10;

    if (avg_a > avg_b) {
        printf("avg_a = %f > avg_b = %f", avg_a, avg_b);
    } else if (avg_a < avg_b) {
        printf("avg_a = %f < avg_b = %f", avg_a, avg_b);
    } else {
        printf("avg_a = %f = avg_b = %f", avg_a, avg_b);
    }


    
    return 0;
}