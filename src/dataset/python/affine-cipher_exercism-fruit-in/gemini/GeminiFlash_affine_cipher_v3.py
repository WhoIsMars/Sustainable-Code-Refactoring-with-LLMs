def encode(plain_text, a, b):
    if modular_multiplicative_inverse(a, 26) is None:
        raise ValueError(r".+")

    chars = [c for c in plain_text.lower() if c.isalnum()]
    encoded_chars = []

    for char in chars:
        if 'a' <= char <= 'z':
            encoded_chars.append(chr((a * (ord(char) - 97) + b) % 26 + 97))
        else:
            encoded_chars.append(char)

    result = ""
    for i, char in enumerate(encoded_chars):
        result += char
        if (i + 1) % 5 == 0 and i + 1 < len(encoded_chars):
            result += " "

    return result


def decode(ciphered_text, a, b):
    n = modular_multiplicative_inverse(a, 26)

    if n is None:
        raise ValueError(r".+")

    chars = [c for c in ciphered_text if c.isalnum()]
    decoded_chars = []

    for char in chars:
        if 'a' <= char <= 'z':
            decoded_chars.append(chr((n * (ord(char) - 97 - b)) % 26 + 97))
        else:
            decoded_chars.append(char)

    return "".join(decoded_chars)


def modular_multiplicative_inverse(a, m):
    for n in range(1, m):
        if (a * n) % m == 1:
            return n
    return None