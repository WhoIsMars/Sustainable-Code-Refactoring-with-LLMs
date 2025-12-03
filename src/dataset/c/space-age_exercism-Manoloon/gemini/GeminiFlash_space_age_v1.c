#include "space_age.h"

float age(planet_t planet, int64_t seconds) {
    static const double orbital_periods[] = {
        1.0,         // EARTH
        0.2408467,   // MERCURY
        0.61519726,  // VENUS
        1.8808158,   // MARS
        11.862615,   // JUPITER
        29.447498,   // SATURN
        84.016846,   // URANUS
        164.79132    // NEPTUNE
    };

    static const double earth_year_in_seconds = 31557600.0;

    if (planet < EARTH || planet > NEPTUNE) {
        return -1.0f;
    }

    return (float)(seconds / (earth_year_in_seconds * orbital_periods[planet]));
}