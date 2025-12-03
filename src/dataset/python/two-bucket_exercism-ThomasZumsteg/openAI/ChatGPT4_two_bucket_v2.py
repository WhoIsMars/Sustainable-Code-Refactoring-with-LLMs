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
        if one < bucket_one:
            queue.append((steps + 1, bucket_one, two))
        if two < bucket_two:
            queue.append((steps + 1, one, bucket_two))

        # Empty
        if one > 0:
            queue.append((steps + 1, 0, two))
        if two > 0:
            queue.append((steps + 1, one, 0))

        # Transfer
        transfer_to_two = min(one, bucket_two - two)
        if transfer_to_two > 0:
            queue.append((steps + 1, one - transfer_to_two, two + transfer_to_two))

        transfer_to_one = min(two, bucket_one - one)
        if transfer_to_one > 0:
            queue.append((steps + 1, one + transfer_to_one, two - transfer_to_one))

    raise ValueError('No solution')