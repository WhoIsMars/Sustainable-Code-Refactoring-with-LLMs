#include "darts.h"

namespace darts {

int score(float x, float y) {
    const float radius_squared = x * x + y * y;
    
    if (radius_squared <= 1.0f) return 10;
    if (radius_squared <= 25.0f) return 5;
    if (radius_squared <= 100.0f) return 1;
    return 0;
}

}  // namespace darts