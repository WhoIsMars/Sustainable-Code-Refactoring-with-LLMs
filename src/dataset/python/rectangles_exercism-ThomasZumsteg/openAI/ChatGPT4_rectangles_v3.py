from itertools import combinations
from re import fullmatch

def count(diagram=""):
    """count find the number of rectangles in a given diagram"""
    corners = find_char(diagram, '+')
    return sum(is_rect(rect, diagram) for rect in combinations(corners, 4))

def find_char(lines, char):
    """find_char returns the location of all the corner characters"""
    return [(row, col) for row, line in enumerate(lines) for col, elem in enumerate(line) if elem == char]

def is_rect(corners, diagram):
    """is_rect determines if a set of corners is a rectangle
    by checking alignment and characters between the corners"""
    (a_r, a_c), (b_r, b_c), (c_r, c_c), (d_r, d_c) = sorted(corners)
    if a_r != b_r or a_c != c_c or b_c != d_c or c_r != d_r:
        return False

    top = diagram[a_r][a_c:d_c + 1]
    bottom = diagram[d_r][a_c:d_c + 1]
    left = ''.join(row[a_c] for row in diagram[a_r:d_r + 1])
    right = ''.join(row[d_c] for row in diagram[a_r:d_r + 1])

    horz_pattern = f"+{'-' * (d_c - a_c - 1)}+"
    vert_pattern = f"+{'|' * (d_r - a_r - 1)}+"

    return (fullmatch(horz_pattern, top) and fullmatch(horz_pattern, bottom) and
            fullmatch(vert_pattern, left) and fullmatch(vert_pattern, right))