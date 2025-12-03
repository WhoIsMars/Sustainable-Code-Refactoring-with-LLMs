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
        # The teenth days are always between the 13th and 19th.
        # Find the first day of the week in that range.
        for day_num in range(13, 20):
            day = datetime.date(year, month, day_num)
            if day.weekday() == weekday_num:
                return day
    elif condition == 'last':
        # Start from the end of the month and work backwards.
        last_day_of_month = datetime.date(year, month + 1, 1) - datetime.timedelta(days=1) if month < 12 else datetime.date(year + 1, 1, 1) - datetime.timedelta(days=1)
        for day_num in range(last_day_of_month.day, 0, -1):
            day = datetime.date(year, month, day_num)
            if day.weekday() == weekday_num:
                return day
    else:
        # Handle 1st, 2nd, 3rd, 4th, 5th
        n = int(condition[0])
        # Calculate the first possible day of the month that matches the weekday.
        first_day = 1
        first_day_date = datetime.date(year, month, first_day)
        day_difference = (weekday_num - first_day_date.weekday()) % 7
        first_occurrence = first_day + day_difference

        # Calculate the date of the nth occurrence.
        nth_occurrence = first_occurrence + (n - 1) * 7
        day = datetime.date(year, month, nth_occurrence)
        if day.month == month:
            return day

    raise AssertionError("Not a valid meetup day")


def nth(n):
    """Returns a function that is true on the nth week of a month"""

    def nth_worker(day):
        """True on the nth week of the month"""
        return (day.day - 1) // 7 == n - 1

    return nth_worker


def teenth(day):
    """True on a days ending in -teenth, ie seventeenth"""
    return 13 <= day.day <= 19


def last(day):
    """True on the last week of the month"""
    return day.month != (day + datetime.timedelta(days=7)).month


# Maps condition to function test
CONDITIONS = {'teenth': teenth,
              'last': last,
              '1st': nth(1),
              '2nd': nth(2),
              '3rd': nth(3),
              '4th': nth(4),
              '5th': nth(5),
              }