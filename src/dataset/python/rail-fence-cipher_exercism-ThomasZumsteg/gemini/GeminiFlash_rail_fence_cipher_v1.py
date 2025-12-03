def encode(message, rails):
    rail_lists = [[] for _ in range(rails)]
    step, rail = 1, 0
    for char in message:
        rail_lists[rail].append(char)
        rail += step
        if rail == 0:
            step = 1
        elif rail == rails - 1:
            step = -1
    return ''.join(''.join(rail) for rail in rail_lists)

def decode(encoded_message, rails):
    rail_lengths = [0] * rails
    step, rail = 1, 0
    for _ in range(len(encoded_message)):
        rail_lengths[rail] += 1
        rail += step
        if rail == 0:
            step = 1
        elif rail == rails - 1:
            step = -1

    rail_texts = []
    start = 0
    for length in rail_lengths:
        rail_texts.append(encoded_message[start:start + length])
        start += length

    message = [''] * len(encoded_message)
    index = 0
    rail = 0
    step = 1
    rail_indices = [0] * rails
    for i in range(len(encoded_message)):
        message[i] = rail_texts[rail][rail_indices[rail]]
        rail_indices[rail] += 1
        rail += step
        if rail == 0:
            step = 1
        elif rail == rails - 1:
            step = -1
    return ''.join(message)