"""Analyzes and creates luhn type codes"""

class Luhn(object):
    """Create and analyze luhn type codes"""

    def __init__(self, number):
        """Initialize a luhn object"""
        self.number_str = str(number)

    def addends(self):
        """Does part of the luhn algorythm"""
        ends = []
        for i, digit_char in enumerate(reversed(self.number_str)):
            digit = int(digit_char)
            if i % 2 == 1:
                digit *= 2
                if digit > 9:
                    digit -= 9
            ends.append(digit)
        ends.reverse()
        return ends

    def checksum(self):
        """Finds the checksum of the luhn code"""
        total = 0
        for i, digit_char in enumerate(reversed(self.number_str)):
            digit = int(digit_char)
            if i % 2 == 1:
                digit *= 2
                if digit > 9:
                    digit -= 9
            total += digit
        return total

    def is_valid(self):
        """Checks if luhn code is valid"""
        return self.checksum() % 10 == 0

    @staticmethod
    def create(number):
        """Creates a valid luhn code"""
        base = 10 * number
        code = Luhn(base)
        return base + (-code.checksum()) % 10