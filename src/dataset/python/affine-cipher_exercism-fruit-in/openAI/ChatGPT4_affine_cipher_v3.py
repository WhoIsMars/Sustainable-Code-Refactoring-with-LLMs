def encode(plain_text, a, b):
    if (n := modular_multiplicative_inverse(a, 26)) is None:
        raise ValueError(r".+")

    chars = []
    for c in plain_text.lower():
        if c.isalnum():
            if c.islower():
                chars.append(chr((a * (ord(c) - 97) + b) % 26 + 97))
            else:
                chars.append(c)

    encoded = "".join(chars)
    return " ".join(encoded[i:i + 5] for i in range(0, len(encoded), 5))


def decode(ciphered_text, a, b):
    if (n := modular_multiplicative_inverse(a, 26)) is None:
        raise ValueError(r".+")

    chars = [
        chr(n * ((ord(c) - 97) - b) % 26 + 97) if c.islower() else c
        for c in ciphered_text if c.isalnum()
    ]

    return "".join(chars)


def modular_multiplicative_inverse(a, m):
    a %= m
    for n in range(1, m):
        if (a * n) % m == 1:
            return n
    return None