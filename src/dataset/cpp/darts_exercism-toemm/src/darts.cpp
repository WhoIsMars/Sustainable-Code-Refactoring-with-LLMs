#include "darts.h"

#include <cmath>

namespace darts {

int score(float x, float y) {

    auto radius = sqrt(x*x + y*y);

    if (radius <= 10.0 && radius > 5.0) return 1;
    else if (radius <= 5.0 && radius > 1.0) return 5;
    else if (radius <= 1.0) return 10;
    else return 0;


}

}  // namespace darts