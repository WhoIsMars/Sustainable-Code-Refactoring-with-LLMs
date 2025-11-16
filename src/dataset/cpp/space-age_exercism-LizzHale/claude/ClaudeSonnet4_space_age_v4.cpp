#include "space_age.h"

namespace {
    constexpr double EARTH_YEAR_SECONDS = 31557600.0;
    constexpr double MERCURY_RATIO = 0.2408467;
    constexpr double VENUS_RATIO = 0.61519726;
    constexpr double MARS_RATIO = 1.8808158;
    constexpr double JUPITER_RATIO = 11.862615;
    constexpr double SATURN_RATIO = 29.447498;
    constexpr double URANUS_RATIO = 84.016846;
    constexpr double NEPTUNE_RATIO = 164.79132;
}

space_age::space_age::space_age(long seconds) : _seconds(seconds), _earth_years(seconds / EARTH_YEAR_SECONDS) {
}

long space_age::space_age::seconds() const {
    return _seconds;
}

double space_age::space_age::on_earth() const {
    return _earth_years;
}

double space_age::space_age::on_mercury() const {
    return _earth_years / MERCURY_RATIO;
}

double space_age::space_age::on_venus() const {
    return _earth_years / VENUS_RATIO;
}

double space_age::space_age::on_mars() const {
    return _earth_years / MARS_RATIO;
}

double space_age::space_age::on_jupiter() const {
    return _earth_years / JUPITER_RATIO;
}

double space_age::space_age::on_saturn() const {
    return _earth_years / SATURN_RATIO;
}

double space_age::space_age::on_uranus() const {
    return _earth_years / URANUS_RATIO;
}

double space_age::space_age::on_neptune() const {
    return _earth_years / NEPTUNE_RATIO;
}