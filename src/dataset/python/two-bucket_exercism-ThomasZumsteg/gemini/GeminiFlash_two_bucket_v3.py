from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    seen = set()
    if start_bucket == 'one':
        initial_state = (bucket_one, 0)
        initial_volumes = (bucket_one, 0)
    elif start_bucket == 'two':
        initial_state = (0, bucket_two)
        initial_volumes = (0, bucket_two)
    else:
        raise ValueError('Only two buckets: {}'.format(start_bucket))

    queue = deque([(1, *initial_volumes)])
    seen.add(initial_state)

    while queue:
        steps, one, two = queue.popleft()

        if one == goal:
            return (steps, "one", two)
        elif two == goal:
            return (steps, "two", one)

        # Fill
        fill_two = (one, bucket_two)
        if fill_two not in seen:
            queue.append((steps + 1, *fill_two))
            seen.add(fill_two)

        fill_one = (bucket_one, two)
        if fill_one not in seen:
            queue.append((steps + 1, *fill_one))
            seen.add(fill_one)

        # Empty
        empty_two = (one, 0)
        if empty_two not in seen:
            queue.append((steps + 1, *empty_two))
            seen.add(empty_two)

        empty_one = (0, two)
        if empty_one not in seen:
            queue.append((steps + 1, *empty_one))
            seen.add(empty_one)

        # Transfer
        transfer_one_to_two = (max(0, one + two - bucket_two), min(bucket_two, one + two))
        if transfer_one_to_two not in seen:
            queue.append((steps + 1, *transfer_one_to_two))
            seen.add(transfer_one_to_two)

        transfer_two_to_one = (min(bucket_one, one + two), max(0, one + two - bucket_one))
        if transfer_two_to_one not in seen:
            queue.append((steps + 1, *transfer_two_to_one))
            seen.add(transfer_two_to_one)

    raise ValueError('No solution')