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
        visited = set()

        while stones:
            curr_x, curr_y = stones.pop()

            if (curr_x, curr_y) in visited:
                continue

            visited.add((curr_x, curr_y))

            if self.board[curr_y][curr_x] == NONE:
                territory.add((curr_x, curr_y))

                neighbors = [(curr_x + 1, curr_y), (curr_x - 1, curr_y),
                             (curr_x, curr_y + 1), (curr_x, curr_y - 1)]

                for nx, ny in neighbors:
                    if 0 <= nx < self.width and 0 <= ny < self.height and (nx, ny) not in visited:
                        stones.append((nx, ny))
            else:
                stone_colors.add(self.board[curr_y][curr_x])

        stone = NONE if len(stone_colors) != 1 else stone_colors.pop()

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