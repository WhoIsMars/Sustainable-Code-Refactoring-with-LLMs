def transpose(input_lines):
    lines = input_lines.splitlines()
    max_len = max(len(line) for line in lines)
    result = [''.join(line[c] if c < len(line) else ' ' for line in lines) for c in range(max_len)]
    return '\n'.join(result)