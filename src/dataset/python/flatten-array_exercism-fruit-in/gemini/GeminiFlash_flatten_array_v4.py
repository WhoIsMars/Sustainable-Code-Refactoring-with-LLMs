def flatten(iterable):
    ret = []
    for x in iterable:
        if isinstance(x, list):
            ret.extend(flatten(x))
        elif x is not None:
            ret.append(x)
    return ret