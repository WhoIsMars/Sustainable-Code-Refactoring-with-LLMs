"""A 2 dimensional matrix object"""

class Matrix:
    """Creates a 2D matrix object with accessible rows and columns"""

    def __init__(self, matrix):
        """Parse the input data into rows"""
        self._rows = [[int(n) for n in row.split()] for row in matrix.split("\n")]
        self._columns = None

    @property
    def rows(self):
        """Matrix displayed as rows"""
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns"""
        if self._columns is None:
            self._columns = list(map(list, zip(*self._rows)))
        return self._columns