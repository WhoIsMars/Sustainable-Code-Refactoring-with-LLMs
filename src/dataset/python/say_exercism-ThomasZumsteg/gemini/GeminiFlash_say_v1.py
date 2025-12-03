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

    parts = []
    power_index = 0
    while num > 0:
        num, power = divmod(num, 1000)
        if power > 0:
            part = say_power(power)
            if power_index > 0:
                part += POWERS[power_index]
            parts.append(part)
        power_index += 1

    return ' '.join(parts[::-1])


def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    hundreds = num // 100
    tens = (num % 100) // 10
    ones = num % 10

    parts = []
    if hundreds > 0:
        parts.append(NUMBERS[hundreds] + ' hundred')
        if tens > 0 or ones > 0:
            parts.append('and')

    if tens == 1:
        parts.append(TEENS[ones])
    elif tens > 1:
        parts.append(TENS[tens])
        if ones > 0:
            parts.append('-' + NUMBERS[ones])
    elif ones > 0:
        parts.append(NUMBERS[ones])

    return ' '.join(parts)