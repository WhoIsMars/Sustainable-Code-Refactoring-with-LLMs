from itertools import combinations

def count(diagram=""):
    """count find the number of rectangles in a given diagram"""
    corners = find_char(diagram)
    return sum(1 for rect in combinations(corners, 4) if is_rect(rect, diagram))

def find_char(lines):
    """find_char returns the location of all the corner characters"""
    return [ (row, col)
        for row, line in enumerate(lines)
        for col, elem in enumerate(line)
        if elem == '+']

def is_rect(corners, diagram):
    """is_rect determines if a set of corners is a rectangle
    by checking alignment and characters between the corners"""
    (a_r, a_c), (b_r, b_c), (c_r, c_c), (d_r, d_c) = sorted(corners)

    if not (a_r == b_r and a_c == c_c and b_c == d_c and c_r == d_r):
        return False

    width = d_c - a_c - 1
    height = d_r - a_r - 1

    # Check horizontal lines
    for col in range(a_c + 1, d_c):
        if diagram[a_r][col] != '-' and diagram[a_r][col] != '+':
            return False
        if diagram[d_r][col] != '-' and diagram[d_r][col] != '+':
            return False

    # Check vertical lines
    for row in range(a_r + 1, d_r):
        if diagram[row][a_c] != '|' and diagram[row][a_c] != '+':
            return False
        if diagram[row][d_c] != '|' and diagram[row][d_c] != '+':
            return False

    return True