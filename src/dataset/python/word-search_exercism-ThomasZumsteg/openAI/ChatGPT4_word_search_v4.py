from itertools import product

class Point:
    __slots__ = ('x', 'y')

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))


class WordSearch:
    dirs = [(dx, dy) for dx, dy in product((0, 1, -1), repeat=2) if dx or dy]

    def __init__(self, puzzle):
        self._hashes = {}
        rows, cols = len(puzzle), len(puzzle[0]) if puzzle else 0
        for r in range(rows):
            for c in range(cols):
                start = Point(c, r)
                for word, end in self._words_starting_from(puzzle, start, rows, cols):
                    if word not in self._hashes:
                        self._hashes[word] = (start, end)

    def _words_starting_from(self, puzzle, start, rows, cols):
        char = puzzle[start.y][start.x]
        yield char, start
        queue = [(char, start.x, start.y, dx, dy) for dx, dy in self.dirs]
        while queue:
            word, x, y, dx, dy = queue.pop()
            x, y = x + dx, y + dy
            if 0 <= y < rows and 0 <= x < cols:
                word += puzzle[y][x]
                yield word, Point(x, y)
                queue.append((word, x, y, dx, dy))

    def search(self, word):
        return self._hashes.get(word, None)