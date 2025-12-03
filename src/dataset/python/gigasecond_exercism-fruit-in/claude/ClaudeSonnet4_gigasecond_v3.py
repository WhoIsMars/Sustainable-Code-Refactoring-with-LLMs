from datetime import timedelta

_ONE_BILLION_SECONDS = timedelta(seconds=1_000_000_000)

def add(moment):
    return moment + _ONE_BILLION_SECONDS