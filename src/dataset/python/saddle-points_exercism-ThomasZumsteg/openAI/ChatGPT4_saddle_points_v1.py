"""Finds saddle points in a rectangular 2d array"""

def saddle_points(matrix):
    """Finds points that are the largest in their row
    and smallest in their column
    """
    if not matrix or not all(len(row) == len(matrix[0]) for row in matrix):
        raise ValueError("Matrix must be non-empty and rectangular")

    saddles = set()
    min_col = [min(row[c] for row in matrix) for c in range(len(matrix[0]))]

    for r, row in enumerate(matrix):
        max_row = max(row)
        for c, value in enumerate(row):
            if value == max_row and value == min_col[c]:
                saddles.add((r, c))
    return saddles