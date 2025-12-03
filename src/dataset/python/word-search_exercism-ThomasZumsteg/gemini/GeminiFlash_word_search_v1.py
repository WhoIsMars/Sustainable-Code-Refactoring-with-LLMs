from collections import defaultdict

class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))


class WordSearch(object):
    dirs = ((0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1))

    def __init__(self, puzzle):
        self.puzzle = puzzle
        self._hashes = self._build_hashes()

    def _build_hashes(self):
        hashes = defaultdict(list)
        rows = len(self.puzzle)
        cols = len(self.puzzle[0]) if rows > 0 else 0

        for r in range(rows):
            for c in range(cols):
                for word, end in self._words_starting_from(c, r):
                    hashes[word].append((Point(c, r), end))
        return dict(hashes)

    def _words_starting_from(self, start_x, start_y):
        char = self.puzzle[start_y][start_x]
        yield (char, Point(start_x, start_y))

        rows = len(self.puzzle)
        cols = len(self.puzzle[0]) if rows > 0 else 0

        for dx, dy in self.dirs:
            word = char
            x, y = start_x, start_y
            while True:
                x += dx
                y += dy
                if 0 <= y < rows and 0 <= x < cols:
                    word += self.puzzle[y][x]
                    yield (word, Point(x, y))
                else:
                    break

    def search(self, word):
        matches = self._hashes.get(word)
        if matches:
            return matches[0]
        else:
            return None