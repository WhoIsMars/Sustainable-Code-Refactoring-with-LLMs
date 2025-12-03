#include "darts.h"

#include <math.h>

#define INNER_CIRCLE_RADIUS_SQ (1.0 * 1.0)
#define MIDDLE_CIRCLE_RADIUS_SQ (5.0 * 5.0)
#define OUTER_CIRCLE_RADIUS_SQ (10.0 * 10.0)

uint8_t score(coordinate_t landing_position) {
  float x = landing_position.x;
  float y = landing_position.y;
  float dist_sq = x * x + y * y;

  if (dist_sq <= INNER_CIRCLE_RADIUS_SQ) {
    return 10;
  } else if (dist_sq <= MIDDLE_CIRCLE_RADIUS_SQ) {
    return 5;
  } else if (dist_sq <= OUTER_CIRCLE_RADIUS_SQ) {
    return 1;
  } else {
    return 0;
  }
}