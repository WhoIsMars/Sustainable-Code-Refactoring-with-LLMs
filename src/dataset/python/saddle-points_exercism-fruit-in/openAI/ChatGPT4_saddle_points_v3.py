def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    if any(len(row) != len(matrix[0]) for row in matrix):
        raise ValueError(r".+")

    row_max = [max(row) for row in matrix]
    col_min = [min(col) for col in zip(*matrix)]

    return [
        {"row": r + 1, "column": c + 1}
        for r, row in enumerate(matrix)
        for c, val in enumerate(row)
        if val == row_max[r] and val == col_min[c]
    ]