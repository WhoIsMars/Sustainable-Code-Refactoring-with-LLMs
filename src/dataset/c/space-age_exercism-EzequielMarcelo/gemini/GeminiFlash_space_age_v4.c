#include "space_age.h"

static const double SECONDS_PER_YEAR = 31557600.0;

float age(planet_t planet, int64_t seconds) {
  double years = (double)seconds / SECONDS_PER_YEAR;

  switch (planet) {
  case MERCURY:
    return (float)(years / 0.2408467);
  case VENUS:
    return (float)(years / 0.61519726);
  case EARTH:
    return (float)years;
  case MARS:
    return (float)(years / 1.8808158);
  case JUPITER:
    return (float)(years / 11.862615);
  case SATURN:
    return (float)(years / 29.447498);
  case URANUS:
    return (float)(years / 84.016846);
  case NEPTUNE:
    return (float)(years / 164.79132);
  default:
    return -1.0f;
  }
}