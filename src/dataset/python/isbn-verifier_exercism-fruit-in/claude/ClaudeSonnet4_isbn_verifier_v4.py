def is_valid(isbn):
    if len(isbn) != 13:
        return False
    
    checksum = 0
    digit_count = 0
    multiplier = 10
    
    for ch in isbn:
        if ch == '-':
            continue
        elif ch == 'X':
            if digit_count != 9:
                return False
            checksum += 10 * multiplier
        elif ch.isdigit():
            checksum += int(ch) * multiplier
        else:
            return False
        
        digit_count += 1
        if digit_count > 10:
            return False
        multiplier -= 1
    
    return digit_count == 10 and checksum % 11 == 0