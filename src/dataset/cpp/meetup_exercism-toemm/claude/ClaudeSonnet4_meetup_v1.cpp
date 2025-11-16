#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) : 
                                                        _month(month), 
                                                        _year(year), 
                                                        teenths(date_period(date(_year, _month, 13), days(7))) {
    // Pre-calculate all teenth dates during construction
    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        teenth_dates[it.day_of_week().as_number()] = it.day();
    }
}

date scheduler::monteenth() const {
    return date(_year, _month, teenth_dates[Monday.as_number()]);
}

date scheduler::tuesteenth() const {
    return date(_year, _month, teenth_dates[Tuesday.as_number()]);
}

date scheduler::wednesteenth() const {
    return date(_year, _month, teenth_dates[Wednesday.as_number()]);
}

date scheduler::thursteenth() const {
    return date(_year, _month, teenth_dates[Thursday.as_number()]);
}

date scheduler::friteenth() const {
    return date(_year, _month, teenth_dates[Friday.as_number()]);
}

date scheduler::saturteenth() const {
    return date(_year, _month, teenth_dates[Saturday.as_number()]);
}

date scheduler::sunteenth() const {
    return date(_year, _month, teenth_dates[Sunday.as_number()]);
}

}  // namespace meetup