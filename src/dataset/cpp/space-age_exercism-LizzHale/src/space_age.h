#ifndef _SPACE_AGE_H_
#define _SPACE_AGE_H_
namespace space_age {
    class space_age{
        long _seconds;
    public:        
        explicit space_age(long);
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
}
#endif