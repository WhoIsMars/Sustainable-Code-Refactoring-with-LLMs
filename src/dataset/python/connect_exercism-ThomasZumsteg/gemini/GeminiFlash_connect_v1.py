class ConnectGame:
    def __init__(self, board):
        self._board = [line.split() for line in board.splitlines()]
        self._rows = len(self._board)
        self._cols = len(self._board[0]) if self._rows > 0 else 0
        self._players = {}
        self._players['X'] = (
            tuple((0, r) for r in range(self._rows)),
            tuple((self._cols - 1, r) for r in range(self._rows))
        )
        self._players['O'] = (
            tuple((c, 0) for c in range(self._cols)),
            tuple((c, self._rows - 1) for c in range(self._cols))
        )

    def get_winner(self):
        for player in self._players.keys():
            if self._find_path(player):
                return player
        return ''

    def _find_path(self, player):
        start, end = self._players[player]
        queue = list(start)
        seen = set()

        while queue:
            x, y = queue.pop()
            if (x, y) in seen:
                continue
            seen.add((x, y))

            if not (0 <= y < self._rows and 0 <= x < self._cols and self._board[y][x] == player):
                continue

            if (x, y) in end:
                return True

            neighbors = [(x + 0, y - 1), (x + 1, y - 1), (x - 1, y + 0),
                         (x + 1, y + 0), (x - 1, y + 1), (x + 0, y + 1)]

            for nx, ny in neighbors:
                if 0 <= ny < self._rows and 0 <= nx < self._cols and self._board[ny][nx] == player and (nx, ny) not in seen:
                    queue.insert(0, (nx, ny))  # Prioritize depth-first for faster path finding

        return False