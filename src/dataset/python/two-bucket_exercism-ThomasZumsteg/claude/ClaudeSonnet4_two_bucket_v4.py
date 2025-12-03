from collections import deque

def measure(bucket_one, bucket_two, goal, start_bucket):
    if start_bucket == 'one':
        initial_state = (bucket_one, 0)
    elif start_bucket == 'two':
        initial_state = (0, bucket_two)
    else:
        raise ValueError('Only two buckets: {}'.format(start_bucket))
    
    if initial_state[0] == goal:
        return (1, "one", initial_state[1])
    elif initial_state[1] == goal:
        return (1, "two", initial_state[0])
    
    seen = {initial_state}
    queue = deque([(1, initial_state[0], initial_state[1])])
    
    while queue:
        steps, one, two = queue.popleft()
        
        if one == goal:
            return (steps, "one", two)
        elif two == goal:
            return (steps, "two", one)
        
        next_steps = steps + 1
        candidates = [
            (one, bucket_two),
            (bucket_one, two),
            (one, 0),
            (0, two),
            (0, min(one + two, bucket_two)) if one + two <= bucket_two else (one + two - bucket_two, bucket_two),
            (min(one + two, bucket_one), 0) if one + two <= bucket_one else (bucket_one, one + two - bucket_one)
        ]
        
        for new_one, new_two in candidates:
            state = (new_one, new_two)
            if state not in seen:
                seen.add(state)
                queue.append((next_steps, new_one, new_two))
    
    raise ValueError('No solution')