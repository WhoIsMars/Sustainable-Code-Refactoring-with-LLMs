def saddle_points(matrix):
    if not matrix or not matrix[0]:
        return []

    row_len = len(matrix[0])
    if any(len(row) != row_len for row in matrix):
        raise ValueError(r".+")

    saddle_points_set = set()

    for row_idx, row in enumerate(matrix):
        max_val = float('-inf')
        max_cols = []
        for col_idx, val in enumerate(row):
            if val > max_val:
                max_val = val
                max_cols = [col_idx]
            elif val == max_val:
                max_cols.append(col_idx)

        for col_idx in max_cols:
            min_in_col = True
            for row_idx2, row2 in enumerate(matrix):
                if matrix[row_idx2][col_idx] < max_val:
                    min_in_col = False
                    break
            if min_in_col:
                saddle_points_set.add((row_idx + 1, col_idx + 1))

    return [{"row": row, "column": col} for row, col in saddle_points_set]