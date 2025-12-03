from datetime import timedelta


__one_billion_seconds = timedelta(seconds=1_000_000_000)


def add(moment):
    return moment + __one_billion_seconds