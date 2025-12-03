def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    row_len = len(matrix[0])
    if any(len(row) != row_len for row in matrix):
        raise ValueError("Irregular matrix")

    saddle_points_set = set()
    for i in range(len(matrix)):
        for j in range(row_len):
            val = matrix[i][j]
            if all(val >= matrix[i][k] for k in range(row_len)) and all(val <= matrix[k][j] for k in range(len(matrix))):
                saddle_points_set.add((i + 1, j + 1))

    return [{"row": row, "column": col} for row, col in saddle_points_set]