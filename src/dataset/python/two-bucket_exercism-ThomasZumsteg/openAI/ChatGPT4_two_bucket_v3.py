from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    seen = set()
    if start_bucket == 'one':
        initial_state = (bucket_one, 0)
    elif start_bucket == 'two':
        initial_state = (0, bucket_two)
    else:
        raise ValueError(f'Only two buckets: {start_bucket}')

    queue = deque([(1, *initial_state)])
    seen.add(initial_state)

    while queue:
        steps, one, two = queue.popleft()

        if one == goal:
            return steps, "one", two
        if two == goal:
            return steps, "two", one

        next_states = [
            (bucket_one, two),  # Fill bucket one
            (one, bucket_two),  # Fill bucket two
            (0, two),           # Empty bucket one
            (one, 0),           # Empty bucket two,
            (max(0, one - (bucket_two - two)), min(bucket_two, one + two)),  # Pour one -> two
            (min(bucket_one, one + two), max(0, two - (bucket_one - one)))   # Pour two -> one
        ]

        for next_state in next_states:
            if next_state not in seen:
                seen.add(next_state)
                queue.append((steps + 1, *next_state))

    raise ValueError('No solution')