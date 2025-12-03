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
        minefield_row = minefield[row]
        
        for col in range(cols):
            cell = minefield_row[col]
            
            if cell == ' ':
                counter = 0
                
                row_start = max(row - 1, 0)
                row_end = min(row + 2, rows)
                col_start = max(col - 1, 0)
                col_end = min(col + 2, cols)
                
                for r in range(row_start, row_end):
                    minefield_r = minefield[r]
                    for c in range(col_start, col_end):
                        if minefield_r[c] == '*':
                            counter += 1
                
                result_row.append(str(counter) if counter > 0 else ' ')
            elif cell == '*':
                result_row.append('*')
            else:
                raise ValueError(r".+")
        
        result.append(''.join(result_row))
    
    return result