from calendar import monthcalendar
from datetime import date

WEEK_DAYS = ['Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday']


def meetup(year, month, week, day_of_week):
    day_index = WEEK_DAYS.index(day_of_week)
    month_days = monthcalendar(year, month)

    if week == 'teenth':
        day = next(week[day_index] for week in month_days if 13 <= week[day_index] <= 19)
    elif week == 'last':
        day = next(week[day_index] for week in reversed(month_days) if week[day_index] != 0)
    else:
        week_number = int(week[0]) - 1
        try:
            day = month_days[week_number][day_index]
            if day == 0:
                raise IndexError
        except IndexError:
            raise MeetupDayException(r".+")

    return date(year, month, day)


class MeetupDayException(Exception):
    pass