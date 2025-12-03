def flatten(iterable):
    def _flatten_gen(iterable):
        for x in iterable:
            if isinstance(x, list):
                yield from _flatten_gen(x)
            elif x is not None:
                yield x

    return list(_flatten_gen(iterable))