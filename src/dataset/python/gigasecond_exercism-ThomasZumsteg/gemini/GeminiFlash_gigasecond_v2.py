"""Adds a gigaseconds to a give date"""

from datetime import timedelta

def add_gigasecond(now):
    """Adds a gigaseconds to a given date"""
    gigasecond = 10**9
    return now + timedelta(seconds=gigasecond)