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
    first_day_of_month = datetime.date(year, month, 1)
    first_occurrence = (weekday_num - first_day_of_month.weekday()) % 7
    first_date = first_day_of_month + datetime.timedelta(days=first_occurrence)

    if condition == 'teenth':
        teenth_start = datetime.date(year, month, 13)
        teenth_occurrence = (weekday_num - teenth_start.weekday()) % 7
        result = teenth_start + datetime.timedelta(days=teenth_occurrence)
        if 13 <= result.day <= 19:
            return result
        else:
            teenth_start = datetime.date(year, month, 13 + 7)
            teenth_occurrence = (weekday_num - teenth_start.weekday()) % 7
            result = teenth_start + datetime.timedelta(days=teenth_occurrence)
            if 13 <= result.day <= 19:
                return result
            else:
                raise AssertionError("Not a valid meetup day")

    elif condition == 'last':
        last_day_of_month = datetime.date(year, month + 1, 1) - datetime.timedelta(days=1) if month < 12 else datetime.date(year + 1, 1, 1) - datetime.timedelta(days=1)
        last_occurrence = (weekday_num - last_day_of_month.weekday()) % 7
        result = last_day_of_month - datetime.timedelta(days=last_occurrence)
        if result.month == month:
            return result
        else:
            raise AssertionError("Not a valid meetup day")

    else:
        n = int(condition[0])
        candidate_date = first_date + datetime.timedelta(weeks=(n - 1))
        if candidate_date.month == month:
            return candidate_date
        else:
            raise AssertionError("Not a valid meetup day")


def last(day):
    """True on the last week of the month"""
    return day.month != (day + datetime.timedelta(days=7)).month


def nth(n):
    """Returns a function that is true on the nth week of a month"""

    def nth_worker(day):
        """True on the nth week of the month"""
        return (day.day - 1) // 7 == n - 1

    return nth_worker


def teenth(day):
    """True on a days ending in -teenth, ie seventeenth"""
    return 13 <= day.day and day.day <= 19


# Maps condition to function test
CONDITIONS = {'teenth': teenth,
              'last': last,
              '1st': nth(1),
              '2nd': nth(2),
              '3rd': nth(3),
              '4th': nth(4),
              '5th': nth(5),
              }