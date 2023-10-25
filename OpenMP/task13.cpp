#include <iostream>
#include <omp.h>
#include <math.h>

int main() {
    
    int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    int result = 0;
    
    #pragma omp parallel for reduction(+:result)
        for (int i = 0; i < 30; i++) {
            result += a[i] * pow(2, 29 - i);
        }

    printf("result: %d", result);
    return 0;
}