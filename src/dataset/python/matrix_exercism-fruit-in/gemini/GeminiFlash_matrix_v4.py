class Matrix:
    def __init__(self, matrix_string):
        self.matrix = [[int(x) for x in row.split()] for row in matrix_string.splitlines()]

    def row(self, index):
        return self.matrix[index - 1]

    def column(self, index):
        index -= 1
        return [row[index] for row in self.matrix]