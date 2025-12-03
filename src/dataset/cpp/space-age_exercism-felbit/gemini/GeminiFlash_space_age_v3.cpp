#include "space_age.h"
#include <cmath>

namespace space_age {

const double EARTH_YEAR_SECONDS = 31557600.0;

space_age::space_age(unsigned long long int seconds) : m_seconds(seconds) {}

unsigned long long int space_age::seconds() const { return m_seconds; }

double space_age::on_earth() const { return m_seconds / EARTH_YEAR_SECONDS; }

double space_age::on_mercury() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 0.2408467);
}

double space_age::on_venus() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 0.61519726);
}

double space_age::on_mars() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 1.8808158);
}

double space_age::on_jupiter() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 11.862615);
}

double space_age::on_saturn() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 29.447498);
}

double space_age::on_uranus() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 84.016846);
}

double space_age::on_neptune() const {
  return m_seconds / (EARTH_YEAR_SECONDS * 164.79132);
}

} // namespace space_age