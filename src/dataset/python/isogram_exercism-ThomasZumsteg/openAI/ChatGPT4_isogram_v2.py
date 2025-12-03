def is_isogram(string):
    seen = set()
    for l in string:
        if l.isalpha():
            lower_l = l.lower()
            if lower_l in seen:
                return False
            seen.add(lower_l)
    return True