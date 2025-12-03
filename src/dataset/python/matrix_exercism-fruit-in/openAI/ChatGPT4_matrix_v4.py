class Matrix:
    __slots__ = ('_matrix',)

    def __init__(self, matrix_string):
        self._matrix = [[int(x) for x in row.split()] for row in matrix_string.splitlines()]

    def row(self, index):
        return self._matrix[index - 1]

    def column(self, index):
        idx = index - 1
        return [row[idx] for row in self._matrix]