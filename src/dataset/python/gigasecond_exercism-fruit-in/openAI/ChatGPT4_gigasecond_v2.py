from datetime import timedelta


__gigasecond = timedelta(seconds=1_000_000_000)

def add(moment):
    return moment + __gigasecond