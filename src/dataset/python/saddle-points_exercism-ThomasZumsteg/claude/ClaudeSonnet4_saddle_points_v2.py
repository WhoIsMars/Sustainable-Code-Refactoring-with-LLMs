"""Finds saddle points in a rectangular 2d array"""

def saddle_points(matrix):
    """Finds points that are the largest in their row
    and smallest in their column
    """
    if not matrix or not matrix[0]:
        return set()
    
    rows = len(matrix)
    cols = len(matrix[0])
    
    # Pre-compute row maxima and column minima
    row_max = [max(row) for row in matrix]
    col_min = [min(matrix[r][c] for r in range(rows)) for c in range(cols)]
    
    saddles = set()
    for r in range(rows):
        for c in range(cols):
            if row_max[r] == col_min[c]:
                saddles.add((r, c))
    
    return saddles