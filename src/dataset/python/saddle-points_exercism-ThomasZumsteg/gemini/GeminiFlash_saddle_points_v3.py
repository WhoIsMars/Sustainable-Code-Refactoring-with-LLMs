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
    row_maxima = [max(row) for row in matrix]
    col_minima = [min(matrix[i][j] for i in range(rows)) for j in range(cols)]

    for r in range(rows):
        for c in range(cols):
            if matrix[r][c] == row_maxima[r] and matrix[r][c] == col_minima[c]:
                saddles.add((r, c))

    return saddles