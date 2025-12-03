def encode(plain_text):
    return ' '.join(
        decode(plain_text.lower())[i:i + 5] 
        for i in range(0, len(plain_text), 5)
    )


def decode(ciphered_text):
    return ''.join(
        chr(219 - ord(ch)) if 'a' <= ch <= 'z' else ch 
        for ch in ciphered_text if ch.isalnum()
    )