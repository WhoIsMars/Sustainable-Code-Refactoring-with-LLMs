#include "space_age.h"

namespace space_age {

    constexpr double seconds_per_earth_year = 31557600.0;

    constexpr double orbital_periods[] = {
        1.0,            // Earth
        0.2408467,      // Mercury
        0.61519726,     // Venus
        1.8808158,      // Mars
        11.862615,      // Jupiter
        29.447498,      // Saturn
        84.016846,      // Uranus
        164.79132       // Neptune
    };

    space_age::space_age(std::uint64_t earth_age_in_seconds) 
        : _earth_age_in_seconds(earth_age_in_seconds),
          _earth_years(earth_age_in_seconds / seconds_per_earth_year) {}

    std::uint64_t space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    double space_age::on_earth() const {
        return _earth_years;
    }

    double space_age::on_mercury() const {
        return _earth_years / orbital_periods[1];
    }

    double space_age::on_venus() const {
        return _earth_years / orbital_periods[2];
    }

    double space_age::on_mars() const {
        return _earth_years / orbital_periods[3];
    }

    double space_age::on_jupiter() const {
        return _earth_years / orbital_periods[4];
    }

    double space_age::on_saturn() const {
        return _earth_years / orbital_periods[5];
    }

    double space_age::on_uranus() const {
        return _earth_years / orbital_periods[6];
    }

    double space_age::on_neptune() const {
        return _earth_years / orbital_periods[7];
    }

}  // namespace space_age