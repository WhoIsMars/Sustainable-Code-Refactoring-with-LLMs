"""Fills in number on a minesweeper board"""

import re

def validate_and_format(func):
    """Finds bad boards and formats function return"""
    def minesweeper(minefield):
        """Finds bad boards and formats function returns"""
        width = len(minefield[0])
        row_regex = re.compile(rf'^\|[* ]{{{width-2}}}\|$')
        cap_regex = re.compile(rf'^\+-{{{width-2}}}\+$')
        if not all(row_regex.match(row) for row in minefield[1:-1]) or \
           not cap_regex.match(minefield[0]) or \
           not cap_regex.match(minefield[-1]):
            raise ValueError
        minefield = [list(row) for row in minefield]
        return [''.join(row) for row in func(minefield)]
    return minesweeper

@validate_and_format
def board(minefield):
    """Fills in numbers on a minesweeper board"""
    directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    for i, row in enumerate(minefield[1:-1], 1):
        for j, char in enumerate(row[1:-1], 1):
            if char == "*":
                for dx, dy in directions:
                    ni, nj = i + dx, j + dy
                    if minefield[ni][nj] == ' ':
                        minefield[ni][nj] = '1'
                    elif minefield[ni][nj].isdigit():
                        minefield[ni][nj] = str(int(minefield[ni][nj]) + 1)
    return minefield