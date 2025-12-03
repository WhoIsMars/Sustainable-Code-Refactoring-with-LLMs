def spiral(size):
    if size == 0:
        return []
    if size == 1:
        return [[1]]
    
    result = [[0] * size for _ in range(size)]
    row, col = 0, 0
    dr, dc = 0, 1
    
    for step in range(1, size * size + 1):
        result[row][col] = step
        next_row, next_col = row + dr, col + dc
        
        if (next_col >= size or next_col < 0 or 
            next_row >= size or next_row < 0 or 
            result[next_row][next_col] != 0):
            dr, dc = dc, -dr
            next_row, next_col = row + dr, col + dc
        
        row, col = next_row, next_col
    
    return result