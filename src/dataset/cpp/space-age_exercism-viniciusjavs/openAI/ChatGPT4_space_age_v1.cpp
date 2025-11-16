#include "space_age.h"

namespace space_age {

constexpr double EARTH_YEAR_IN_SECONDS = 31557600.0;

constexpr double ORBITAL_PERIODS[] = {
    0.2408467,  // Mercury
    0.61519726, // Venus
    1.0,        // Earth
    1.8808158,  // Mars
    11.862615,  // Jupiter
    29.447498,  // Saturn
    84.016846,  // Uranus
    164.79132   // Neptune
};

inline double age_on_planet(double seconds, double orbital_period) {
    return seconds / (EARTH_YEAR_IN_SECONDS * orbital_period);
}

double age_on_mercury(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[0]);
}

double age_on_venus(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[1]);
}

double age_on_earth(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[2]);
}

double age_on_mars(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[3]);
}

double age_on_jupiter(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[4]);
}

double age_on_saturn(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[5]);
}

double age_on_uranus(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[6]);
}

double age_on_neptune(double seconds) {
    return age_on_planet(seconds, ORBITAL_PERIODS[7]);
}

}  // namespace space_age