class SgfTree:
    __slots__ = ('properties', 'children')

    def __init__(self, properties=None, children=None):
        self.properties = properties or {}
        self.children = children or []

    def __eq__(self, other):
        if not isinstance(other, SgfTree):
            return False
        return (self.properties == other.properties and
                len(self.children) == len(other.children) and
                all(a == b for a, b in zip(self.children, other.children)))

    def __repr__(self):
        return f"SgfTree({self.properties}, [{','.join(map(repr, self.children))}])"

def parse(input_string):
    stack = []
    state = 'START'
    escape = False
    key, value, values = '', '', None

    def raise_error(c):
        raise ValueError(f"Invalid SgfTree '{input_string}' at '{input_string[:c]}' {input_string[c]} '{input_string[c+1:]}'")

    for c, char in enumerate(input_string):
        if state == 'START':
            if char == '(':
                state = 'TREE'
        elif state == 'TREE':
            if char == ';':
                stack.append(SgfTree())
                state = 'KEY'
                key = ''
        elif state == 'KEY':
            if char == ')':
                if key and values is not None:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
            elif char == '(':
                if key and values is not None:
                    stack[-1].properties[key] = values
                stack.append(SgfTree())
                key, values = '', None
            elif char == ';':
                if key and values is not None:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
                stack.append(SgfTree())
                key, values = '', None
            elif char == '[':
                if not key:
                    raise_error(c)
                value = ''
                values = stack[-1].properties.setdefault(key, [])
                state = 'VALUE'
            elif char.islower():
                raise_error(c)
            else:
                key += char
        elif state == 'VALUE':
            if char == '\\':
                escape = not escape
            elif char == ']' and not escape:
                values.append(value)
                value = ''
                state = 'KEY'
            elif char == '\t':
                value += ' '
            else:
                value += char
                escape = False
        else:
            raise_error(c)

    if not stack:
        raise ValueError(f"Invalid SgfTree '{input_string}'")
    while len(stack) > 1:
        node = stack.pop()
        stack[-1].children.append(node)
    return stack[0]