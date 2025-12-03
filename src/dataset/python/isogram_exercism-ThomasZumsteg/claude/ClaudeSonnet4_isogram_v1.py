def is_isogram(string):
    seen = set()
    for char in string:
        if char.isalpha():
            lower_char = char.lower()
            if lower_char in seen:
                return False
            seen.add(lower_char)
    return True