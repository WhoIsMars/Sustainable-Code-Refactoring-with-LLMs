from itertools import combinations

def count(diagram=""):
    """count find the number of rectangles in a given diagram"""
    if not diagram:
        return 0
    
    corners = find_char(diagram, '+')
    if len(corners) < 4:
        return 0
    
    return sum(1 for rect in combinations(corners, 4) if is_rect(rect, diagram))

def find_char(lines, char):
    """find_char returns the location of all the corner characters"""
    corners = []
    for row, line in enumerate(lines):
        for col, elem in enumerate(line):
            if elem == char:
                corners.append((row, col))
    return corners

def is_rect(corners, diagram):
    """is_rect determines if a set of corners is a rectangle
    by checking alignment and characters between the corners"""
    (a_r, a_c), (b_r, b_c), (c_r, c_c), (d_r, d_c) = sorted(corners)
    
    # Quick alignment check
    if not (a_r == b_r and a_c == c_c and b_c == d_c and c_r == d_r):
        return False
    
    # Check if rectangle has valid dimensions
    width = d_c - a_c
    height = d_r - a_r
    if width < 2 or height < 2:
        return False
    
    # Check horizontal edges (top and bottom)
    for col in range(a_c + 1, d_c):
        if diagram[a_r][col] not in '-+' or diagram[d_r][col] not in '-+':
            return False
    
    # Check vertical edges (left and right)
    for row in range(a_r + 1, d_r):
        if diagram[row][a_c] not in '|+' or diagram[row][d_c] not in '|+':
            return False
    
    return True