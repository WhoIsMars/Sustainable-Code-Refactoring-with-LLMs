def flatten(iterable):
    ret = []
    stack = [iter(iterable)]
    
    while stack:
        try:
            x = next(stack[-1])
            if isinstance(x, list):
                stack.append(iter(x))
            elif x is not None:
                ret.append(x)
        except StopIteration:
            stack.pop()
    
    return ret