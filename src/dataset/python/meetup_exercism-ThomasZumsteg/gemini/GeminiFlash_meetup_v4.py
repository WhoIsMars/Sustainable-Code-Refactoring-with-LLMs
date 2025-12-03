"""Returns a datetime date object for a given year, month, and weekday that meet
a predefined natrual language description. e.g. 1st, 2nd, last, teenth
"""

import datetime

def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition
    Current conditions [1-4]th occurence, last, teenth
    """
    weekday_num = WEEKDAY_TO_NUM[weekday]
    if condition == 'teenth':
        for day_num in range(13, 20):
            day = datetime.date(year, month, day_num)
            if day.weekday() == weekday_num:
                return day
    elif condition == 'last':
        last_day_of_month = (datetime.date(year, month + 1, 1) - datetime.timedelta(days=1)).day if month < 12 else (datetime.date(year + 1, 1, 1) - datetime.timedelta(days=1)).day
        for day_num in range(last_day_of_month, last_day_of_month - 7, -1):
            day = datetime.date(year, month, day_num)
            if day.weekday() == weekday_num:
                return day
    else:
        n = int(condition[0])
        first_day = datetime.date(year, month, 1)
        first_occurrence_day = (weekday_num - first_day.weekday()) % 7
        day_num = 1 + first_occurrence_day + (n - 1) * 7
        if day_num <= datetime.date(year, month, 1).max.day:
            day = datetime.date(year, month, day_num)
            return day

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