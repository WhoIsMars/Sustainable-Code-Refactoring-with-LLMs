def annotate(minefield):
    if not all(len(row) == len(minefield[0]) for row in minefield):
        raise ValueError(r".+")

    minefield = [list(row) for row in minefield]
    rows, cols = len(minefield), len(minefield[0])
    directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

    for row in range(rows):
        for col in range(cols):
            cell = minefield[row][col]
            if cell == ' ':
                counter = sum(
                    1 for dr, dc in directions
                    if 0 <= row + dr < rows and 0 <= col + dc < cols and minefield[row + dr][col + dc] == '*'
                )
                if counter > 0:
                    minefield[row][col] = str(counter)
            elif cell != '*':
                raise ValueError(r".+")

    return [''.join(row) for row in minefield]