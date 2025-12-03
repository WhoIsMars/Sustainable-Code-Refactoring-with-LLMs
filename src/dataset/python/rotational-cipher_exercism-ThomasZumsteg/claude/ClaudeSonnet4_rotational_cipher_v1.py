def rotate(text, key):
    key = key % 26
    if key == 0:
        return text
    
    result = []
    for letter in text:
        if 'a' <= letter <= 'z':
            result.append(chr((ord(letter) - 97 + key) % 26 + 97))
        elif 'A' <= letter <= 'Z':
            result.append(chr((ord(letter) - 65 + key) % 26 + 65))
        else:
            result.append(letter)
    
    return ''.join(result)