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
        week_num = int(week[0]) - 1
        if week_num >= len(month_days) or month_days[week_num][day_index] == 0:
            raise MeetupDayException(r".+")
        day = month_days[week_num][day_index]

    return date(year, month, day)


class MeetupDayException(Exception):
    pass