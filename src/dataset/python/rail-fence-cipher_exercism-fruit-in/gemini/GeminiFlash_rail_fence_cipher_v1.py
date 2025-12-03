def encode(message, rails):
    if rails <= 1:
        return message

    period = 2 * rails - 2
    rows = [''] * rails

    for i, char in enumerate(message):
        rail_index = min(i % period, period - i % period)
        rows[rail_index] += char

    return ''.join(rows)


def decode(encoded_message, rails):
    if rails <= 1:
        return encoded_message

    period = 2 * rails - 2
    row_lengths = [0] * rails

    for i in range(len(encoded_message)):
        row_lengths[min(i % period, period - i % period)] += 1

    row_starts = [0] * rails
    start = 0
    for i in range(rails):
        row_starts[i] = start
        start += row_lengths[i]

    plaintext = [''] * len(encoded_message)
    index = 0
    for i in range(len(encoded_message)):
        rail_index = min(i % period, period - i % period)
        plaintext[i] = encoded_message[row_starts[rail_index]]
        row_starts[rail_index] += 1

    return ''.join(plaintext)