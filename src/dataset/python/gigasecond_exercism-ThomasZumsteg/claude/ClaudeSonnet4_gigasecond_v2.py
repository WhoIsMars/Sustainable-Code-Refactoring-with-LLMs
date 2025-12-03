"""Adds a gigaseconds to a give date"""

from datetime import timedelta

# Pre-calculate the gigasecond timedelta to avoid repeated computation
_GIGASECOND = timedelta(seconds=1000000000)

def add_gigasecond(now):
    """Adds a gigaseconds to a given date"""
    return now + _GIGASECOND