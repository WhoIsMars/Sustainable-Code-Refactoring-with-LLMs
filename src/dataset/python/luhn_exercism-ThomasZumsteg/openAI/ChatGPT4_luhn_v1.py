"""Analyzes and creates luhn type codes"""

class Luhn:
    """Create and analyze luhn type codes"""

    def __init__(self, number):
        """Initialize a luhn object"""
        self.digits = list(map(int, str(number)))

    def addends(self):
        """Does part of the luhn algorithm"""
        return [
            digit if i % 2 == 0 else (digit * 2 - 9 if digit * 2 > 9 else digit * 2)
            for i, digit in enumerate(reversed(self.digits))
        ][::-1]

    def checksum(self):
        """Finds the checksum of the luhn code"""
        return sum(self.addends())

    def is_valid(self):
        """Checks if luhn code is valid"""
        return self.checksum() % 10 == 0

    @staticmethod
    def create(number):
        """Creates a valid luhn code"""
        checksum = Luhn(number * 10).checksum()
        return number * 10 + (10 - checksum % 10) % 10