"""A 2 dimensional matrix object"""

class Matrix(object):
    """Creates a 2d matrix object with accessible rows and columns"""

    def __init__(self, matrix):
        """Copy of the input data"""
        self._rows = [[int(n) for n in row.split()] for row in matrix.split("\n")]
        self._columns = list(map(list, zip(*self._rows)))

    @property
    def rows(self):
        """Matrix displayed as rows"""
        return self._rows

    @property
    def columns(self):
        """Matrix displayed as columns"""
        return self._columns