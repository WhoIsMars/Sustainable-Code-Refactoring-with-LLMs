class StackUnderflowError(Exception):
    pass


keywords = {
    '+': (2, lambda a, b: (a + b,)),
    '-': (2, lambda a, b: (a - b,)),
    '*': (2, lambda a, b: (a * b,)),
    '/': (2, lambda a, b: (a // b,)),
    'swap': (2, lambda a, b: (b, a)),
    'over': (2, lambda a, b: (a, b, a)),
    'dup': (1, lambda x: (x, x)),
    'drop': (1, lambda x: ()),
}


def evaluate(input_data):
    tokens = (token for line in input_data for token in line.split())
    stack = []
    env = {}
    for token in tokens:
        token = token.lower()
        if token == ':':
            keyword = next(tokens).lower()
            if keyword.isdigit():
                raise ValueError("Variables cannot be numbers: " + keyword)
            env[keyword] = []
            for token in tokens:
                if token == ';':
                    break
                env[keyword].append(token.lower())
        elif token in env:
            tokens = iter(env[token] + list(tokens))
        elif token in keywords:
            n_args, func = keywords[token]
            if len(stack) < n_args:
                raise StackUnderflowError('Cannot apply ' + token)
            args = stack[-n_args:]
            stack[-n_args:] = func(*args)
        else:
            stack.append(int(token))
    return stack