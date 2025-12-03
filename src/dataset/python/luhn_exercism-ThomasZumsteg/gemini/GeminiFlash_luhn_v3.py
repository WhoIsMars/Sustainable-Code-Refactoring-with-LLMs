"""Analyzes and creates luhn type codes"""

class Luhn(object):
    """Create and analyze luhn type codes"""

    def __init__(self, number):
        """Initialize a luhn object"""
        self.digits = [int(d) for d in str(number)]

    def addends(self):
        """Does part of the luhn algorythm"""
        ends = []
        for i in range(len(self.digits) - 1, -1, -1):
            digit = self.digits[i]
            if (len(self.digits) - 1 - i) % 2 == 1:
                digit *= 2
                if digit > 9:
                    digit -= 9
            ends.insert(0, digit)
        return ends

    def checksum(self):
        """Finds the checksum of the luhn code"""
        return sum(self.addends())

    def is_valid(self):
        """Checks if luhn code is valid"""
        return self.checksum() % 10 == 0

    @staticmethod
    def create(number):
        """Creates a valid luhn code"""
        checksum = sum(Luhn.calculate_addends(10 * number))
        return 10 * number + (-checksum) % 10

    @staticmethod
    def calculate_addends(number):
        """Calculates addends for a given number"""
        digits = [int(d) for d in str(number)]
        ends = []
        for i in range(len(digits) - 1, -1, -1):
            digit = digits[i]
            if (len(digits) - 1 - i) % 2 == 1:
                digit *= 2
                if digit > 9:
                    digit -= 9
            ends.insert(0, digit)
        return ends