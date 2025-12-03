"""Encodes and decodes text using the atbash cipher"""
import re

def decode(cipher_text):
    """Decodes atbash cipher text"""
    return ''.join(cipher_gen(cipher_text))

def encode(clear_text):
    """Encodes atbash cipher text,
    spaces added after every 5 characters to hide word boundaries"""
    result = []
    count = 0
    for char in cipher_gen(clear_text):
        result.append(char)
        count += 1
        if count == 5:
            result.append(' ')
            count = 0
    return ''.join(result).rstrip()

def cipher_gen(text):
    """Strips whitespace and punctuation, converts to lower case,
    and translates a->z, b->y, ... z->a"""
    text = re.sub(r'\W', '', text).lower()
    for char in text:
        if '0' <= char <= '9':
            yield char
        else:
            yield chr(219 - ord(char))