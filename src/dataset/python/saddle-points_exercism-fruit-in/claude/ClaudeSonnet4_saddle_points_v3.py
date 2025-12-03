def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    if any(len(row) != len(matrix[0]) for row in matrix):
        raise ValueError(r".+")

    rows, cols = len(matrix), len(matrix[0])
    row_maxes = [max(row) for row in matrix]
    col_mins = [min(matrix[row][col] for row in range(rows)) for col in range(cols)]
    
    saddles = []
    for row in range(rows):
        for col in range(cols):
            if matrix[row][col] == row_maxes[row] == col_mins[col]:
                saddles.append({"row": row + 1, "column": col + 1})
    
    return saddles