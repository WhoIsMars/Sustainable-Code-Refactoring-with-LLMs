def transpose(input_lines):
    lines = input_lines.splitlines()
    num_rows = len(lines)
    num_cols = max(len(line) for line in lines) if lines else 0

    result = [[' '] * num_rows for _ in range(num_cols)]

    for r in range(num_rows):
        for c in range(len(lines[r])):
            result[c][r] = lines[r][c]

    return '\n'.join(''.join(row) for row in result)