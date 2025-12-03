"""Returns a datetime date object for a given year, month, and weekday that meet
a predefined natrual language description. e.g. 1st, 2nd, last, teenth
"""

import datetime
import calendar

WEEKDAY_TO_NUM = {
    'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 'Thursday': 3,
    'Friday': 4, 'Saturday': 5, 'Sunday': 6
}

def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition
    Current conditions [1-4]th occurence, last, teenth
    """
    target_weekday = WEEKDAY_TO_NUM[weekday]
    
    if condition == 'teenth':
        for day in range(13, 20):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == target_weekday:
                return date_obj
    
    elif condition == 'last':
        last_day = calendar.monthrange(year, month)[1]
        for day in range(last_day, last_day - 7, -1):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == target_weekday:
                return date_obj
    
    else:
        occurrence = int(condition[0])
        first_day = datetime.date(year, month, 1)
        first_target_weekday = first_day.weekday()
        
        days_to_add = (target_weekday - first_target_weekday) % 7
        target_day = 1 + days_to_add + (occurrence - 1) * 7
        
        if target_day <= calendar.monthrange(year, month)[1]:
            return datetime.date(year, month, target_day)
    
    raise AssertionError("Not a valid meetup day")

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

CONDITIONS = {
    'teenth': teenth,
    'last': last,
    '1st': nth(1),
    '2nd': nth(2),
    '3rd': nth(3),
    '4th': nth(4),
    '5th': nth(5),
}