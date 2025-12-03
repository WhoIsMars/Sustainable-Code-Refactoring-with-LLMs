from math import gcd


class Rational:
    __slots__ = ('numer', 'denom')

    def __init__(self, numer, denom):
        if denom == 0:
            raise ValueError("Denominator cannot be zero.")
        common = gcd(numer, denom)
        if denom < 0:
            common = -common
        self.numer = numer // common
        self.denom = denom // common

    def __eq__(self, other):
        return (self.numer, self.denom) == (other.numer, other.denom)

    def __repr__(self):
        return f'{self.numer}/{self.denom}'

    def __add__(self, other):
        numer = self.numer * other.denom + other.numer * self.denom
        denom = self.denom * other.denom
        return Rational(numer, denom)

    def __sub__(self, other):
        numer = self.numer * other.denom - other.numer * self.denom
        denom = self.denom * other.denom
        return Rational(numer, denom)

    def __mul__(self, other):
        return Rational(self.numer * other.numer, self.denom * other.denom)

    def __truediv__(self, other):
        return Rational(self.numer * other.denom, self.denom * other.numer)

    def __abs__(self):
        return Rational(abs(self.numer), abs(self.denom))

    def __pow__(self, power):
        if power < 0:
            return Rational(self.denom ** -power, self.numer ** -power)
        return Rational(self.numer ** power, self.denom ** power)

    def __rpow__(self, base):
        return base ** (self.numer / self.denom)