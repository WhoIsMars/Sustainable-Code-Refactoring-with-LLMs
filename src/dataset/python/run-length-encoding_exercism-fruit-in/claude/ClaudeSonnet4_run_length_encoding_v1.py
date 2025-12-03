from itertools import groupby
from re import findall


def decode(string):
    result = []
    
    for c, k in findall(r'(\d*)(\D)', string):
        if c:
            result.append(int(c) * k)
        else:
            result.append(k)
    
    return ''.join(result)


def encode(string):
    if not string:
        return ''
    
    result = []
    
    for k, g in groupby(string):
        count = sum(1 for _ in g)
        if count == 1:
            result.append(k)
        else:
            result.append(str(count) + k)
    
    return ''.join(result)