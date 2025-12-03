def encode(plain_text, a, b):
    if modular_multiplicative_inverse(a, 26) is None:
        raise ValueError(r".+")

    chars = []
    count = 0
    for c in plain_text.lower():
        if c.isalnum():
            if c.islower():
                chars.append(chr((a * (ord(c) - 97) + b) % 26 + 97))
            else:
                chars.append(c)
            count += 1
            if count % 5 == 0:
                chars.append(" ")

    if chars and chars[-1] == " ":
        chars.pop()

    return "".join(chars)


def decode(ciphered_text, a, b):
    n = modular_multiplicative_inverse(a, 26)

    if n is None:
        raise ValueError(r".+")

    return "".join(
        chr(n * ((ord(c) - 97) - b) % 26 + 97) if c.islower() else c
        for c in ciphered_text if c.isalnum()
    )


def modular_multiplicative_inverse(a, m):
    a = a % m
    for n in range(1, m):
        if (a * n) % m == 1:
            return n
    return None