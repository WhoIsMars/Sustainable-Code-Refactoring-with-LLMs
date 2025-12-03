#include "space_age.h"

namespace space_age {

space_age::space_age(double seconds) : time(seconds) {}

double space_age::seconds() const {
  return time;
}

double space_age::on_earth() const {
  return time / earth_orbital_period;
}

double space_age::on_mercury() const {
  return time / (earth_orbital_period * mercury_orbital_period);
}

double space_age::on_venus() const {
  return time / (earth_orbital_period * venus_orbital_period);
}

double space_age::on_mars() const {
  return time / (earth_orbital_period * mars_orbital_period);
}

double space_age::on_jupiter() const {
  return time / (earth_orbital_period * jupiter_orbital_period);
}

double space_age::on_saturn() const {
  return time / (earth_orbital_period * saturn_orbital_period);
}

double space_age::on_uranus() const {
  return time / (earth_orbital_period * uranus_orbital_period);
}

double space_age::on_neptune() const {
  return time / (earth_orbital_period * neptune_orbital_period);
}

}  // namespace space_age