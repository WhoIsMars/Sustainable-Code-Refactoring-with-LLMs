#include "darts.h"

#include <cmath>

namespace darts {

int score(float x, float y) {
    float radiusSquared = x * x + y * y;

    if (radiusSquared > 25.0f && radiusSquared <= 100.0f) return 1;
    if (radiusSquared > 1.0f && radiusSquared <= 25.0f) return 5;
    if (radiusSquared <= 1.0f) return 10;
    return 0;
}

}  // namespace darts