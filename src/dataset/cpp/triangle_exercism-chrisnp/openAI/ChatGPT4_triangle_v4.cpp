#include "triangle.h"
#include <array>
#include <stdexcept>
#include <algorithm>
#include <numeric>

triangle::flavor triangle::kind(double s1, double s2, double s3) {
    std::array<double, 3> sides {s1, s2, s3};
    std::sort(sides.begin(), sides.end());

    if (sides[0] <= 0)
        throw std::domain_error("sides cannot be zero or less");

    if (sides[0] + sides[1] <= sides[2])
        throw std::domain_error("triangle inequality violated");

    return static_cast<triangle::flavor>(std::unique(sides.begin(), sides.end()) - sides.begin() - 1);
}

double doubles::minimum(const std::vector<double>& vecd) noexcept {
    return *std::min_element(vecd.begin(), vecd.end());
}

double doubles::maximum(const std::vector<double>& vecd) noexcept {
    return *std::max_element(vecd.begin(), vecd.end());
}

double doubles::kahanSum(const std::vector<double>& vecd) noexcept {
    double sum = 0.0, c = 0.0;
    for (const double& f : vecd) {
        double y = f - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}