"""Fills in number on a minesweeper board"""

from re import match

def validate_and_format(func):
    """Finds bad boards and formats function return"""
    def minesweeper(minefield):
        """Finds bad boards and formats function returns"""
        width = len(minefield[0])
        row_regex = rf'^\|[* ]{{{width-2}}}\|$'
        cap_regex = rf'^\+-{{{width-2}}}\+$'
        if not (all(match(row_regex, row) for row in minefield[1:-1]) and
                match(cap_regex, minefield[0]) and
                match(cap_regex, minefield[-1])):
            raise ValueError
        minefield = [list(row) for row in minefield]
        return [''.join(row) for row in func(minefield)]
    return minesweeper

@validate_and_format
def board(minefield):
    """Fills in numbers on a minesweeper board"""
    height, width = len(minefield), len(minefield[0])
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            if minefield[i][j] == "*":
                for m, n in ((i-1, j-1), (i-1, j), (i-1, j+1),
                             (i, j-1),           (i, j+1),
                             (i+1, j-1), (i+1, j), (i+1, j+1)):
                    if minefield[m][n] == ' ':
                        minefield[m][n] = '1'
                    elif minefield[m][n].isdigit():
                        minefield[m][n] = str(int(minefield[m][n]) + 1)
    return minefield