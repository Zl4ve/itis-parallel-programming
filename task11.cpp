#include <iostream>
#include <omp.h>

int main() {
    
    int a[10];
    int max = -1;

    std::srand(time(0));

    for (int i = 0; i < 10; i++) {
        a[i] = 1 + std::rand() % 100;
    }

    #pragma omp parallel for num_threads(5)
        for (int i = 0; i < 10; i++) {
            if (a[i] % 7 == 0 && a[i] > max) {
                #pragma omp critical
                    max = a[i];
            }
        }
    
    if (max != -1) {
        printf("max: %d", max);
    } else {
        std::cout << "there are no elements % 7 == 0 in array" << std::endl;
    }

    return 0;
}