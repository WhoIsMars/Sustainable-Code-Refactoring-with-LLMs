from itertools import groupby
from re import findall


def decode(string):
    result = []
    
    for c, k in findall(r'(\d*)(\D)', string):
        count = int(c) if c else 1
        result.append(k * count)
    
    return ''.join(result)


def encode(string):
    result = []
    
    for k, g in groupby(string):
        count = sum(1 for _ in g)
        if count == 1:
            result.append(k)
        else:
            result.append(str(count) + k)
    
    return ''.join(result)