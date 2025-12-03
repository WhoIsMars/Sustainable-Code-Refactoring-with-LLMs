def encode(message, rails):
    if rails == 1:
        return message
    period = 2 * rails - 2
    rows = [''] * rails

    for i, c in enumerate(message):
        row = min(i % period, period - i % period)
        rows[row] += c

    return ''.join(rows)


def decode(encoded_message, rails):
    if rails == 1:
        return encoded_message
    period = 2 * rails - 2
    rows_size = [0] * rails
    text = [''] * len(encoded_message)

    for i in range(len(encoded_message)):
        rows_size[min(i % period, period - i % period)] += 1

    indices = []
    start = 0
    for size in rows_size:
        indices.append(range(start, start + size))
        start += size

    row_iters = [iter(encoded_message[start:start + size]) for start, size in zip(indices, rows_size)]

    for i in range(len(encoded_message)):
        row = min(i % period, period - i % period)
        text[i] = next(row_iters[row])

    return ''.join(text)