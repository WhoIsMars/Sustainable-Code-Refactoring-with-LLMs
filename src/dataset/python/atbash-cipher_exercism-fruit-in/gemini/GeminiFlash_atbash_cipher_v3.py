import string

def encode(plain_text):
    text = decode(plain_text.lower())
    return ' '.join(text[i:i + 5] for i in range(0, len(text), 5))


def decode(ciphered_text):
    translation_table = {}
    for char in string.ascii_lowercase:
        translation_table[char] = chr(219 - ord(char))

    result = []
    for char in ciphered_text:
        if char.isalnum():
            result.append(translation_table.get(char, char))
    return ''.join(result)