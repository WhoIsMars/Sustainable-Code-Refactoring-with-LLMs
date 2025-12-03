"""Adds a gigasecond to a given date"""

from datetime import timedelta

_GIGASECOND_DELTA = timedelta(seconds=1000000000)

def add_gigasecond(now):
    """Adds a gigasecond to a given date"""
    return now + _GIGASECOND_DELTA