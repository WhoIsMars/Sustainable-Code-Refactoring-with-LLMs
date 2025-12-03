def rotate(text, key):
    key = key % 26
    if key == 0:
        return text
    
    result = []
    for char in text:
        if 'a' <= char <= 'z':
            result.append(chr((ord(char) - 97 + key) % 26 + 97))
        elif 'A' <= char <= 'Z':
            result.append(chr((ord(char) - 65 + key) % 26 + 65))
        else:
            result.append(char)
    
    return ''.join(result)