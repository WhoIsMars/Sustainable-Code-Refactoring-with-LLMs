def encode(plain_text):
    text = ''.join(chr(219 - ord(ch)) if 'a' <= ch <= 'z' else ch for ch in plain_text.lower() if ch.isalnum())
    return ' '.join(text[i:i + 5] for i in range(0, len(text), 5))


def decode(ciphered_text):
    return ''.join(chr(219 - ord(ch)) if 'a' <= ch <= 'z' else ch for ch in ciphered_text if ch.isalnum())