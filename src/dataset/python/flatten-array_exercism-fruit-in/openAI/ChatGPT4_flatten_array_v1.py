def flatten(iterable):
    for x in iterable:
        if isinstance(x, list):
            yield from flatten(x)
        elif x is not None:
            yield x