#include "darts.h"

#include <cmath>

namespace darts {

int score(float x, float y) {

    float radius_squared = x*x + y*y;

    if (radius_squared > 100.0f) return 0;
    if (radius_squared > 25.0f) return 1;
    if (radius_squared > 1.0f) return 5;
    return 10;
}

}  // namespace darts