class ConnectGame:
    def __init__(self, board):
        self._board = [line.split() for line in board.splitlines()]
        self._rows = len(self._board)
        self._cols = len(self._board[0])
        self._players = {
            'X': (
                {(0, r) for r in range(self._rows)},
                {(self._cols - 1, r) for r in range(self._rows)}
            ),
            'O': (
                {(c, 0) for c in range(self._cols)},
                {(c, self._rows - 1) for c in range(self._cols)}
            )
        }

    def get_winner(self):
        for player, (start, end) in self._players.items():
            if self._find_path(player, start, end):
                return player
        return ''

    def _find_path(self, player, start, end):
        stack = list(start)
        seen = set(start)
        directions = [(0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1)]
        while stack:
            x, y = stack.pop()
            if (x, y) in end:
                return True
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < self._cols and 0 <= ny < self._rows and (nx, ny) not in seen:
                    if self._board[ny][nx] == player:
                        seen.add((nx, ny))
                        stack.append((nx, ny))
        return False