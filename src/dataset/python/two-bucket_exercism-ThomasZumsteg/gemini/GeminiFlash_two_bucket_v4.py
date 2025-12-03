def measure(bucket_one, bucket_two, goal, start_bucket):
    if start_bucket == 'one':
        initial_state = (bucket_one, 0)
    elif start_bucket == 'two':
        initial_state = (0, bucket_two)
    else:
        raise ValueError('Invalid start bucket: {}'.format(start_bucket))

    queue = [(1, initial_state[0], initial_state[1])]
    visited = {initial_state}

    while queue:
        steps, one, two = queue.pop(0)

        if one == goal:
            return (steps, "one", two)
        elif two == goal:
            return (steps, "two", one)

        # Fill
        next_states = [
            (one, bucket_two),
            (bucket_one, two),
            (one, 0),
            (0, two)
        ]

        # Transfer
        transfer_one_to_two = min(one, bucket_two - two)
        next_states.append((one - transfer_one_to_two, two + transfer_one_to_two))

        transfer_two_to_one = min(two, bucket_one - one)
        next_states.append((one + transfer_two_to_one, two - transfer_two_to_one))

        for next_one, next_two in next_states:
            if (next_one, next_two) not in visited:
                queue.append((steps + 1, next_one, next_two))
                visited.add((next_one, next_two))

    raise ValueError('No solution')