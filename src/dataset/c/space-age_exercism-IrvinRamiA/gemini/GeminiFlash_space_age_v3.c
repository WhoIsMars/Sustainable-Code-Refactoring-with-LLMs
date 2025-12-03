#include "space_age.h"

#include <stdint.h>

float age(planet_t planet, int64_t seconds) {
  static const double earth_year_seconds = 31557600.0;
  double years = seconds / earth_year_seconds;

  switch (planet) {
    case MERCURY:
      years /= 0.2408467;
      break;
    case VENUS:
      years /= 0.61519726;
      break;
    case EARTH:
      break;
    case MARS:
      years /= 1.8808158;
      break;
    case JUPITER:
      years /= 11.862615;
      break;
    case SATURN:
      years /= 29.447498;
      break;
    case URANUS:
      years /= 84.016846;
      break;
    case NEPTUNE:
      years /= 164.79132;
      break;
    default:
      break;
  }

  return (float)years;
}