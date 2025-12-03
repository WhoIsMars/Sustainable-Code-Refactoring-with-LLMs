def is_isogram(string):
    seen = set()
    for l in string:
        if l.isalpha():
            l = l.lower()
            if l in seen:
                return False
            seen.add(l)
    return True