#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

constexpr double EARTH_YEAR_SECS    =   31557600;
constexpr double MERCURY_ORBIT      =   0.2408467 * EARTH_YEAR_SECS;
constexpr double VENUS_ORBIT        =	0.61519726 * EARTH_YEAR_SECS;
constexpr double EARTH_ORBIT        =	1.0 * EARTH_YEAR_SECS;
constexpr double MARS_ORBIT         =	1.8808158 * EARTH_YEAR_SECS;
constexpr double JUPITER_ORBIT      =	11.862615 * EARTH_YEAR_SECS;
constexpr double SATURN_ORBIT       =	29.447498 * EARTH_YEAR_SECS;
constexpr double URANUS_ORBIT       =	84.016846 * EARTH_YEAR_SECS;
constexpr double NEPTUNE_ORBIT      =	164.79132 * EARTH_YEAR_SECS;

namespace space_age {


    class space_age {
        public:

        space_age(double secs);
        double seconds() const;
        double on_earth() const;
        double on_mercury() const;
        double on_venus() const;
        double on_mars() const;
        double on_jupiter() const;
        double on_saturn() const;
        double on_uranus() const;
        double on_neptune() const;


        private:
        double secs;



    };

}  // namespace space_age

#endif  // SPACE_AGE_H