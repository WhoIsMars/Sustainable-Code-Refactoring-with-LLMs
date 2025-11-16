#include "space_age.h"

enum planet { MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE };

static constexpr double Orbital_Period[] {
    0.2408467, 0.61519726, 1.0000000, 1.8808158, 
    11.862615, 29.447498, 84.016846, 164.79132 
};
static constexpr double Earth_Year_Reciprocal = 1.0 / 31557600.0;

[[nodiscard]]
space_age::space_age::space_age(const uint_fast64_t _seconds): age(_seconds) {}

uint_fast64_t space_age::space_age::seconds() const noexcept {
    return age;
}

float space_age::space_age::on_mercury() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[MERCURY]);
}
float space_age::space_age::on_venus() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[VENUS]);
}
float space_age::space_age::on_earth() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[EARTH]);
}
float space_age::space_age::on_mars() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[MARS]);
}
float space_age::space_age::on_jupiter() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[JUPITER]);
}
float space_age::space_age::on_saturn() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[SATURN]);
}
float space_age::space_age::on_uranus() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[URANUS]);
}
float space_age::space_age::on_neptune() const noexcept { 
    return static_cast<float>(age * Earth_Year_Reciprocal / Orbital_Period[NEPTUNE]);
}