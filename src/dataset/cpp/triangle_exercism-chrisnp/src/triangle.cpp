#include "triangle.h"
#include <set>
#include <stdexcept>

triangle::flavor triangle::kind(double s1, double s2, double s3) {
    std::vector<double> sides {s1, s2, s3};
    
    if (doubles::minimum(sides) <= 0) 
        throw std::domain_error("sides cannot be zero or less");
        
    if (2 * doubles::maximum(sides) >= doubles::kahanSum(sides))  
        throw std::domain_error("triangle inequality violated");
    
    int uniq_sides = std::set<double>(sides.begin(), sides.end()).size();

    return static_cast<triangle::flavor>(uniq_sides - 1);
}

double doubles::minimum(std::vector<double>& vecd) noexcept {
    double min {vecd[0]};
    for (double &f : vecd) if (f <= min) min = f;
    return min;
}

double doubles::maximum(std::vector<double>& vecd) noexcept {
    double max {vecd[0]};
    for (double &f : vecd) if (f >= max) max = f;
    return max;
}

double doubles::kahanSum(std::vector<double>& vecd) noexcept {
    double sum {0.0}; double e {0.0};
    for(double &f : vecd) {
        double y {f - e}; double t {sum + y};
        e = (t - sum) - y; sum = t;
    }
    return sum;
}
