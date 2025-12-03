def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    rows, cols = len(matrix), len(matrix[0])
    if any(len(row) != cols for row in matrix):
        raise ValueError(r".+")

    row_maxes = [max(row) for row in matrix]
    col_mins = [min(matrix[r][c] for r in range(rows)) for c in range(cols)]
    
    result = []
    for r in range(rows):
        for c in range(cols):
            if matrix[r][c] == row_maxes[r] and matrix[r][c] == col_mins[c]:
                result.append({"row": r + 1, "column": c + 1})
    
    return result