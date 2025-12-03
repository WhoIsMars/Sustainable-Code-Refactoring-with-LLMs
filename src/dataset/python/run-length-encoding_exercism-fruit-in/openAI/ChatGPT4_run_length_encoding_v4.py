from itertools import groupby
from re import finditer


def decode(string):
    return ''.join((int(c) if c else 1) * k for c, k in finditer(r'(\d*)(\D)', string))


def encode(string):
    return ''.join(f"{len(list(g))}{k}" if (count := len(list(g))) > 1 else k for k, g in groupby(string))