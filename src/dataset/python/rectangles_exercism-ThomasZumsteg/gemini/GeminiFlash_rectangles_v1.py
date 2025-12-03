from itertools import combinations

def count(diagram=""):
    """count find the number of rectangles in a given diagram"""
    corners = find_char(diagram, '+')
    return sum(1 for rect in combinations(corners, 4) if is_rect(rect, diagram))

def find_char(lines, char):
    """find_char returns the location of all the corner characters"""
    return [ (row, col)
        for row, line in enumerate(lines)
        for col, elem in enumerate(line)
        if elem == char]

def is_rect(corners, diagram):
    """is_rect determines if a set of corners is a rectangle
    by checking alignment and characters between the corners"""
    (a_r, a_c), (b_r, b_c), (c_r, c_c), (d_r, d_c) = sorted(corners)

    if not (a_r == b_r and a_c == c_c and b_c == d_c and c_r == d_r):
        return False

    width = d_c - a_c - 1
    height = d_r - a_r - 1

    # Pre-check width and height for validity
    if width < 0 or height < 0:
        return False

    # Optimized horizontal and vertical checks using slicing and all()
    top = diagram[a_r][a_c:(d_c+1)]
    bottom = diagram[d_r][a_c:(d_c+1)]
    left = [row[a_c] for row in diagram[a_r:(d_r+1)]]
    right = [row[d_c] for row in diagram[a_r:(d_r+1)]]

    if len(top) != d_c - a_c + 1 or len(bottom) != d_c - a_c + 1 or len(left) != d_r - a_r + 1 or len(right) != d_r - a_r + 1:
        return False

    if not all(c in '-+' for c in top[1:-1]) or not all(c in '-+' for c in bottom[1:-1]):
        return False

    if not all(c in '|+ ' for c in left[1:-1]) or not all(c in '|+ ' for c in right[1:-1]):
        return False

    return True