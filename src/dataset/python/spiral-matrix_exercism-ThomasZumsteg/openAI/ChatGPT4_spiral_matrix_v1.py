def spiral(size):
    result = [[0] * size for _ in range(size)]
    row, col, dr, dc = 0, 0, 0, 1
    for step in range(1, size * size + 1):
        result[row][col] = step
        next_row, next_col = row + dr, col + dc
        if not (0 <= next_col < size and 0 <= next_row < size and result[next_row][next_col] == 0):
            dr, dc = dc, -dr
        row, col = row + dr, col + dc
    return result