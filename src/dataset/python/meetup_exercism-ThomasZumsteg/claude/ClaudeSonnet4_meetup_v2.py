"""Returns a datetime date object for a given year, month, and weekday that meet
a predefined natrual language description. e.g. 1st, 2nd, last, teenth
"""

import datetime
import calendar

# Conversion of string weekday to number
WEEKDAY_TO_NUM = {'Monday'   : 0,
                  'Tuesday'  : 1,
                  'Wednesday': 2,
                  'Thursday' : 3,
                  'Friday'   : 4,
                  'Saturday' : 5,
                  'Sunday'   : 6,
                 }

def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition
    Current conditions [1-4]th occurence, last, teenth
    """
    target_weekday = WEEKDAY_TO_NUM[weekday]
    
    if condition == 'teenth':
        # Check only days 13-19
        for day in range(13, 20):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == target_weekday:
                return date_obj
    
    elif condition == 'last':
        # Start from the last day of the month and work backwards
        last_day = calendar.monthrange(year, month)[1]
        for day in range(last_day, 0, -1):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == target_weekday:
                return date_obj
    
    else:
        # Handle nth occurrences (1st, 2nd, 3rd, 4th, 5th)
        nth = int(condition[0])
        count = 0
        last_day = calendar.monthrange(year, month)[1]
        
        for day in range(1, last_day + 1):
            date_obj = datetime.date(year, month, day)
            if date_obj.weekday() == target_weekday:
                count += 1
                if count == nth:
                    return date_obj
    
    raise AssertionError("Not a valid meetup day")