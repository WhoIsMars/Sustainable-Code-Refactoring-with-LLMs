#include <cassert>
#include "space_age.h"

namespace space_age {

    // Constants are best defined as static const members.
    const double space_age::secs_in_earth_year = 31557600.0;
    const double space_age::earth_years_on_earth = 1.0;
    const double space_age::earth_years_on_mercury = 0.2408467;
    const double space_age::earth_years_on_venus = 0.61519726;
    const double space_age::earth_years_on_mars = 1.8808158;
    const double space_age::earth_years_on_jupiter = 11.862615;
    const double space_age::earth_years_on_saturn = 29.447498;
    const double space_age::earth_years_on_uranus = 84.016846;
    const double space_age::earth_years_on_neptune = 164.79132;


    space_age::space_age(age_in_seconds earth_age_in_seconds) : _earth_age_in_seconds(earth_age_in_seconds) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const {
        return _earth_age_in_seconds / secs_in_earth_year;
    }

    age_in_years space_age::on_mercury() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_mercury;
    }

    age_in_years space_age::on_venus() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_venus;
    }

    age_in_years space_age::on_mars() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_mars;
    }

    age_in_years space_age::on_jupiter() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_jupiter;
    }

    age_in_years space_age::on_saturn() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_saturn;
    }

    age_in_years space_age::on_uranus() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_uranus;
    }

    age_in_years space_age::on_neptune() const {
        return _earth_age_in_seconds / secs_in_earth_year / earth_years_on_neptune;
    }
}  // namespace space_age