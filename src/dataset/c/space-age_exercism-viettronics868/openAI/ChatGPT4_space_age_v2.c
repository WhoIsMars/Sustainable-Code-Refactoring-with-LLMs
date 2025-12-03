#include "space_age.h"
#include <stdint.h>

static const float PLANET_YEAR_FACTORS[] = {
    0.2408467,  // MERCURY
    0.61519726, // VENUS
    1.0,        // EARTH
    1.8808158,  // MARS
    11.862615,  // JUPITER
    29.447498,  // SATURN
    84.016846,  // URANUS
    164.79132   // NEPTUNE
};

static inline float seconds_to_Earth_year(uint64_t seconds) {
    return seconds / 31557600.0f; // 60 * 60 * 24 * 365.25
}

static inline float planet_to_Earth_year(planet_t planet) {
    if (planet < MERCURY || planet > NEPTUNE) return -1.0f;
    return PLANET_YEAR_FACTORS[planet];
}

float age(planet_t planet, uint64_t seconds) {
    float earth_years = seconds_to_Earth_year(seconds);
    float planet_factor = planet_to_Earth_year(planet);
    return (planet_factor < 0) ? -1.0f : (earth_years / planet_factor);
}