MATCHING_BRACKETS = {
    '(': ')',
    '{': '}',
    '[': ']'
}

def check_brackets(line):
    """check_brackets checks if brackets are properly balanced"""
    stack = []
    for char in line:
        if char in MATCHING_BRACKETS:
            stack.append(MATCHING_BRACKETS[char])
        elif stack and char == stack[-1]:
            stack.pop()
        else:
            return False
    return not stack