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

class space_age {
public:
    explicit space_age(long long seconds) : seconds_(seconds) {}

    long long seconds() const { return seconds_; }

    double on_mercury() const { return age_on_planet(0); }
    double on_venus() const { return age_on_planet(1); }
    double on_earth() const { return age_on_planet(2); }
    double on_mars() const { return age_on_planet(3); }
    double on_jupiter() const { return age_on_planet(4); }
    double on_saturn() const { return age_on_planet(5); }
    double on_uranus() const { return age_on_planet(6); }
    double on_neptune() const { return age_on_planet(7); }

private:
    long long seconds_;
    
    double age_on_planet(int planet_index) const {
        return seconds_ / (EARTH_YEAR_IN_SECONDS * ORBITAL_PERIODS[planet_index]);
    }
};

}  // namespace space_age