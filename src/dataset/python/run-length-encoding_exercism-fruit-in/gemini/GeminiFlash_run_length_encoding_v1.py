from itertools import groupby
import re


def decode(string):
    decompressed = []
    for match in re.finditer(r'(\d*)(\D)', string):
        count_str, char = match.groups()
        count = int(count_str) if count_str else 1
        decompressed.append(char * count)
    return ''.join(decompressed)


def encode(string):
    compressed = []
    for k, g in groupby(string):
        group_list = list(g)
        count = len(group_list)
        if count == 1:
            compressed.append(k)
        else:
            compressed.append(str(count) + k)
    return ''.join(compressed)