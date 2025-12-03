OPENING_BRACKETS = {'(', '{', '['}
BRACKET_PAIRS = {'(': ')', '{': '}', '[': ']'}

def check_brackets(line):
    """check_brackets checks if brackets are properly balanced"""
    stack = []
    for char in line:
        if char in OPENING_BRACKETS:
            stack.append(BRACKET_PAIRS[char])
        elif char in (')', '}', ']'):
            if not stack or char != stack.pop():
                return False
    return not stack