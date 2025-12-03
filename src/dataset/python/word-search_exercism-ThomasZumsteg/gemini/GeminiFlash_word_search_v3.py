from collections import defaultdict
from itertools import product

class Point(object):
    __slots__ = ('x', 'y')

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))


class WordSearch(object):
    dirs = tuple(prod for prod in product((0, 1, -1), repeat=2) if prod != (0,0))

    def __init__(self, puzzle):
        self._puzzle = puzzle
        self._height = len(puzzle)
        self._width = len(puzzle[0]) if self._height > 0 else 0
        self._hashes = self._build_hashes()

    def _build_hashes(self):
        hashes = defaultdict(list)
        for r in range(self._height):
            for c in range(self._width):
                start = Point(c, r)
                for word, end in self._words_starting_from(start):
                    hashes[word].append((start, end))
        return dict(hashes)

    def _words_starting_from(self, start):
        char = self._puzzle[start.y][start.x]
        yield (char, start)
        queue = [(char, start.x, start.y, diff) for diff in self.dirs]
        while queue:
            word, x, y, diff = queue.pop()
            new_x, new_y = x + diff[0], y + diff[1]
            if 0 <= new_y < self._height and 0 <= new_x < self._width:
                next_char = self._puzzle[new_y][new_x]
                new_word = word + next_char
                yield (new_word, Point(new_x, new_y))
                queue.append((new_word, new_x, new_y, diff))

    def search(self, word):
        matches = self._hashes.get(word)
        if matches:
            assert len(matches) == 1
            return matches[0]
        else:
            return None