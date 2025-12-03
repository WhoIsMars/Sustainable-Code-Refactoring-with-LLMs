from itertools import combinations
from re import compile

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
    
    # Early exit for invalid rectangles
    if not (a_r == b_r and a_c == c_c and b_c == d_c and c_r == d_r):
        return False
    
    # Check minimum size
    if d_c - a_c < 2 or d_r - a_r < 2:
        return False
    
    # Pre-compile regex patterns
    horz_len = d_c - a_c - 1
    vert_len = d_r - a_r - 1
    
    horz_pattern = compile(f'\\+[-+]{{{horz_len}}}\\+')
    vert_pattern = compile(f'\\+[|+]{{{vert_len}}}\\+')
    
    # Extract strings once
    top = diagram[a_r][a_c:d_c+1]
    bottom = diagram[d_r][a_c:d_c+1]
    
    # Check horizontal edges first (likely to fail faster)
    if not (horz_pattern.match(top) and horz_pattern.match(bottom)):
        return False
    
    # Build vertical strings more efficiently
    left = ''.join(diagram[row][a_c] for row in range(a_r, d_r+1))
    right = ''.join(diagram[row][d_c] for row in range(a_r, d_r+1))
    
    return vert_pattern.match(left) and vert_pattern.match(right)