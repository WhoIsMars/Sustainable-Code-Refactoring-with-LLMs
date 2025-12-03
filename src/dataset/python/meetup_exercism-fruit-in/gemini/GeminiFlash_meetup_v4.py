from calendar import Calendar
from datetime import date

WEEK_DAYS = ['Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday', ]


def meetup(year, month, week, day_of_week):
    calendar = Calendar()
    days = []
    for day, weekday in calendar.itermonthdays2(year, month):
        if day != 0 and WEEK_DAYS[weekday] == day_of_week:
            days.append(day)

    if week == 'teenth':
        day = next((d for d in days if 13 <= d <= 19), None)
        if day is None:
            raise MeetupDayException(r".+")
    elif week == 'last':
        if not days:
            raise MeetupDayException(r".+")
        day = days[-1]
    else:
        try:
            day = days[int(week[0]) - 1]
        except IndexError:
            raise MeetupDayException(r".+")

    return date(year, month, day)


class MeetupDayException(Exception):
    pass