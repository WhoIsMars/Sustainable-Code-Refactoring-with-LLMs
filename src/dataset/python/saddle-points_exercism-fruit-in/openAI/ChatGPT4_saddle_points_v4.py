def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    if any(len(row) != len(matrix[0]) for row in matrix):
        raise ValueError(r".+")

    row_max = {row: max(row) for row in matrix}
    col_min = {col: min(matrix[row][col] for row in range(len(matrix))) for col in range(len(matrix[0]))}

    return [
        {"row": r + 1, "column": c + 1}
        for r, row in enumerate(matrix)
        for c, val in enumerate(row)
        if val == row_max[row] and val == col_min[c]
    ]