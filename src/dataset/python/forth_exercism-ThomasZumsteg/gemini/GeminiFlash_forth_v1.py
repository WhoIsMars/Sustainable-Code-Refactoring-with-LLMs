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
    'drop': (1, lambda x: tuple()),
}


def evaluate(input_data):
    stack = []
    env = {}
    tokens = []
    for line in input_data:
        tokens.extend(line.split())

    token_idx = 0
    while token_idx < len(tokens):
        token = tokens[token_idx].lower()
        token_idx += 1

        if token == ':':
            keyword = tokens[token_idx].lower()
            token_idx += 1
            if keyword.isdigit():
                raise ValueError("Variables cannot be numbers: " + keyword)
            
            definition = []
            while token_idx < len(tokens) and tokens[token_idx] != ';':
                definition.append(tokens[token_idx])
                token_idx += 1
            
            if token_idx == len(tokens):
                raise ValueError("Missing semicolon")
            
            token_idx += 1  # Skip the semicolon
            env[keyword] = definition
        elif token in env:
            tokens = env[token] + tokens[token_idx:]
            token_idx = 0
        elif token in keywords:
            n_args, func = keywords[token]
            if len(stack) < n_args:
                raise StackUnderflowError('Cannot apply ' + token)
            args = stack[-n_args:]
            del stack[-n_args:]
            stack.extend(func(*args))
        else:
            try:
                stack.append(int(token))
            except ValueError:
                raise ValueError(f"Invalid token: {token}")
    return stack