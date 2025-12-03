NUMBERS = ('', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine')
TENS = ('', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety')
TEENS = ('ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen')
POWERS = ('', 'thousand', 'million', 'billion')

def say(num):
    """say constructs the english phrase for a number between 0 and one trillion"""
    
    if not (0 <= num < 1000000000000):
        raise AttributeError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    parts = []
    power_idx = 0
    
    while num > 0:
        num, remainder = divmod(num, 1000)
        if remainder > 0:
            power_str = say_power(remainder)
            if power_idx > 0:
                power_str += ' ' + POWERS[power_idx]
            parts.append(power_str)
        power_idx += 1
    
    if len(parts) > 1 and int(parts[0].split()[0] if parts[0].split()[0].isdigit() else 0) == 0:
        if any(c.isdigit() for c in parts[0]) and int(''.join(filter(str.isdigit, parts[0]))) < 100:
            parts[0] = 'and ' + parts[0]
    
    return ' '.join(reversed(parts))

def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    if num == 0:
        return ''
    
    result = []
    
    hundreds = num // 100
    if hundreds:
        result.append(NUMBERS[hundreds] + ' hundred')
    
    remainder = num % 100
    if remainder == 0:
        return ' '.join(result)
    
    if result:
        result.append('and')
    
    if 10 <= remainder <= 19:
        result.append(TEENS[remainder - 10])
    else:
        tens = remainder // 10
        ones = remainder % 10
        
        if tens >= 2:
            if ones:
                result.append(TENS[tens] + '-' + NUMBERS[ones])
            else:
                result.append(TENS[tens])
        elif ones:
            result.append(NUMBERS[ones])
    
    return ' '.join(result)