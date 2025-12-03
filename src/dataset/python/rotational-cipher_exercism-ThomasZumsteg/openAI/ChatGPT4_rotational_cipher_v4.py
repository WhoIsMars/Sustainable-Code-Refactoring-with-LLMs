def rotate(text, key):
    key = key % 26
    def rot(letter):
        o = ord(letter)
        if 'a' <= letter <= 'z':
            return chr((o - 97 + key) % 26 + 97)
        if 'A' <= letter <= 'Z':
            return chr((o - 65 + key) % 26 + 65)
        return letter
    return ''.join(map(rot, text))