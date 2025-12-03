"""Finds saddle points in a rectangular 2d array"""

def saddle_points(matrix):
    """Finds points that are the largest in their row
    and smallest in their column
    """
    if not matrix or not matrix[0]:
        return set()

    rows = len(matrix)
    cols = len(matrix[0])

    for row in matrix:
        if len(row) != cols:
            raise ValueError("Irregular matrix")

    saddles = set()
    min_in_cols = [float('inf')] * cols
    for c in range(cols):
        for r in range(rows):
            min_in_cols[c] = min(min_in_cols[c], matrix[r][c])

    for r in range(rows):
        max_in_row = float('-inf')
        col_index = -1

        for c in range(cols):
            if matrix[r][c] > max_in_row:
                max_in_row = matrix[r][c]
                col_index = c

        if max_in_row == min_in_cols[col_index]:
            saddles.add((r, col_index))

    return saddles