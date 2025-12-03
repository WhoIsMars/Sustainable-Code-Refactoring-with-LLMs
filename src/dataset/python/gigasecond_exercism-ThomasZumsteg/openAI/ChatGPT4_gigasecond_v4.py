from datetime import timedelta

__GIGASECOND = timedelta(seconds=10**9)

def add_gigasecond(now):
    return now + __GIGASECOND