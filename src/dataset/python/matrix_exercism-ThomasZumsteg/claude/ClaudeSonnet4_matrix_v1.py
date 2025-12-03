"""A 2 dimentional matrix object"""

class Matrix(object):
    """Creates a 2d matrix object with accessable rows and columns"""

    def __init__(self, matrix):
        """Copy of the input data"""
        self.matrix = matrix
        self._rows = None
        self._columns = None

    @property
    def rows(self):
        """Matrix displayed as rows, coumns"""
        if self._rows is None:
            self._rows = [[int(n) for n in row.split()]
                          for row in self.matrix.split("\n")]
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns, rows"""
        if self._columns is None:
            rows = self.rows
            num_cols = len(rows[0])
            self._columns = [[] for _ in range(num_cols)]
            for row in rows:
                for i, item in enumerate(row):
                    self._columns[i].append(item)
        return self._columns