def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    row_len = len(matrix[0])
    if any(len(row) != row_len for row in matrix):
        raise ValueError("Irregular matrix")

    saddle_points_set = set()
    for row_idx, row in enumerate(matrix):
        max_val = max(row)
        for col_idx, val in enumerate(row):
            if val == max_val:
                is_saddle = True
                for k in range(len(matrix)):
                    if matrix[k][col_idx] < val:
                        is_saddle = False
                        break
                if is_saddle:
                    saddle_points_set.add((row_idx + 1, col_idx + 1))

    return [{"row": row, "column": col} for row, col in saddle_points_set]