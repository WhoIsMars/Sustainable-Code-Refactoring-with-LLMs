#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>


namespace meetup {

    using namespace boost::gregorian;

    class scheduler {

        public:
        scheduler(months_of_year month, int year);
    
        date monteenth() const;
        date tuesteenth() const;
        date wednesteenth() const;
        date thursteenth() const;
        date friteenth() const;
        date saturteenth() const;
        date sunteenth() const;

        date first_monday() const { return first_day_of_the_week_in_month(Monday, _month).get_date(_year); }
        date first_tuesday() const { return first_day_of_the_week_in_month(Tuesday, _month).get_date(_year); }
        date first_wednesday() const { return first_day_of_the_week_in_month(Wednesday, _month).get_date(_year); }
        date first_thursday() const { return first_day_of_the_week_in_month(Thursday, _month).get_date(_year); }
        date first_friday() const { return first_day_of_the_week_in_month(Friday, _month).get_date(_year); }
        date first_saturday() const { return first_day_of_the_week_in_month(Saturday, _month).get_date(_year); }
        date first_sunday() const { return first_day_of_the_week_in_month(Sunday, _month).get_date(_year); }

        date second_monday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Monday, _month).get_date(_year); }
        date second_tuesday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Tuesday, _month).get_date(_year); }
        date second_wednesday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Wednesday, _month).get_date(_year); }
        date second_thursday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Thursday, _month).get_date(_year); }
        date second_friday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Friday, _month).get_date(_year); }
        date second_saturday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Saturday, _month).get_date(_year); }
        date second_sunday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::second, Sunday, _month).get_date(_year); }
        
        date third_monday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Monday, _month).get_date(_year); }
        date third_tuesday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Tuesday, _month).get_date(_year); }
        date third_wednesday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Wednesday, _month).get_date(_year); }
        date third_thursday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Thursday, _month).get_date(_year); }
        date third_friday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Friday, _month).get_date(_year); }
        date third_saturday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Saturday, _month).get_date(_year); }
        date third_sunday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::third, Sunday, _month).get_date(_year); }

        date fourth_monday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Monday, _month).get_date(_year); }
        date fourth_tuesday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Tuesday, _month).get_date(_year); }
        date fourth_wednesday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Wednesday, _month).get_date(_year); }
        date fourth_thursday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Thursday, _month).get_date(_year); }
        date fourth_friday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Friday, _month).get_date(_year); }
        date fourth_saturday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Saturday, _month).get_date(_year); }
        date fourth_sunday() const { return nth_day_of_the_week_in_month(nth_day_of_the_week_in_month::fourth, Sunday, _month).get_date(_year); }

        date last_monday() const { return last_day_of_the_week_in_month(Monday, _month).get_date(_year); }
        date last_tuesday() const { return last_day_of_the_week_in_month(Tuesday, _month).get_date(_year); }
        date last_wednesday() const { return last_day_of_the_week_in_month(Wednesday, _month).get_date(_year); }
        date last_thursday() const { return last_day_of_the_week_in_month(Thursday, _month).get_date(_year); }
        date last_friday() const { return last_day_of_the_week_in_month(Friday, _month).get_date(_year); }
        date last_saturday() const { return last_day_of_the_week_in_month(Saturday, _month).get_date(_year); }
        date last_sunday() const { return last_day_of_the_week_in_month(Sunday, _month).get_date(_year); }
    
        private:
        months_of_year _month;
        int _year;
        date_period teenths;

    };
    
}  // namespace meetup

#endif  // MEETUP_H