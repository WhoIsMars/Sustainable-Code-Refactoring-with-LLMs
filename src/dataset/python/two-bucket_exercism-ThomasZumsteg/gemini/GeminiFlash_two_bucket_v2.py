from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    if not (0 <= goal <= max(bucket_one, bucket_two) and (goal == bucket_one or goal == bucket_two or (bucket_one > 0 and bucket_two > 0))):
        raise ValueError("Goal cannot be reached with given buckets.")

    seen = set()
    if start_bucket == 'one':
        initial_state = (bucket_one, 0)
    elif start_bucket == 'two':
        initial_state = (0, bucket_two)
    else:
        raise ValueError('Only two buckets: {}'.format(start_bucket))

    queue = deque([(1, initial_state[0], initial_state[1])])
    seen.add(initial_state)

    while queue:
        steps, one, two = queue.popleft()

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
        next_states.append((max(0, one + two - bucket_two), min(bucket_two, one + two)))
        next_states.append((min(bucket_one, one + two), max(0, one + two - bucket_one)))

        for next_one, next_two in next_states:
            next_state = (next_one, next_two)
            if next_state not in seen:
                queue.append((steps + 1, next_one, next_two))
                seen.add(next_state)

    raise ValueError('No solution')