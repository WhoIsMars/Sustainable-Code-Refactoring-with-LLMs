#include "space_age.h"

namespace space_age {
space_age::space_age(long input_seconds) {
  age_in_seconds = input_seconds;
  age_in_years = age_in_seconds / seconds_in_year;
}

long space_age::seconds() const { return age_in_seconds; }
double space_age::on_earth() const {
  return age_in_years / convert_tot.at("earth");
}

double space_age::on_mercury() const {
  return age_in_years / convert_tot.at("mercury");
}

double space_age::on_venus() const {
  return age_in_years / convert_tot.at("venus");
}

double space_age::on_mars() const {
  return age_in_years / convert_tot.at("mars");
}

double space_age::on_jupiter() const {
  return age_in_years / convert_tot.at("jupiter");
}

double space_age::on_saturn() const {
  return age_in_years / convert_tot.at("saturn");
}

double space_age::on_uranus() const {
  return age_in_years / convert_tot.at("uranus");
}

double space_age::on_neptune() const {
  return age_in_years / convert_tot.at("neptune");
}

}  // namespace space_age
