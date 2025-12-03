def is_paired(input_string):
    stack = []
    matching_brackets = {')': '(', ']': '[', '}': '{'}

    for bracket in input_string:
        if bracket in matching_brackets.values():
            stack.append(bracket)
        elif bracket in matching_brackets:
            if not stack or stack.pop() != matching_brackets[bracket]:
                return False

    return not stack