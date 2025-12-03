#include "space_age.h"

#define EARTH_SECONDS_PER_YEAR (31557600.0)

float age(planet_t planet, int64_t seconds) {
  static const float orbital_period[] = {
      0.2408467f, 0.61519726f, 1.0f, 1.8808158f, 11.862615f, 29.447498f,
      84.016846f, 164.79132f};

  if (planet < MERCURY || planet > NEPTUNE) {
    return -1.0f;
  }

  return (float)seconds / (EARTH_SECONDS_PER_YEAR * orbital_period[planet]);
}