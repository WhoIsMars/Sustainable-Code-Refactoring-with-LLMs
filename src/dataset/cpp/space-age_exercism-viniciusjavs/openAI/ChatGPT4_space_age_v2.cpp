#include "space_age.h"

namespace space_age {

constexpr double EARTH_YEAR_IN_SECONDS = 31557600.0;

constexpr double ORBITAL_PERIODS[] = {
    0.2408467,  // Mercury
    0.61519726, // Venus
    1.0,        // Earth
    1.8808158,  // Mars
    11.862615,  // Jupiter
    29.447498,  // Saturn
    84.016846,  // Uranus
    164.79132   // Neptune
};

enum Planet {
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE
};

inline double age_on(Planet planet, double seconds) {
    return seconds / (EARTH_YEAR_IN_SECONDS * ORBITAL_PERIODS[planet]);
}

}  // namespace space_age