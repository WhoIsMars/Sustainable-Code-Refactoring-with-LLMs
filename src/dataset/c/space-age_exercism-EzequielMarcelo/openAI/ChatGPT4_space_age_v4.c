#include "space_age.h"

static inline float seconds_to_earth_years(int64_t seconds)
{
    return seconds / 31557600.0f; // Precomputed seconds in an Earth year
}

float age(planet_t planet, int64_t seconds)
{
    static const float orbital_periods[] = {
        0.2408467f,  // MERCURY
        0.61519726f, // VENUS
        1.0f,        // EARTH
        1.8808158f,  // MARS
        11.862615f,  // JUPITER
        29.447498f,  // SATURN
        84.016846f,  // URANUS
        164.79132f   // NEPTUNE
    };

    if (planet < MERCURY || planet > NEPTUNE)
        return -1.0f;

    return seconds_to_earth_years(seconds) / orbital_periods[planet];
}