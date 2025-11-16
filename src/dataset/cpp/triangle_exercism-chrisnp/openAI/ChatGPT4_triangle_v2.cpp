#include "triangle.h"
#include <algorithm>
#include <stdexcept>

triangle::flavor triangle::kind(double s1, double s2, double s3) {
    double sides[] = {s1, s2, s3};
    std::sort(sides, sides + 3);

    if (sides[0] <= 0)
        throw std::domain_error("sides cannot be zero or less");

    if (sides[0] + sides[1] <= sides[2])
        throw std::domain_error("triangle inequality violated");

    int uniq_sides = (sides[0] != sides[1]) + (sides[1] != sides[2]) + 1;

    return static_cast<triangle::flavor>(3 - uniq_sides);
}

double doubles::minimum(const std::vector<double>& vecd) noexcept {
    return *std::min_element(vecd.begin(), vecd.end());
}

double doubles::maximum(const std::vector<double>& vecd) noexcept {
    return *std::max_element(vecd.begin(), vecd.end());
}

double doubles::kahanSum(const std::vector<double>& vecd) noexcept {
    double sum = 0.0, e = 0.0;
    for (const double& f : vecd) {
        double y = f - e;
        double t = sum + y;
        e = (t - sum) - y;
        sum = t;
    }
    return sum;
}