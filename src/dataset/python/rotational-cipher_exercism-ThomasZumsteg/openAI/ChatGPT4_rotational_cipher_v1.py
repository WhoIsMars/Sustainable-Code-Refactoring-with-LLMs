def rotate(text, key):
    def rot(letter):
        if 'a' <= letter <= 'z':
            return chr((ord(letter) - 97 + key) % 26 + 97)
        if 'A' <= letter <= 'Z':
            return chr((ord(letter) - 65 + key) % 26 + 65)
        return letter
    return ''.join(map(rot, text))