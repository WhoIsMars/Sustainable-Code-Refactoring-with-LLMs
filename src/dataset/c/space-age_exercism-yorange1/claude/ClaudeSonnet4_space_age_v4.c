#include "space_age.h"

#define EARTH_SECONDS_PER_YEAR (31557600.0f)

static const float ORBITAL_PERIODS[] = {
    0.2408467f, 0.61519726f, 1.0f, 1.8808158f, 
    11.862615f, 29.447498f, 84.016846f, 164.79132f
};

static const float INVERSE_ORBITAL_SECONDS[] = {
    1.0f / (EARTH_SECONDS_PER_YEAR * 0.2408467f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 0.61519726f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 1.0f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 1.8808158f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 11.862615f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 29.447498f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 84.016846f),
    1.0f / (EARTH_SECONDS_PER_YEAR * 164.79132f)
};

float age(planet_t planet, int64_t seconds)
{
    if (planet < MERCURY || planet > NEPTUNE)
    {
        return -1.0f;
    }

    return (float)seconds * INVERSE_ORBITAL_SECONDS[planet];
}