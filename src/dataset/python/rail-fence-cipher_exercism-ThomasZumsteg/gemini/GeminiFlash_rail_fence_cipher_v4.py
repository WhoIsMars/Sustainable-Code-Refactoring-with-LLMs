def encode(message, rails):
    rail_lists = [[] for _ in range(rails)]
    step, rail = 1, 0
    for char in message:
        rail_lists[rail].append(char)
        if not (0 <= rail + step < rails):
            step *= -1
        rail += step
    return ''.join(''.join(rail) for rail in rail_lists)

def decode(encoded_message, rails):
    rail_indices = [[] for _ in range(rails)]
    step, rail = 1, 0
    for i in range(len(encoded_message)):
        rail_indices[rail].append(i)
        if not (0 <= rail + step < rails):
            step *= -1
        rail += step

    index_map = {}
    index = 0
    for rail_list in rail_indices:
        for rail_index in rail_list:
            index_map[rail_index] = encoded_message[index]
            index += 1

    message = ''.join(index_map[i] for i in range(len(encoded_message)))
    return message