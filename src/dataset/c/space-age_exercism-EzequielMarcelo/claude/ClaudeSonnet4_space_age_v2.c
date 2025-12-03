#include "space_age.h"

float age(planet_t planet, int64_t seconds)
{
    // Pre-computed conversion factors: seconds to planet years
    static const float conversion_factors[] = {
        [MERCURY] = 1.0f / (0.2408467f * 60.0f * 60.0f * 24.0f * 365.25f),
        [VENUS]   = 1.0f / (0.61519726f * 60.0f * 60.0f * 24.0f * 365.25f),
        [EARTH]   = 1.0f / (60.0f * 60.0f * 24.0f * 365.25f),
        [MARS]    = 1.0f / (1.8808158f * 60.0f * 60.0f * 24.0f * 365.25f),
        [JUPITER] = 1.0f / (11.862615f * 60.0f * 60.0f * 24.0f * 365.25f),
        [SATURN]  = 1.0f / (29.447498f * 60.0f * 60.0f * 24.0f * 365.25f),
        [URANUS]  = 1.0f / (84.016846f * 60.0f * 60.0f * 24.0f * 365.25f),
        [NEPTUNE] = 1.0f / (164.79132f * 60.0f * 60.0f * 24.0f * 365.25f)
    };
    
    if (planet >= MERCURY && planet <= NEPTUNE) {
        return seconds * conversion_factors[planet];
    }
    
    return -1;
}