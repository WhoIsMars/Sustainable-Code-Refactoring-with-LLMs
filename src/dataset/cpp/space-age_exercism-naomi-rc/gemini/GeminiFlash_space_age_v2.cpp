#include "space_age.h"

namespace space_age {

const double space_age::earth_seconds = 31557600.0;
const double space_age::mercury_ratio = 0.2408467;
const double space_age::venus_ratio = 0.61519726;
const double space_age::mars_ratio = 1.8808158;
const double space_age::jupiter_ratio = 11.862615;
const double space_age::saturn_ratio = 29.447498;
const double space_age::uranus_ratio = 84.016846;
const double space_age::neptune_ratio = 164.79132;

space_age::space_age(double age_in_seconds) : age(age_in_seconds) {}

int space_age::seconds() const {
  return static_cast<int>(age);
}

double space_age::on_earth() const {
  return age / earth_seconds;
}

double space_age::on_mercury() const {
  return age / (earth_seconds * mercury_ratio);
}

double space_age::on_venus() const {
  return age / (earth_seconds * venus_ratio);
}

double space_age::on_mars() const {
  return age / (earth_seconds * mars_ratio);
}

double space_age::on_jupiter() const {
  return age / (earth_seconds * jupiter_ratio);
}

double space_age::on_saturn() const {
  return age / (earth_seconds * saturn_ratio);
}

double space_age::on_uranus() const {
  return age / (earth_seconds * uranus_ratio);
}

double space_age::on_neptune() const {
  return age / (earth_seconds * neptune_ratio);
}

} // namespace space_age