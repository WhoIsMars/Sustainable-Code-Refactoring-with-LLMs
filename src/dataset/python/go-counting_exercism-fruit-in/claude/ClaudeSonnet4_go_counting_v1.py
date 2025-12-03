WHITE, BLACK, NONE = "W", "B", " "


class Board:

    def __init__(self, board):
        self.board = [list(row) for row in board]
        self.height = len(self.board)
        self.width = len(self.board[0]) if self.height > 0 else 0

    def territory(self, x, y):
        if x < 0 or x >= self.width or y < 0 or y >= self.height:
            raise ValueError(r".+")
        if self.board[y][x] != NONE:
            return (NONE, set())

        stones = [(x, y)]
        stone = set()
        seen = set()
        territory = set()

        while stones:
            x, y = stones.pop()
            if (x, y) in seen:
                continue
            seen.add((x, y))
            
            if self.board[y][x] == NONE:
                territory.add((x, y))
                # Add neighbors
                if x > 0:
                    stones.append((x - 1, y))
                if x < self.width - 1:
                    stones.append((x + 1, y))
                if y > 0:
                    stones.append((x, y - 1))
                if y < self.height - 1:
                    stones.append((x, y + 1))
            else:
                stone.add(self.board[y][x])

        stone = NONE if len(stone) != 1 else next(iter(stone))

        return (stone, territory)

    def territories(self):
        territories = {BLACK: set(), WHITE: set(), NONE: set()}
        visited = set()

        for y in range(self.height):
            for x in range(self.width):
                if (x, y) not in visited:
                    stone, territory = self.territory(x, y)
                    territories[stone].update(territory)
                    visited.update(territory)

        return territories