def encode(plain_text):
    text = decode(plain_text.lower())
    return ' '.join(text[i:i + 5] for i in range(0, len(text), 5))


def decode(ciphered_text):
    result = []
    for char in ciphered_text:
        if 'a' <= char <= 'z':
            result.append(chr(219 - ord(char)))
        elif '0' <= char <= '9':
            result.append(char)
    return ''.join(result)