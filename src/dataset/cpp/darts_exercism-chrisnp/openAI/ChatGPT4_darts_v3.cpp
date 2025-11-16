#include "darts.h"
#include <cmath>

[[gnu::pure]]
unsigned int darts::score(const double& x, const double& y) noexcept {
    const double radiusSquared = x * x + y * y;

    if (radiusSquared <= 1.0) return 10u;
    if (radiusSquared <= 25.0) return 5u;
    if (radiusSquared <= 100.0) return 1u;
    return 0u;
}