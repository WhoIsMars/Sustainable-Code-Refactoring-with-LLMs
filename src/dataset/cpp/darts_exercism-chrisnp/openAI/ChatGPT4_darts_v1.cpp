#include "darts.h"
#include <cmath>

[[gnu::pure]]
unsigned int darts::score(const double& x, const double& y) noexcept {
    double radius_squared = x * x + y * y;

    if (radius_squared <= 1.0) return 10u; // 5 + 4 + 1
    if (radius_squared <= 25.0) return 5u; // 4 + 1
    if (radius_squared <= 100.0) return 1u;

    return 0u;
}