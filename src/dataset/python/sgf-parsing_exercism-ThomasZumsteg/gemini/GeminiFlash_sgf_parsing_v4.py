class SgfTree(object):
    def __init__(self, properties=None, children=None):
        self.properties = properties or {}
        self.children = children or []

    def __eq__(self, other):
        if not isinstance(other, SgfTree):
            return False

        if self.properties.keys() != other.properties.keys():
            return False

        for k, v in self.properties.items():
            if other.properties[k] != v:
                return False

        if len(self.children) != len(other.children):
            return False

        for a, b in zip(self.children, other.children):
            if a != b:
                return False

        return True

    def __repr__(self):
        return 'SgfTree({}, [{}])'.format(
                self.properties,
                ','.join(repr(c) for c in self.children))

def parse(input_string):
    stack = []
    state = 'START'
    escape = False
    input_length = len(input_string)

    def raise_error(c):
        raise ValueError(
                "Invalid SgfTree '{}' at '{}' {} '{}'".format(
                    input_string,
                    input_string[:c],
                    input_string[c],
                    input_string[c+1:]))

    i = 0
    while i < input_length:
        char = input_string[i]

        if state == 'START' and char == '(':
            state = 'TREE'
        elif state == 'TREE' and char == ';':
            stack.append(SgfTree())
            state = 'KEY'
            key = ''
            values = None
        elif state == 'KEY':
            if char == ')':
                if key and values is not None:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
                i += 1
                continue
            elif char == '(':
                if key and values is not None:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
                i += 1
                continue
            elif char == ';':
                if key and values is not None:
                    stack[-1].properties[key] = values
                if len(stack) > 1:
                    node = stack.pop()
                    stack[-1].children.append(node)
                stack.append(SgfTree())
                key = ''
                values = None
                i += 1
                continue
            elif char == '[':
                if not key:
                    raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(input_string,input_string[:i], char, input_string[i+1:]))
                value = ""
                if key not in stack[-1].properties:
                    stack[-1].properties[key] = []
                values = stack[-1].properties[key]
                state = 'VALUE'
            elif 'a' <= char <= 'z':
                raise ValueError("Invalid SgfTree '{}' at '{}' {} '{}'".format(input_string,input_string[:i], char, input_string[i+1:]))
            else:
                key += char
        elif state == 'VALUE':
            if char == '\\':
                escape = True
            elif not escape and char == ']':
                if value:
                    values.append(value)
                value = ""
                state = "KEY"
            elif char == '\t':
                value += ' '
            else:
                value += char
                escape = False
        else:
            raise_error(i)
        i += 1

    if not stack:
        raise ValueError("Invalid SgfTree '{}'".format(input_string))

    while len(stack) > 1:
        node = stack.pop()
        stack[-1].children.append(node)

    return stack[0]