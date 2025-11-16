#include "space_age.h"

namespace space_age {

class space_age {
private:
    double time;
    static constexpr double earth = 31557600.0;
    static constexpr double mercury = 0.2408467;
    static constexpr double venus = 0.61519726;
    static constexpr double mars = 1.8808158;
    static constexpr double jupiter = 11.862615;
    static constexpr double saturn = 29.447498;
    static constexpr double uranus = 84.016846;
    static constexpr double neptune = 164.79132;

    double calculate(double planet_ratio) const noexcept {
        return time / (earth * planet_ratio);
    }

public:
    explicit space_age(double input) noexcept : time(input) {}

    double seconds() const noexcept { return time; }
    double on_earth() const noexcept { return calculate(1.0); }
    double on_mercury() const noexcept { return calculate(mercury); }
    double on_venus() const noexcept { return calculate(venus); }
    double on_mars() const noexcept { return calculate(mars); }
    double on_jupiter() const noexcept { return calculate(jupiter); }
    double on_saturn() const noexcept { return calculate(saturn); }
    double on_uranus() const noexcept { return calculate(uranus); }
    double on_neptune() const noexcept { return calculate(neptune); }
};

} // namespace space_age