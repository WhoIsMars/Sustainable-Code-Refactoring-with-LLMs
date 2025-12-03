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
    tokens = []
    for line in input_data:
        tokens.extend(line.split())
    
    stack = []
    env = {}
    i = 0
    
    while i < len(tokens):
        token = tokens[i].lower()
        i += 1
        
        if token == ':':
            keyword = tokens[i].lower()
            i += 1
            if keyword.isdigit():
                raise ValueError("Variables cannot be numbers: " + keyword)
            
            definition = []
            while tokens[i] != ';':
                definition.append(tokens[i])
                i += 1
            i += 1  # skip ';'
            env[keyword] = definition
            
        elif token in env:
            tokens[i:i] = env[token]
            
        elif token in keywords:
            n_args, func = keywords[token]
            if len(stack) < n_args:
                raise StackUnderflowError('Cannot apply ' + token)
            
            if n_args == 1:
                result = func(stack.pop())
            else:  # n_args == 2
                b = stack.pop()
                a = stack.pop()
                result = func(a, b)
            
            stack.extend(result)
            
        else:
            stack.append(int(token))
            
    return stack