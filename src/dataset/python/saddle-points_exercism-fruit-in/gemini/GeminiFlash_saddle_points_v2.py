def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    row_len = len(matrix[0])
    if any(len(row) != row_len for row in matrix):
        raise ValueError("Irregular matrix")

    rows = len(matrix)
    cols = row_len
    saddle_points_set = set()

    for r in range(rows):
        max_in_row = matrix[r][0]
        col_indices = [0]

        for c in range(1, cols):
            if matrix[r][c] > max_in_row:
                max_in_row = matrix[r][c]
                col_indices = [c]
            elif matrix[r][c] == max_in_row:
                col_indices.append(c)

        for c in col_indices:
            min_in_col = matrix[0][c]
            is_saddle = True
            for rr in range(1, rows):
                if matrix[rr][c] < min_in_col:
                    is_saddle = False
                    break
            if is_saddle:
                saddle_points_set.add((r + 1, c + 1))

    return [{"row": row, "column": col} for row, col in saddle_points_set]