WHITE, BLACK, NONE = "W", "B", " "


class Board:

    def __init__(self, board):
        self.board = [list(row) for row in board]
        self.rows = len(self.board)
        self.cols = len(self.board[0])
        self.visited = set()

    def territory(self, x, y):
        if not (0 <= x < self.cols and 0 <= y < self.rows):
            raise ValueError(r".+")
        if (x, y) in self.visited or self.board[y][x] != NONE:
            return (NONE, set())

        queue = [(x, y)]
        territory = set()
        borders = set()
        self.visited.add((x, y))

        while queue:
            cx, cy = queue.pop()
            territory.add((cx, cy))
            for nx, ny in [(cx - 1, cy), (cx + 1, cy), (cx, cy - 1), (cx, cy + 1)]:
                if 0 <= nx < self.cols and 0 <= ny < self.rows:
                    if (nx, ny) not in self.visited:
                        self.visited.add((nx, ny))
                        if self.board[ny][nx] == NONE:
                            queue.append((nx, ny))
                        else:
                            borders.add(self.board[ny][nx])

        owner = borders.pop() if len(borders) == 1 else NONE
        return (owner, territory)

    def territories(self):
        territories = {BLACK: set(), WHITE: set(), NONE: set()}

        for y in range(self.rows):
            for x in range(self.cols):
                if (x, y) not in self.visited and self.board[y][x] == NONE:
                    owner, territory = self.territory(x, y)
                    territories[owner].update(territory)

        return territories