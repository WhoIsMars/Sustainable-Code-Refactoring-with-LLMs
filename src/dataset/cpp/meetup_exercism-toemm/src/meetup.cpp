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
  
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Monday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}

date scheduler::tuesteenth() const {
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Tuesday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}
date scheduler::wednesteenth() const {
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Wednesday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}
date scheduler::thursteenth() const {
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Thursday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}
date scheduler::friteenth() const {
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Friday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}
date scheduler::saturteenth() const {
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Saturday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}
date scheduler::sunteenth() const {
    int teenth_date{};

    for (auto it = teenths.begin(); it != teenths.end(); it += days(1)) {
        if (it.day_of_week() == Sunday)
            teenth_date = it.day();
    }
    return date(_year, _month, teenth_date);
}





}  // namespace meetup
