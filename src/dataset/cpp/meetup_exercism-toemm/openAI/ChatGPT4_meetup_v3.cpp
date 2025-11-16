#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(months_of_year month, int year) : 
                                                        _month(month), 
                                                        _year(year), 
                                                        teenths(date(_year, _month, 13)) {}

date scheduler::monteenth() const {
    return teenths + days((Monday - teenths.day_of_week() + 7) % 7);
}

date scheduler::tuesteenth() const {
    return teenths + days((Tuesday - teenths.day_of_week() + 7) % 7);
}

date scheduler::wednesteenth() const {
    return teenths + days((Wednesday - teenths.day_of_week() + 7) % 7);
}

date scheduler::thursteenth() const {
    return teenths + days((Thursday - teenths.day_of_week() + 7) % 7);
}

date scheduler::friteenth() const {
    return teenths + days((Friday - teenths.day_of_week() + 7) % 7);
}

date scheduler::saturteenth() const {
    return teenths + days((Saturday - teenths.day_of_week() + 7) % 7);
}

date scheduler::sunteenth() const {
    return teenths + days((Sunday - teenths.day_of_week() + 7) % 7);
}

}  // namespace meetup