def rotate(text, key):
    def encode_single(char, key):
        if char.isalpha():
            base = 65 if char.isupper() else 97
            return chr((ord(char) - base + key) % 26 + base)
        return char

    return ''.join(encode_single(c, key) for c in text)