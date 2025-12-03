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
    power_index = 0
    
    while num > 0:
        num, remainder = divmod(num, 1000)
        if remainder > 0:
            power_str = say_power(remainder)
            if power_index > 0:
                power_str += ' ' + POWERS[power_index]
            parts.append(power_str)
        power_index += 1
    
    if len(parts) > 1 and int(parts[0].split()[0] if parts[0].split()[0].isdigit() else 0) == 0:
        if any(word in parts[0] for word in ('one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine')):
            parts[0] = 'and ' + parts[0]
    
    return ' '.join(reversed(parts))

def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    hundreds = num // 100
    remainder = num % 100
    tens_digit = remainder // 10
    ones_digit = remainder % 10
    
    result = []
    
    if hundreds:
        result.append(NUMBERS[hundreds] + ' hundred')
    
    if remainder:
        if hundreds:
            result.append('and')
        
        if tens_digit == 1:
            result.append(TEENS[ones_digit])
        else:
            if tens_digit > 1:
                if ones_digit:
                    result.append(TENS[tens_digit] + '-' + NUMBERS[ones_digit])
                else:
                    result.append(TENS[tens_digit])
            elif ones_digit:
                result.append(NUMBERS[ones_digit])
    
    return ' '.join(result)