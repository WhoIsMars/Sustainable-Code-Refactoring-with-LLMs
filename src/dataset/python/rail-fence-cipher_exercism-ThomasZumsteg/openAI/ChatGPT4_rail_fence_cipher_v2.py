def encode(message, rails):
    return ''.join(_make_rails(message, rails))

def decode(encoded_message, rails):
    indices = _make_rails(range(len(encoded_message)), rails)
    message = [''] * len(encoded_message)
    for i, idx in enumerate(indices):
        message[idx] = encoded_message[i]
    return ''.join(message)

def _make_rails(items, rails):
    rail_positions = []
    step, rail = 1, 0
    for _ in items:
        rail_positions.append(rail)
        if rail == 0 or rail == rails - 1:
            step = -step
        rail += step
    sorted_items = sorted(zip(rail_positions, items))
    return [item for _, item in sorted_items]