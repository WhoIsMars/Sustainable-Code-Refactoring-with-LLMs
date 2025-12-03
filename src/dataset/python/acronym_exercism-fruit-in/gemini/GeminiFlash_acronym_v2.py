import re


def abbreviate(words):
    return ''.join(match[0].upper() for match in re.findall(r"\b(\w)", words))