class Matrix:
    def __init__(self, matrix_string):
        lines = matrix_string.split('\n')
        self.matrix = [list(map(int, line.split())) for line in lines]
        self._num_rows = len(self.matrix)
        self._num_cols = len(self.matrix[0]) if self._num_rows > 0 else 0

    def row(self, index):
        return self.matrix[index - 1]

    def column(self, index):
        col_index = index - 1
        return [self.matrix[i][col_index] for i in range(self._num_rows)]