class ConnectGame:
    def __init__(self, board):
        self._board = [line.split() for line in board.splitlines()]
        rows, cols = len(self._board), len(self._board[0])
        self._players = {
            'X': (
                {(0, r) for r in range(rows)},
                {(cols - 1, r) for r in range(rows)}
            ),
            'O': (
                {(c, 0) for c in range(cols)},
                {(c, rows - 1) for c in range(cols)}
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
                if (nx, ny) not in seen and 0 <= ny < len(self._board) and 0 <= nx < len(self._board[ny]) and self._board[ny][nx] == player:
                    seen.add((nx, ny))
                    stack.append((nx, ny))
        return False