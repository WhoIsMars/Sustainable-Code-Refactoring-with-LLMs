def annotate(minefield):
    if not minefield or any(len(row) != len(minefield[0]) for row in minefield):
        raise ValueError(r".+")

    rows, cols = len(minefield), len(minefield[0])
    result = []

    for row in range(rows):
        new_row = []
        for col in range(cols):
            cell = minefield[row][col]
            if cell == ' ':
                counter = sum(
                    1
                    for r in range(max(row - 1, 0), min(row + 2, rows))
                    for c in range(max(col - 1, 0), min(col + 2, cols))
                    if minefield[r][c] == '*'
                )
                new_row.append(str(counter) if counter > 0 else ' ')
            elif cell == '*':
                new_row.append('*')
            else:
                raise ValueError(r".+")
        result.append(''.join(new_row))

    return result