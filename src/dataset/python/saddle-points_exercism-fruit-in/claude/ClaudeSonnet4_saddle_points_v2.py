def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    if any(len(row) != len(matrix[0]) for row in matrix):
        raise ValueError(r".+")

    rows, cols = len(matrix), len(matrix[0])
    
    # Pre-compute row maximums and column minimums
    row_maxs = [max(row) for row in matrix]
    col_mins = [min(matrix[row][col] for row in range(rows)) for col in range(cols)]
    
    saddle_points_list = []
    
    for row in range(rows):
        for col in range(cols):
            val = matrix[row][col]
            if val == row_maxs[row] and val == col_mins[col]:
                saddle_points_list.append({"row": row + 1, "column": col + 1})
    
    return saddle_points_list