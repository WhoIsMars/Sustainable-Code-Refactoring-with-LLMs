#include "triangle.h"
#include <stdbool.h>

static inline bool complies_triangle_inequality(triangle_t triangle) {
  return (triangle.a + triangle.b > triangle.c) &&
         (triangle.b + triangle.c > triangle.a) &&
         (triangle.c + triangle.a > triangle.b);
}

bool is_equilateral(triangle_t triangle) {
  if (triangle.a == 0) {
    return false;
  }
  return (triangle.a == triangle.b) && (triangle.b == triangle.c);
}

bool is_isosceles(triangle_t triangle) {
  if (!complies_triangle_inequality(triangle)) {
    return false;
  }

  if (is_equilateral(triangle)) {
    return true;
  }

  return (triangle.a == triangle.b) || (triangle.b == triangle.c) ||
         (triangle.a == triangle.c);
}

bool is_scalene(triangle_t triangle) {
  return complies_triangle_inequality(triangle) &&
         (triangle.a != triangle.b) && (triangle.b != triangle.c) &&
         (triangle.a != triangle.c);
}