from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    seen = set()
    if start_bucket == 'one':
        vol_one, vol_two = bucket_one, 0
    elif start_bucket == 'two':
        vol_one, vol_two = 0, bucket_two
    else:
        raise ValueError(f'Only two buckets: {start_bucket}')

    queue = deque([(1, vol_one, vol_two)])
    seen.add((vol_one, vol_two))

    while queue:
        steps, one, two = queue.popleft()

        if one == goal:
            return (steps, "one", two)
        if two == goal:
            return (steps, "two", one)

        # Generate next states
        next_states = [
            (one, bucket_two),  # Fill bucket two
            (bucket_one, two),  # Fill bucket one
            (one, 0),           # Empty bucket two
            (0, two),           # Empty bucket one
            (max(0, one + two - bucket_two), min(bucket_two, one + two)),  # Transfer one -> two
            (min(bucket_one, one + two), max(0, one + two - bucket_one))   # Transfer two -> one
        ]

        for next_one, next_two in next_states:
            if (next_one, next_two) not in seen:
                seen.add((next_one, next_two))
                queue.append((steps + 1, next_one, next_two))

    raise ValueError('No solution')