#include "space_age.h"

namespace space_age {

constexpr double EARTH_RATIO = 1.0;
constexpr double MERCURY_RATIO = 0.2408467;
constexpr double VENUS_RATIO = 0.61519726;
constexpr double MARS_RATIO = 1.8808158;
constexpr double JUPITER_RATIO = 11.862615;
constexpr double SATURN_RATIO = 29.447498;
constexpr double URANUS_RATIO = 84.016846;
constexpr double NEPTUNE_RATIO = 164.79132;

space_age::space_age(long input_seconds) 
    : age_in_seconds(input_seconds), 
      age_in_years(static_cast<double>(input_seconds) / seconds_in_year) {
}

long space_age::seconds() const { 
    return age_in_seconds; 
}

double space_age::on_earth() const {
    return age_in_years / EARTH_RATIO;
}

double space_age::on_mercury() const {
    return age_in_years / MERCURY_RATIO;
}

double space_age::on_venus() const {
    return age_in_years / VENUS_RATIO;
}

double space_age::on_mars() const {
    return age_in_years / MARS_RATIO;
}

double space_age::on_jupiter() const {
    return age_in_years / JUPITER_RATIO;
}

double space_age::on_saturn() const {
    return age_in_years / SATURN_RATIO;
}

double space_age::on_uranus() const {
    return age_in_years / URANUS_RATIO;
}

double space_age::on_neptune() const {
    return age_in_years / NEPTUNE_RATIO;
}

}  // namespace space_age