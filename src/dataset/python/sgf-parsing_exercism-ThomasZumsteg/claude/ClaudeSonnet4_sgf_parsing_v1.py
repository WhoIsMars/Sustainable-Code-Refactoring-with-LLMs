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
        return 'SgfTree({}, [{}])'.format(
                self.properties,
                ','.join(repr(c) for c in self.children))

def parse(input_string):
    stack = []
    state = 'START'
    escape = False
    key = ''
    value = ''
    values = []
    
    for c, char in enumerate(input_string):
        if state == 'START':
            if char == '(':
                state = 'TREE'
            else:
                raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(
                    input_string, input_string[:c], char, input_string[c+1:]))
        elif state == 'TREE':
            if char == ';':
                stack.append(SgfTree())
                state = 'KEY'
                key = ''
            else:
                raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(
                    input_string, input_string[:c], char, input_string[c+1:]))
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
                    raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(
                        input_string, input_string[:c], char, input_string[c+1:]))
                value = ""
                if key not in stack[-1].properties:
                    stack[-1].properties[key] = []
                values = stack[-1].properties[key]
                state = 'VALUE'
            elif char.islower():
                raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(
                    input_string, input_string[:c], char, input_string[c+1:]))
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
                value = ""
                state = "KEY"
            elif char == '\t':
                value += ' '
            else:
                value += char
        else:
            raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(
                input_string, input_string[:c], char, input_string[c+1:]))
    
    if not stack:
        raise ValueError("Invalid SgfTree '{}'".format(input_string))
    
    while len(stack) > 1:
        node = stack.pop()
        stack[-1].children.append(node)
    
    return stack[0]