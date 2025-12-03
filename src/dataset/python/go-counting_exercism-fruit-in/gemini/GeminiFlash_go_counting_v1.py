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
        adjacent_stones = set()
        territory = set()
        visited = set()

        while stones:
            x, y = stones.pop()

            if (x, y) in visited:
                continue
            visited.add((x, y))

            if self.board[y][x] == NONE:
                territory.add((x, y))
                neighbors = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]
                for nx, ny in neighbors:
                    if 0 <= nx < self.width and 0 <= ny < self.height:
                        if (nx, ny) not in visited:
                            stones.append((nx, ny))
            else:
                adjacent_stones.add(self.board[y][x])

        if not adjacent_stones:
            stone = NONE
        elif len(adjacent_stones) == 1:
            stone = adjacent_stones.pop()
        else:
            stone = NONE

        return (stone, territory)

    def territories(self):
        territories = {BLACK: set(), WHITE: set(), NONE: set()}
        visited = set()

        for y in range(self.height):
            for x in range(self.width):
                if (x, y) not in visited:
                    stone, territory = self.territory(x, y)
                    if territory:
                        territories[stone].update(territory)
                        visited.update(territory)
        return territories