#include "darts.h"

namespace darts {

int score(float x, float y) {
    float radiusSquared = x * x + y * y;

    if (radiusSquared > 100.0f) return 0;
    if (radiusSquared > 25.0f) return 1;
    if (radiusSquared > 1.0f) return 5;
    return 10;
}

}  // namespace darts