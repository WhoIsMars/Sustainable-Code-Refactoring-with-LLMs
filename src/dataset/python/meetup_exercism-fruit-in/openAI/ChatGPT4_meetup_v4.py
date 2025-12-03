from calendar import monthcalendar
from datetime import date

WEEK_DAYS = ['Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday']


def meetup(year, month, week, day_of_week):
    day_index = WEEK_DAYS.index(day_of_week)
    weeks = monthcalendar(year, month)
    days = [week[day_index] for week in weeks if week[day_index] != 0]

    if week == 'teenth':
        day = next(d for d in days if 13 <= d <= 19)
    elif week == 'last':
        day = days[-1]
    else:
        try:
            day = days[int(week[0]) - 1]
        except IndexError:
            raise MeetupDayException(r".+")

    return date(year, month, day)


class MeetupDayException(Exception):
    pass