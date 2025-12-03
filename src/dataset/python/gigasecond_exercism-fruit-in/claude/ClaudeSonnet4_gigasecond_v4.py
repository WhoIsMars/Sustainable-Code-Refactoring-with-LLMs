from datetime import timedelta

_CACHED_DELTA = timedelta(seconds=1_000_000_000)

def add(moment):
    return moment + _CACHED_DELTA