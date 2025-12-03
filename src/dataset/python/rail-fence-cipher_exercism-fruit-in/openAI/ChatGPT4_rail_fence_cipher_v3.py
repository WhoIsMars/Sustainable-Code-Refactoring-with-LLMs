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
    message_len = len(encoded_message)
    rows = [''] * rails
    text = []

    for i in range(message_len):
        rows_size[min(i % period, period - i % period)] += 1

    idx = 0
    for row, size in enumerate(rows_size):
        rows[row] = encoded_message[idx:idx + size]
        idx += size

    row_pointers = [0] * rails
    for i in range(message_len):
        row = min(i % period, period - i % period)
        text.append(rows[row][row_pointers[row]])
        row_pointers[row] += 1

    return ''.join(text)