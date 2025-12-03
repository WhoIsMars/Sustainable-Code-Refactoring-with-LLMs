def encode(message, rails):
    if rails <= 1:
        return message
    
    period = 2 * rails - 2
    rows = [[] for _ in range(rails)]
    
    for i, c in enumerate(message):
        rail = i % period
        if rail >= rails:
            rail = period - rail
        rows[rail].append(c)
    
    return ''.join(''.join(row) for row in rows)


def decode(encoded_message, rails):
    if rails <= 1 or not encoded_message:
        return encoded_message
    
    period = 2 * rails - 2
    msg_len = len(encoded_message)
    
    rows_size = [0] * rails
    for i in range(msg_len):
        rail = i % period
        if rail >= rails:
            rail = period - rail
        rows_size[rail] += 1
    
    rows = []
    start = 0
    for size in rows_size:
        rows.append(list(encoded_message[start:start + size]))
        start += size
    
    result = []
    for i in range(msg_len):
        rail = i % period
        if rail >= rails:
            rail = period - rail
        result.append(rows[rail].pop(0))
    
    return ''.join(result)