#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) : 
                                                        _month(month), 
                                                        _year(year), 
                                                        teenths(date(_year, _month, 13)) {}

date scheduler::find_teenth(day_of_week target_day) const {
    for (int i = 0; i < 7; ++i) {
        date current_date = teenths + days(i);
        if (current_date.day_of_week() == target_day) {
            return current_date;
        }
    }
    return teenths; // Fallback, though this should never be reached
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

}  // namespace meetup