"""A 2 dimentional matrix object"""

class Matrix(object):
    """Creates a 2d matrix object with accessable rows and columns"""

    def __init__(self, matrix):
        """Copy of the input data"""
        self._matrix_string = matrix
        self._rows = None
        self._columns = None

    @property
    def rows(self):
        """Matrix displayed as rows, coumns"""
        if self._rows is None:
            self._rows = []
            for row in self._matrix_string.splitlines():
                self._rows.append([int(n) for n in row.split()])
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns, rows"""
        if self._columns is None:
            if not self.rows:  # Ensure rows are processed first
                return []
            num_cols = len(self.rows[0])
            self._columns = [[] for _ in range(num_cols)]
            for row in self.rows:
                for i, item in enumerate(row):
                    self._columns[i].append(item)
        return self._columns