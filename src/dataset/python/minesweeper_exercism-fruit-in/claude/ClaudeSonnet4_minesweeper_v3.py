def annotate(minefield):
    if not minefield:
        return []
    
    rows = len(minefield)
    cols = len(minefield[0])
    
    for row in minefield:
        if len(row) != cols:
            raise ValueError(r".+")
    
    result = []
    
    for row in range(rows):
        result_row = []
        for col in range(cols):
            cell = minefield[row][col]
            if cell == ' ':
                counter = 0
                for r in range(max(row - 1, 0), min(row + 2, rows)):
                    for c in range(max(col - 1, 0), min(col + 2, cols)):
                        if minefield[r][c] == '*':
                            counter += 1
                result_row.append(str(counter) if counter > 0 else ' ')
            elif cell == '*':
                result_row.append('*')
            else:
                raise ValueError(r".+")
        result.append(''.join(result_row))
    
    return result