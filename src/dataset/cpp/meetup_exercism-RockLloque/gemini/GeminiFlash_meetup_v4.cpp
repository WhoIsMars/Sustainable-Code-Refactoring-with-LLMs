#include "meetup.h"

namespace meetup {

boost::gregorian::date scheduler::teenth_day(boost::date_time::weekdays const& d) const {
  static const int teenth_start = 13;
  boost::gregorian::date date(year_, month_, teenth_start);
  boost::date_time::weekdays weekday = d;

  for (int day = teenth_start; day <= 19; ++day) {
    date = boost::gregorian::date(year_, month_, day);
    if (date.day_of_week() == weekday) {
      return date;
    }
  }
  return boost::gregorian::date(boost::date_time::not_a_date_time); // Should never happen
}

boost::gregorian::date scheduler::monteenth() const {
  return teenth_day(boost::date_time::weekdays::Monday);
}

boost::gregorian::date scheduler::tuesteenth() const {
  return teenth_day(boost::date_time::weekdays::Tuesday);
}

boost::gregorian::date scheduler::wednesteenth() const {
  return teenth_day(boost::date_time::weekdays::Wednesday);
}

boost::gregorian::date scheduler::thursteenth() const {
  return teenth_day(boost::date_time::weekdays::Thursday);
}

boost::gregorian::date scheduler::friteenth() const {
  return teenth_day(boost::date_time::weekdays::Friday);
}

boost::gregorian::date scheduler::saturteenth() const {
  return teenth_day(boost::date_time::weekdays::Saturday);
}

boost::gregorian::date scheduler::sunteenth() const {
  return teenth_day(boost::date_time::weekdays::Sunday);
}

boost::gregorian::date scheduler::nth_day(int n, boost::date_time::weekdays const& d) const {
    boost::gregorian::date first_of_month(year_, month_, 1);
    boost::gregorian::date first_instance = boost::gregorian::first_day_of_the_week_after(d).get_date(first_of_month - boost::gregorian::days(1));
    boost::gregorian::date result = first_instance + boost::gregorian::weeks(n - 1);

    if (result.month() != month_) {
        return boost::gregorian::date(boost::date_time::not_a_date_time);
    }

    return result;
}

boost::gregorian::date scheduler::first_monday() const {
  return nth_day(1, boost::date_time::weekdays::Monday);
}

boost::gregorian::date scheduler::first_tuesday() const {
  return nth_day(1, boost::date_time::weekdays::Tuesday);
}

boost::gregorian::date scheduler::first_wednesday() const {
  return nth_day(1, boost::date_time::weekdays::Wednesday);
}

boost::gregorian::date scheduler::first_thursday() const {
  return nth_day(1, boost::date_time::weekdays::Thursday);
}

boost::gregorian::date scheduler::first_friday() const {
  return nth_day(1, boost::date_time::weekdays::Friday);
}

boost::gregorian::date scheduler::first_saturday() const {
  return nth_day(1, boost::date_time::weekdays::Saturday);
}

boost::gregorian::date scheduler::first_sunday() const {
  return nth_day(1, boost::date_time::weekdays::Sunday);
}

boost::gregorian::date scheduler::second_monday() const {
    return nth_day(2, boost::date_time::weekdays::Monday);
}

boost::gregorian::date scheduler::second_tuesday() const {
    return nth_day(2, boost::date_time::weekdays::Tuesday);
}

boost::gregorian::date scheduler::second_wednesday() const {
    return nth_day(2, boost::date_time::weekdays::Wednesday);
}

boost::gregorian::date scheduler::second_thursday() const {
    return nth_day(2, boost::date_time::weekdays::Thursday);
}

boost::gregorian::date scheduler::second_friday() const {
    return nth_day(2, boost::date_time::weekdays::Friday);
}

boost::gregorian::date scheduler::second_saturday() const {
    return nth_day(2, boost::date_time::weekdays::Saturday);
}

boost::gregorian::date scheduler::second_sunday() const {
    return nth_day(2, boost::date_time::weekdays::Sunday);
}

boost::gregorian::date scheduler::third_monday() const {
    return nth_day(3, boost::date_time::weekdays::Monday);
}

boost::gregorian::date scheduler::third_tuesday() const {
    return nth_day(3, boost::date_time::weekdays::Tuesday);
}

boost::gregorian::date scheduler::third_wednesday() const {
    return nth_day(3, boost::date_time::weekdays::Wednesday);
}

boost::gregorian::date scheduler::third_thursday() const {
    return nth_day(3, boost::date_time::weekdays::Thursday);
}

boost::gregorian::date scheduler::third_friday() const {
    return nth_day(3, boost::date_time::weekdays::Friday);
}

boost::gregorian::date scheduler::third_saturday() const {
    return nth_day(3, boost::date_time::weekdays::Saturday);
}

boost::gregorian::date scheduler::third_sunday() const {
    return nth_day(3, boost::date_time::weekdays::Sunday);
}

boost::gregorian::date scheduler::fourth_monday() const {
    return nth_day(4, boost::date_time::weekdays::Monday);
}

boost::gregorian::date scheduler::fourth_tuesday() const {
    return nth_day(4, boost::date_time::weekdays::Tuesday);
}

boost::gregorian::date scheduler::fourth_wednesday() const {
    return nth_day(4, boost::date_time::weekdays::Wednesday);
}

boost::gregorian::date scheduler::fourth_thursday() const {
    return nth_day(4, boost::date_time::weekdays::Thursday);
}

boost::gregorian::date scheduler::fourth_friday() const {
    return nth_day(4, boost::date_time::weekdays::Friday);
}

boost::gregorian::date scheduler::fourth_saturday() const {
    return nth_day(4, boost::date_time::weekdays::Saturday);
}

boost::gregorian::date scheduler::fourth_sunday() const {
    return nth_day(4, boost::date_time::weekdays::Sunday);
}

boost::gregorian::date scheduler::last_day(boost::date_time::weekdays const& d) const {
    boost::gregorian::date last_day_of_month = boost::gregorian::date(year_, month_, boost::gregorian::gregorian_calendar::end_of_month(year_, month_));
    boost::date_time::weekdays weekday = d;
    boost::gregorian::date result = last_day_of_month;

    while (result.day_of_week() != weekday) {
        result -= boost::gregorian::days(1);
    }
    return result;
}

boost::gregorian::date scheduler::last_monday() const {
  return last_day(boost::date_time::weekdays::Monday);
}

boost::gregorian::date scheduler::last_tuesday() const {
  return last_day(boost::date_time::weekdays::Tuesday);
}

boost::gregorian::date scheduler::last_wednesday() const {
  return last_day(boost::date_time::weekdays::Wednesday);
}

boost::gregorian::date scheduler::last_thursday() const {
  return last_day(boost::date_time::weekdays::Thursday);
}

boost::gregorian::date scheduler::last_friday() const {
  return last_day(boost::date_time::weekdays::Friday);
}

boost::gregorian::date scheduler::last_saturday() const {
  return last_day(boost::date_time::weekdays::Saturday);
}

boost::gregorian::date scheduler::last_sunday() const {
  return last_day(boost::date_time::weekdays::Sunday);
}

} // namespace meetup