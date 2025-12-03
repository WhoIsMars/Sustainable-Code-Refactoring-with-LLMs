from __future__ import division
import math


class Rational(object):
    def __init__(self, numer, denom):
        if denom == 0:
            raise ZeroDivisionError("Denominator cannot be zero")
        
        gcd = math.gcd(abs(numer), abs(denom))
        if denom < 0:
            numer, denom = -numer, -denom
        
        self.numer = numer // gcd
        self.denom = denom // gcd

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
        return Rational(self.numer * other.numer, self.denom * other.denom)

    def __truediv__(self, other):
        return Rational(self.numer * other.denom, self.denom * other.numer)

    def __abs__(self):
        return Rational(abs(self.numer), self.denom)

    def __pow__(self, power):
        if power == 0:
            return Rational(1, 1)
        elif power < 0:
            return Rational(self.denom ** (-power), self.numer ** (-power))
        else:
            return Rational(self.numer ** power, self.denom ** power)

    def __rpow__(self, base):
        return base ** (self.numer / self.denom)