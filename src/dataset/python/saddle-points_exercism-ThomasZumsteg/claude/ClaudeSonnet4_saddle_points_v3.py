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
            raise ValueError
    
    row_maxes = [max(row) for row in matrix]
    col_mins = [min(matrix[r][c] for r in range(rows)) for c in range(cols)]
    
    saddles = set()
    for r in range(rows):
        for c in range(cols):
            if row_maxes[r] == col_mins[c]:
                saddles.add((r, c))
    
    return saddles