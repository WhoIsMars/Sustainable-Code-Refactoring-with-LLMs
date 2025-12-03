def encode(message, rails):
    if rails <= 1:
        return message
    
    rail_lists = [[] for _ in range(rails)]
    step, rail = 1, 0
    
    for char in message:
        rail_lists[rail].append(char)
        if rail == 0:
            step = 1
        elif rail == rails - 1:
            step = -1
        rail += step
    
    result = []
    for sublist in rail_lists:
        result.extend(sublist)
    return ''.join(result)

def decode(encoded_message, rails):
    if rails <= 1:
        return encoded_message
    
    length = len(encoded_message)
    message = [None] * length
    rail_lists = [[] for _ in range(rails)]
    step, rail = 1, 0
    
    for i in range(length):
        rail_lists[rail].append(i)
        if rail == 0:
            step = 1
        elif rail == rails - 1:
            step = -1
        rail += step
    
    idx = 0
    for sublist in rail_lists:
        for pos in sublist:
            message[pos] = encoded_message[idx]
            idx += 1
    
    return ''.join(message)