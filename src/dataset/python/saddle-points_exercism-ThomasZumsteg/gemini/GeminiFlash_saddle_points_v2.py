"""Finds saddle points in a rectangular 2d array"""

def saddle_points(matrix):
    """Finds points that are the largest in their row
    and smallest in their column
    """
    if not matrix or not matrix[0]:
        return set()

    rows = len(matrix)
    cols = len(matrix[0])

    row_maxima = [max(row) for row in matrix]

    col_minima = []
    for c in range(cols):
        col_minima.append(min(matrix[r][c] for r in range(rows)))

    saddles = set()
    for r in range(rows):
        for c in range(cols):
            if matrix[r][c] == row_maxima[r] and matrix[r][c] == col_minima[c]:
                saddles.add((r, c))
    return saddles