"""Encodes and decodes text using the atbash cipher"""
from re import sub

def decode(cipher_text):
    """Decodes atbash cipher text"""
    return ''.join(cipher_gen(cipher_text))

def encode(clear_text):
    """Encodes atbash cipher text,
    spaces added after every 5 characters to hide word boundaries"""
    result = []
    for num, char in enumerate(cipher_gen(clear_text), 1):
        result.append(char)
        if num % 5 == 0:
            result.append(' ')
    return ''.join(result).rstrip()

def cipher_gen(text):
    """Strips whitespace and punctuation, converts to lower case,
    and translates a->z, b->y, ... z->a"""
    text = sub(r'\W', '', text).lower()
    for char in text:
        if char.isdigit():
            yield char
        else:
            yield chr(219 - ord(char))