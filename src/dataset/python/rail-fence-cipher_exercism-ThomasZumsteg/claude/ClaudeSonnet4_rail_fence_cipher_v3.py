def encode(message, rails):
    if rails <= 1:
        return message
    
    result = []
    cycle_len = 2 * (rails - 1)
    
    for rail in range(rails):
        for pos in range(rail, len(message), cycle_len):
            result.append(message[pos])
            if rail != 0 and rail != rails - 1:
                mid_pos = pos + cycle_len - 2 * rail
                if mid_pos < len(message):
                    result.append(message[mid_pos])
    
    return ''.join(result)

def decode(encoded_message, rails):
    if rails <= 1:
        return encoded_message
    
    length = len(encoded_message)
    message = [''] * length
    cycle_len = 2 * (rails - 1)
    idx = 0
    
    for rail in range(rails):
        positions = []
        for pos in range(rail, length, cycle_len):
            positions.append(pos)
            if rail != 0 and rail != rails - 1:
                mid_pos = pos + cycle_len - 2 * rail
                if mid_pos < length:
                    positions.append(mid_pos)
        
        positions.sort()
        for pos in positions:
            message[pos] = encoded_message[idx]
            idx += 1
    
    return ''.join(message)

def _make_rails(items, rails):
    if rails <= 1:
        return tuple(items)
    
    rail_lists = [[] for _ in range(rails)]
    step, rail = 1, 0
    
    for item in items:
        rail_lists[rail].append(item)
        if rail == 0:
            step = 1
        elif rail == rails - 1:
            step = -1
        rail += step
    
    result = []
    for sublist in rail_lists:
        result.extend(sublist)
    return tuple(result)