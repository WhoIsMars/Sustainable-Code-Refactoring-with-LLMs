#include "darts.h"

#include <math.h>

uint8_t score(coordinate_t c) {
  float r_squared = (float)(c.x * c.x + c.y * c.y);

  if (r_squared <= 1.0f) {
    return 10;
  }
  if (r_squared <= 25.0f) {
    return 5;
  }
  if (r_squared <= 100.0f) {
    return 1;
  }

  return 0;
}