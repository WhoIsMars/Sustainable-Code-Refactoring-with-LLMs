from datetime import date
from calendar import monthrange

WEEK_DAYS = ['Monday', 'Tuesday', 'Wednesday',
             'Thursday', 'Friday', 'Saturday', 'Sunday']


def meetup(year, month, week, day_of_week):
    """Find the date of the meetup that happens on the given year, month, week, and day of the week."""

    first_day, num_days = monthrange(year, month)
    day_index = WEEK_DAYS.index(day_of_week)

    if week == 'teenth':
        for day in range(13, 20):
            date_obj = date(year, month, day)
            if date_obj.weekday() == day_index:
                return date_obj
        raise MeetupDayException("No matching teenth day found.")

    elif week == 'last':
        for day in range(num_days, num_days - 7, -1):
            if day < 1:
                continue
            date_obj = date(year, month, day)
            if date_obj.weekday() == day_index:
                return date_obj
        raise MeetupDayException("No matching last day found.")

    else:
        week_num = int(week[0])
        count = 0
        for day in range(1, 8):
            date_obj = date(year, month, day)
            if date_obj.weekday() == day_index:
                count += 1
                if count == week_num:
                    return date_obj
        raise MeetupDayException("No matching day found.")


class MeetupDayException(Exception):
    pass