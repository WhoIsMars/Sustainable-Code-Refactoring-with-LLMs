from datetime import timedelta

# Pre-compute the timedelta constant to avoid repeated object creation
_ONE_BILLION_SECONDS = timedelta(seconds=1_000_000_000)

def add(moment):
    return moment + _ONE_BILLION_SECONDS