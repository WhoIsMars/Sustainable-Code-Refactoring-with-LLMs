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
            self._rows = [list(map(int, row.split())) 
                         for row in self.matrix.split("\n")]
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns, rows"""
        if self._columns is None:
            rows = self.rows
            self._columns = list(map(list, zip(*rows)))
        return self._columns