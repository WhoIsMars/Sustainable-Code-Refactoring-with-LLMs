NUMBERS = ('', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine')
TENS = ('', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety')
TEENS = ('ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen')

POWERS = ('', ' thousand', ' million', ' billion')

def say(num):
    """say constructs the english phrase for a number between 0 and one trillion"""

    if not (0 <= num < 1E12):
        raise AttributeError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    parts = []
    power_index = 0
    
    while num > 0:
        num, remainder = divmod(num, 1000)
        if remainder == 0:
            power_index += 1
            continue
            
        power_str = say_power(remainder)
        if power_index > 0:
            power_str += POWERS[power_index]
            
        if power_index == 0 and 0 < remainder < 100 and num != 0:
            parts.append('and ' + power_str)
        else:
            parts.append(power_str)
            
        power_index += 1
    
    return ' '.join(reversed(parts))

def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    hundreds = num // 100
    remainder = num % 100
    tens = remainder // 10
    ones = remainder % 10
    
    result = []
    
    if hundreds:
        result.append(NUMBERS[hundreds] + ' hundred')
        if remainder == 0:
            return result[0]
        result.append('and')
    
    if tens == 1:
        result.append(TEENS[ones])
    elif tens > 1:
        if ones:
            result.append(TENS[tens] + '-' + NUMBERS[ones])
        else:
            result.append(TENS[tens])
    elif ones:
        result.append(NUMBERS[ones])
    
    return ' '.join(result)