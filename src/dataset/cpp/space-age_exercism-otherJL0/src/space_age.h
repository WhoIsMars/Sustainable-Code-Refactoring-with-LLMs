#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H
#include <map>
#include <string>

namespace space_age {
class space_age {
 private:
  long age_in_seconds;
  double seconds_in_year = 31557600.0;
  double age_in_years;
  std::map<std::string, double> convert_tot = {
      {"mercury", 0.2408467}, {"venus", 0.61519726},  {"earth", 1.0},
      {"mars", 1.8808158},    {"jupiter", 11.862615}, {"saturn", 29.447498},
      {"uranus", 84.016846},  {"neptune", 164.79132}};

 public:
  explicit space_age(long input_seconds);
  long seconds() const;
  double on_earth() const;
  double on_mercury() const;
  double on_venus() const;
  double on_mars() const;
  double on_jupiter() const;
  double on_saturn() const;
  double on_uranus() const;
  double on_neptune() const;
};

}  // namespace space_age

#endif  // SPACE_AGE_H
