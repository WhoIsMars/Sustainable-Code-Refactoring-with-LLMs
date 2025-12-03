from itertools import groupby
import re


def decode(string):
    decompressed = []
    for count, char in re.findall(r'(\d*)(\D)', string):
        num = int(count) if count else 1
        decompressed.append(char * num)
    return ''.join(decompressed)


def encode(string):
    compressed = []
    for char, group in groupby(string):
        count = sum(1 for _ in group)
        compressed.append(char if count == 1 else str(count) + char)
    return ''.join(compressed)