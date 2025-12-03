#include "space_age.h"

namespace space_age {

    constexpr double seconds_per_earth_year = 31557600.0;

    constexpr double orbital_period_mercury =   0.2408467;
    constexpr double orbital_period_venus   =   0.61519726;
    constexpr double orbital_period_mars    =   1.8808158;
    constexpr double orbital_period_jupiter =  11.862615;
    constexpr double orbital_period_saturn  =  29.447498;
    constexpr double orbital_period_uranus  =  84.016846;
    constexpr double orbital_period_neptune = 164.79132;

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
        static const double ratio = 1.0 / orbital_period_mercury;
        return on_earth() * ratio;
    }

    double space_age::on_venus() const {
        static const double ratio = 1.0 / orbital_period_venus;
        return on_earth() * ratio;
    }

    double space_age::on_mars() const {
        static const double ratio = 1.0 / orbital_period_mars;
        return on_earth() * ratio;
    }

    double space_age::on_jupiter() const {
        static const double ratio = 1.0 / orbital_period_jupiter;
        return on_earth() * ratio;
    }

    double space_age::on_saturn() const {
        static const double ratio = 1.0 / orbital_period_saturn;
        return on_earth() * ratio;
    }

    double space_age::on_uranus() const {
        static const double ratio = 1.0 / orbital_period_uranus;
        return on_earth() * ratio;
    }

    double space_age::on_neptune() const {
        static const double ratio = 1.0 / orbital_period_neptune;
        return on_earth() * ratio;
    }

}  // namespace space_age