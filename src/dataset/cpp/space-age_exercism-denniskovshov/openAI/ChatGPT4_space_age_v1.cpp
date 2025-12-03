#include <cassert>
#include "space_age.h"

namespace space_age {
    // private
    inline age_in_years space_age::age_on_planet(double earth_years_on_planet) const {
        return _earth_age_in_seconds / (secs_in_earth_year * earth_years_on_planet);
    }

    // public
    space_age::space_age(age_in_seconds earth_age_in_seconds) : _earth_age_in_seconds(earth_age_in_seconds) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const {
        static constexpr double factor = 1.0 / secs_in_earth_year;
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_mercury() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_mercury);
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_venus() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_venus);
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_mars() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_mars);
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_jupiter() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_jupiter);
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_saturn() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_saturn);
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_uranus() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_uranus);
        return _earth_age_in_seconds * factor;
    }

    age_in_years space_age::on_neptune() const {
        static constexpr double factor = 1.0 / (secs_in_earth_year * earth_years_on_neptune);
        return _earth_age_in_seconds * factor;
    }
}  // namespace space_age