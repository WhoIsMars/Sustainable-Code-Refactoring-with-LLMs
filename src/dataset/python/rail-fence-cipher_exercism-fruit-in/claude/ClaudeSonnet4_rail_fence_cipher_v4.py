def encode(message, rails):
    if rails <= 1:
        return message
    
    period = 2 * rails - 2
    rows = [[] for _ in range(rails)]
    
    for i, c in enumerate(message):
        row_index = i % period
        if row_index >= rails:
            row_index = period - row_index
        rows[row_index].append(c)
    
    result = []
    for row in rows:
        result.extend(row)
    return ''.join(result)


def decode(encoded_message, rails):
    if rails <= 1 or not encoded_message:
        return encoded_message
    
    period = 2 * rails - 2
    message_len = len(encoded_message)
    rows_size = [0] * rails
    
    for i in range(message_len):
        row_index = i % period
        if row_index >= rails:
            row_index = period - row_index
        rows_size[row_index] += 1
    
    rows = []
    start = 0
    for size in rows_size:
        rows.append(list(encoded_message[start:start + size]))
        start += size
    
    result = []
    for i in range(message_len):
        row_index = i % period
        if row_index >= rails:
            row_index = period - row_index
        result.append(rows[row_index].pop(0))
    
    return ''.join(result)