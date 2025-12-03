#include "space_age.h"

static const float EARTH_YEAR_SECONDS = 31557600.0f;
static const float PLANET_ORBITAL_PERIODS[] = {
    [MERCURY] = 0.2408467f,
    [VENUS] = 0.61519726f,
    [EARTH] = 1.0f,
    [MARS] = 1.8808158f,
    [JUPITER] = 11.862615f,
    [SATURN] = 29.447498f,
    [URANUS] = 84.016846f,
    [NEPTUNE] = 164.79132f
};

float age(planet_t planet, int64_t seconds)
{
    if (planet < MERCURY || planet > NEPTUNE) {
        return 0.0f;
    }
    
    return (seconds / EARTH_YEAR_SECONDS) / PLANET_ORBITAL_PERIODS[planet];
}