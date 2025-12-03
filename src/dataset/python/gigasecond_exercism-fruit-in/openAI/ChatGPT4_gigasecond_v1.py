from datetime import timedelta


__ONE_BILLION_SECONDS = timedelta(seconds=1_000_000_000)

def add(moment):
    return moment + __ONE_BILLION_SECONDS