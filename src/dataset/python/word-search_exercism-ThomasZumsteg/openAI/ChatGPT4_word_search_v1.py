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
                for word, end in self._words_starting_from(puzzle, start):
                    if word not in self._hashes:
                        self._hashes[word] = (start, end)

    def _words_starting_from(self, puzzle, start):
        char = puzzle[start.y][start.x]
        yield (char, start)
        for dx, dy in self.dirs:
            x, y = start.x, start.y
            word = char
            while True:
                x, y = x + dx, y + dy
                if 0 <= y < len(puzzle) and 0 <= x < len(puzzle[y]):
                    word += puzzle[y][x]
                    yield (word, Point(x, y))
                else:
                    break

    def search(self, word):
        return self._hashes.get(word, None)