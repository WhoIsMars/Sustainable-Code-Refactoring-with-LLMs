def flatten(iterable):
    if isinstance(iterable, str):
        return list(iterable)
    
    flat = []
    stack = [iterable]
    
    while stack:
        current = stack.pop()
        if isinstance(current, str):
            flat.extend(current)
        else:
            try:
                iterator = iter(current)
                for item in iterator:
                    if hasattr(item, '__iter__') and not isinstance(item, str):
                        stack.append(item)
                    elif item is not None:
                        flat.append(item)
            except TypeError:
                if current is not None:
                    flat.append(current)
    
    return flat