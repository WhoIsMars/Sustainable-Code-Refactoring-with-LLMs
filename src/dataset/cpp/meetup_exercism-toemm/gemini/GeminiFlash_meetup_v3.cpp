#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) :
    _month(month),
    _year(year),
    teenths(date(_year, _month, 13)) {
}

date scheduler::teenth_of_week(boost::date_time::weekdays day) const {
    date d = teenths;
    for (int i = 0; i < 7; ++i) {
        if (d.day_of_week() == day) {
            return d;
        }
        d += days(1);
    }
    return {}; // Should not happen, but return a default date if it does.
}

date scheduler::monteenth() const {
    return teenth_of_week(Monday);
}

date scheduler::tuesteenth() const {
    return teenth_of_week(Tuesday);
}

date scheduler::wednesteenth() const {
    return teenth_of_week(Wednesday);
}

date scheduler::thursteenth() const {
    return teenth_of_week(Thursday);
}

date scheduler::friteenth() const {
    return teenth_of_week(Friday);
}

date scheduler::saturteenth() const {
    return teenth_of_week(Saturday);
}

date scheduler::sunteenth() const {
    return teenth_of_week(Sunday);
}

}  // namespace meetup