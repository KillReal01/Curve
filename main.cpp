#include "curve.hpp"
#include <omp.h>

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

#define _USE_MATH_DEFINES

int main() {
    srand(time(NULL));
    size_t n = 15;

    // 2.
    std::vector<std::shared_ptr<Curve>> vec;
    for (size_t i = 0; i < n; ++i) {
        std::shared_ptr<Curve> ptr;
        switch (rand() % 3) {
        case 0:
            ptr = std::make_shared<Ellipse>(rand() % 10 + 1, rand() % 10 + 1);
            break;
        case 1:
            ptr = std::make_shared<Circle>(rand() % 10 + 1);
            break;
        case 2:
            ptr = std::make_shared<Helix>(rand() % 10 + 1, (rand() % 10 + 1) / 10.0);
            break;
        }
        vec.push_back(ptr);
    }

    // 3. 
    double t = M_PI_4;
    for (const auto& item : vec) {
        Point3d tmp;
        tmp = item->getPoint3d(t);
        std::cout << "Point: " << tmp << "\n";
        tmp = item->getDerivative(t);
        std::cout << "Derivative: " << tmp << "\n\n";
    }

    // 4.
    std::vector<std::shared_ptr<Circle>> circle_vec;
    for (auto& item : vec) {
        if (auto circle_ptr = std::dynamic_pointer_cast<Circle>(item)) {
            circle_vec.push_back(circle_ptr);
        }
    }

    // 5.
    std::sort(circle_vec.begin(), circle_vec.end(), circle::compareByRadius);

    // 6.
    double totalRadiusSum = 0;
    for (const auto& circle : circle_vec) {
        totalRadiusSum += circle->getRadius();
    }
    std::cout << "Sum: " << totalRadiusSum <<  "\n";

    // 8.
    double totalRadiusSumMP = 0;
    int num_threads = omp_get_max_threads();
    int vector_size = circle_vec.size(); 

    #pragma omp parallel num_threads(num_threads)
    {
        double local_sum = 0;
        int thread_id = omp_get_thread_num();
        int chunk_size = vector_size / num_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? vector_size : start + chunk_size;

        for (int i = start; i < end; i++) {
            local_sum += circle_vec[i]->getRadius();
        }

        #pragma omp critical
        totalRadiusSumMP += local_sum;
    }
    std::cout << "OpenMP sum: " << totalRadiusSumMP << "\n";

    return 0;
}

