#include "space_age.h"
/*
| Planet  | Orbital period in Earth Years 365.25 |
| ------- | ----------------------------- |
| Mercury | 0.2408467                     |
| Venus   | 0.61519726                    |
| Earth   | 1.0                           |
| Mars    | 1.8808158                     |
| Jupiter | 11.862615                     |
| Saturn  | 29.447498                     |
| Uranus  | 84.016846                     |
| Neptune | 164.79132                     |
*/
float age(planet_t planet, int64_t seconds) 
{ 
    const int32_t EARTH_DAYS_SECONDS = 31557600;
    float Orbital = 1.0f;
    switch (planet)
    {
    case EARTH:
        Orbital =1;
        break;
    case MERCURY:
        Orbital = 0.2408467;
        break;
    case VENUS:
        Orbital = 0.61519726;
        break;
    case MARS:
        Orbital = 1.8808158;
        break;
    case JUPITER:
        Orbital = 11.862615;
        break;
    case SATURN:
        Orbital = 29.447498;
        break;
    case URANUS:
        Orbital = 84.016846;
        break;
    case NEPTUNE:
        Orbital = 164.79132;
        break;
    default:
        return -1;
        break;
    }
    return seconds / (EARTH_DAYS_SECONDS * Orbital);
}
