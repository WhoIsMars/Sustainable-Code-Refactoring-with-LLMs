#include "space_age.h"

namespace space_age {

    constexpr double seconds_per_earth_year = 31557600.0;

    // Constructors:

    space_age::space_age(std::uint64_t earth_age_in_seconds) 
        : _earth_age_in_seconds(earth_age_in_seconds) {}

    // Accessors:

    std::uint64_t space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    // Age in planets:

    double space_age::on_earth() const {
        return _earth_age_in_seconds / seconds_per_earth_year;
    }

    double space_age::on_mercury() const {
        static constexpr double orbital_period = 0.2408467;
        return on_earth() / orbital_period;
    }

    double space_age::on_venus() const {
        static constexpr double orbital_period = 0.61519726;
        return on_earth() / orbital_period;
    }

    double space_age::on_mars() const {
        static constexpr double orbital_period = 1.8808158;
        return on_earth() / orbital_period;
    }

    double space_age::on_jupiter() const {
        static constexpr double orbital_period = 11.862615;
        return on_earth() / orbital_period;
    }

    double space_age::on_saturn() const {
        static constexpr double orbital_period = 29.447498;
        return on_earth() / orbital_period;
    }

    double space_age::on_uranus() const {
        static constexpr double orbital_period = 84.016846;
        return on_earth() / orbital_period;
    }

    double space_age::on_neptune() const {
        static constexpr double orbital_period = 164.79132;
        return on_earth() / orbital_period;
    }

}  // namespace space_age