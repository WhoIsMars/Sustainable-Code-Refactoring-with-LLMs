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
    'drop': (1, lambda x: ())
}


def evaluate(input_data):
    stack = []
    env = {}
    for line in input_data:
        tokens = line.split()
        i = 0
        while i < len(tokens):
            token = tokens[i].lower()
            if token == ':':
                i += 1
                keyword = tokens[i].lower()
                if keyword.isdigit():
                    raise ValueError("Variables cannot be numbers: " + keyword)
                i += 1
                definition = []
                while i < len(tokens) and tokens[i] != ';':
                    definition.append(tokens[i])
                    i += 1
                if i == len(tokens):
                    raise ValueError("Missing semicolon")
                env[keyword] = definition
            elif token in env:
                tokens = env[token] + tokens[i+1:]
                i = 0
            elif token in keywords:
                n_args, func = keywords[token]
                if len(stack) < n_args:
                    raise StackUnderflowError('Cannot apply ' + token)
                args = stack[-n_args:]
                del stack[-n_args:]
                stack.extend(func(*args))
                i += 1
            else:
                try:
                    stack.append(int(token))
                except ValueError:
                    raise ValueError("Invalid token: " + token)
                i += 1
    return stack