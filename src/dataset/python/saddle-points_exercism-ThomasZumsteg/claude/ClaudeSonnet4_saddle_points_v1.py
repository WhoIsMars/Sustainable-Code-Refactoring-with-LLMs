"""Finds saddle points in a rectangular 2d array"""

def saddle_points(matrix):
    """Finds points that are the largest in their row
    and smallest in their column
    """
    if not matrix:
        return set()
    
    # Validate matrix structure once
    row_length = len(matrix[0])
    if not all(len(row) == row_length for row in matrix):
        raise ValueError
    
    saddles = set()
    
    # Pre-compute all row maxima and column minima
    row_maxima = [max(row) for row in matrix]
    col_minima = [min(matrix[r][c] for r in range(len(matrix))) for c in range(row_length)]
    
    # Find saddle points by comparing pre-computed values
    for r in range(len(matrix)):
        row_max = row_maxima[r]
        for c in range(row_length):
            if row_max == col_minima[c]:
                saddles.add((r, c))
    
    return saddles