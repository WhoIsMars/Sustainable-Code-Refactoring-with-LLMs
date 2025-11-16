#include "space_age.h"

namespace space_age {

    constexpr double EARTH_YEAR_IN_SECONDS = 31557600.0;

    constexpr double ORBITAL_PERIODS[] = {
        1.0,            // Earth
        0.2408467,      // Mercury
        0.61519726,     // Venus
        1.8808158,      // Mars
        11.862615,      // Jupiter
        29.447498,      // Saturn
        84.016846,      // Uranus
        164.79132       // Neptune
    };

    enum Planet {
        EARTH = 0,
        MERCURY,
        VENUS,
        MARS,
        JUPITER,
        SATURN,
        URANUS,
        NEPTUNE
    };

    class space_age {
    private:
        double seconds_;

    public:
        explicit space_age(double seconds) : seconds_(seconds) {}

        double seconds() const {
            return seconds_;
        }

        double on_earth() const {
            return seconds_ / EARTH_YEAR_IN_SECONDS;
        }

        double on_mercury() const {
            return on_earth() / ORBITAL_PERIODS[MERCURY];
        }

        double on_venus() const {
            return on_earth() / ORBITAL_PERIODS[VENUS];
        }

        double on_mars() const {
            return on_earth() / ORBITAL_PERIODS[MARS];
        }

        double on_jupiter() const {
            return on_earth() / ORBITAL_PERIODS[JUPITER];
        }

        double on_saturn() const {
            return on_earth() / ORBITAL_PERIODS[SATURN];
        }

        double on_uranus() const {
            return on_earth() / ORBITAL_PERIODS[URANUS];
        }

        double on_neptune() const {
            return on_earth() / ORBITAL_PERIODS[NEPTUNE];
        }
    };

}  // namespace space_age