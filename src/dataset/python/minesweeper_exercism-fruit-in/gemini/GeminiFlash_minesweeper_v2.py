def annotate(minefield):
    rows = len(minefield)
    if rows == 0:
        return []
    cols = len(minefield[0])
    
    for row in minefield:
        if len(row) != cols:
            raise ValueError(r".+")

    annotated_minefield = ['' for _ in range(rows)]

    for r in range(rows):
        row_string = ''
        for c in range(cols):
            if minefield[r][c] == '*':
                row_string += '*'
            else:
                count = 0
                for i in range(max(0, r - 1), min(rows, r + 2)):
                    for j in range(max(0, c - 1), min(cols, c + 2)):
                        if minefield[i][j] == '*':
                            count += 1
                if count > 0:
                    row_string += str(count)
                else:
                    row_string += ' '
        annotated_minefield[r] = row_string

    for row in annotated_minefield:
        for cell in row:
            if cell not in (' ', '*', '1', '2', '3', '4', '5', '6', '7', '8'):
                raise ValueError(r".+")

    return annotated_minefield