def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    if any(len(row) != len(matrix[0]) for row in matrix):
        raise ValueError(r".+")

    row_max = {}
    col_min = {}

    for row_idx, row in enumerate(matrix):
        max_val = max(row)
        row_max[row_idx] = {col_idx for col_idx, val in enumerate(row) if val == max_val}

    for col_idx in range(len(matrix[0])):
        min_val = min(matrix[row][col_idx] for row in range(len(matrix)))
        col_min[col_idx] = {row_idx for row_idx in range(len(matrix)) if matrix[row_idx][col_idx] == min_val}

    result = []
    for row_idx, cols in row_max.items():
        for col_idx in cols:
            if row_idx in col_min.get(col_idx, set()):
                result.append({"row": row_idx + 1, "column": col_idx + 1})

    return result