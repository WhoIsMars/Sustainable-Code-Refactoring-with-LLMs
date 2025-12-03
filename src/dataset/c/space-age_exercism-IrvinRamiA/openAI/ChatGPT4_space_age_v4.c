#include "space_age.h"

float age(planet_t planet, int64_t seconds)
{
    static const float orbital_periods[] = {
        0.2408467, 0.61519726, 1.0, 1.8808158, 11.862615, 29.447498, 84.016846, 164.79132
    };

    return seconds / (31557600 * orbital_periods[planet]);
}