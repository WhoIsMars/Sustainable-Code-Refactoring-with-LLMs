WHITE, BLACK, NONE = "W", "B", " "


class Board:

    def __init__(self, board):
        self.board = [list(row) for row in board]
        self.width = len(self.board[0])
        self.height = len(self.board)

    def territory(self, x, y):
        if not (0 <= x < self.width and 0 <= y < self.height):
            raise ValueError(r".+")

        if self.board[y][x] != NONE:
            return (NONE, set())

        stones = [(x, y)]
        stone_colors = set()
        territory = set()
        seen = set()

        while stones:
            x, y = stones.pop()
            if (x, y) in seen:
                continue
            seen.add((x, y))

            if self.board[y][x] == NONE:
                territory.add((x, y))
                neighbors = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]
                for nx, ny in neighbors:
                    if 0 <= nx < self.width and 0 <= ny < self.height and (nx, ny) not in seen:
                        stones.append((nx, ny))
            else:
                stone_colors.add(self.board[y][x])

        if not stone_colors:
            stone = NONE
        elif len(stone_colors) > 1:
            stone = NONE
        else:
            stone = stone_colors.pop()

        return (stone, territory)

    def territories(self):
        territories = {BLACK: set(), WHITE: set(), NONE: set()}
        seen = set()

        for y in range(self.height):
            for x in range(self.width):
                if (x, y) not in seen:
                    stone, territory = self.territory(x, y)
                    if territory:
                        territories[stone].update(territory)
                        seen.update(territory)
        return territories