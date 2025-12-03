def saddle_points(matrix):
    if len(matrix) == 0 or len(matrix[0]) == 0:
        return []

    if any(len(row) != len(matrix[0]) for row in matrix):
        raise ValueError(r".+")

    rows = len(matrix)
    cols = len(matrix[0])
    
    # Pre-compute row maxima and column minima
    row_maxima = [max(matrix[row]) for row in range(rows)]
    col_minima = [min(matrix[row][col] for row in range(rows)) for col in range(cols)]
    
    saddle_points_list = []
    
    # Check each position once
    for row in range(rows):
        for col in range(cols):
            val = matrix[row][col]
            if val == row_maxima[row] and val == col_minima[col]:
                saddle_points_list.append({"row": row + 1, "column": col + 1})
    
    return saddle_points_list