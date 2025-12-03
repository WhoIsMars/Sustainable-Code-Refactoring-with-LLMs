def rotate(text, key):
    key = key % 26
    result = []
    
    for char in text:
        if 'A' <= char <= 'Z':
            result.append(chr((ord(char) - 65 + key) % 26 + 65))
        elif 'a' <= char <= 'z':
            result.append(chr((ord(char) - 97 + key) % 26 + 97))
        else:
            result.append(char)
    
    return ''.join(result)