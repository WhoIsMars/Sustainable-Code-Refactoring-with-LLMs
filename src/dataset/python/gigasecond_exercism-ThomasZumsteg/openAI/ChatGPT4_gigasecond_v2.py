"""Adds a gigasecond to a given date"""

from datetime import timedelta

__GIGASECOND = timedelta(seconds=1_000_000_000)

def add_gigasecond(now):
    """Adds a gigasecond to a given date"""
    return now + __GIGASECOND