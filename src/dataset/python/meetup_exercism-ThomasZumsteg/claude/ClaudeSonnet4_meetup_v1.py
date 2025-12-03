"""Returns a datetime date object for a given year, month, and weekday that meet
a predefined natrual language description. e.g. 1st, 2nd, last, teenth
"""

import datetime
import calendar

def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition
    Current conditions [1-4]th occurence, last, teenth
    """
    weekday_num = WEEKDAY_TO_NUM[weekday]
    
    if condition == 'teenth':
        # Direct calculation for teenth (13-19)
        for day in range(13, 20):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == weekday_num:
                return date_obj
    
    elif condition == 'last':
        # Start from last day of month and work backwards
        last_day = calendar.monthrange(year, month)[1]
        for day in range(last_day, 0, -1):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == weekday_num:
                return date_obj
    
    else:
        # For nth occurrences (1st-5th)
        nth_value = NTH_MAP[condition]
        count = 0
        for day in range(1, 32):
            try:
                date_obj = datetime.date(year, month, day)
            except ValueError:
                break
            if date_obj.weekday() == weekday_num:
                count += 1
                if count == nth_value:
                    return date_obj
    
    raise AssertionError("Not a valid meetup day")

# Conversion of string weekday to number
WEEKDAY_TO_NUM = {'Monday'   : 0,
                  'Tuesday'  : 1,
                  'Wednesday': 2,
                  'Thursday' : 3,
                  'Friday'   : 4,
                  'Saturday' : 5,
                  'Sunday'   : 6,
                 }

# Direct mapping for nth conditions
NTH_MAP = {'1st': 1, '2nd': 2, '3rd': 3, '4th': 4, '5th': 5}

def last(day):
    """True on the last week of the month"""
    return day.month != (day + datetime.timedelta(days=7)).month

def nth(n):
    """Returns a function that is true on the nth week of a month"""
    def nth_worker(day):
        """True on the nth week of the month"""
        return (day.day - 1) // 7 == n-1
    return nth_worker

def teenth(day):
    """True on a days ending in -teenth, ie seventeenth"""
    return 13 <= day.day <= 19

# Maps condition to function test
CONDITIONS = {'teenth': teenth,
              'last': last,
              '1st': nth(1),
              '2nd': nth(2),
              '3rd': nth(3),
              '4th': nth(4),
              '5th': nth(5),
             }