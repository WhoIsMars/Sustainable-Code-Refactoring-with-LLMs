from datetime import timedelta


def add(moment):
    seconds_in_a_billion = 1_000_000_000
    days = seconds_in_a_billion // (24 * 3600)
    remaining_seconds = seconds_in_a_billion % (24 * 3600)
    return moment + timedelta(days=days, seconds=remaining_seconds)