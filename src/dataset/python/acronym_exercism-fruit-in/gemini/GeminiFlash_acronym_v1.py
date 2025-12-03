import re


def abbreviate(words):
    return ''.join(char.upper() for char in re.findall(r"\b\w", words))