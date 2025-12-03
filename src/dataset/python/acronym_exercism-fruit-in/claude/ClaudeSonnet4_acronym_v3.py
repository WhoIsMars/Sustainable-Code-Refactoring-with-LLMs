import re


def abbreviate(words):
    pattern = re.compile(r"[A-Za-z]+(?:'[a-z]*)?")
    
    return ''.join(match[0].upper() for match in pattern.findall(words))