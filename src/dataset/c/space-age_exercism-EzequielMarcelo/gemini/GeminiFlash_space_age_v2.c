#include "space_age.h"

#define SECONDS_PER_YEAR 31557600.0f // 60 * 60 * 24 * 365.25

float age(planet_t planet, int64_t seconds) {
    float earth_years = (float)seconds / SECONDS_PER_YEAR;

    switch (planet) {
        case MERCURY: return earth_years / 0.2408467f;
        case VENUS:   return earth_years / 0.61519726f;
        case EARTH:   return earth_years;
        case MARS:    return earth_years / 1.8808158f;
        case JUPITER: return earth_years / 11.862615f;
        case SATURN:  return earth_years / 29.447498f;
        case URANUS:  return earth_years / 84.016846f;
        case NEPTUNE: return earth_years / 164.79132f;
        default:      return -1.0f;
    }
}