import datetime

def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition
    Current conditions [1-4]th occurrence, last, teenth
    """
    weekday_num = WEEKDAY_TO_NUM[weekday]
    condition_func = CONDITIONS[condition]

    # Start with the first weekday of the month
    day = datetime.date(year, month, 1)
    offset = (weekday_num - day.weekday()) % 7
    day += datetime.timedelta(days=offset)

    # Iterate only over valid weekdays in the month
    while day.month == month:
        if condition_func(day):
            return day
        day += datetime.timedelta(days=7)

    raise AssertionError("Not a valid meetup day")

# Conversion of string weekday to number
WEEKDAY_TO_NUM = {'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 'Thursday': 3,
                  'Friday': 4, 'Saturday': 5, 'Sunday': 6}

def last(day):
    """True on the last week of the month"""
    return (day + datetime.timedelta(days=7)).month != day.month

def nth(n):
    """Returns a function that is true on the nth week of a month"""
    return lambda day: (day.day - 1) // 7 == n - 1

def teenth(day):
    """True on days ending in -teenth, i.e., 13th to 19th"""
    return 13 <= day.day <= 19

# Maps condition to function test
CONDITIONS = {'teenth': teenth,
              'last': last,
              '1st': nth(1),
              '2nd': nth(2),
              '3rd': nth(3),
              '4th': nth(4),
              '5th': nth(5)}