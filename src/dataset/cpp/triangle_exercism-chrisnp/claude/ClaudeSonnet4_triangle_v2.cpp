#include "triangle.h"
#include <stdexcept>
#include <algorithm>

triangle::flavor triangle::kind(double s1, double s2, double s3) {
    if (s1 <= 0 || s2 <= 0 || s3 <= 0) 
        throw std::domain_error("sides cannot be zero or less");
    
    double sum = s1 + s2 + s3;
    double max_side = std::max({s1, s2, s3});
    
    if (2 * max_side >= sum)  
        throw std::domain_error("triangle inequality violated");
    
    int unique_count = 1;
    if (s1 != s2) unique_count++;
    if (s1 != s3 && s2 != s3) unique_count++;

    return static_cast<triangle::flavor>(unique_count - 1);
}

double doubles::minimum(std::vector<double>& vecd) noexcept {
    return *std::min_element(vecd.begin(), vecd.end());
}

double doubles::maximum(std::vector<double>& vecd) noexcept {
    return *std::max_element(vecd.begin(), vecd.end());
}

double doubles::kahanSum(std::vector<double>& vecd) noexcept {
    double sum = 0.0;
    double c = 0.0;
    for(double f : vecd) {
        double y = f - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}