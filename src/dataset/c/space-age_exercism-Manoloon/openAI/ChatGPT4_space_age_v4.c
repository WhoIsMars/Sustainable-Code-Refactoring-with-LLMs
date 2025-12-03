#include "space_age.h"

float age(planet_t planet, int64_t seconds) 
{ 
    const int32_t EARTH_DAYS_SECONDS = 31557600;
    static const float ORBITAL_PERIODS[] = {
        [MERCURY] = 0.2408467,
        [VENUS] = 0.61519726,
        [EARTH] = 1.0,
        [MARS] = 1.8808158,
        [JUPITER] = 11.862615,
        [SATURN] = 29.447498,
        [URANUS] = 84.016846,
        [NEPTUNE] = 164.79132
    };

    if (planet < MERCURY || planet > NEPTUNE) {
        return -1;
    }

    return seconds / (EARTH_DAYS_SECONDS * ORBITAL_PERIODS[planet]);
}