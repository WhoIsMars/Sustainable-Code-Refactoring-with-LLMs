import string

def encode(plain_text):
    encoded = decode(plain_text.lower())
    return ' '.join((encoded[i:i+5] for i in range(0, len(encoded), 5)))

def decode(ciphered_text):
    translation_table = {
        char: chr(219 - ord(char)) for char in string.ascii_lowercase
    }
    result = []
    for char in ciphered_text:
        if 'a' <= char <= 'z':
            result.append(translation_table[char])
        elif '0' <= char <= '9':
            result.append(char)
    return ''.join(result)