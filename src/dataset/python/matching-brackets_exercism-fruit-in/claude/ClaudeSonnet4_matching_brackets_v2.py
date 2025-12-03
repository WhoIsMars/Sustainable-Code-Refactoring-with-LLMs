def is_paired(input_string):
    stack = []
    pairs = {'(': ')', '[': ']', '{': '}'}
    
    for bracket in input_string:
        if bracket in pairs:
            stack.append(bracket)
        elif bracket in pairs.values():
            if not stack or pairs[stack.pop()] != bracket:
                return False
    
    return len(stack) == 0