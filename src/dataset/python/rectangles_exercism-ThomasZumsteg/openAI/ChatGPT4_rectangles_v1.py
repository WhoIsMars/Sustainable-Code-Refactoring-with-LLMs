from itertools import combinations

def count(diagram=""):
    """count find the number of rectangles in a given diagram"""
    corners = find_char(diagram, '+')
    corner_set = set(corners)
    return sum(1 for rect in combinations(corners, 4) if is_rect(rect, corner_set))

def find_char(lines, char):
    """find_char returns the location of all the corner characters"""
    return [(row, col)
            for row, line in enumerate(lines)
            for col, elem in enumerate(line)
            if elem == char]

def is_rect(corners, corner_set):
    """is_rect determines if a set of corners is a rectangle
    by checking alignment and characters between the corners"""
    (a_r, a_c), (b_r, b_c), (c_r, c_c), (d_r, d_c) = sorted(corners)
    if not (a_r == b_r and c_r == d_r and a_c == c_c and b_c == d_c):
        return False

    if (a_r, d_c) in corner_set and (d_r, a_c) in corner_set:
        for col in range(a_c + 1, d_c):
            if (a_r, col) not in corner_set and (c_r, col) not in corner_set:
                return False
        for row in range(a_r + 1, c_r):
            if (row, a_c) not in corner_set and (row, d_c) not in corner_set:
                return False
        return True
    return False