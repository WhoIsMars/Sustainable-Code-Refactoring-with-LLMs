from calendar import Calendar
from datetime import date

def meetup(year, month, week, day_of_week):
    # Convert day_of_week string to weekday index once
    try:
        target_weekday = ['Monday', 'Tuesday', 'Wednesday',
                         'Thursday', 'Friday', 'Saturday', 'Sunday'].index(day_of_week)
    except ValueError:
        raise MeetupDayException(r".+")
    
    # Generate only the days we need based on week type
    if week == 'teenth':
        # Only check days 13-19
        for day_num in range(13, 20):
            try:
                if date(year, month, day_num).weekday() == target_weekday:
                    return date(year, month, day_num)
            except ValueError:
                continue
        raise MeetupDayException(r".+")
    
    # For other cases, collect matching days efficiently
    matching_days = []
    for day_num, weekday in Calendar().itermonthdays2(year, month):
        if day_num != 0 and weekday == target_weekday:
            if week == 'last':
                # For 'last', we only need to keep track of the most recent
                matching_days = [day_num]
            else:
                matching_days.append(day_num)
                # For numbered weeks, we can stop early if we have enough
                week_num = int(week[0])
                if len(matching_days) == week_num:
                    return date(year, month, matching_days[-1])
    
    if week == 'last' and matching_days:
        return date(year, month, matching_days[0])
    
    raise MeetupDayException(r".+")


class MeetupDayException(Exception):
    pass