NUMBERS = [''] + 'one two three four five six seven eight nine'.split()
TENS = [''] + 'ten twenty thirty forty fifty sixty seventy eighty ninety'.split()
TEENS = 'ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen'.split()

POWERS = [''] + ' thousand million billion'.split()

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
            part = say_power(power)
            if i > 0:
                part += ' ' + POWERS[i]
            parts.append(part)

    return ' '.join(parts[::-1])


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
            parts.append(NUMBERS[ones])

    return ' '.join(parts) if tens == 1 else '-'.join(parts)