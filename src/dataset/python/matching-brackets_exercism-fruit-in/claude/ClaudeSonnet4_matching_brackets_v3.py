def is_paired(input_string):
    stack_size = 0
    bracket_map = {']': '[', '}': '{', ')': '('}
    
    for bracket in input_string:
        if bracket in '[{(':
            stack_size += 1
        elif bracket in ']})':
            if stack_size == 0:
                return False
            stack_size -= 1
            
    return stack_size == 0