#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) : 
    _month(month), 
    _year(year), 
    teenths(date_period(date(_year, _month, 13), days(7))) {
}

date scheduler::monteenth() const {
    return find_teenth_for_weekday(Monday);
}

date scheduler::tuesteenth() const {
    return find_teenth_for_weekday(Tuesday);
}

date scheduler::wednesteenth() const {
    return find_teenth_for_weekday(Wednesday);
}

date scheduler::thursteenth() const {
    return find_teenth_for_weekday(Thursday);
}

date scheduler::friteenth() const {
    return find_teenth_for_weekday(Friday);
}

date scheduler::saturteenth() const {
    return find_teenth_for_weekday(Saturday);
}

date scheduler::sunteenth() const {
    return find_teenth_for_weekday(Sunday);
}

date scheduler::find_teenth_for_weekday(greg_weekday target_weekday) const {
    date start_date(_year, _month, 13);
    greg_weekday start_weekday = start_date.day_of_week();
    
    int days_offset = (target_weekday.as_number() - start_weekday.as_number() + 7) % 7;
    
    return start_date + days(days_offset);
}

}  // namespace meetup