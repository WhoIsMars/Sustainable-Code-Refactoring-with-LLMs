#include "space_age.h"

namespace space_age {

constexpr double EARTH_YEAR_SECONDS = 31557600.0;

inline double calculate_age(double seconds, double orbital_period) {
    return seconds / (EARTH_YEAR_SECONDS * orbital_period);
}

double age_on_earth(double seconds) {
    return calculate_age(seconds, 1.0);
}

double age_on_mercury(double seconds) {
    return calculate_age(seconds, 0.2408467);
}

double age_on_venus(double seconds) {
    return calculate_age(seconds, 0.61519726);
}

double age_on_mars(double seconds) {
    return calculate_age(seconds, 1.8808158);
}

double age_on_jupiter(double seconds) {
    return calculate_age(seconds, 11.862615);
}

double age_on_saturn(double seconds) {
    return calculate_age(seconds, 29.447498);
}

double age_on_uranus(double seconds) {
    return calculate_age(seconds, 84.016846);
}

double age_on_neptune(double seconds) {
    return calculate_age(seconds, 164.79132);
}

}  // namespace space_age