#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {
    class space_age
    {
        public:
            static constexpr double cx_sec2day = 60*60*24.0;
            static constexpr double cx_sec2year= cx_sec2day * 365.25; //Using an astronomical year of 365.2 days
            static constexpr double cx_earth2mercury = 0.2408467;
            static constexpr double cx_earth2venus = 0.61519726;
            static constexpr double cx_earth2mars = 1.8808158;
            static constexpr double cx_earth2jupiter = 11.862615;
            static constexpr double cx_earth2saturn = 29.447498;
            static constexpr double cx_earth2uranus = 84.016846;
            static constexpr double cx_earth2neptun = 164.79132;

            explicit space_age(uint64_t ageSec);

            uint64_t seconds() const;
            double on_earth() const;
            double on_mercury() const;
            double on_venus() const;
            double on_mars() const;
            double on_jupiter() const;
            double on_saturn() const;
            double on_uranus() const;
            double on_neptune() const;
        private:
            uint64_t ageSec;
    };
}  // namespace space_age

#endif // SPACE_AGE_H