"""Encodes and decodes text using the atbash cipher"""
import re

def decode(cipher_text):
    """Decodes atbash cipher text"""
    return ''.join(cipher_gen(cipher_text))

def encode(clear_text):
    """Encodes atbash cipher text,
    spaces added after every 5 characters to hide word boundaries"""
    cipher_text = ''.join(cipher_gen(clear_text))
    return ' '.join(cipher_text[i:i+5] for i in range(0, len(cipher_text), 5))

def cipher_gen(text):
    """Strips whitespace and punctuation, converts to lower case,
    and translates a->z, b->y, ... z->a"""
    atbash = lambda c: chr(219 - ord(c)) if c.isalpha() else c
    return (atbash(char) for char in re.sub(r'\W', '', text.lower()))