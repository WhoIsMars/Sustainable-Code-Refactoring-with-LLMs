from itertools import groupby
from re import findall


def decode(string):
    decompressed = []
    for count_str, char in findall(r'(\d*)(\D)', string):
        count = int(count_str) if count_str else 1
        decompressed.append(char * count)
    return ''.join(decompressed)


def encode(string):
    compressed = []
    for char, group in groupby(string):
        count = sum(1 for _ in group)
        compressed.append(char if count == 1 else str(count) + char)
    return ''.join(compressed)