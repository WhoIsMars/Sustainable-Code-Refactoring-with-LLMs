def encode(plain_text):
    text = decode(plain_text.lower())
    return ' '.join(text[i:i + 5] for i in range(0, len(text), 5))


def decode(ciphered_text):
    return ''.join(
        chr(219 - ord(ch)) if ch.islower() and ch.isalnum() else ch
        for ch in ciphered_text
        if ch.isalnum()
    )