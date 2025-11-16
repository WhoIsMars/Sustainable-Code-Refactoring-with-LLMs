#include "triangle.h"
#include <stdexcept>
#include <algorithm>

triangle::flavor triangle::kind(double s1, double s2, double s3) {
    // Direct validation without vector allocation
    if (s1 <= 0 || s2 <= 0 || s3 <= 0) 
        throw std::domain_error("sides cannot be zero or less");
    
    // Find min and max directly
    double min_side = std::min({s1, s2, s3});
    double max_side = std::max({s1, s2, s3});
    double sum = s1 + s2 + s3;
    
    if (2 * max_side >= sum)  
        throw std::domain_error("triangle inequality violated");
    
    // Count unique sides without set allocation
    int unique_count = 1;
    if (s1 != s2) unique_count++;
    if (s3 != s1 && s3 != s2) unique_count++;

    return static_cast<triangle::flavor>(unique_count - 1);
}

double doubles::minimum(std::vector<double>& vecd) noexcept {
    double min = vecd[0];
    for (const double& f : vecd) {
        if (f < min) min = f;
    }
    return min;
}

double doubles::maximum(std::vector<double>& vecd) noexcept {
    double max = vecd[0];
    for (const double& f : vecd) {
        if (f > max) max = f;
    }
    return max;
}

double doubles::kahanSum(std::vector<double>& vecd) noexcept {
    double sum = 0.0;
    double c = 0.0;
    for (const double& f : vecd) {
        double y = f - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}