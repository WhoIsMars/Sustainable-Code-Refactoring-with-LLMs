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
    dirs = [(dx, dy) for dx, dy in product((0, 1, -1), repeat=2) if dx != 0 or dy != 0]

    def __init__(self, puzzle):
        self._hashes = {}
        for r, row in enumerate(puzzle):
            for c, char in enumerate(row):
                start = Point(c, r)
                self._add_words_from(puzzle, start)

    def _add_words_from(self, puzzle, start):
        char = puzzle[start.y][start.x]
        self._hashes.setdefault(char, []).append((start, start))
        for dx, dy in self.dirs:
            x, y = start.x, start.y
            word = char
            while True:
                x, y = x + dx, y + dy
                if 0 <= y < len(puzzle) and 0 <= x < len(puzzle[0]):
                    word += puzzle[y][x]
                    self._hashes.setdefault(word, []).append((start, Point(x, y)))
                else:
                    break

    def search(self, word):
        matches = self._hashes.get(word)
        return matches[0] if matches else None