#include "space_age.h"

namespace space_age {

// Precomputed constants to avoid map lookups
static constexpr double EARTH_FACTOR = 1.0;
static constexpr double MERCURY_FACTOR = 0.2408467;
static constexpr double VENUS_FACTOR = 0.61519726;
static constexpr double MARS_FACTOR = 1.8808158;
static constexpr double JUPITER_FACTOR = 11.862615;
static constexpr double SATURN_FACTOR = 29.447498;
static constexpr double URANUS_FACTOR = 84.016846;
static constexpr double NEPTUNE_FACTOR = 164.79132;

space_age::space_age(long input_seconds) 
  : age_in_seconds(input_seconds), 
    age_in_years(static_cast<double>(input_seconds) / seconds_in_year) {
}

long space_age::seconds() const { 
  return age_in_seconds; 
}

double space_age::on_earth() const {
  return age_in_years / EARTH_FACTOR;
}

double space_age::on_mercury() const {
  return age_in_years / MERCURY_FACTOR;
}

double space_age::on_venus() const {
  return age_in_years / VENUS_FACTOR;
}

double space_age::on_mars() const {
  return age_in_years / MARS_FACTOR;
}

double space_age::on_jupiter() const {
  return age_in_years / JUPITER_FACTOR;
}

double space_age::on_saturn() const {
  return age_in_years / SATURN_FACTOR;
}

double space_age::on_uranus() const {
  return age_in_years / URANUS_FACTOR;
}

double space_age::on_neptune() const {
  return age_in_years / NEPTUNE_FACTOR;
}

}  // namespace space_age