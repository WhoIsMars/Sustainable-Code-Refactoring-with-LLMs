def is_paired(input_string):
    stack = []
    bracket_map = {')': '(', ']': '[', '}': '{'}

    for bracket in input_string:
        if bracket in '([{':
            stack.append(bracket)
        elif bracket in ')]}':
            if not stack or stack[-1] != bracket_map[bracket]:
                return False
            stack.pop()

    return not stack