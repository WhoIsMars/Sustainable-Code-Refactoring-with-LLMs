#include "space_age.h"

static inline float seconds_to_earth_years(int64_t seconds)
{
    const float seconds_per_year = 31557600.0; // Precomputed: 60 * 60 * 24 * 365.25
    return seconds / seconds_per_year;
}

float age(planet_t planet, int64_t seconds)
{
    static const float orbital_periods[] = {
        0.2408467,  // MERCURY
        0.61519726, // VENUS
        1.0,        // EARTH
        1.8808158,  // MARS
        11.862615,  // JUPITER
        29.447498,  // SATURN
        84.016846,  // URANUS
        164.79132   // NEPTUNE
    };

    if (planet < MERCURY || planet > NEPTUNE)
        return -1;

    return seconds_to_earth_years(seconds) / orbital_periods[planet];
}