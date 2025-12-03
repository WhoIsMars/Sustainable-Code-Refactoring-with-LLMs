class Matrix:
    def __init__(self, matrix_string):
        self.matrix = [
            [int(x) for x in row.split()]
            for row in matrix_string.split('\n')
        ]

    def row(self, index):
        return self.matrix[index - 1]

    def column(self, index):
        col_index = index - 1
        return [row[col_index] for row in self.matrix]