#include "space_age.h"
#include <stdint.h>

// Precomputed values for planet orbital periods relative to Earth
static const float planet_orbital_periods[] = {
    0.2408467,   // MERCURY
    0.61519726,  // VENUS
    1.0,         // EARTH
    1.8808158,   // MARS
    11.862615,   // JUPITER
    29.447498,   // SATURN
    84.016846,   // URANUS
    164.79132    // NEPTUNE
};

float age(planet_t planet, uint64_t seconds) {
    if (planet < MERCURY || planet > NEPTUNE) {
        return -1.0f;
    }

    // Constant for seconds in an Earth year
    const double seconds_in_earth_year = 31557600.0;

    return (float)(seconds / seconds_in_earth_year / planet_orbital_periods[planet]);
}