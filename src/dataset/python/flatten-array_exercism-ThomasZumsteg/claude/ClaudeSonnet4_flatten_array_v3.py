def flatten(iterable):
    if isinstance(iterable, str):
        return list(iterable)
    
    flat = []
    stack = [iterable]
    
    while stack:
        current = stack.pop()
        if isinstance(current, str):
            flat.extend(current)
        elif hasattr(current, '__iter__'):
            try:
                stack.extend(reversed(current))
            except TypeError:
                if current is not None:
                    flat.append(current)
        elif current is not None:
            flat.append(current)
    
    return flat