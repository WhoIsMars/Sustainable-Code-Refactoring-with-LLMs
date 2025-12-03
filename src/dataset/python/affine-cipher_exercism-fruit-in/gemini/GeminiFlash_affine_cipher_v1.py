def encode(plain_text, a, b):
    if modular_multiplicative_inverse(a, 26) is None:
        raise ValueError(r".+")

    chars = [c for c in plain_text.lower() if 'a' <= c <= 'z' or '0' <= c <= '9']
    encoded_chars = []
    count = 0
    for char in chars:
        if 'a' <= char <= 'z':
            encoded_char = chr((a * (ord(char) - 97) + b) % 26 + 97)
        else:
            encoded_char = char
        encoded_chars.append(encoded_char)
        count += 1
        if count % 5 == 0 and count < len(chars):
            encoded_chars.append(" ")

    return "".join(encoded_chars)


def decode(ciphered_text, a, b):
    n = modular_multiplicative_inverse(a, 26)

    if n is None:
        raise ValueError(r".+")

    chars = [c for c in ciphered_text if 'a' <= c <= 'z' or '0' <= c <= '9']

    decoded_chars = []
    for char in chars:
        if 'a' <= char <= 'z':
            decoded_char = chr((n * (ord(char) - 97 - b)) % 26 + 97)
        else:
            decoded_char = char
        decoded_chars.append(decoded_char)

    return "".join(decoded_chars)


def modular_multiplicative_inverse(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return None