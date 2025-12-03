"""A 2 dimentional matrix object"""

class Matrix(object):
    """Creates a 2d matrix object with accessable rows and columns"""

    def __init__(self, matrix):
        """Copy of the input data"""
        self.matrix = matrix

    @property
    def rows(self):
        """Matrix displayed as rows, coumns"""
        if not hasattr(self, '_rows'):
            rows = []
            for row in self.matrix.splitlines():
                rows.append([int(n) for n in row.split()])
            self._rows = rows
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns, rows"""
        if not hasattr(self, '_columns'):
            rows = self.rows  # Access already computed rows
            num_cols = len(rows[0])
            columns = [[] for _ in range(num_cols)]
            for row in rows:
                for i, item in enumerate(row):
                    columns[i].append(item)
            self._columns = columns
        return self._columns