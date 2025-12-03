WHITE, BLACK, NONE = "W", "B", " "


class Board:

    def __init__(self, board):
        self.board = [list(row) for row in board]
        self.height = len(self.board)
        self.width = len(self.board[0])

    def territory(self, x, y):
        if not (0 <= x < self.width and 0 <= y < self.height):
            raise ValueError(r".+")
        if self.board[y][x] != NONE:
            return (NONE, set())

        stack = [(x, y)]
        territory = set()
        borders = set()
        seen = set()

        while stack:
            cx, cy = stack.pop()
            if (cx, cy) in seen:
                continue
            seen.add((cx, cy))
            if self.board[cy][cx] == NONE:
                territory.add((cx, cy))
                for nx, ny in ((cx - 1, cy), (cx + 1, cy), (cx, cy - 1), (cx, cy + 1)):
                    if 0 <= nx < self.width and 0 <= ny < self.height:
                        stack.append((nx, ny))
            else:
                borders.add(self.board[cy][cx])

        owner = NONE if len(borders) != 1 else borders.pop()
        return (owner, territory)

    def territories(self):
        territories = {BLACK: set(), WHITE: set(), NONE: set()}
        visited = set()

        for y in range(self.height):
            for x in range(self.width):
                if (x, y) not in visited and self.board[y][x] == NONE:
                    owner, territory = self.territory(x, y)
                    territories[owner].update(territory)
                    visited.update(territory)

        return territories