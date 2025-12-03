from datetime import timedelta

__GIGASECOND = timedelta(seconds=10**9)

def add_gigasecond(now):
    """Adds a gigaseconds to a given date"""
    return now + __GIGASECOND