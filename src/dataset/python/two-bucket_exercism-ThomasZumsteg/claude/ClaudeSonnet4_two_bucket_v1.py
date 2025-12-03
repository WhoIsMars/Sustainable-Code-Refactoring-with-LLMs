def measure(bucket_one, bucket_two, goal, start_bucket):
    if start_bucket == 'one':
        initial_state = (bucket_one, 0)
    elif start_bucket == 'two':
        initial_state = (0, bucket_two)
    else:
        raise ValueError('Only two buckets: {}'.format(start_bucket))

    seen = {initial_state}
    queue = [(1, initial_state[0], initial_state[1])]

    while queue:
        steps, one, two = queue.pop(0)
        
        if one == goal:
            return (steps, "one", two)
        elif two == goal:
            return (steps, "two", one)

        # Generate all possible next states
        next_states = [
            (one, bucket_two),  # Fill bucket two
            (bucket_one, two),  # Fill bucket one
            (one, 0),           # Empty bucket two
            (0, two),           # Empty bucket one
        ]
        
        # Transfer from one to two
        transfer_amount = min(one, bucket_two - two)
        next_states.append((one - transfer_amount, two + transfer_amount))
        
        # Transfer from two to one
        transfer_amount = min(two, bucket_one - one)
        next_states.append((one + transfer_amount, two - transfer_amount))

        for new_one, new_two in next_states:
            state = (new_one, new_two)
            if state not in seen:
                seen.add(state)
                queue.append((steps + 1, new_one, new_two))

    raise ValueError('No solution')