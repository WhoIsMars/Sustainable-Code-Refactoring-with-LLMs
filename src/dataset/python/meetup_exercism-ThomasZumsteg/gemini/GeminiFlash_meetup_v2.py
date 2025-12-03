"""Returns a datetime date object for a given year, month, and weekday that meet
a predefined natrual language description. e.g. 1st, 2nd, last, teenth
"""

import datetime

# Conversion of string weekday to number
WEEKDAY_TO_NUM = {'Monday': 0,
                  'Tuesday': 1,
                  'Wednesday': 2,
                  'Thursday': 3,
                  'Friday': 4,
                  'Saturday': 5,
                  'Sunday': 6,
                  }


def meetup_day(year, month, weekday, condition):
    """Returns date object for a given year, month, weekday and given condition
    Current conditions [1-4]th occurence, last, teenth
    """
    weekday_num = WEEKDAY_TO_NUM[weekday]

    if condition == 'teenth':
        # The teenth dates are always between the 13th and 19th.
        first_teenth = datetime.date(year, month, 13)
        day_diff = (weekday_num - first_teenth.weekday()) % 7
        meetup_date = first_teenth + datetime.timedelta(days=day_diff)
        return meetup_date

    if condition == 'last':
        # Start from the end of the month and work backwards.
        last_day_of_month = datetime.date(year, month + 1, 1) - datetime.timedelta(days=1) if month < 12 else datetime.date(year + 1, 1, 1) - datetime.timedelta(days=1)
        day_diff = (last_day_of_month.weekday() - weekday_num) % 7
        meetup_date = last_day_of_month - datetime.timedelta(days=day_diff)
        return meetup_date

    # For 1st, 2nd, 3rd, 4th, 5th
    n = int(condition[0])  # Extract the number from the condition string
    first_of_month = datetime.date(year, month, 1)
    day_diff = (weekday_num - first_of_month.weekday()) % 7
    meetup_date = first_of_month + datetime.timedelta(days=(n - 1) * 7 + day_diff)

    if meetup_date.month != month:
        raise AssertionError("Not a valid meetup day")

    return meetup_date