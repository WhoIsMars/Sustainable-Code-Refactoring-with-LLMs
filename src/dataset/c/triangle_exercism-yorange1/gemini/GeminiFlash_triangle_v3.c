#include "triangle.h"

#include <float.h>
#include <math.h>
#include <stdbool.h>

static inline bool is_same(double a, double b) {
  return fabs(a - b) < DBL_EPSILON;
}

static inline bool is_valid_side(double side) {
  return !is_same(side, 0.0);
}

static bool is_triangle(triangle_t sides) {
  if (!is_valid_side(sides.a) || !is_valid_side(sides.b) ||
      !is_valid_side(sides.c)) {
    return false;
  }

  if (sides.a + sides.b <= sides.c || sides.a + sides.c <= sides.b ||
      sides.b + sides.c <= sides.a) {
    return false;
  }

  return true;
}

bool is_equilateral(triangle_t sides) {
  if (!is_triangle(sides)) {
    return false;
  }

  return (is_same(sides.a, sides.b) && is_same(sides.b, sides.c));
}

bool is_isosceles(triangle_t sides) {
  if (!is_triangle(sides)) {
    return false;
  }

  return (is_same(sides.a, sides.b) || is_same(sides.a, sides.c) ||
          is_same(sides.b, sides.c));
}

bool is_scalene(triangle_t sides) {
  if (!is_triangle(sides)) {
    return false;
  }

  return (!is_same(sides.a, sides.b) && !is_same(sides.a, sides.c) &&
          !is_same(sides.b, sides.c));
}