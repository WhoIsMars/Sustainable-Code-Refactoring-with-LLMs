#include "space_age.h"

namespace space_age {

space_age::space_age(double seconds) : time(seconds) {}

double space_age::seconds() const {
  return time;
}

double space_age::on_earth() const {
  return time / earth;
}

double space_age::on_mercury() const {
  return time / mercury_orbital_period;
}

double space_age::on_venus() const {
  return time / venus_orbital_period;
}

double space_age::on_mars() const {
  return time / mars_orbital_period;
}

double space_age::on_jupiter() const {
  return time / jupiter_orbital_period;
}

double space_age::on_saturn() const {
  return time / saturn_orbital_period;
}

double space_age::on_uranus() const {
  return time / uranus_orbital_period;
}

double space_age::on_neptune() const {
  return time / neptune_orbital_period;
}

} // namespace space_age