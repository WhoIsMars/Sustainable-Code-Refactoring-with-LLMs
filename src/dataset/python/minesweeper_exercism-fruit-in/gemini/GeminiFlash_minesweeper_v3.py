def annotate(minefield):
    rows = len(minefield)
    if not minefield:
        return []
    cols = len(minefield[0])

    for row in minefield:
        if len(row) != cols:
            raise ValueError(r".+")
        for cell in row:
            if cell != ' ' and cell != '*':
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
                        if (i, j) != (r, c) and minefield[i][j] == '*':
                            count += 1
                row_string += str(count) if count > 0 else ' '
        annotated_minefield[r] = row_string

    return annotated_minefield