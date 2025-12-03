MATCHING_BRACKETS = {"(": ")", "{": "}", "[": "]"}

def check_brackets(line):
    """check_brackets checks if brackets are properly balanced"""
    queue = []
    for char in line:
        if char in MATCHING_BRACKETS:
            queue.append(MATCHING_BRACKETS[char])
        elif queue and char == queue[-1]:
            queue.pop()
        else:
            return False
    return not queue