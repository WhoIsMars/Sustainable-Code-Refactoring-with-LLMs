from __future__ import division
from math import gcd


class Rational(object):
    def __init__(self, numer, denom):
        g = gcd(numer, denom)
        if denom < 0:
            g = -g
        self.numer = numer // g
        self.denom = denom // g

    def __eq__(self, other):
        return self.numer == other.numer and self.denom == other.denom

    def __repr__(self):
        return '{}/{}'.format(self.numer, self.denom)

    def __add__(self, other):
        numer = self.numer * other.denom + other.numer * self.denom
        denom = self.denom * other.denom
        return Rational(numer, denom)

    def __sub__(self, other):
        numer = self.numer * other.denom - other.numer * self.denom
        denom = self.denom * other.denom
        return Rational(numer, denom)

    def __mul__(self, other):
        numer = self.numer * other.numer
        denom = self.denom * other.denom
        return Rational(numer, denom)

    def __truediv__(self, other):
        numer = self.numer * other.denom
        denom = self.denom * other.numer
        return Rational(numer, denom)

    def __abs__(self):
        return Rational(abs(self.numer), self.denom)

    def __pow__(self, power):
        if power < 0:
            return Rational(self.denom ** abs(power), self.numer ** abs(power))
        return Rational(self.numer ** power, self.denom ** power)

    def __rpow__(self, base):
        return base ** (self.numer / self.denom)