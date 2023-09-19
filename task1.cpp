#include <iostream>
#include <omp.h>

int main() {
 
    #pragma omp parallel num_threads(8)
    {
        int current_thread_id = omp_get_thread_num();
        int threads_count = omp_get_num_threads();


        /* Вывод будет разным, так как нет конкретного порядка выполнения потоков.
         Порядок выполнения потоков может меняться под действием многих факторов (загрузка процессора и т.д) */
        printf("Current thread: %d, Threads: %d, Hello World!\n", current_thread_id, threads_count);
    }

    return 0;
}