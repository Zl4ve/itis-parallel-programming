#include <iostream>
#include <omp.h>
#include <math.h>
#include <vector>

int main() {
    
    int start;
    int end;

    std::cin >> start;
    std::cin >> end;

    std::vector<int> result;

    #pragma omp parallel for num_threads(5)
        for (int i = start; i <= end; i++) {

            if (i != 1) {
                bool is_simple = true;
            
                for (int j = 2; j <= sqrt(i); j++) {
                    if (i % j == 0) {
                        is_simple = false;
                        break;
                    }
                }

                if (is_simple) {
                    #pragma omp critical
                        result.push_back(i);
                }
            }
        }

    for (int num : result) {
        std::cout << num << " " << std::endl;
    }

    return 0;
}