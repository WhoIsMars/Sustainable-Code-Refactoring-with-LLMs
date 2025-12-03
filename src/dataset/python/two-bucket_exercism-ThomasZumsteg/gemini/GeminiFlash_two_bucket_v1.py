from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    if start_bucket == 'one':
        start_state = (bucket_one, 0)
        other_bucket_capacity = bucket_two
    elif start_bucket == 'two':
        start_state = (0, bucket_two)
        other_bucket_capacity = bucket_one
    else:
        raise ValueError('Only two buckets: {}'.format(start_bucket))

    queue = deque([(1, start_state[0], start_state[1])])
    visited = {start_state}

    while queue:
        steps, one, two = queue.popleft()

        if one == goal:
            return (steps, "one", two)
        elif two == goal:
            return (steps, "two", one)

        # Fill
        fill_one = (bucket_one, two)
        if fill_one not in visited:
            queue.append((steps + 1, *fill_one))
            visited.add(fill_one)

        fill_two = (one, bucket_two)
        if fill_two not in visited:
            queue.append((steps + 1, *fill_two))
            visited.add(fill_two)

        # Empty
        empty_one = (0, two)
        if empty_one not in visited:
            queue.append((steps + 1, *empty_one))
            visited.add(empty_one)

        empty_two = (one, 0)
        if empty_two not in visited:
            queue.append((steps + 1, *empty_two))
            visited.add(empty_two)

        # Transfer
        transfer_one_to_two = (max(0, one + two - bucket_two), min(bucket_two, one + two))
        if transfer_one_to_two not in visited:
            queue.append((steps + 1, *transfer_one_to_two))
            visited.add(transfer_one_to_two)

        transfer_two_to_one = (min(bucket_one, one + two), max(0, one + two - bucket_one))
        if transfer_two_to_one not in visited:
            queue.append((steps + 1, *transfer_two_to_one))
            visited.add(transfer_two_to_one)

    raise ValueError('No solution')