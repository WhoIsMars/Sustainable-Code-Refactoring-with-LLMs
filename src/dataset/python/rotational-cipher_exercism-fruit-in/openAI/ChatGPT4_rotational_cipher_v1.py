def rotate(text, key):
    def encode_single(char, key):
        if 'A' <= char <= 'Z':
            return chr((ord(char) - 65 + key) % 26 + 65)
        elif 'a' <= char <= 'z':
            return chr((ord(char) - 97 + key) % 26 + 97)
        return char

    return ''.join(encode_single(c, key) for c in text)