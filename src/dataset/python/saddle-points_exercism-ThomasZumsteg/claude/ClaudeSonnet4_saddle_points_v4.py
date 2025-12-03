"""Finds saddle points in a rectangular 2d array"""

def saddle_points(matrix):
    """Finds points that are the largest in their row
    and smallest in their column
    """
    if not matrix or not matrix[0]:
        return set()
    
    saddles = set()
    num_cols = len(matrix[0])
    
    # Pre-compute all row maxima and column minima
    row_maxima = [max(row) for row in matrix]
    col_minima = [min(matrix[r][c] for r in range(len(matrix))) for c in range(num_cols)]
    
    # Find saddle points by comparing pre-computed values
    for r in range(len(matrix)):
        row_max = row_maxima[r]
        for c in range(num_cols):
            if row_max == col_minima[c]:
                saddles.add((r, c))
    
    return saddles