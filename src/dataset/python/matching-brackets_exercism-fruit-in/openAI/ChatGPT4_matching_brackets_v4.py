def is_paired(input_string):
    stack = []
    pairs = {')': '(', ']': '[', '}': '{'}

    for bracket in input_string:
        if bracket in pairs.values():
            stack.append(bracket)
        elif bracket in pairs:
            if not stack or stack.pop() != pairs[bracket]:
                return False

    return not stack