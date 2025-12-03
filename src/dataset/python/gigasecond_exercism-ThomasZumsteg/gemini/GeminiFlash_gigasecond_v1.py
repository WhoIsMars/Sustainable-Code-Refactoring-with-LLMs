"""Adds a gigaseconds to a give date"""

from datetime import timedelta

GIGASECOND = 10**9

def add_gigasecond(now):
    """Adds a gigaseconds to a given date"""
    return now + timedelta(seconds=GIGASECOND)