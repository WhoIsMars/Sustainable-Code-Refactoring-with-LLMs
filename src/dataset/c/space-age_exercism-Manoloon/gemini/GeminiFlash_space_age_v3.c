#include "space_age.h"

float age(planet_t planet, int64_t seconds) {
    static const float orbital_periods[] = {
        1.0f,         // EARTH
        0.2408467f,   // MERCURY
        0.61519726f,  // VENUS
        1.8808158f,   // MARS
        11.862615f,  // JUPITER
        29.447498f,  // SATURN
        84.016846f,  // URANUS
        164.79132f   // NEPTUNE
    };

    const int32_t EARTH_YEAR_SECONDS = 31557600;

    if (planet < EARTH || planet > NEPTUNE) {
        return -1.0f;
    }

    return (float)seconds / (EARTH_YEAR_SECONDS * orbital_periods[planet]);
}