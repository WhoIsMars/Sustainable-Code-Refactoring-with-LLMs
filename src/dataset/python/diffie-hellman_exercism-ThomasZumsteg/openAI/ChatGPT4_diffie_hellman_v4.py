from secrets import randbelow

def private_key(p):
    return randbelow(p - 1) + 1

def public_key(p, g, private):
    return pow(g, private, p)

def secret(p, public, private):
    return pow(public, private, p)