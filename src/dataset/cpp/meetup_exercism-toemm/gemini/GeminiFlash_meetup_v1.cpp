#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) :
    _month(month),
    _year(year),
    teenths(date(_year, _month, 13))
{
}

date scheduler::monteenth() const {
    return find_teenth(Monday);
}

date scheduler::tuesteenth() const {
    return find_teenth(Tuesday);
}

date scheduler::wednesteenth() const {
    return find_teenth(Wednesday);
}

date scheduler::thursteenth() const {
    return find_teenth(Thursday);
}

date scheduler::friteenth() const {
    return find_teenth(Friday);
}

date scheduler::saturteenth() const {
    return find_teenth(Saturday);
}

date scheduler::sunteenth() const {
    return find_teenth(Sunday);
}

date scheduler::find_teenth(boost::date_time::weekdays day) const {
    for (int i = 0; i < 7; ++i) {
        date current_date = teenths + days(i);
        if (current_date.day_of_week() == day) {
            return current_date;
        }
    }
    // Should not happen, but return a default value to avoid undefined behavior
    return date(_year, _month, 13);
}

}  // namespace meetup