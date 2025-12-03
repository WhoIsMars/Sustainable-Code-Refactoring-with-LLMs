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
    text = []

    for i in range(len(encoded_message)):
        rows_size[min(i % period, period - i % period)] += 1

    rows = []
    idx = 0
    for size in rows_size:
        rows.append(encoded_message[idx:idx + size])
        idx += size

    pointers = [0] * rails
    for i in range(len(encoded_message)):
        row = min(i % period, period - i % period)
        text.append(rows[row][pointers[row]])
        pointers[row] += 1

    return ''.join(text)