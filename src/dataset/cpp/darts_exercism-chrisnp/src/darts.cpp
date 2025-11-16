#include "darts.h"
#include <cmath>

[[gnu::pure]]
unsigned int darts::score(const double& x, const double& y) noexcept {
    unsigned int points { 0 };

    double radius = std::hypot(x, y);
    if (radius <= 10.) points += 1u;
    if (radius <= 5.0) points += 4u; 
    if (radius <= 1.0) points += 5u;
    return points; 
}