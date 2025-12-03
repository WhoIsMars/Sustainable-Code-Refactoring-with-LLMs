from calendar import Calendar
from datetime import date

WEEK_DAYS = ['Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday', ]


def meetup(year, month, week, day_of_week):
    calendar = Calendar()
    days = []
    for day_number, weekday in calendar.itermonthdays2(year, month):
        if day_number != 0 and WEEK_DAYS[weekday] == day_of_week:
            days.append(day_number)

    if week == 'teenth':
        for day in days:
            if 13 <= day <= 19:
                return date(year, month, day)
        raise MeetupDayException(r".+")  # Should not happen given the problem constraints, but good to have.
    elif week == 'last':
        return date(year, month, days[-1])
    else:
        try:
            index = int(week[0]) - 1
            return date(year, month, days[index])
        except IndexError:
            raise MeetupDayException(r".+")


class MeetupDayException(Exception):
    pass