#include "space_age.h"

namespace space_age {

space_age::space_age(double input) : time(input) {}

double space_age::calculate(double planet_ratio) const {
    static constexpr double earth_year_in_seconds = 31557600.0;
    return time / (earth_year_in_seconds * planet_ratio);
}

double space_age::seconds() const {
    return time;
}

double space_age::on_earth() const {
    return calculate(1.0);
}

double space_age::on_mercury() const {
    return calculate(0.2408467);
}

double space_age::on_venus() const {
    return calculate(0.61519726);
}

double space_age::on_mars() const {
    return calculate(1.8808158);
}

double space_age::on_jupiter() const {
    return calculate(11.862615);
}

double space_age::on_saturn() const {
    return calculate(29.447498);
}

double space_age::on_uranus() const {
    return calculate(84.016846);
}

double space_age::on_neptune() const {
    return calculate(164.79132);
}

} // namespace space_age