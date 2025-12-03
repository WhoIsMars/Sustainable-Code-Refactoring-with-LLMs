def encode(message, rails):
    if rails <= 1:
        return message
    
    period = 2 * rails - 2
    rows = [[] for _ in range(rails)]
    
    for i, c in enumerate(message):
        row_idx = i % period
        if row_idx >= rails:
            row_idx = period - row_idx
        rows[row_idx].append(c)
    
    result = []
    for row in rows:
        result.extend(row)
    return ''.join(result)


def decode(encoded_message, rails):
    if rails <= 1 or not encoded_message:
        return encoded_message
    
    period = 2 * rails - 2
    msg_len = len(encoded_message)
    
    # Calculate row sizes
    rows_size = [0] * rails
    for i in range(msg_len):
        row_idx = i % period
        if row_idx >= rails:
            row_idx = period - row_idx
        rows_size[row_idx] += 1
    
    # Build rows with direct indexing
    rows = []
    start_idx = 0
    for size in rows_size:
        rows.append(list(encoded_message[start_idx:start_idx + size]))
        start_idx += size
    
    # Reverse rows for pop efficiency
    for row in rows:
        row.reverse()
    
    # Reconstruct message
    result = []
    for i in range(msg_len):
        row_idx = i % period
        if row_idx >= rails:
            row_idx = period - row_idx
        result.append(rows[row_idx].pop())
    
    return ''.join(result)