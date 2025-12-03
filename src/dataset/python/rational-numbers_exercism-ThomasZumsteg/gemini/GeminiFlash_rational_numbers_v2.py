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
        g = gcd(numer, denom)
        return Rational(numer // g, denom // g)

    def __sub__(self, other):
        numer = self.numer * other.denom - other.numer * self.denom
        denom = self.denom * other.denom
        g = gcd(numer, denom)
        return Rational(numer // g, denom // g)

    def __mul__(self, other):
        numer = self.numer * other.numer
        denom = self.denom * other.denom
        g = gcd(numer, denom)
        return Rational(numer // g, denom // g)

    def __truediv__(self, other):
        return Rational(self.numer * other.denom, self.denom * other.numer)

    def __abs__(self):
        return Rational(abs(self.numer), self.denom)

    def __pow__(self, power):
        if power < 0:
            numer, denom = self.denom, self.numer
            power = -power
        else:
            numer, denom = self.numer, self.denom
        return Rational(numer ** power, denom ** power)

    def __rpow__(self, base):
        return base ** (self.numer / self.denom)