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
        day = next(day for day in days if 13 <= day <= 19)
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