from collections.abc import Iterable

def flatten(iterable):
    ret = []
    for x in iterable:
        if isinstance(x, Iterable) and not isinstance(x, (str, bytes)):
            ret.extend(flatten(x))
        elif x is not None:
            ret.append(x)
    return ret