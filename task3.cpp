#include <iostream>
#include <omp.h>

int main() {
    
    int a = 10;
    int b = 25;

    printf("Before region 1: a = %d b = %d\n", a, b);

    #pragma omp parallel private(a) firstprivate(b) num_threads(2)
    {
        int thread_num = omp_get_thread_num();
        a += thread_num;
        b += thread_num;
        printf("Thread ID: %d a = %d b = %d\n", thread_num, a, b);
    }

    printf("After region 1: a = %d b = %d\n", a, b);

    printf("Before region 2: a = %d b = %d\n", a, b);

    #pragma omp parallel shared(a) private(b) num_threads(4)
    {
        int thread_num = omp_get_thread_num();
        a -= thread_num;
        b -= thread_num;
        printf("Thread ID: %d a = %d b = %d\n", thread_num, a, b);
    }

    printf("After region 2: a = %d b = %d\n", a, b);
    
    return 0;
}