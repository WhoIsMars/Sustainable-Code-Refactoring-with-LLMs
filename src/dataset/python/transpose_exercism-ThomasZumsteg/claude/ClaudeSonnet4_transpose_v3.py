def transpose(input_lines):
    lines = input_lines.splitlines()
    if not lines:
        return ''
    
    max_width = max(len(line) for line in lines)
    result = [[] for _ in range(max_width)]
    
    for r, line in enumerate(lines):
        line_len = len(line)
        for c in range(max_width):
            if c < line_len:
                result[c].append(line[c])
            elif c < len(result) and len(result[c]) < r:
                result[c].append(' ')
    
    for col in result:
        while len(col) < len(lines):
            col.append(' ')
    
    return '\n'.join(''.join(row) for row in result)