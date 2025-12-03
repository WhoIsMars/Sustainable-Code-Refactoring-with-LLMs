def is_paired(input_string):
    stack = []
    bracket_map = {')': '(', ']': '[', '}': '{'}

    for bracket in input_string:
        if bracket in bracket_map.values():
            stack.append(bracket)
        elif bracket in bracket_map:
            if not stack or stack.pop() != bracket_map[bracket]:
                return False

    return not stack