from calendar import Calendar
from datetime import date

def meetup(year, month, week, day_of_week):
    target_weekday = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday'].index(day_of_week)
    
    if week == 'teenth':
        for day_num, weekday in Calendar().itermonthdays2(year, month):
            if day_num != 0 and weekday == target_weekday and 13 <= day_num <= 19:
                return date(year, month, day_num)
    elif week == 'last':
        last_day = None
        for day_num, weekday in Calendar().itermonthdays2(year, month):
            if day_num != 0 and weekday == target_weekday:
                last_day = day_num
        if last_day is not None:
            return date(year, month, last_day)
    else:
        occurrence = int(week[0])
        count = 0
        for day_num, weekday in Calendar().itermonthdays2(year, month):
            if day_num != 0 and weekday == target_weekday:
                count += 1
                if count == occurrence:
                    return date(year, month, day_num)
        raise MeetupDayException(r".+")

class MeetupDayException(Exception):
    pass