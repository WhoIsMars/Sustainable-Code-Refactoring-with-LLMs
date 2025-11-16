#include "space_age.h"

enum planet { MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE };

static constexpr double Orbital_Period[] {
    0.2408467, 0.61519726, 1.0000000, 1.8808158, 
    11.862615, 29.447498, 84.016846, 164.79132 
};
static constexpr double Earth_Year_Seconds = 31557600.0;

[[nodiscard]]
space_age::space_age::space_age(const uint_fast64_t _seconds) noexcept : age(static_cast<double>(_seconds)) {}

uint_fast64_t space_age::space_age::seconds() const noexcept {
    return static_cast<uint_fast64_t>(age);
}

float space_age::space_age::on_mercury() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[MERCURY] * Earth_Year_Seconds));
}
float space_age::space_age::on_venus() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[VENUS] * Earth_Year_Seconds));
}
float space_age::space_age::on_earth() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[EARTH] * Earth_Year_Seconds));
}
float space_age::space_age::on_mars() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[MARS] * Earth_Year_Seconds));
}
float space_age::space_age::on_jupiter() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[JUPITER] * Earth_Year_Seconds));
}
float space_age::space_age::on_saturn() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[SATURN] * Earth_Year_Seconds));
}
float space_age::space_age::on_uranus() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[URANUS] * Earth_Year_Seconds));
}
float space_age::space_age::on_neptune() const noexcept { 
    return static_cast<float>(age / (Orbital_Period[NEPTUNE] * Earth_Year_Seconds));
}