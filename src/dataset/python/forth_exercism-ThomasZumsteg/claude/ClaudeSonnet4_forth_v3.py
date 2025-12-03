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
        
        if token == ':':
            i += 1
            keyword = tokens[i].lower()
            if keyword.isdigit():
                raise ValueError("Variables cannot be numbers: " + keyword)
            
            i += 1
            definition = []
            while tokens[i] != ';':
                definition.append(tokens[i])
                i += 1
            env[keyword] = definition
            
        elif token in env:
            tokens[i:i+1] = env[token]
            continue
            
        elif token in keywords:
            n_args, func = keywords[token]
            if len(stack) < n_args:
                raise StackUnderflowError('Cannot apply ' + token)
            
            if n_args == 1:
                arg = stack.pop()
                result = func(arg)
            else:
                args = [stack.pop() for _ in range(n_args)]
                args.reverse()
                result = func(*args)
            
            stack.extend(result)
            
        else:
            stack.append(int(token))
        
        i += 1
    
    return stack