import datetime

def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition"""
    weekday_num = WEEKDAY_TO_NUM[weekday]
    condition_func = CONDITIONS[condition]
    first_day = datetime.date(year, month, 1)
    days_to_add = (weekday_num - first_day.weekday()) % 7
    day = first_day + datetime.timedelta(days=days_to_add)
    
    while day.month == month:
        if condition_func(day):
            return day
        day += datetime.timedelta(weeks=1)
    
    raise AssertionError("Not a valid meetup day")

WEEKDAY_TO_NUM = {'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 'Thursday': 3,
                  'Friday': 4, 'Saturday': 5, 'Sunday': 6}

def last(day):
    return day.month != (day + datetime.timedelta(days=7)).month

def nth(n):
    return lambda day: (day.day - 1) // 7 == n - 1

def teenth(day):
    return 13 <= day.day <= 19

CONDITIONS = {'teenth': teenth, 'last': last, '1st': nth(1), '2nd': nth(2),
              '3rd': nth(3), '4th': nth(4), '5th': nth(5)}