def is_paired(input_string):
    stack = []
    opening = {'[', '{', '('}
    pairs = {']': '[', '}': '{', ')': '('}

    for bracket in input_string:
        if bracket in opening:
            stack.append(bracket)
        elif bracket in pairs:
            if not stack or stack.pop() != pairs[bracket]:
                return False

    return len(stack) == 0