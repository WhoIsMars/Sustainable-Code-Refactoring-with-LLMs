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
    max_in_rows = [float('-inf')] * rows

    for r in range(rows):
        for c in range(cols):
            val = matrix[r][c]
            min_in_cols[c] = min(min_in_cols[c], val)
            max_in_rows[r] = max(max_in_rows[r], val)

    for r in range(rows):
        for c in range(cols):
            if matrix[r][c] == max_in_rows[r] and matrix[r][c] == min_in_cols[c]:
                saddles.add((r, c))

    return saddles