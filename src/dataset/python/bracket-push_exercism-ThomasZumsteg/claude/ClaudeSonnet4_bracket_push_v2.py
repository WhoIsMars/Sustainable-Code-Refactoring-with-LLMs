MATCHING_BRACKETS = {"(": ")", "{": "}", "[": "]"}
CLOSING_BRACKETS = {")", "}", "]"}

def check_brackets(line):
    """check_brackets checks if brackets are properly balanced"""
    stack = []
    for char in line:
        if char in MATCHING_BRACKETS:
            stack.append(MATCHING_BRACKETS[char])
        elif char in CLOSING_BRACKETS:
            if not stack or char != stack.pop():
                return False
    return not stack