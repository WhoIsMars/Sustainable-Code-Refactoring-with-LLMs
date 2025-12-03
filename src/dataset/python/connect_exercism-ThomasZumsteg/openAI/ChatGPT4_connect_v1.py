class ConnectGame:
    def __init__(self, board):
        self._board = [line.split() for line in board.splitlines()]
        self._players = {
            'X': (
                {(0, r) for r in range(len(self._board))},
                {(len(row) - 1, r) for r, row in enumerate(self._board)}
            ),
            'O': (
                {(c, 0) for c in range(len(self._board[0]))},
                {(c, len(self._board) - 1) for c in range(len(self._board[0]))}
            )
        }

    def get_winner(self):
        for player, (start, end) in self._players.items():
            if self._find_path(player, start, end):
                return player
        return ''

    def _find_path(self, player, start, end):
        stack = list(start)
        seen = set()
        directions = ((0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1))
        while stack:
            x, y = stack.pop()
            if (x, y) in seen or not (0 <= y < len(self._board) and 0 <= x < len(self._board[0])):
                continue
            seen.add((x, y))
            if self._board[y][x] != player:
                continue
            if (x, y) in end:
                return True
            stack.extend((x + dx, y + dy) for dx, dy in directions if (x + dx, y + dy) not in seen)
        return False