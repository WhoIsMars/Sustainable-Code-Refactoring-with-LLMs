from calendar import Calendar
from datetime import date

def meetup(year, month, week, day_of_week):
    # Convert day_of_week string to weekday number once
    day_num = {'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 
               'Thursday': 3, 'Friday': 4, 'Saturday': 5, 'Sunday': 6}[day_of_week]
    
    if week == 'teenth':
        # Direct iteration for teenth case - stop when found
        for d, w in Calendar().itermonthdays2(year, month):
            if d != 0 and w == day_num and 13 <= d <= 19:
                return date(year, month, d)
    elif week == 'last':
        # Iterate backwards to find last occurrence
        last_day = None
        for d, w in Calendar().itermonthdays2(year, month):
            if d != 0 and w == day_num:
                last_day = d
        if last_day:
            return date(year, month, last_day)
    else:
        # For numbered weeks, count occurrences
        week_num = int(week[0]) - 1
        count = 0
        for d, w in Calendar().itermonthdays2(year, month):
            if d != 0 and w == day_num:
                if count == week_num:
                    return date(year, month, d)
                count += 1
        raise MeetupDayException(r".+")

class MeetupDayException(Exception):
    pass