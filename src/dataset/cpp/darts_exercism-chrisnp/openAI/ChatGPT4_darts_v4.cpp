#include "darts.h"

[[gnu::pure]]
unsigned int darts::score(const double& x, const double& y) noexcept {
    const double radiusSquared = x * x + y * y;

    if (radiusSquared <= 1.0) return 10u; // 5 + 4 + 1
    if (radiusSquared <= 25.0) return 5u; // 4 + 1
    if (radiusSquared <= 100.0) return 1u;

    return 0u;
}