#include "space_age.h"
#include <stdint.h>

// Precomputed values for planet orbital periods relative to Earth
static const float orbital_periods[] = {
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
        return -1.0f; // Indicate an error for invalid planet
    }

    // Calculate Earth years directly
    float earth_years = (float)seconds / 31557600.0f;

    return earth_years / orbital_periods[planet];
}