def encode(message, rails):
    if rails <= 1:
        return message
    
    rail_lists = [[] for _ in range(rails)]
    rail = 0
    direction = 1
    
    for char in message:
        rail_lists[rail].append(char)
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    result = []
    for sublist in rail_lists:
        result.extend(sublist)
    return ''.join(result)

def decode(encoded_message, rails):
    if rails <= 1:
        return encoded_message
    
    length = len(encoded_message)
    rail_positions = [[] for _ in range(rails)]
    rail = 0
    direction = 1
    
    # Calculate positions for each rail
    for i in range(length):
        rail_positions[rail].append(i)
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    # Reconstruct message
    message = [''] * length
    char_index = 0
    
    for positions in rail_positions:
        for pos in positions:
            message[pos] = encoded_message[char_index]
            char_index += 1
    
    return ''.join(message)

def _make_rails(items, rails):
    if rails <= 1:
        return tuple(items)
    
    rail_lists = [[] for _ in range(rails)]
    rail = 0
    direction = 1
    
    for item in items:
        rail_lists[rail].append(item)
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    result = []
    for sublist in rail_lists:
        result.extend(sublist)
    return tuple(result)