/*
 * =====================================================================================
 *
 *       Filename:  meetup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12.01.2016 15:12:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */

#include "meetup.h"

namespace meetup
{
    // Pre-computed static days offset to avoid repeated object creation
    static const boost::gregorian::days WEEK_OFFSET(7);
    static const boost::gregorian::days TWO_WEEKS_OFFSET(14);
    static const boost::gregorian::days THREE_WEEKS_OFFSET(21);

    boost::gregorian::date scheduler::teenth_day(boost::date_time::weekdays const& d) const 
    {
        return boost::gregorian::first_day_of_the_week_after(d).get_date({year_,month_,12});
    }

    boost::gregorian::date scheduler::monteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Monday);
    }

    boost::gregorian::date scheduler::tuesteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Tuesday);
    }

    boost::gregorian::date scheduler::wednesteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Wednesday);
    }

    boost::gregorian::date scheduler::thursteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Thursday);
    }

    boost::gregorian::date scheduler::friteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Friday);
    }

    boost::gregorian::date scheduler::saturteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Saturday);
    }

    boost::gregorian::date scheduler::sunteenth() const 
    {
        return teenth_day(boost::date_time::weekdays::Sunday);
    }

    boost::gregorian::date scheduler::first_day(boost::date_time::weekdays const& d) const
    {
        return boost::gregorian::nth_day_of_the_week_in_month(boost::gregorian::nth_day_of_the_week_in_month::first, d, month_).get_date(year_);
    }

    boost::gregorian::date scheduler::first_monday() const
    {
        return first_day(boost::date_time::weekdays::Monday);
    }

    boost::gregorian::date scheduler::first_tuesday() const
    {
        return first_day(boost::date_time::weekdays::Tuesday);
    }

    boost::gregorian::date scheduler::first_wednesday() const
    {
        return first_day(boost::date_time::weekdays::Wednesday);
    }

    boost::gregorian::date scheduler::first_thursday() const
    {
        return first_day(boost::date_time::weekdays::Thursday);
    }

    boost::gregorian::date scheduler::first_friday() const
    {
        return first_day(boost::date_time::weekdays::Friday);
    }

    boost::gregorian::date scheduler::first_saturday() const
    {
        return first_day(boost::date_time::weekdays::Saturday);
    }

    boost::gregorian::date scheduler::first_sunday() const
    {
        return first_day(boost::date_time::weekdays::Sunday);
    }

    boost::gregorian::date scheduler::second_monday() const
    {
        return first_day(boost::date_time::weekdays::Monday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::second_tuesday() const
    {
        return first_day(boost::date_time::weekdays::Tuesday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::second_wednesday() const
    {
        return first_day(boost::date_time::weekdays::Wednesday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::second_thursday() const
    {
        return first_day(boost::date_time::weekdays::Thursday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::second_friday() const
    {
        return first_day(boost::date_time::weekdays::Friday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::second_saturday() const
    {
        return first_day(boost::date_time::weekdays::Saturday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::second_sunday() const
    {
        return first_day(boost::date_time::weekdays::Sunday) + WEEK_OFFSET;
    }

    boost::gregorian::date scheduler::third_monday() const
    {
        return first_day(boost::date_time::weekdays::Monday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::third_tuesday() const
    {
        return first_day(boost::date_time::weekdays::Tuesday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::third_wednesday() const
    {
        return first_day(boost::date_time::weekdays::Wednesday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::third_thursday() const
    {
        return first_day(boost::date_time::weekdays::Thursday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::third_friday() const
    {
        return first_day(boost::date_time::weekdays::Friday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::third_saturday() const
    {
        return first_day(boost::date_time::weekdays::Saturday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::third_sunday() const
    {
        return first_day(boost::date_time::weekdays::Sunday) + TWO_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_monday() const
    {
        return first_day(boost::date_time::weekdays::Monday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_tuesday() const
    {
        return first_day(boost::date_time::weekdays::Tuesday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_wednesday() const
    {
        return first_day(boost::date_time::weekdays::Wednesday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_thursday() const
    {
        return first_day(boost::date_time::weekdays::Thursday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_friday() const
    {
        return first_day(boost::date_time::weekdays::Friday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_saturday() const
    {
        return first_day(boost::date_time::weekdays::Saturday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::fourth_sunday() const
    {
        return first_day(boost::date_time::weekdays::Sunday) + THREE_WEEKS_OFFSET;
    }

    boost::gregorian::date scheduler::last_day(boost::date_time::weekdays const& d) const
    {
        return boost::gregorian::last_day_of_the_week_in_month(d, month_).get_date(year_);
    }

    boost::gregorian::date scheduler::last_monday() const
    {
        return last_day(boost::date_time::weekdays::Monday);
    }

    boost::gregorian::date scheduler::last_tuesday() const
    {
        return last_day(boost::date_time::weekdays::Tuesday);
    }

    boost::gregorian::date scheduler::last_wednesday() const
    {
        return last_day(boost::date_time::weekdays::Wednesday);
    }

    boost::gregorian::date scheduler::last_thursday() const
    {
        return last_day(boost::date_time::weekdays::Thursday);
    }

    boost::gregorian::date scheduler::last_friday() const
    {
        return last_day(boost::date_time::weekdays::Friday);
    }

    boost::gregorian::date scheduler::last_saturday() const
    {
        return last_day(boost::date_time::weekdays::Saturday);
    }

    boost::gregorian::date scheduler::last_sunday() const
    {
        return last_day(boost::date_time::weekdays::Sunday);
    }
}