"""A 2 dimensional matrix object"""

class Matrix:
    """Creates a 2D matrix object with accessible rows and columns"""

    def __init__(self, matrix):
        """Copy of the input data"""
        self._matrix = matrix
        self._rows = None
        self._columns = None

    @property
    def rows(self):
        """Matrix displayed as rows"""
        if self._rows is None:
            self._rows = [list(map(int, row.split())) for row in self._matrix.splitlines()]
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns"""
        if self._columns is None:
            self._columns = list(map(list, zip(*self.rows)))
        return self._columns