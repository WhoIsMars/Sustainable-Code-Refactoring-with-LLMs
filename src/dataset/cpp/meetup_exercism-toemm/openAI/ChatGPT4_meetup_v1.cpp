#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) : 
                                                        _month(month), 
                                                        _year(year), 
                                                        teenths(date(_year, _month, 13)) {}

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

date scheduler::find_teenth(day_of_week day) const {
    for (date d = teenths; d.day() <= 19; d += days(1)) {
        if (d.day_of_week() == day) {
            return d;
        }
    }
    return date(); // Should never reach here
}

}  // namespace meetup