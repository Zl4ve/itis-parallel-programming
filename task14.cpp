#include <iostream>
#include <omp.h>
#include <math.h>

int main() {
    
    int n = 210;
    int result = 0;
    
    #pragma omp parallel for reduction(+:result)
        for (int i = 1; i < 2 * n; i += 2) {
            result += i;
        }

    printf("result: %d", result);
    return 0;
}