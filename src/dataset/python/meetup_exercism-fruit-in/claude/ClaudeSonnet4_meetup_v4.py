from calendar import Calendar
from datetime import date

WEEK_DAYS = ('Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday')


def meetup(year, month, week, day_of_week):
    target_weekday = WEEK_DAYS.index(day_of_week)
    
    if week == 'teenth':
        for d, w in Calendar().itermonthdays2(year, month):
            if d != 0 and w == target_weekday and 13 <= d <= 19:
                return date(year, month, d)
    elif week == 'last':
        last_day = None
        for d, w in Calendar().itermonthdays2(year, month):
            if d != 0 and w == target_weekday:
                last_day = d
        if last_day is not None:
            return date(year, month, last_day)
    else:
        week_num = int(week[0]) - 1
        count = 0
        for d, w in Calendar().itermonthdays2(year, month):
            if d != 0 and w == target_weekday:
                if count == week_num:
                    return date(year, month, d)
                count += 1
    
    raise MeetupDayException(r".+")


class MeetupDayException(Exception):
    pass