#include "space_age.h"
#include <stdint.h>

#define SECONDS_IN_EARTH_YEAR 31557600.0f

float age(planet_t planet, uint64_t seconds);

float age(planet_t planet, uint64_t seconds) {
  float orbital_period;

  switch (planet) {
  case MERCURY:
    orbital_period = 0.2408467f;
    break;
  case VENUS:
    orbital_period = 0.61519726f;
    break;
  case EARTH:
    orbital_period = 1.0f;
    break;
  case MARS:
    orbital_period = 1.8808158f;
    break;
  case JUPITER:
    orbital_period = 11.862615f;
    break;
  case SATURN:
    orbital_period = 29.447498f;
    break;
  case URANUS:
    orbital_period = 84.016846f;
    break;
  case NEPTUNE:
    orbital_period = 164.79132f;
    break;
  default:
    return -1.0f;
  }

  return (float)seconds / (SECONDS_IN_EARTH_YEAR * orbital_period);
}