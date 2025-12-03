from collections.abc import Iterable

def flatten(iterable):
    if isinstance(iterable, str):
        return list(iterable)
    flat = []
    for item in iterable:
        if isinstance(item, Iterable) and not isinstance(item, (str, bytes)):
            flat.extend(flatten(item))
        elif item is not None:
            flat.append(item)
    return flat