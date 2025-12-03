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
                          for row in self.matrix.split("\n") if row.strip()]
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns, rows"""
        if self._columns is None:
            rows = self.rows
            if rows:
                self._columns = [[rows[j][i] for j in range(len(rows))]
                                for i in range(len(rows[0]))]
            else:
                self._columns = []
        return self._columns