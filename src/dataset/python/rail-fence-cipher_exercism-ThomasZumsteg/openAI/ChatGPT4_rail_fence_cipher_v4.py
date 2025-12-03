def encode(message, rails):
    return ''.join(_make_rails(message, rails))

def decode(encoded_message, rails):
    message = [None] * len(encoded_message)
    indices = _make_rails(range(len(encoded_message)), rails)
    for i, idx in enumerate(indices):
        message[idx] = encoded_message[i]
    return ''.join(message)

def _make_rails(items, rails):
    rail_lists = [[] for _ in range(rails)]
    step, rail = 1, 0
    for char in items:
        rail_lists[rail].append(char)
        rail += step
        if rail == 0 or rail == rails - 1:
            step = -step
    return (item for sublist in rail_lists for item in sublist)