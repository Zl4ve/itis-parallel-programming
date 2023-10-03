#include <iostream>
#include <omp.h>

int main() {
    
    int a[30];
    int count = 0;

    std::srand(time(0));

    for (int i = 0; i < 30; i++) {
        a[i] = 1 + std::rand() % 100;
    }

    #pragma omp parallel for num_threads(5)
        for (int i = 0; i < 30; i++) {
            if (a[i] % 9 == 0) {
                #pragma omp atomic
                    count++;
            }
        }
    
    printf("count: %d", count);

    return 0;
}