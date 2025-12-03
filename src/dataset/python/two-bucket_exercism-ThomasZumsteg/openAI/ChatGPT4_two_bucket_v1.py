from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    seen = set()
    if start_bucket == 'one':
        vol_one, vol_two = bucket_one, 0
    elif start_bucket == 'two':
        vol_one, vol_two = 0, bucket_two
    else:
        raise ValueError('Only two buckets: {}'.format(start_bucket))

    queue = deque([(1, vol_one, vol_two)])

    while queue:
        steps, one, two = queue.popleft()
        if (one, two) in seen:
            continue
        seen.add((one, two))

        if one == goal:
            return (steps, "one", two)
        if two == goal:
            return (steps, "two", one)

        # Fill
        if (one, bucket_two) not in seen:
            queue.append((steps + 1, one, bucket_two))
        if (bucket_one, two) not in seen:
            queue.append((steps + 1, bucket_one, two))

        # Empty
        if (one, 0) not in seen:
            queue.append((steps + 1, one, 0))
        if (0, two) not in seen:
            queue.append((steps + 1, 0, two))

        # Transfer
        transfer_to_two = min(one, bucket_two - two)
        new_one, new_two = one - transfer_to_two, two + transfer_to_two
        if (new_one, new_two) not in seen:
            queue.append((steps + 1, new_one, new_two))

        transfer_to_one = min(two, bucket_one - one)
        new_one, new_two = one + transfer_to_one, two - transfer_to_one
        if (new_one, new_two) not in seen:
            queue.append((steps + 1, new_one, new_two))

    raise ValueError('No solution')