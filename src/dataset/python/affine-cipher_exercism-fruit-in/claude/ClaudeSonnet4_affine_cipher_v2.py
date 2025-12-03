def encode(plain_text, a, b):
    n = modular_multiplicative_inverse(a, 26)
    if n is None:
        raise ValueError(r".+")

    chars = []
    for c in plain_text.lower():
        if c.isalnum():
            if c.islower():
                chars.append(chr((a * (ord(c) - 97) + b) % 26 + 97))
            else:
                chars.append(c)

    result = []
    for i, char in enumerate(chars):
        if i > 0 and i % 5 == 0:
            result.append(" ")
        result.append(char)

    return "".join(result)


def decode(ciphered_text, a, b):
    n = modular_multiplicative_inverse(a, 26)
    if n is None:
        raise ValueError(r".+")

    result = []
    for c in ciphered_text:
        if c.isalnum():
            if c.islower():
                result.append(chr(n * ((ord(c) - 97) - b) % 26 + 97))
            else:
                result.append(c)

    return "".join(result)


def modular_multiplicative_inverse(a, m):
    def extended_gcd(a, b):
        if a == 0:
            return b, 0, 1
        gcd, x1, y1 = extended_gcd(b % a, a)
        x = y1 - (b // a) * x1
        y = x1
        return gcd, x, y

    gcd, x, _ = extended_gcd(a % m, m)
    if gcd != 1:
        return None
    return (x % m + m) % m