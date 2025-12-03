#include "space_age.h"

namespace space_age {

    constexpr double seconds_per_earth_year = 31557600.0;

    constexpr double orbital_periods[] = {
        1.0,              // Earth
        0.2408467,        // Mercury
        0.61519726,       // Venus
        1.8808158,        // Mars
        11.862615,        // Jupiter
        29.447498,        // Saturn
        84.016846,        // Uranus
        164.79132         // Neptune
    };

    enum Planet {
        Earth = 0,
        Mercury,
        Venus,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune
    };

    space_age::space_age(std::uint64_t earth_age_in_seconds) 
        : _earth_age_in_seconds(earth_age_in_seconds),
          _age_on_earth(earth_age_in_seconds / seconds_per_earth_year) {}

    std::uint64_t space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    double space_age::on_earth() const {
        return _age_on_earth;
    }

    double space_age::on_mercury() const {
        return _age_on_earth / orbital_periods[Mercury];
    }

    double space_age::on_venus() const {
        return _age_on_earth / orbital_periods[Venus];
    }

    double space_age::on_mars() const {
        return _age_on_earth / orbital_periods[Mars];
    }

    double space_age::on_jupiter() const {
        return _age_on_earth / orbital_periods[Jupiter];
    }

    double space_age::on_saturn() const {
        return _age_on_earth / orbital_periods[Saturn];
    }

    double space_age::on_uranus() const {
        return _age_on_earth / orbital_periods[Uranus];
    }

    double space_age::on_neptune() const {
        return _age_on_earth / orbital_periods[Neptune];
    }

}  // namespace space_age