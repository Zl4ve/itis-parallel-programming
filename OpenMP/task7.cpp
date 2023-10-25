#include <iostream>
#include <omp.h>

int main() {
    
    int arrays_length = 12;

    int a[arrays_length];
    int b[arrays_length];
    int c[arrays_length];

    int num_threads_first = 3;
    int num_threads_second = 4;

    #pragma omp parallel for schedule(static, arrays_length / num_threads_first) num_threads(num_threads_first)
        for (int i = 0; i < arrays_length; i++) {
            a[i] = i + 1;
            b[i] = i * 2;
            printf("Threads: %d, current thread: %d, a[%d] = %d, b[%d] = %d\n", omp_get_num_threads(), omp_get_thread_num(), i, a[i], i, b[i]);
        }

    #pragma omp parallel for schedule(dynamic, arrays_length / num_threads_second) num_threads(num_threads_second)
        for (int i = 0; i < arrays_length; i++) {
            c[i] = a[i] + b[i];
            printf("Threads: %d, current thread: %d, c[%d] = %d\n", omp_get_num_threads(), omp_get_thread_num(), i, c[i]);
        }

    return 0;
}