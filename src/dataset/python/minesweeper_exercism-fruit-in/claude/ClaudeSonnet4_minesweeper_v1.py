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
    
    # Pre-calculate mine positions for faster lookup
    mines = set()
    for row in range(rows):
        for col in range(cols):
            if result[row][col] == '*':
                mines.add((row, col))
            elif result[row][col] != ' ':
                raise ValueError(r".+")
    
    # Process only empty cells
    for row in range(rows):
        for col in range(cols):
            if result[row][col] == ' ':
                counter = 0
                # Check 8 adjacent cells
                for r in range(max(row - 1, 0), min(row + 2, rows)):
                    for c in range(max(col - 1, 0), min(col + 2, cols)):
                        if (r, c) in mines:
                            counter += 1
                
                if counter > 0:
                    result[row][col] = str(counter)
    
    return [''.join(row) for row in result]