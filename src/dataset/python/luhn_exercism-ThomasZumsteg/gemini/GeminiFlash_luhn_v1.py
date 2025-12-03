"""Analyzes and creates luhn type codes"""

class Luhn(object):
    """Create and analyze luhn type codes"""

    def __init__(self, number):
        """Initialize a luhn object"""
        self.digits = [int(d) for d in str(number)]

    def addends(self):
        """Does part of the luhn algorythm"""
        addends = []
        for i, digit in enumerate(reversed(self.digits)):
            if i % 2 == 1:
                digit *= 2
                if digit > 9:
                    digit -= 9
            addends.insert(0, digit)
        return addends

    def checksum(self):
        """Finds the checksum of the luhn code"""
        return sum(self.addends())

    def is_valid(self):
        """Checks if luhn code is valid"""
        return self.checksum() % 10 == 0

    @staticmethod
    def create(number):
        """Creates a valid luhn code"""
        checksum = sum(Luhn(number * 10).addends()) % 10
        return number * 10 + (10 - checksum) % 10