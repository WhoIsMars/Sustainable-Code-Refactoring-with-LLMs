"""Encodes and decodes text using the atbash cipher"""
import re

def decode(cipher_text):
    """Decodes atbash cipher text"""
    return "".join(cipher_gen(cipher_text))

def encode(clear_text):
    """Encodes atbash cipher text,
    spaces added after every 5 characters to hide word boundaries"""
    cipher = "".join(cipher_gen(clear_text))
    return " ".join(cipher[i:i+5] for i in range(0, len(cipher), 5))

def cipher_gen(text):
    """Strips whitespace and punctuation, converts to lower case,
    and translates a->z, b->y, ... z->a"""
    text = re.sub(r'\W', '', text).lower()
    for char in text:
        if '0' <= char <= '9':
            yield char
        elif 'a' <= char <= 'z':
            yield chr(219 - ord(char))