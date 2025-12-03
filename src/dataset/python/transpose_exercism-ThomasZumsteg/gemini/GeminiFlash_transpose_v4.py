def transpose(input_lines):
    lines = input_lines.splitlines()
    num_rows = len(lines)
    num_cols = 0
    for line in lines:
        num_cols = max(num_cols, len(line))

    result = [''] * num_cols
    for c in range(num_cols):
        result[c] = [' '] * num_rows

    for r in range(num_rows):
        for c, char in enumerate(lines[r]):
            result[c][r] = char

    return '\n'.join(''.join(row) for row in result)