#include "space_age.h"

enum planet { MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE };

static constexpr double Orbital_Period[] {
    0.2408467, 0.61519726, 1.0000000, 1.8808158, 
    11.862615, 29.447498, 84.016846, 164.79132 
};
static constexpr uint64_t Earth_Year { 31557600 };

[[nodiscard]]
space_age::space_age::space_age(const uint_fast64_t _seconds): age(_seconds) {}

uint_fast64_t space_age::space_age::seconds() const noexcept {
    return age;
}
float space_age::space_age::on_mercury() const noexcept { 
    return age / (Orbital_Period[MERCURY] * Earth_Year);
}
float space_age::space_age::on_venus() const noexcept { 
    return age / (Orbital_Period[VENUS] * Earth_Year);
}
float space_age::space_age::on_earth() const noexcept { 
    return age / (Orbital_Period[EARTH] * Earth_Year);
}
float space_age::space_age::on_mars() const noexcept { 
    return age / (Orbital_Period[MARS] * Earth_Year);
}
float space_age::space_age::on_jupiter() const noexcept { 
    return age / (Orbital_Period[JUPITER] * Earth_Year);
}
float space_age::space_age::on_saturn() const noexcept { 
    return age / (Orbital_Period[SATURN] * Earth_Year);
}
float space_age::space_age::on_uranus() const noexcept { 
    return age / (Orbital_Period[URANUS] * Earth_Year);
}
float space_age::space_age::on_neptune() const noexcept { 
    return age / (Orbital_Period[NEPTUNE] * Earth_Year);
}