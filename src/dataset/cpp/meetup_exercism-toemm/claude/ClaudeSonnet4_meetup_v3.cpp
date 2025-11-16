#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) : 
    _month(month), 
    _year(year), 
    teenths(date_period(date(_year, _month, 13), days(7))) {
    precompute_teenth_dates();
}

void scheduler::precompute_teenth_dates() {
    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        teenth_dates[it.day_of_week().as_number()] = it.day();
    }
}

date scheduler::get_teenth_by_weekday(greg_weekday weekday) const {
    return date(_year, _month, teenth_dates[weekday.as_number()]);
}

date scheduler::monteenth() const {
    return get_teenth_by_weekday(Monday);
}

date scheduler::tuesteenth() const {
    return get_teenth_by_weekday(Tuesday);
}

date scheduler::wednesteenth() const {
    return get_teenth_by_weekday(Wednesday);
}

date scheduler::thursteenth() const {
    return get_teenth_by_weekday(Thursday);
}

date scheduler::friteenth() const {
    return get_teenth_by_weekday(Friday);
}

date scheduler::saturteenth() const {
    return get_teenth_by_weekday(Saturday);
}

date scheduler::sunteenth() const {
    return get_teenth_by_weekday(Sunday);
}

}  // namespace meetup