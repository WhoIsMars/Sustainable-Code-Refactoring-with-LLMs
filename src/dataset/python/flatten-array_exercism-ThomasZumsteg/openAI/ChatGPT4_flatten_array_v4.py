from collections.abc import Iterable

def flatten(iterable):
    if isinstance(iterable, str):
        return list(iterable)
    flat = []
    stack = [iterable]
    while stack:
        current = stack.pop()
        if isinstance(current, Iterable) and not isinstance(current, (str, bytes)):
            stack.extend(reversed(current))
        elif current is not None:
            flat.append(current)
    return flat