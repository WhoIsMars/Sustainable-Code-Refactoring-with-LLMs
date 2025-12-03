def encode(message, rails):
    if rails <= 1:
        return message

    period = 2 * rails - 2
    rows = [''] * rails

    for i, c in enumerate(message):
        rows[min(i % period, period - i % period)] += c

    return ''.join(rows)


def decode(encoded_message, rails):
    if rails <= 1:
        return encoded_message

    period = 2 * rails - 2
    rows_size = [0] * rails

    for i in range(len(encoded_message)):
        rows_size[min(i % period, period - i % period)] += 1

    rows = [''] * rails
    start = 0
    for i, size in enumerate(rows_size):
        rows[i] = encoded_message[start:start + size]
        start += size

    text = []
    for i in range(len(encoded_message)):
        rail_index = min(i % period, period - i % period)
        text.append(rows[rail_index][0])
        rows[rail_index] = rows[rail_index][1:]

    return ''.join(text)