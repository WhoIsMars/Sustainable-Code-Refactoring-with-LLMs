def encode(message, rails):
    if rails <= 1:
        return message

    period = 2 * (rails - 1)
    rows = [''] * rails

    for i, char in enumerate(message):
        rail = min(i % period, period - (i % period))
        rows[rail] += char

    return ''.join(rows)


def decode(encoded_message, rails):
    if rails <= 1:
        return encoded_message

    period = 2 * (rails - 1)
    rail_indices = [[] for _ in range(rails)]
    message_len = len(encoded_message)

    for i in range(message_len):
        rail_indices[min(i % period, period - (i % period))].append(i)

    result = [''] * message_len
    index = 0
    for rail in rail_indices:
        for i in rail:
            result[i] = encoded_message[index]
            index += 1

    return ''.join(result)