#include "darts.h"

[[gnu::pure]]
unsigned int darts::score(const double& x, const double& y) noexcept {
    double radius_squared = x * x + y * y;
    
    if (radius_squared <= 1.0) return 10u;
    if (radius_squared <= 25.0) return 5u;
    if (radius_squared <= 100.0) return 1u;
    return 0u;
}