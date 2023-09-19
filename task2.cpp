#include <iostream>
#include <omp.h>

int main() {
    
    int first_case_num_threads = 3;

    #pragma omp parallel num_threads(first_case_num_threads) if (first_case_num_threads > 1)
    {
        int current_thread_id = omp_get_thread_num();
        int threads_count = omp_get_num_threads();

        printf("Current thread ID: %d, Threads: %d\n", current_thread_id, threads_count);
    }

    int second_case_num_threads = 1;

    #pragma omp parallel num_threads(second_case_num_threads) if (first_case_num_threads > 1)
    {
        int current_thread_id = omp_get_thread_num();
        int threads_count = omp_get_num_threads();

        printf("Current thread ID: %d, Threads: %d\n", current_thread_id, threads_count);
    }
    
    return 0;
}