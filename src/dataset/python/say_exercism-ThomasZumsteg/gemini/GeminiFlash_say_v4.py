NUMBERS = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
TENS = ['', 'ten', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']
TEENS = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
POWERS = ['', ' thousand', ' million', ' billion']


def say(num):
    """say constructs the english phrase for a number between 0 and one trillion"""

    if not (0 <= num < 1E12):
        raise AttributeError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    result = []
    power_index = 0
    while num > 0:
        num, chunk = divmod(num, 1000)
        if chunk != 0:
            chunk_str = say_power(chunk)
            power_str = POWERS[power_index]
            if power_index > 0:
                chunk_str += power_str
            result.append(chunk_str)
        power_index += 1

    return ' '.join(result[::-1])


def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    hundreds = num // 100
    tens = (num % 100) // 10
    ones = num % 10

    parts = []

    if hundreds:
        parts.append(NUMBERS[hundreds] + ' hundred')
        if tens or ones:
            parts.append('and')

    if tens == 1:
        parts.append(TEENS[ones])
    elif tens:
        parts.append(TENS[tens])
        if ones:
            parts.append('-' + NUMBERS[ones])
    elif ones:
        parts.append(NUMBERS[ones])

    return ' '.join(parts)