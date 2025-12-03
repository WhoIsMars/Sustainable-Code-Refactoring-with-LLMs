def rotate(text, key):
    def encode_single(char, key):
        if 'A' <= char <= 'Z':
            return chr(((ord(char) - ord('A') + key) % 26) + ord('A'))
        elif 'a' <= char <= 'z':
            return chr(((ord(char) - ord('a') + key) % 26) + ord('a'))
        else:
            return char

    return ''.join(encode_single(c, key) for c in text)