from collections.abc import Iterable

def flatten(iterable):
    if isinstance(iterable, str):
        return list(iterable)
    flat = []
    for item in iterable:
        if isinstance(item, Iterable):
            if not isinstance(item, (str, bytes, bytearray)):
                flat.extend(flatten(item))
            else:
                flat.append(item)
        else:
            if item is not None:
                flat.append(item)
    return flat