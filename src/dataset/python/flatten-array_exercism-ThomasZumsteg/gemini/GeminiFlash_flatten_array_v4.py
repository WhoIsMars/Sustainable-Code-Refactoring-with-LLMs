def flatten(iterable):
    if isinstance(iterable, str):
        return list(iterable)
    flat = []
    for item in iterable:
        if isinstance(item, (list, tuple)):
            flat.extend(flatten(item))
        else:
            if item is not None:
                flat.append(item)
    return flat