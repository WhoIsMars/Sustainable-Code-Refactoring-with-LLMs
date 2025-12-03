def annotate(minefield):
    if not minefield:
        return []
    
    rows = len(minefield)
    cols = len(minefield[0])
    
    # Validate input and convert to list of lists in one pass
    result = []
    for i, row in enumerate(minefield):
        if len(row) != cols:
            raise ValueError(r".+")
        result.append(list(row))
    
    # Pre-calculate neighbor offsets
    offsets = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    
    for row in range(rows):
        for col in range(cols):
            cell = result[row][col]
            if cell == ' ':
                counter = 0
                for dr, dc in offsets:
                    r, c = row + dr, col + dc
                    if 0 <= r < rows and 0 <= c < cols and result[r][c] == '*':
                        counter += 1
                
                if counter > 0:
                    result[row][col] = str(counter)
            elif cell != '*':
                raise ValueError(r".+")
    
    return [''.join(row) for row in result]