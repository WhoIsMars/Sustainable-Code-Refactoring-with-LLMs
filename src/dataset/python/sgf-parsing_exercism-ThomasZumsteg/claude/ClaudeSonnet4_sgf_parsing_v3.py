class SgfTree(object):
    def __init__(self, properties=None, children=None):
        self.properties = properties or {}
        self.children = children or []

    def __eq__(self, other):
        if not isinstance(other, SgfTree):
            return False
        if self.properties != other.properties:
            return False
        if len(self.children) != len(other.children):
            return False
        return all(a == b for a, b in zip(self.children, other.children))

    def __repr__(self):
        children_repr = ','.join(repr(c) for c in self.children)
        return f'SgfTree({self.properties}, [{children_repr}])'

def parse(input_string):
    if not input_string or input_string[0] != '(':
        raise ValueError(f"Invalid SgfTree '{input_string}'")
    
    stack = []
    state = 'START'
    escape = False
    key = ''
    value = ''
    values = []
    
    for c, char in enumerate(input_string):
        if state == 'START' and char == '(':
            state = 'TREE'
        elif state == 'TREE' and char == ';':
            stack.append(SgfTree())
            state = 'KEY'
            key = ''
        elif state == 'KEY':
            if char == ')':
                if key and values:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
            elif char == '(':
                if key and values:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
                state = 'TREE'
            elif char == ';':
                if key and values:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
                stack.append(SgfTree())
                key = ''
            elif char == '[':
                if not key:
                    raise ValueError(f"Invalid SgfTree '{input_string}' at '{input_string[:c]}' {input_string[c]} '{input_string[c+1:]}'")
                value = ''
                if key not in stack[-1].properties:
                    stack[-1].properties[key] = []
                values = stack[-1].properties[key]
                state = 'VALUE'
            elif char.islower():
                raise ValueError(f"Invalid SgfTree '{input_string}' at '{input_string[:c]}' {input_string[c]} '{input_string[c+1:]}'")
            else:
                key += char
        elif state == 'VALUE':
            if escape:
                if char == '\t':
                    value += ' '
                else:
                    value += char
                escape = False
            elif char == '\\':
                escape = True
            elif char == ']':
                values.append(value)
                value = ''
                state = 'KEY'
            elif char == '\t':
                value += ' '
            else:
                value += char
        else:
            raise ValueError(f"Invalid SgfTree '{input_string}' at '{input_string[:c]}' {input_string[c]} '{input_string[c+1:]}'")
    
    if not stack:
        raise ValueError(f"Invalid SgfTree '{input_string}'")
    
    while len(stack) > 1:
        node = stack.pop()
        stack[-1].children.append(node)
    
    return stack[0]