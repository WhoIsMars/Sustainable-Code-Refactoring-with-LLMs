NUMBERS = [''] + 'one two three four five six seven eight nine'.split()
TENS = [''] + 'ten twenty thirty forty fifty sixty seventy eighty ninety'.split()
TEENS = 'ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen'.split()

POWERS = ['', ' thousand', ' million', ' billion']

def say(num):
    """say constructs the english phrase for a number between 0 and one trillion"""

    if not (0 <= num < 1E12):
        raise AttributeError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    parts = []
    for i in range(4):
        num, power = divmod(num, 1000)
        if power:
            parts.append(say_power(power) + POWERS[i])

    return ' '.join(parts[::-1]).strip()


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
    else:
        if tens:
            parts.append(TENS[tens])
        if ones:
            if tens:
                parts.append('-' + NUMBERS[ones])
            else:
                parts.append(NUMBERS[ones])

    return ' '.join(parts)