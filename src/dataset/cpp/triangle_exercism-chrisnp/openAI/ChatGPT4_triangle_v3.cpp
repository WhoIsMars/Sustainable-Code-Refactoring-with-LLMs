#include "triangle.h"
#include <set>
#include <stdexcept>
#include <algorithm>
#include <numeric>

triangle::flavor triangle::kind(double s1, double s2, double s3) {
    double sides[] = {s1, s2, s3};
    
    if (*std::min_element(sides, sides + 3) <= 0) 
        throw std::domain_error("sides cannot be zero or less");
        
    double max_side = *std::max_element(sides, sides + 3);
    double sum_sides = std::accumulate(sides, sides + 3, 0.0);
    if (2 * max_side >= sum_sides)  
        throw std::domain_error("triangle inequality violated");
    
    int uniq_sides = std::set<double>(sides, sides + 3).size();

    return static_cast<triangle::flavor>(uniq_sides - 1);
}

double doubles::minimum(std::vector<double>& vecd) noexcept {
    return *std::min_element(vecd.begin(), vecd.end());
}

double doubles::maximum(std::vector<double>& vecd) noexcept {
    return *std::max_element(vecd.begin(), vecd.end());
}

double doubles::kahanSum(std::vector<double>& vecd) noexcept {
    double sum = 0.0, e = 0.0;
    for (const double f : vecd) {
        double y = f - e;
        double t = sum + y;
        e = (t - sum) - y;
        sum = t;
    }
    return sum;
}